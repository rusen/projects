package mobySystem.mobile;

import java.io.IOException;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.View;
import android.widget.*;

public class Notification extends Activity{

private long notid, id, etkinlikid;
  private String tur, nottext, nottype, eventname,eventaddress,eventdate;
  Cursor not,event;
  TextView proName;
  
  public void onCreate(Bundle savedInstanceState) {
  	
	    super.onCreate(savedInstanceState);
	    // 	    DBAdapter.addUsers();
	    	Bundle bundle = this.getIntent().getExtras();
	    	
	    	notid=bundle.getLong("notid");
	    	tur = bundle.getString("tur");
	    	id = bundle.getLong("id");
	    	DBAdapter.open();
	    	//GET not FROM DATABASE.
	    	setContentView(R.layout.event);
	    	if (tur.equals("event"))
	    	{
	    		event = DBAdapter.getEvent(id);
	    		eventname = event.getString(1);
				eventdate = event.getString(2);
				eventaddress = event.getString(3);
	    	}
 	    	
	    	not = DBAdapter.getNotification(notid);
	    	
	    	DBAdapter.close();
	    	
	    	notid = not.getLong(0);
	    	nottype = not.getString(1);
			nottext = not.getString(2);
			
	    	opennotPage();
	}
private void opennotPage() {
		
		
		
		Button backButton = (Button) findViewById(R.id.back);
		backButton.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				Intent intent = new Intent();
				setResult(RESULT_OK,intent);
				finish();
				
			}
		});
		
		TextView eventnameField = (TextView) findViewById(R.id.eventname);
		eventnameField.setText("\t"+eventname);
		TextView eventdateField = (TextView) findViewById(R.id.eventdate);
		eventdateField.setText("\t"+eventdate);
		TextView eventaddressField = (TextView) findViewById(R.id.eventaddress);
		eventaddressField.setText("\t"+eventaddress);
		
		Button participantsButton = (Button) findViewById(R.id.participants);
		participantsButton.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				Bundle bundle = new Bundle();
				
				bundle.putLong("name", id);
				
				Intent newIntent = new Intent(v.getContext(), EventPeopleMenu.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			}
		});
		
		TextView notnameField = (TextView) findViewById(R.id.noti);
		notnameField.setText("\t"+nottext);
		

		
		Button exitButton = (Button) findViewById(R.id.exit);
		exitButton.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				quitApp();
			}


		});
	}
		void quitApp(){
			this.finish();
		}
 	
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

