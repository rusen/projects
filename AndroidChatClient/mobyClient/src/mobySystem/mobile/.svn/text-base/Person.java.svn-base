package mobySystem.mobile;

import java.io.IOException;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.*;

public class Person extends Activity{
  public long getUsername() {
		return username;
	}
	public void setUsername(long username) {
		this.username = username;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getSurname() {
		return surname;
	}
	public void setSurname(String surname) {
		this.surname = surname;
	}
	public String getPhone() {
		return phone;
	}
	public void setPhone(String phone) {
		this.phone = phone;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public String getPosition() {
		return position;
	}
	public void setPosition(String position) {
		this.position = position;
	}
	
	private long projemi;
	private long projectid,eventid;
  private long username;
  private String name;
  private String surname;
  private String email;
  private String phone;
  private String position; 
  
  public void onCreate(Bundle savedInstanceState) {
  	
	    super.onCreate(savedInstanceState);
	    // 	    DBAdapter.addUsers();
	    	Bundle bundle = this.getIntent().getExtras();
	    	
	    	username=bundle.getLong("username");
	    	projectid=bundle.getLong("projectid");
	    	projemi=bundle.getLong("projectmi");
	    	eventid=bundle.getLong("eventid");
			
	    	
	    	Log.v("BUNUNLA CAGIRDIK:",""+ username);
	    	
	    	DBAdapter.open();
	    	//GET PERSON FROM DATABASE.	
	    	Cursor person = DBAdapter.getUser(username);
	    	
	    	DBAdapter.close();
	    	
			name = person.getString(1);
			surname = person.getString(2);
			email = person.getString(4);
			phone = person.getString(5);
			position = person.getString(6);
			
	    	openPersonPage();
	}
private void openPersonPage() {
		setContentView(R.layout.person);
		Button backButton = (Button) findViewById(R.id.back);
		backButton.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				Intent intent = new Intent();
				setResult(RESULT_OK,intent);
				finish();
			}
		});
		
		
		ImageView profilePicture = (ImageView) findViewById(R.id.profilePicture);
//		profilePicture.setImageDrawable(Drawable.createFromPath(getResources().getAssets().open("profilePictures/"+username+".png")));
		//TODO > Dynamic Image setting to a profile
		
		TextView nameField = (TextView) findViewById(R.id.name);
		nameField.setText("\t"+name);
		TextView surnameField = (TextView) findViewById(R.id.surname);
		surnameField.setText("\t"+surname);
		TextView positionField = (TextView) findViewById(R.id.position);
		positionField.setText("\t"+position);
		TextView phoneField = (TextView) findViewById(R.id.phone);
		phoneField.setText("\t"+phone);
		TextView emailField = (TextView) findViewById(R.id.email);
		emailField.setText("\t"+email);
		
		Button removeButton = (Button) findViewById(R.id.removeuser);
		if (MobySystem.isAdmin==true)
			removeButton.setVisibility(0);
		else
			removeButton.setVisibility(4);
		removeButton.setOnClickListener(new View.OnClickListener() {
			
			public void onClick(View v) {
				DBAdapter.open();
				if (projemi==1)
					DBAdapter.removeUserFromProject(username,projectid);
				else if (projemi==0)
					DBAdapter.removeUserFromEvent(username,eventid);
				DBAdapter.close();
				Intent intent = new Intent();
				setResult(10,intent);
				finish();
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
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

