package mobySystem.mobile;

import java.io.IOException;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.View;
import android.widget.*;

public class Event extends Activity{
	
  public long getEventid() {
		return eventid;
	}
	public void setEventid(long eventid) {
		this.eventid = eventid;
	}
	public String getEventname() {
		return eventname;
	}
	public void setEventname(String eventname) {
		this.eventname = eventname;
	}
	public String getEventdate() {
		return eventdate;
	}
	public void setEventdate(String eventdate) {
		this.eventdate = eventdate;
	}
	public String getEventaddress() {
		return eventaddress;
	}
	public void setEventaddress(String eventaddress) {
		this.eventaddress = eventaddress;
	}
private long eventid;
  private String eventname;
  private String eventdate;
  private String eventaddress;
  private String projname;
  private long projid, mainmi;
  Cursor event;
  TextView proName;
  
  public void onCreate(Bundle savedInstanceState) {
  	
	    super.onCreate(savedInstanceState);
	    // 	    DBAdapter.addUsers();
	    	Bundle bundle = this.getIntent().getExtras();
	    	
	    	eventid=bundle.getLong("eventid");
	    	projid = bundle.getLong("projid");
	    	mainmi = bundle.getLong("projemi");
	    	
	    	DBAdapter.open();
	    	//GET EVENT FROM DATABASE.
	    	setContentView(R.layout.event);
	    	
	    	if (mainmi==1) {
 	    	event = DBAdapter.getProject(projid);
 	    	projname = event.getString(1);
 	    	proName = (TextView) findViewById(R.id.projname);
 	    	proName.setText(projname);}
	    	else {
	    		event = DBAdapter.getUser(projid);
	 	    	projname = event.getString(1) + " " + event.getString(2);
	 	    	proName = (TextView) findViewById(R.id.projname);
	 	    	proName.setText(projname);
	    	}
 	    	
	    	event = DBAdapter.getEvent(eventid);
	    	
	    	DBAdapter.close();
	    	
	    	eventname = event.getString(1);
			eventdate = event.getString(2);
			eventaddress = event.getString(3);
			
	    	openEventPage();
	}
private void openEventPage() {
		
		
		
		Button backButton = (Button) findViewById(R.id.back);
		backButton.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				Intent intent = new Intent();
				setResult(RESULT_OK,intent);
				finish();
				
			}
		});
		
		
	//	ImageView profilePicture = (ImageView) findViewById(R.id.profilePicture);
//		profilePicture.setImageDrawable(Drawable.createFromPath(getResources().getAssets().open("profilePictures/"+username+".png")));
		//TODO > Dynamic Image setting to a profile
		
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
				
				bundle.putLong("name", eventid);
				
				Intent newIntent = new Intent(v.getContext(), EventPeopleMenu.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			}
		});
		
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
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

