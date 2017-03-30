package mobySystem.mobile;
import java.util.StringTokenizer;

import android.util.Log;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import mobySystem.mobile.R;
import mobySystem.mobile.R.id;
import mobySystem.mobile.R.layout;
import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;



public class EventPeopleMenu extends Activity{
	private long first,second,third,fourth;
	private String firstName,secondName,thirdName,fourthName,eventName,firstJob,secondJob,thirdJob,fourthJob;
	private long eventID;
	private int numberOfPeople=0;
	private int currentIndex=0;
	Cursor people;
	private String preview[] = null;
	TextView eventname;
	TextView personJob1,personJob2,personJob3,personJob4;
	Button personButton1,personButton2,personButton3,personButton4;
	
	
	
public void onCreate(Bundle savedInstanceState) {
    	
 	    super.onCreate(savedInstanceState);
 	    // 	    DBAdapter.addUsers();
 	    	Bundle bundle = this.getIntent().getExtras();
 	    	
 	    	eventID=bundle.getLong("name");
 	    	
 	    	setContentView(R.layout.people);
 	    	
 	    	DBAdapter.open();
	    	
	    	//GET PROJECT FROM DATABASE.	
 	    	
	    	people = DBAdapter.getEvent(eventID);
	    	
	    	eventName = people.getString(1);
	    	
	    	eventname = (TextView) findViewById(R.id.eventname);
		   	eventname.setVisibility(0);
	   		
			eventname.setText(eventName);
	    	
	    	people = DBAdapter.getEventPeople(eventID);
	    	
	    	people.move(currentIndex); 	    	
	    	
	 //   	people.move(currentIndex);
	
	    	numberOfPeople=people.getCount();
	    	
	    	DBAdapter.close();
 	    	

	    	
			   

		   	personButton1 = (Button)findViewById(R.id.first);

			personButton2 = (Button)findViewById(R.id.second);

			personButton3 = (Button)findViewById(R.id.third);
			
			personButton4 = (Button)findViewById(R.id.fourth);
			
			personJob1 = (TextView) findViewById(R.id.firstjob);
			personJob2 = (TextView) findViewById(R.id.secondjob);
			personJob3 = (TextView) findViewById(R.id.thirdjob);
			personJob4 = (TextView) findViewById(R.id.fourthjob);
			
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
		            	openPeople();
		            }
		            Log.v("Moby","Hop");
		        }

				});//Up.
			
			Button downButton = (Button)findViewById(R.id.down);
			
			downButton.setOnClickListener(new View.OnClickListener(){ 
				public void onClick(View v)
				{
		            if (currentIndex+4<numberOfPeople){
		            	currentIndex+=4;
		            	openPeople();
		            }
		            Log.v("Moby","Hop");
		        }

				});//Down.
 	    	
 	    	openPeople();
 	}

protected void onActivityResult(int a, int result, Intent data)
{
	if (result==10)
		openPeople();
}

	
	
	public void openPeople() 
	   {
		setContentView(R.layout.people);
    	
    	eventname = (TextView) findViewById(R.id.eventname); //R.id.eventname is used as project name here
    	eventname.setVisibility(0);
   		
    	eventname.setText(eventName);

	   	personButton1 = (Button)findViewById(R.id.first);

		personButton2 = (Button)findViewById(R.id.second);

		personButton3 = (Button)findViewById(R.id.third);
		
		personButton4 = (Button)findViewById(R.id.fourth);
		
		personJob1 = (TextView) findViewById(R.id.firstjob);
		personJob2 = (TextView) findViewById(R.id.secondjob);
		personJob3 = (TextView) findViewById(R.id.thirdjob);
		personJob4 = (TextView) findViewById(R.id.fourthjob);
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
	            	openPeople();
	            }
	            Log.v("Moby","Hop");
	        }

			});//Up.
		
		Button downButton = (Button)findViewById(R.id.down);
		
		downButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
	            if (currentIndex+4<numberOfPeople){
	            	currentIndex+=4;
	            	openPeople();
	            }
	            Log.v("Moby","Hop");
	        }

			});//Down.
			Log.v("Moby", "Current Index:"+currentIndex+" "+ numberOfPeople);
	    	DBAdapter.open();
