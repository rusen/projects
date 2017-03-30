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



public class NotificationMenu extends Activity{
	private long first,second,third,fourth,mainmi;
	private String firstName,secondName,thirdName,fourthName,proname,firstText,secondText,thirdText,fourthText;
	private String firstal,secondal,thirdal,fourthal;
	private long firstalid,secondalid,thirdalid,fourthalid;
	private long userID;
	private int numberOfnots=0;
	private int currentIndex=0;
	Cursor not;
	TextView proName;
	Button notButton1,notButton2,notButton3,notButton4;
	
public void onCreate(Bundle savedInstanceState) {
    	
 	    super.onCreate(savedInstanceState);
 	    // 	    DBAdapter.addUsers();
 	    	Bundle bundle = this.getIntent().getExtras();
 	    	
 	    	userID = bundle.getLong("name");
 	    	
 	    	DBAdapter.open();
 	    	setContentView(R.layout.events);
 	    	not = DBAdapter.getUser(userID);
	    		proname = not.getString(1) + " " + not.getString(2);
		    	proName = (TextView) findViewById(R.id.projname);
	     	proName.setText(proname);
 	    	
	    	not = DBAdapter.getAllHasNotifications(userID);
 	    	not.move(currentIndex); 	    	
	    	
	 //   	not.move(currentIndex);
	
	    	numberOfnots=not.getCount();
	    	DBAdapter.close();
			   

		   	notButton1 = (Button)findViewById(R.id.first);

			notButton2 = (Button)findViewById(R.id.second);

			notButton3 = (Button)findViewById(R.id.third);
			
			notButton4 = (Button)findViewById(R.id.fourth);
			
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
		            	opennots();
		            }
		            Log.v("Moby","Hop");
		        }

				});//Up.
			
			Button downButton = (Button)findViewById(R.id.down);
			
			downButton.setOnClickListener(new View.OnClickListener(){ 
				public void onClick(View v)
				{
		            if (currentIndex+4<numberOfnots){
		            	currentIndex+=4;
		            	opennots();
		            }
		            Log.v("Moby","Hop");
		        }

				});//Down.
 	    	
 	    	opennots();
 	}
	
	
	public void opennots() 
	   {
		
			Log.v("Moby", "Current Index:"+currentIndex+" "+ numberOfnots);
	    	DBAdapter.open();
	    	
	    	if (numberOfnots-currentIndex>0){
	    		not.moveToPosition(currentIndex);
	    		first=not.getLong(0);
	    		Log.v("Moby","First:"+first);
	    		Cursor firstnot = DBAdapter.getNotification(first);
	    		firstName=firstnot.getString(1);
	    		firstal=firstnot.getString(3);
	    		firstText=firstnot.getString(2) + firstal;
	    		firstalid = firstnot.getLong(4);
	    	}
	    	
	    	if (numberOfnots-currentIndex>1){
	    		not.moveToNext();
	    		
	    		second=not.getLong(0);
	    		Log.v("Moby","Second:"+second);
	    		Cursor secondnot = DBAdapter.getNotification(second);
	    		secondName=secondnot.getString(1);
	    		secondal = secondnot.getString(3);
	    		secondText=secondnot.getString(2) + secondal;
	    		secondalid = secondnot.getLong(4);
	    	}
	    	
	    	if (numberOfnots-currentIndex>2){	
	    		not.moveToNext();
	    		
	    		third=not.getLong(0);
	    		Log.v("Moby","Third:"+third);
	    		Cursor thirdnot = DBAdapter.getNotification(third);
	    		thirdName=thirdnot.getString(1);
	    		thirdal = thirdnot.getString(3);
	    		thirdText=thirdnot.getString(2) + thirdal;
	    		thirdalid = thirdnot.getLong(4);
	    	}
	    	
	    	if (numberOfnots-currentIndex>3){
	    		not.moveToNext();
	    		fourth=not.getLong(0);
	    		Log.v("Moby","Fourth:"+fourth);
	    		Cursor fourthnot = DBAdapter.getNotification(fourth);
	    		fourthName=fourthnot.getString(1);
	    		fourthal = fourthnot.getString(3);
	    		fourthText=fourthnot.getString(2) + fourthal;
	    		fourthalid = fourthnot.getLong(4);
	    	}
	    	
	    	DBAdapter.close();
		
		
		
		
		//Set up the not buttons.
		if (numberOfnots-currentIndex>0){
	   	
	   	notButton1.setVisibility(0);
	   		
	   	
	   	notButton1.setText(firstName + ": " + firstal);
		notButton1.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				Bundle bundle=new Bundle();
				
				bundle.putLong("notid", first);
				if (firstName.equals("New Event") || firstName.equals("Removal"))
					bundle.putString("tur","event");
				else
					bundle.putString("tur","proje");
				bundle.putLong("id",firstalid);
				
				
				Intent newIntent = new Intent(v.getContext(), Notification.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
				
			}
			});
		} else{
			Log.v("Moby", "Make Invisible:"+1);
    	
			
//	   	notButton1 = (Button)findViewById(R.id.first);
		   	
		   	notButton1.setVisibility(4);
		}
		
		if (numberOfnots-currentIndex>1){		
	   	notButton2.setVisibility(0);
	   		
	   	
		notButton2.setText(secondName + ": " + secondal);
		notButton2.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{  
				Bundle bundle=new Bundle();
				
				bundle.putLong("notid", second);
				if (secondName.equals("New Event") || secondName.equals( "Removal"))
					bundle.putString("tur","event");
				else
					bundle.putString("tur","proje");
				bundle.putLong("id",secondalid);
				
				Intent newIntent = new Intent(v.getContext(), Notification.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			}
			});
		}
		else{
			Log.v("Moby", "Make Invisible:"+2);
	//	   	notButton2 = (Button)findViewById(R.id.second);
		   	
		   	notButton2.setVisibility(4);
		}
		if (numberOfnots-currentIndex>2){

	   		notButton3.setVisibility(0);
	   		
	   	
		notButton3.setText(thirdName + ": " + thirdal);
		
		notButton3.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				Bundle bundle=new Bundle();
				
				bundle.putLong("notid", third);
				if (thirdName.equals("New Event") || thirdName.equals( "Removal"))
					bundle.putString("tur","event");
				else
					bundle.putString("tur","proje");
				bundle.putLong("id",thirdalid);
				
				Intent newIntent = new Intent(v.getContext(), Notification.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			}
			});
		
		}
		else{
			Log.v("Moby", "Make Invisible:"+3);
//		   	notButton3 = (Button)findViewById(R.id.third);
		   	
		   	notButton3.setVisibility(4);
		}		
		if (numberOfnots-currentIndex>3){


	   	notButton4.setVisibility(0);
	   		
	   	
		notButton4.setText(fourthName + ": " + fourthal);
		notButton4.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{  
				Bundle bundle=new Bundle();
				
				bundle.putLong("notid", fourth);
				if (fourthName.equals("New Event") || fourthName.equals( "Removal"))
					bundle.putString("tur","event");
				else
					bundle.putString("tur","proje");
				bundle.putLong("id",fourthalid);
				
				Intent newIntent = new Intent(v.getContext(), Notification.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
	//			notButton4.();
			}
			});
		}
		else{
			Log.v("Moby", "Make Invisible:"+4);
//		  	notButton4 = (Button)findViewById(R.id.fourth);
		   	
		   	notButton4.setVisibility(4);
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