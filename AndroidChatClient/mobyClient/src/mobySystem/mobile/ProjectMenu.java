/**
 * 
 */
package mobySystem.mobile;

import mobySystem.mobile.R;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.app.Activity;
import android.os.Bundle;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;

import java.util.*;
import android.widget.*;
import android.text.Editable;
import android.view.*;
import android.media.*;
/**
 * @author rusi
 *
 */


public class ProjectMenu extends Activity {
	Project first = new Project(),second = new Project(),third = new Project(),fourth = new Project();
 	int count = 0;
 	long user;
 	private int currentIndex=0;
 	
 	public void onCreate(Bundle savedInstanceState) {
    	
 	    super.onCreate(savedInstanceState);
 	   Bundle bundle = this.getIntent().getExtras();
    	
    	user = bundle.getLong("user");
 	    
 	    // 	    DBAdapter.addUsers();
 	    
 	    	openProjectMenu();
 	}
 	
 	
 	private void openProjectMenu(){
 		
 	try{
	DBAdapter.open();
//	Cursor projects=db.getAllProjects();
//	count=projects.getCount();
	
	Cursor projects=DBAdapter.getAllProjects();
	
	int numRows=projects.getCount();
	
//	for(int i=0;i<numRows;++i){
		projects.moveToPosition(currentIndex);	//UP and DOWN buttons change the value of currentIndex.
		
		if (numRows>currentIndex){
			first.setProjectID(projects.getLong(0));
			first.setProjectName(projects.getString(1));
			first.setStartdate(projects.getString(2));
			first.setDeadline(projects.getString(3));
			projects.moveToNext();
		}
		if (numRows>currentIndex+1){
			second.setProjectID(projects.getLong(0));
			second.setProjectName(projects.getString(1));
			second.setStartdate(projects.getString(2));
			second.setDeadline(projects.getString(3));
			projects.moveToNext();
		}
		if (numRows>currentIndex+2){
			third.setProjectID(projects.getLong(0));
			third.setProjectName(projects.getString(1));
			third.setStartdate(projects.getString(2));
			third.setDeadline(projects.getString(3));
			projects.moveToNext();
		}
		if (numRows>currentIndex+3){
			fourth.setProjectID(projects.getLong(0));
			fourth.setProjectName(projects.getString(1));
			fourth.setStartdate(projects.getString(2));
			fourth.setDeadline(projects.getString(3));	
		}
		
//	}
	DBAdapter.close();
	
	// 	projects.moveToFirst();
	// 	first.initialize(projects.getLong(0), projects.getString(1), projects.getString(2), projects.getString(3));
	// 	second.initialize(projects.getLong(4), projects.getString(5), projects.getString(6), projects.getString(7));
	// 	third.initialize(projects.getLong(8), projects.getString(9), projects.getString(10), projects.getString(11));
	//	fourth.initialize(projects.getLong(12), projects.getString(13), projects.getString(14), projects.getString(15));
		
}

catch(Exception s){
	s.printStackTrace();
//	HttpDownload.moveToMainMenu();
}

//	 db.open();
//	 Cursor projects = db.getAllProjects();
 
//	 db.close();

// System.out.println(projects.getCount());
 /*
 if ( projects.moveToFirst()){

	 long projectID;
	
	 projectID=projects.getLong(1);
	 projectID=projects.getLong(5);
	
	
	
}
*/
 	setContentView(R.layout.clickprojects);
 	TextView User = (TextView)findViewById(R.id.user);
	DBAdapter.open();
	Cursor c = DBAdapter.getUser(user);
	DBAdapter.close();
	User.setText(c.getString(1) + " " + c.getString(2));
 
	Button projectsButton = (Button)findViewById(R.id.projects);
	
	projectsButton.setOnClickListener(new View.OnClickListener(){ 

		public void onClick(View v)
	{ 
            Intent intent = new Intent();
            setResult(RESULT_OK, intent);
            finish();
	}
	});

	Button projectsButton1 = (Button)findViewById(R.id.first);
	
	projectsButton1.setText(first.getProjectName());

	projectsButton1.setOnClickListener(new View.OnClickListener(){ 
	public void onClick(View v)
	{	
		Bundle bundle=new Bundle();
		
		bundle.putLong("name", first.getProjectID());
		
		Intent newIntent = new Intent(v.getContext(), Project.class);
		
		newIntent.putExtras(bundle);
		
		startActivityForResult(newIntent, 0);
		getLost();
			
	}
	});
	
	Button projectsButton2 = (Button)findViewById(R.id.second);
	projectsButton2.setText(second.getProjectName());
	
	projectsButton2.setOnClickListener(new View.OnClickListener(){ 
	public void onClick(View v)
	{   		
		Bundle bundle=new Bundle();
		bundle.putLong("name", second.getProjectID());
	
		Intent newIntent = new Intent(v.getContext(), Project.class);
	
		newIntent.putExtras(bundle);
	
		startActivityForResult(newIntent, 0);
		getLost();
		
	}
	});
	

Button projectsButton3 = (Button)findViewById(R.id.third);
	projectsButton3.setText(third.getProjectName());
projectsButton3.setOnClickListener(new View.OnClickListener(){ 
	public void onClick(View v)
	{   
		Bundle bundle=new Bundle();
		bundle.putLong("name", third.getProjectID());
	
		Intent newIntent = new Intent(v.getContext(), Project.class);
	
		newIntent.putExtras(bundle);
	
		startActivityForResult(newIntent, 0);
		getLost();
	}
	});

Button projectsButton4 = (Button)findViewById(R.id.fourth);
	projectsButton4.setText(fourth.getProjectName());
	projectsButton4.setOnClickListener(new View.OnClickListener(){ 
	public void onClick(View v)
	{  
		Bundle bundle=new Bundle();
		bundle.putLong("name", fourth.getProjectID());
	
		Intent newIntent = new Intent(v.getContext(), Project.class);
	
		newIntent.putExtras(bundle);
	
		startActivityForResult(newIntent, 0);
		getLost();
		
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
 	public void getLost(){
 		RadioGroup group = (RadioGroup)findViewById(R.id.group);
    	group.setVisibility(4);
    	Button button = (Button)findViewById(R.id.first);
    	button.setVisibility(4);
    	Button button2 = (Button)findViewById(R.id.second);
    	button2.setVisibility(4);
    	Button button3 = (Button)findViewById(R.id.third);
    	button3.setVisibility(4);
    	Button button4 = (Button)findViewById(R.id.fourth);
    	button4.setVisibility(4);
 	}
 	
 	protected void onActivityResult(int a, int result, Intent data)
	{

		if (result==10){
			 Intent intent = new Intent();
		           setResult(10, intent);	// 11 signals exit.
		           finish();		
		}
		else if(result==11){
			Intent intent = new Intent();
			setResult(11, intent);
			finish();
			
		}
	}
 	private void quitApp() {
		// TODO Auto-generated method stub
		this.finish();
	}
	
}
