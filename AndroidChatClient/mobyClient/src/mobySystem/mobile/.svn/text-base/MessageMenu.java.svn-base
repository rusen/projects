package mobySystem.mobile;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.TextView;

public class MessageMenu extends Activity {
	private long username=MobySystem.userID;
	
	private long messageIDs[] = null;
	private String preview[] = null;
	private String message[] = null;
	
	private int currentIndex=0,numberOfMessages;
	
	private long sender[] =null;
	
	private String senderName[]=null; 
	private String time[]=null;
	private boolean messageUnread[]=null;
	
	protected void onActivityResult(int a, int result, Intent data)
	{
		if (result==10){
			
			Log.v("Moby", "Message received by message menu, quitting");
			getMessageFromDB();
			openMessagePage();
			
		}
		else if (result==11){
		
			Intent intent = new Intent();
		    setResult(11, intent);	// 11 signals exit.
		    finish();
		}
	}
	
	
	public void onCreate(Bundle savedInstanceState) {
		  	
	    super.onCreate(savedInstanceState);
		    // 	    DBAdapter.addUsers();
		    	
	    Log.v("Moby", "username:" + username);

	    
	    getMessageFromDB();
	    openMessagePage();

	}
	
	private void getMessageFromDB(){

		DBAdapter.open();
		
		//GET PERSON FROM DATABASE.
		
		Cursor messages = DBAdapter.getMessages(username);

		messages.moveToFirst();			
		
		numberOfMessages = messages.getCount();

		Log.v("Moby", "numberOfMessages:" + numberOfMessages);	    

		messageIDs=new long[numberOfMessages];
		preview=new String[numberOfMessages];
		message=new String[numberOfMessages];
		time=new String[numberOfMessages];
		sender=new long[numberOfMessages];
		senderName=new String[numberOfMessages];
		messageUnread=new boolean[numberOfMessages];
		
		int counter=0;  
		
		while(numberOfMessages>0&&!messages.isAfterLast()){

			messageIDs[counter]=messages.getLong(0);
	
//   		Log.v("Moby", "MESSAGE number:" + counter);		    	
					
			Cursor temp = DBAdapter.getPersonalMessage(messageIDs[counter]);
	
			preview[counter] = new String();
			message[counter] = new String();
			senderName[counter]=new String();	
			time[counter]=new String();
			sender[counter]=0;		
			
			preview[counter] = temp.getString(0);
			message[counter] = preview[counter];
			
			sender[counter] = temp.getLong(1);
			
			if (temp.getInt(2)==1)	messageUnread[counter]=true;
			else messageUnread[counter]=false;
			
			time[counter] = temp.getString(3);
			Cursor user = DBAdapter.getUserName(sender[counter]);				
			
			if (preview[counter].length()>9)	preview[counter]=preview[counter].substring(0, 8);
			preview[counter] += ".. by " + user.getString(0)+ " " + user.getString(1);
				
			senderName[counter]=user.getString(0)+" "+user.getString(1); 
			
			Log.v("message", message[counter]);		
			
			//    	Log.v("Moby", "MESSAGE PREVIEW:" + preview[counter]);
	
			counter++;
	
			messages.moveToNext();	
		
		}	

		DBAdapter.close();
	
	}
	
	
	private void openMessagePage() {

		setContentView(R.layout.messages);
		
			
		Log.v("Moby", "number:"+numberOfMessages);
		
		
		if(numberOfMessages-currentIndex>0){
			
			Log.v("Moby", "number:"+numberOfMessages);
			
			CheckBox first = (CheckBox) findViewById(R.id.first);
			
			first.setVisibility(0);
		
			if (messageUnread[numberOfMessages-currentIndex-1])	{
				first.setTextSize(13);
				first.setTextColor(Color.RED);
			}
			else {
				first.setTextSize(13);
				first.setTextColor(Color.BLACK);
			}
		
			first.setText(preview[numberOfMessages-currentIndex-1]);
		
			first.setOnCheckedChangeListener(new OnCheckedChangeListener() {
		
				public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
					if (isChecked)
					{									
						
						DBAdapter.open();
						CheckBox first = (CheckBox) findViewById(R.id.first);
						DBAdapter.markRead(messageIDs[numberOfMessages-currentIndex-1]);
						first.setChecked(false);
						DBAdapter.close();
						
						Bundle bundle=new Bundle();

						bundle.putLong("messageID", messageIDs[numberOfMessages-currentIndex-1]);
						
						bundle.putBoolean("newMessage", false);
						
						bundle.putBoolean("isReply", false);
						
						bundle.putString("time", time[numberOfMessages-currentIndex-1]);
						
						bundle.putLong("sender", sender[numberOfMessages-currentIndex-1]);
						
						bundle.putString("text", message[numberOfMessages-currentIndex-1]);

						bundle.putString("senderName", senderName[numberOfMessages-currentIndex-1]);
						
						Intent newIntent = new Intent(buttonView.getContext(), Message.class);
						
						newIntent.putExtras(bundle);
						
						startActivityForResult(newIntent, 0);
						
						
					
					}
				}
			});
		}
		else {
			CheckBox first = (CheckBox) findViewById(R.id.first);					
			first.setVisibility(4);
		}
	
