package mobySystem.mobile;

import java.util.StringTokenizer;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;

public class Message extends Activity {
	
	private long sender;	
	private String senderName=new String();
	private String text=new String();
	private String time=new String();
	private boolean isNewMessage = false;
	private boolean isReply = false;
	private long messageID;
	
	public void onCreate(Bundle savedInstanceState) {
	  	
	    super.onCreate(savedInstanceState);
		    // 	    DBAdapter.addUsers();
		    	
	  Bundle bundle = this.getIntent().getExtras();
	  
	  isNewMessage=bundle.getBoolean("newMessage");
	  
	  sender=bundle.getLong("sender");
	  text= bundle.getString("text");
	  senderName=bundle.getString("senderName");
	  isReply=bundle.getBoolean("isReply");
	  messageID=bundle.getLong("messageID");
	  time = bundle.getString("time");
	  showMessage();

	}
	

	private void showMessage() {

		
		if (!isNewMessage){

			setContentView(R.layout.textmessage);
		
			TextView messageBody = (TextView) findViewById(R.id.text);
			messageBody.setText(text);
			//Body written.
			TextView t = (TextView) findViewById(R.id.time);
			t.setText(time);
			TextView senderNameField = (TextView)	findViewById(R.id.sender);
			senderNameField.setText(senderName);
			//Sender specified.
			
			Button replyButton = (Button)findViewById(R.id.reply);
			replyButton.setOnClickListener(new View.OnClickListener(){ 
				public void onClick(View v)
				{
				
					Bundle bundle=new Bundle();

					bundle.putBoolean("newMessage", true);
					
					bundle.putString("senderName", senderName);
					
					bundle.putBoolean("isReply", true);
					
					Intent newIntent = new Intent(v.getContext(), Message.class);
					
					newIntent.putExtras(bundle);
					
					startActivityForResult(newIntent, 0);
					
				}

				});//Back.
			
			Button deleteButton = (Button)findViewById(R.id.delete);
			deleteButton.setOnClickListener(new View.OnClickListener(){ 
				
				public void onClick(View v)
				{
					DBAdapter.open();
					
					DBAdapter.deletePersonalMessage(messageID);
					
					DBAdapter.close();					
					
		            Intent intent = new Intent();
		            
		            setResult(10, intent);	
		            		            
		            finish();
		            
		            }
				});//Back.	
		
		}
		else{
			sendMessage();
			
		}
		
		Button backButton = (Button)findViewById(R.id.back);
		backButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
	            Intent intent = new Intent();
	            
	            if (isReply)	setResult(12, intent);	// 12 signals back.
	            
	            else setResult(10,intent);	// 10 signals reply.
	            
	            finish();
			}

			});//Back.
		
		
		
		Button exitButton = (Button)findViewById(R.id.exit);
		exitButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
	            Intent intent = new Intent();
	            setResult(11, intent);	// 11 signals exit.
	            finish();
			}

			});//Back.
		
	}
	private void sendMessage(){
		setContentView(R.layout.newmessage);		
		
		EditText receiverName=(EditText) findViewById(R.id.receiverName);
		
		if (isReply)	receiverName.setText(senderName);
		
		Button sendButton = (Button)findViewById(R.id.send);
		sendButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
				EditText messageArea=(EditText) findViewById(R.id.text);
				String messageBody = messageArea.getText().toString();
				
				EditText receiver=(EditText) findViewById(R.id.receiverName);
				String receiverName = receiver.getText().toString();

				StringTokenizer parser=new StringTokenizer(receiverName);
				String firstName=parser.nextToken();
				String surname=new String();
				
				while(true){
					surname=parser.nextToken();
					if (!parser.hasMoreTokens()) break;
					else firstName+=" "+surname;						
				}
				DBAdapter.open();
				Cursor recUser = DBAdapter.getUserByName("'"+firstName+"'","'"+surname+"'");
				
				long recUserID=-1;
				long messageID=-1;
				
				if (recUser!=null){
					recUserID = recUser.getLong(0);
					messageID = DBAdapter.insertPersonalMessage(messageBody,MobySystem.userID,recUserID);
					
					
				}
				else {
					sendMessage();
				}
				
				if (messageID==-1)
				{
					sendMessage();
					//TODO message was not sent, try again.	
				}
				else {
					Intent intent = new Intent();
			        if(isReply){
			        	setResult(12, intent);	// 12 signals back from reply.
			        }
			        else setResult(10,intent);
			        finish();
					
					
					//TODO message sent successfully.
					
				}
				DBAdapter.close();
				
			}
			});//Back.	
		}
	
	protected void onActivityResult(int a, int result, Intent data)
	{
		if(result==11){
			Intent intent = new Intent();
			setResult(11, intent);
			finish();
			
		}
		else if (result==12){
			Intent intent =  new Intent();
			setResult(10,intent);
			finish();
			
		}
	}
	
}
