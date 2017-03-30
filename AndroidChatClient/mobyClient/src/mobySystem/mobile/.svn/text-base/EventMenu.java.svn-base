package mobySystem.mobile;
import android.util.Log;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import mobySystem.mobile.R;
import mobySystem.mobile.R.id;
import mobySystem.mobile.R.layout;
import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;



public class EventMenu extends Activity{
	private long first,second,third,fourth,mainmi;
	private String firstName,secondName,thirdName,fourthName,proname;
	private long projectID;
	private int numberOfEvents=0;
	private int currentIndex=0;
	Cursor event;
	TextView proName;
	Button eventButton1,eventButton2,eventButton3,eventButton4;
	
public void onCreate(Bundle savedInstanceState) {
    	
 	    super.onCreate(savedInstanceState);
 	    // 	    DBAdapter.addUsers();
 	    	Bundle bundle = this.getIntent().getExtras();
 	    	
 	    	projectID = bundle.getLong("name");
 	    	mainmi = bundle.getLong("projevent");
 	    	
 	    	DBAdapter.open();
 	    	setContentView(R.layout.events);
 	    	if (mainmi==1){
 	    		event = DBAdapter.getProject(projectID);
 	    	proname = event.getString(1);
	    	proName = (TextView) findViewById(R.id.projname);
     	proName.setText(proname);}
 	    	else{
 	    		event = DBAdapter.getUser(projectID);
 	    		proname = event.getString(1) + " " + event.getString(2);
 		    	proName = (TextView) findViewById(R.id.projname);
 	     	proName.setText(proname);
 	    	}
 	    	
	    	//GET PROJECT FROM DATABASE.	
	    	
 	    	if (mainmi==1)
 	    		event = DBAdapter.getProjectEvents(projectID);
 	    	else // events is clicked on main menu, not from projects menu
 	    		event = DBAdapter.getUserEvents(projectID); // here projectID is used as userName
	    	
 	    	event.move(currentIndex); 	    	
	    	
	 //   	event.move(currentIndex);
	
	    	numberOfEvents=event.getCount();
	    	DBAdapter.close();
			   

		   	eventButton1 = (Button)findViewById(R.id.first);

			eventButton2 = (Button)findViewById(R.id.second);

			eventButton3 = (Button)findViewById(R.id.third);
			
			eventButton4 = (Button)findViewById(R.id.fourth);
			
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
		            	openEvents();
		            }
		            Log.v("Moby","Hop");
		        }

				});//Up.
			
			Button downButton = (Button)findViewById(R.id.down);
			
			downButton.setOnClickListener(new View.OnClickListener(){ 
				public void onClick(View v)
				{
		            if (currentIndex+4<numberOfEvents){
		            	currentIndex+=4;
		            	openEvents();
		            }
		            Log.v("Moby","Hop");
		        }

				});//Down.
 	    	
 	    	openEvents();
 	}
	
	
	public void openEvents() 
	   {
		
			Log.v("Moby", "Current Index:"+currentIndex+" "+ numberOfEvents);
	    	DBAdapter.open();
	    	
	    	if (numberOfEvents-currentIndex>0){
	    		event.moveToPosition(currentIndex);
	    		first=event.getLong(0);
	    		Log.v("Moby","First:"+first);
	    		Cursor firstEvent = DBAdapter.getEvent(first);
	    		firstName=firstEvent.getString(1);
	    	}
	    	
	    	if (numberOfEvents-currentIndex>1){
	    		event.moveToNext();
	    		
	    		second=event.getLong(0);
	    		Log.v("Moby","Second:"+second);
	    		Cursor secondEvent = DBAdapter.getEvent(second);
	    		secondName=secondEvent.getString(1);
	    		
	    	}
	    	
	    	if (numberOfEvents-currentIndex>2){	
	    		event.moveToNext();
	    		
	    		third=event.getLong(0);
	    		Log.v("Moby","Third:"+third);
	    		Cursor thirdEvent = DBAdapter.getEvent(third);
	    		thirdName=thirdEvent.getString(1);

	    	}
	    	
	    	if (numberOfEvents-currentIndex>3){
	    		event.moveToNext();
	    		fourth=event.getLong(0);
	    		Log.v("Moby","Fourth:"+fourth);
	    		Cursor fourthEvent = DBAdapter.getEvent(fourth);
	    		fourthName=fourthEvent.getString(1);
	    		
	    	}
	    	
	    	DBAdapter.close();
		
		
		
		
		//Set up the event buttons.
		if (numberOfEvents-currentIndex>0){
	   	
	   	eventButton1.setVisibility(0);
	   		
	   	
	   	eventButton1.setText(firstName);
		eventButton1.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				Bundle bundle=new Bundle();
				
				bundle.putLong("eventid", first);
				bundle.putLong("projid", projectID);
				bundle.putLong("projemi", mainmi);
				
				Intent newIntent = new Intent(v.getContext(), Event.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
				
			}
			});
		} else{
			Log.v("Moby", "Make Invisible:"+1);
    	
			
//	   	eventButton1 = (Button)findViewById(R.id.first);
		   	
		   	eventButton1.setVisibility(4);
		}
		
		if (numberOfEvents-currentIndex>1){		
	   	eventButton2.setVisibility(0);
	   		
	   	
		eventButton2.setText(secondName);
		eventButton2.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{  
				Bundle bundle=new Bundle();
				
				bundle.putLong("eventid", second);
				bundle.putLong("projid", projectID);
				bundle.putLong("projemi", mainmi);
				
				Intent newIntent = new Intent(v.getContext(), Event.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			}
			});
		}
		else{
			Log.v("Moby", "Make Invisible:"+2);
	//	   	eventButton2 = (Button)findViewById(R.id.second);
		   	
		   	eventButton2.setVisibility(4);
		}
		if (numberOfEvents-currentIndex>2){

	   		eventButton3.setVisibility(0);
	   		
	   	
		eventButton3.setText(thirdName);
		
		eventButton3.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				Bundle bundle=new Bundle();
				
				bundle.putLong("eventid", third);
				bundle.putLong("projid", projectID);
				bundle.putLong("projemi", mainmi);
				
				Intent newIntent = new Intent(v.getContext(), Event.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			}
			});
		
		}
		else{
			Log.v("Moby", "Make Invisible:"+3);
//		   	eventButton3 = (Button)findViewById(R.id.third);
		   	
		   	eventButton3.setVisibility(4);
		}		
		if (numberOfEvents-currentIndex>3){


	   	eventButton4.setVisibility(0);
	   		
	   	
		eventButton4.setText(fourthName);
		eventButton4.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{  
				Bundle bundle=new Bundle();
				
				bundle.putLong("eventid", fourth);
				bundle.putLong("projid", projectID);
				bundle.putLong("projemi", mainmi);
				
				Intent newIntent = new Intent(v.getContext(), Event.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
	//			eventButton4.();
			}
			});
		}
		else{
			Log.v("Moby", "Make Invisible:"+4);
//		  	eventButton4 = (Button)findViewById(R.id.fourth);
		   	
		   	eventButton4.setVisibility(4);
		}
		
		Button exitButton = (Button)findViewById(R.id.exit);
		exitButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				quitApp();
			}
			});
	   }

	private void quitApp() {
		this.finish();
	}
	
	
	
}