		if(numberOfMessages-currentIndex>1){			
			
			CheckBox second = (CheckBox) findViewById(R.id.second);
			
			second.setVisibility(0);
			
			if (messageUnread[numberOfMessages-currentIndex-2])	{
				second.setTextSize(13);
				second.setTextColor(Color.RED);
				
			}
			else {
				second.setTextSize(13);
				second.setTextColor(Color.BLACK);
			}
			
			second.setText(preview[numberOfMessages-currentIndex-2]);
		
			second.setOnCheckedChangeListener(new OnCheckedChangeListener() {
		
				public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
					if (isChecked)
					{	
						DBAdapter.open();
						CheckBox second = (CheckBox) findViewById(R.id.second);
						DBAdapter.markRead(messageIDs[numberOfMessages-currentIndex-2]);
						second.setChecked(false);
						DBAdapter.close();
						
						Bundle bundle=new Bundle();

						bundle.putLong("messageID", messageIDs[numberOfMessages-currentIndex-2]);
						
						bundle.putBoolean("newMessage", false);
						
						bundle.putBoolean("isReply", false);

						bundle.putString("time", time[numberOfMessages-currentIndex-2]);
						bundle.putLong("sender", sender[numberOfMessages-currentIndex-2]);
						
						bundle.putString("text", message[numberOfMessages-currentIndex-2]);
						
						bundle.putString("senderName", senderName[numberOfMessages-currentIndex-2]);
						
						Intent newIntent = new Intent(buttonView.getContext(), Message.class);
						
						newIntent.putExtras(bundle);
						
						startActivityForResult(newIntent, 0);
					}
				}
			});	
		}
		else{
			CheckBox second = (CheckBox) findViewById(R.id.second);
			second.setVisibility(4);		
		}
		
		if(numberOfMessages-currentIndex>2){
			CheckBox third = (CheckBox) findViewById(R.id.third);
			third.setVisibility(0);
			
			if (messageUnread[numberOfMessages-currentIndex-3])	{
				third.setTextSize(13);
				third.setTextColor(Color.RED);
				
			}
			else {
				third.setTextSize(13);
				third.setTextColor(Color.BLACK);
			}
			third.setText(preview[numberOfMessages-currentIndex-3]);
		
			third.setOnCheckedChangeListener(new OnCheckedChangeListener() {
		
				public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
					if (isChecked)
					{	
						DBAdapter.open();
						CheckBox third = (CheckBox) findViewById(R.id.third);
						DBAdapter.markRead(messageIDs[numberOfMessages-currentIndex-3]);
						third.setChecked(false);
						DBAdapter.close();
						
						Bundle bundle=new Bundle();

						bundle.putBoolean("newMessage", false);
						
						bundle.putLong("messageID", messageIDs[numberOfMessages-currentIndex-3]);
						
						bundle.putBoolean("isReply", false);
						
						bundle.putLong("sender", sender[numberOfMessages-currentIndex-3]);
						bundle.putString("time", time[numberOfMessages-currentIndex-3]);
						
						bundle.putString("text", message[numberOfMessages-currentIndex-3]);
						
						bundle.putString("senderName", senderName[numberOfMessages-currentIndex-3]);
						
						Intent newIntent = new Intent(buttonView.getContext(), Message.class);
						
						newIntent.putExtras(bundle);
						
						startActivityForResult(newIntent, 0);
					
					}
				}
			});	
		}
		else{
			CheckBox third = (CheckBox) findViewById(R.id.third);
			third.setVisibility(4);
		}
		if(numberOfMessages-currentIndex>3){
			
			
			CheckBox fourth = (CheckBox) findViewById(R.id.fourth);
			fourth.setVisibility(0);
			
			if (messageUnread[numberOfMessages-currentIndex-4])	{
				fourth.setTextSize(13);
				fourth.setTextColor(Color.RED);
				
			}
			else {
				fourth.setTextSize(13);
				fourth.setTextColor(Color.BLACK);
			}
			
			fourth.setText(preview[numberOfMessages-currentIndex-4]);
		
			fourth.setOnCheckedChangeListener(new OnCheckedChangeListener() {
		
				public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
					if (isChecked)
					{	
						DBAdapter.open();
						CheckBox fourth = (CheckBox) findViewById(R.id.fourth);
						DBAdapter.markRead(messageIDs[numberOfMessages-currentIndex-4]);
						fourth.setChecked(false);
						DBAdapter.close();
						
						Bundle bundle=new Bundle();
						
						bundle.putBoolean("newMessage", false);
						
						bundle.putLong("messageID", messageIDs[numberOfMessages-currentIndex-4]);

						bundle.putString("time", time[numberOfMessages-currentIndex-4]);
						bundle.putBoolean("isReply", false);
						
						bundle.putLong("sender", sender[numberOfMessages-currentIndex-4]);
						
						bundle.putString("text", message[numberOfMessages-currentIndex-4]);
						
						bundle.putString("senderName", senderName[numberOfMessages-currentIndex-4]);
						
						Intent newIntent = new Intent(buttonView.getContext(), Message.class);
						
						newIntent.putExtras(bundle);
						
						startActivityForResult(newIntent, 0);
					}
				}
			});	
		}
		
		else{
			CheckBox fourth = (CheckBox) findViewById(R.id.fourth);
			fourth.setVisibility(4);				
		}
	
		
	
			if (numberOfMessages<1){
				TextView txt = (TextView) findViewById(R.id.noMessages);
				txt.setVisibility(0);
				Button upButton = (Button)findViewById(R.id.up);
				upButton.setVisibility(4);
				Button downButton = (Button)findViewById(R.id.down);
				downButton.setVisibility(4);
				
			}
			
			else {
				TextView txt = (TextView) findViewById(R.id.noMessages);
				txt.setVisibility(4);
			}
		Button backButton = (Button)findViewById(R.id.back);
		backButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
	            Intent intent = new Intent();
	            setResult(RESULT_OK, intent);
	            finish();
			}

			});//Back.
		
		Button upButton = (Button)findViewById(R.id.up);
		upButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
	            if (currentIndex>3)	{
	            	currentIndex-=4;
	            	openMessagePage();
	            }
	        }
					
			});//Up.
		
		Button downButton = (Button)findViewById(R.id.down);
		
		downButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
	            if (currentIndex+4<numberOfMessages){
	            	currentIndex+=4;
	            	openMessagePage();
	            }
	            
	        }

			});//Down.
		
		Button exitButton = (Button)findViewById(R.id.exit);
		exitButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
		
				Intent intent = new Intent();
				setResult(11, intent);
				finish();
						
		
			}

			});//Exit.
		
		Button newMessageButton = (Button)findViewById(R.id.newMessage);
		newMessageButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
			
				Bundle bundle=new Bundle();
				
				bundle.putBoolean("newMessage", true);
				
				Intent newIntent = new Intent(v.getContext(), Message.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
				
			}

			});//Exit.
		
		
			
	}
	
	
	
	
	
	
	
	
}