people = DBAdapter.getEventPeople(eventID);
	    	
	    	people.move(currentIndex); 	    	
	    	
	 //   	people.move(currentIndex);
	    	numberOfPeople=people.getCount();
	    	
	    	if (numberOfPeople-currentIndex>0){
	    		people.moveToPosition(currentIndex);
	    		first=people.getLong(0);
	    		Log.v("Moby","First:"+first);
	    		Cursor firstPerson = DBAdapter.getUser(first);
	    		firstName=firstPerson.getString(1)+" "+firstPerson.getString(2);
	    		firstJob = firstPerson.getString(6);
	    		personJob1.setText(firstJob);
	    	}
	    	
	    	if (numberOfPeople-currentIndex>1){
	    		people.moveToNext();
	    		
	    		second=people.getLong(0);
	    		Log.v("Moby","Second:"+second);
	    		Cursor secondPerson = DBAdapter.getUser(second);
	    		secondName=secondPerson.getString(1)+" "+secondPerson.getString(2);
	    		secondJob = secondPerson.getString(6);
	    		personJob2.setText(secondJob);
	    	}
	    	
	    	if (numberOfPeople-currentIndex>2){	
	    		people.moveToNext();
	    		
	    		third=people.getLong(0);
	    		Log.v("Moby","Third:"+third);
	    		Cursor thirdPerson = DBAdapter.getUser(third);
	    		thirdName=thirdPerson.getString(1)+" "+thirdPerson.getString(2);
	    		thirdJob = thirdPerson.getString(6);
	    		personJob3.setText(thirdJob);
	    	}
	    	
	    	if (numberOfPeople-currentIndex>3){
	    		people.moveToNext();
	    		fourth=people.getLong(0);
	    		Log.v("Moby","Fourth:"+fourth);
	    		Cursor fourthPerson = DBAdapter.getUser(fourth);
	    		fourthName=fourthPerson.getString(1)+" "+fourthPerson.getString(2);
	    		fourthJob = fourthPerson.getString(6);
	    		personJob4.setText(fourthJob);
	    	}
	    	
	    	DBAdapter.close();
		
		
		
		
		//Set up the person buttons.
		if (numberOfPeople-currentIndex>0){
	   	
			personButton1.setVisibility(0);
		   	personJob1.setVisibility(0);
	   		
	   	
	   	personButton1.setText(firstName);
		personButton1.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				Bundle bundle=new Bundle();
				
				bundle.putLong("username", first);
				bundle.putLong("projectmi", 0);
				bundle.putLong("eventid", eventID);
				
				Intent newIntent = new Intent(v.getContext(), Person.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
				
			}
			});
		} else{
			Log.v("Moby", "Make Invisible:"+1);
    	
			
//	   	personButton1 = (Button)findViewById(R.id.first);
		   	
		   	personButton1.setVisibility(4);
		   	personJob1.setVisibility(4);
		}
		
		if (numberOfPeople-currentIndex>1){		
	   	personButton2.setVisibility(0);
	   	personJob2.setVisibility(0);
	   	
		personButton2.setText(secondName);
		personButton2.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{  
				Bundle bundle=new Bundle();
				
				bundle.putLong("username", second);
				bundle.putLong("projectmi", 0);
				bundle.putLong("eventid", eventID);
				
				Intent newIntent = new Intent(v.getContext(), Person.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			}
			});
		}
		else{
			Log.v("Moby", "Make Invisible:"+2);
	//	   	personButton2 = (Button)findViewById(R.id.second);
		   	
		   	personButton2.setVisibility(4);
			personJob2.setVisibility(4);
		}
		if (numberOfPeople-currentIndex>2){

	   		personButton3.setVisibility(0);
	   		personJob3.setVisibility(0);	
	   	
		personButton3.setText(thirdName);
		
		personButton3.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				Bundle bundle=new Bundle();
				
				bundle.putLong("username", third);
				bundle.putLong("projectmi", 0);
				bundle.putLong("eventid", eventID);
				
				Intent newIntent = new Intent(v.getContext(), Person.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			}
			});
		
		}
		else{
			Log.v("Moby", "Make Invisible:"+3);
//		   	personButton3 = (Button)findViewById(R.id.third);
		   	
		   	personButton3.setVisibility(4);	//4 for buttons.
		   	personJob3.setVisibility(4);
		}		
		if (numberOfPeople-currentIndex>3){


	   	personButton4.setVisibility(0);
	   	personJob4.setVisibility(0);
	   	
		personButton4.setText(fourthName);
		personButton4.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{  
				Bundle bundle=new Bundle();
				
				bundle.putLong("username", fourth);
				bundle.putLong("projectmi", 0);
				bundle.putLong("eventid", eventID);
				
				Intent newIntent = new Intent(v.getContext(), Person.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
	//			personButton4.();
			}
			});
		}
		else{
			Log.v("Moby", "Make Invisible:"+4);
//		  	personButton4 = (Button)findViewById(R.id.fourth);
		   	
		   	personButton4.setVisibility(4);
		   	personJob4.setVisibility(4);
		}
		EditText x = (EditText)findViewById(R.id.userName);
		Button addUserButton = (Button)findViewById(R.id.adduser);
		if (MobySystem.isAdmin==true)
		{
			addUserButton.setVisibility(0);
			x.setVisibility(0);
		}
		else
		{
			addUserButton.setVisibility(4);
			x.setVisibility(4);
		}
			
		addUserButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{
				DBAdapter.open();
				preview=new String[3];
				preview[0] = new String();
				preview[1] = new String();
		  //  	preview[2] = new String();
				
				String eklenen=((EditText)findViewById(R.id.userName)).getText().toString();
				
				StringTokenizer parser=new StringTokenizer(eklenen);
				String name=parser.nextToken();
				String surname=new String();
				
				while(true){
					surname=parser.nextToken();
					if (!parser.hasMoreTokens()) break;
					else name+=" "+surname;						
				}
				
				
				Cursor user = DBAdapter.getUserByName("'"+name+"'","'"+surname+"'");
				DBAdapter.addUserToEvent(eventID,user.getLong(0));
				DBAdapter.close();
				openPeople();
			}
			});
		
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
