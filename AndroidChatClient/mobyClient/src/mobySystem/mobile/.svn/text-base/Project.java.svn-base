package mobySystem.mobile;

import mobySystem.mobile.R;
import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Project extends Activity{
	private long projectID;
	private String projectName;
	private String startdate;
	private String deadline;
	
	public void onCreate(Bundle savedInstanceState) {
    	
 	    super.onCreate(savedInstanceState);
 	    // 	    DBAdapter.addUsers();
 	    Bundle bundle = this.getIntent().getExtras();
 	    	
 	    projectID=bundle.getLong("name");
 	    	
 	    DBAdapter.open();
 	    //GET PROJECT FROM DATABASE.
 	    	
 	   	Cursor project = DBAdapter.getProject(projectID);
 	    	
 	   	DBAdapter.close();
		projectName = project.getString(1);
		startdate = project.getString(2);
		deadline = project.getString(3);

 	    openProjectPage();
}
	
	public void initialize(long pid,String name,String start,String dead){
		projectID=pid;
		projectName=name;
		startdate=start;
		deadline=dead;
	}
	
	public long getProjectID() {
		return projectID;
	}
	public void setProjectID(long projectID) {
		this.projectID = projectID;
	}
	public String getProjectName() {
		return projectName;
	}
	public void setProjectName(String projectName) {
		this.projectName = projectName;
	}
	public String getStartdate() {
		return startdate;
	}
	public void setStartdate(String startdate) {
		this.startdate = startdate;
	}
	public String getDeadline() {
		return deadline;
	}
	public void setDeadline(String deadline) {
		this.deadline = deadline;
	}

	public void openProjectPage() {
		
		setContentView(R.layout.project);
		
		Button exitButton = (Button) findViewById(R.id.exit);
		exitButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				quitApp();
				
			}
			
			});
		
		Button peopleButton = (Button) findViewById(R.id.people);
		peopleButton.setOnClickListener(new View.OnClickListener(){ 
			

			
			public void onClick(View v)
			{ 
				// OPEN PEOPLE
				Bundle bundle = new Bundle();
				
				bundle.putLong("name", projectID);
				
				Intent newIntent = new Intent(v.getContext(), PeopleMenu.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
				
			}
			
			});

		Button eventButton = (Button) findViewById(R.id.events);
		eventButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				// OPEN EVENTS
				Bundle bundle = new Bundle();
				
				bundle.putLong("name", projectID);
				bundle.putLong("projevent", 1);
				
				Intent newIntent = new Intent(v.getContext(), EventMenu.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
				
			}
			
			});
		
		Button documentButton = (Button) findViewById(R.id.documents);
		documentButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				// OPEN documents
				
			}
			
			});
		
		Button backButton = (Button) findViewById(R.id.back);
		backButton.setOnClickListener(new View.OnClickListener(){ 
			public void onClick(View v)
			{ 
				 Intent intent = new Intent();
		           setResult(10, intent);	// 10 signals back.
		           finish();
	            
				// go back
				
			}
			
			});
		
		TextView name= (TextView) findViewById(R.id.name);
		name.setText(projectName);
		
	}
		void quitApp(){
			 Intent intent = new Intent();
	         setResult(11, intent);	// 11 signals exit.
	         finish();
		//FINISH THE GAME
		}		
				
		protected void onActivityResult(int a, int result, Intent data)
		{
			if (result==11){
				 Intent intent = new Intent();
		           setResult(11, intent);	// 11 signals back.
		           finish();
			}
		}
		
		
		
		
		
	
	
	
}
