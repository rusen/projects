package mobySystem.mobile;

import android.app.Activity;
import android.os.Bundle;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import android.content.Intent;


import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import mobySystem.mobile.DBAdapter;
import mobySystem.mobile.R;

import org.w3c.dom.Document;
import org.w3c.dom.Element; 
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import android.app.Activity;
import android.database.Cursor;
import android.database.SQLException;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.SystemClock;
import java.util.*;
import android.widget.*;
import android.text.Editable;
import android.util.Log;
import android.view.*;
import android.media.*;

public class MobySystem extends Activity {
	public static long userID;
	public static boolean isAdmin;
	int projectno=0;
	int hangisi = 0;
	String date1 = "";
	String date2 = "";
//The database handler for database queries, adding and more.
	DBAdapter db=new DBAdapter(this);

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	
    super.onCreate(savedInstanceState);
    
    Log.v("Moby", "Proje:"+hangisi);
    
    DBAdapter.addUsers();
    	
    	popLoginMenu();
    }
    
    
    	//LET US LOG ON TO THE SYTEM.
    	private void popLoginMenu(){
    		
    	
        setContentView(R.layout.main);
        
        //setContentView(R.layout.letter);
        
        /* try {
        InputStream a = OpenHttpConnection("http://144.122.238.239");
        }
        catch(Exception ex){
        	System.err.println("seks"); 
        }*/
        
        Button loginButton = (Button)findViewById(R.id.widget45);
        loginButton.setOnClickListener(new View.OnClickListener(){ 
        	
        	public void onClick(View v)
        	
        	{  
        		long userName=-1;
        		try{
        			userName = Long.parseLong(((EditText)findViewById(R.id.userName)).getText().toString());
        		}
        		catch(NumberFormatException n){
        			popLoginMenu();
        			
        		}
        		
        		Cursor c = null;
        		
        		try{
        			
        			DBAdapter.open();
        			c=DBAdapter.getUser(userName);
        			
        			DBAdapter.close();
        			String passwd=((EditText)findViewById(R.id.password)).getText().toString();
        			
	            	if (c!=null){
	            		
	            		if (c.getString(3).equals(passwd)){
	            			userID=userName;
	            			moveToMainMenu();
	            		}	            		
	            		else popLoginMenu();
	            		}
            		else popLoginMenu();
        		
        		}
        		
        		catch(Exception s){
        		//	s.printStackTrace();
        		popLoginMenu();
        		}
        		
        		DBAdapter.close();
	
        		
        	}
        	});
        
        Button exitButton = (Button)findViewById(R.id.widget51);
        exitButton.setOnClickListener(new View.OnClickListener(){ 
        	public void onClick(View v)
        	{   quitApp();  }
        	});
        
     /*   Date date = new Date();
        String str = date.toGMTString();
        String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/proposal.txt");
        TextView txt = (TextView) findViewById(R.id.text);
        txt.setText(satr + ":" + str);*/
    }   
   /*
   private void openMeetingKodak()
   {
	   setContentView(R.layout.meetingkodak);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectKodak();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openMeetingWarSim()
   {
	   setContentView(R.layout.meetingwarsim);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectWarSim();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openMeetingVestel()
   {
	   setContentView(R.layout.meetingvestel);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectVestel();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openMeetingVivident()
   {
	   setContentView(R.layout.meetingvivident);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectVivident();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openScheduleKodak()
   {
	   setContentView(R.layout.schedulekodak);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectKodak();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openScheduleWarSim()
   {
	   setContentView(R.layout.schedulewarsim);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectWarSim();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openScheduleVestel()
   {
	   setContentView(R.layout.schedulevestel);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectVestel();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openScheduleVivident()
   {
	   setContentView(R.layout.schedulevivident);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectVivident();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openEventWarSim()
   {
	   setContentView(R.layout.eventwarsim);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectWarSim();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openEventKodak()
   {
	   setContentView(R.layout.eventkodak);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectKodak();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openEventVestel()
   {
	   setContentView(R.layout.eventvestel);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectVestel();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   private void openEventVivident()
   {
	   setContentView(R.layout.eventvivident);
		Button backButton = (Button)findViewById(R.id.widget29);
       	backButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   openProjectVivident();  }
       		});
       	Button exitButton = (Button)findViewById(R.id.widget51);
       	exitButton.setOnClickListener(new View.OnClickListener(){ 
       		public void onClick(View v)
       		{   quitApp();  }
       		});
   }
   */
   private void popMessagesMenu()
   {
	   setContentView(R.layout.clickmessages);
   	Button messagesButton = (Button)findViewById(R.id.messages);	// Go back.
	messagesButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   moveToMainMenu();  }
		});
   	Button projectsButton = (Button)findViewById(R.id.projects);
	projectsButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{ 	ProjectMenu project=new ProjectMenu();
		}
		});
	Button documentsButton = (Button)findViewById(R.id.documents);
	documentsButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   popDocumentsMenu();  }
		});
   	Button personalmessagesButton = (Button)findViewById(R.id.messages);
	personalmessagesButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   openPersonalMessages();  }
		});
   	Button notificationsButton = (Button)findViewById(R.id.notifications);
   	notificationsButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   openNotifications();  }
		});
	Button exitButton = (Button)findViewById(R.id.exit);
	exitButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   quitApp();  }
		});
   }
   
   private void openNotifications()
   {
	   setContentView(R.layout.notifications);
      	Button mButton = (Button)findViewById(R.id.widget29);
    	mButton.setOnClickListener(new View.OnClickListener(){
    		public void onClick(View v)
    		{   
    			moveToMainMenu();  }
    		});
    	Button exitButton = (Button)findViewById(R.id.widget51);
    	exitButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{
    			quitApp();  }
    		});
   }
   
   private void openTextMessage()
   {
	   setContentView(R.layout.textmessage);
      	Button mButton = (Button)findViewById(R.id.widget29);
    	mButton.setOnClickListener(new View.OnClickListener(){
    		public void onClick(View v)
    		{   
    			openPersonalMessages();  }
    		});
    	Button exitButton = (Button)findViewById(R.id.widget51);
    	exitButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{
    			quitApp();  }
    		});
   }
   
   private void openVoiceMessage()
   {
	   setContentView(R.layout.voicemessage);
	   MediaPlayer mp = MediaPlayer.create(this, R.raw.mesaj);
	   mp.start();
      	Button mButton = (Button)findViewById(R.id.widget29);
    	mButton.setOnClickListener(new View.OnClickListener(){
    		public void onClick(View v)
    		{   
    			openPersonalMessages();  }
    		});
    	Button exitButton = (Button)findViewById(R.id.widget51);
    	exitButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{
    			quitApp();  }
    		});
   }
   
   private void openPersonalMessages()
   {
	   setContentView(R.layout.personalmessages);
   	Button mButton = (Button)findViewById(R.id.widget29);
	mButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   moveToMainMenu();  }
		});
   	Button voiceMessage = (Button)findViewById(R.id.widget46);
	voiceMessage.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   openVoiceMessage();  }
		});
   	Button textMessage = (Button)findViewById(R.id.widget47);
	textMessage.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   openTextMessage();  }
		});
	Button exitButton = (Button)findViewById(R.id.widget51);
	exitButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   quitApp();  }
		});
   }
 
   private void openRecentDocuments()
   {
	   setContentView(R.layout.recentdocuments);
  	Button mButton = (Button)findViewById(R.id.widget29);
	mButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   moveToMainMenu();  }
		});
	RadioButton txtt = (RadioButton) findViewById(R.id.widget46);
	txtt.setVisibility(View.INVISIBLE);
	RadioButton txtt2 = (RadioButton) findViewById(R.id.widget47);
	txtt2.setVisibility(View.INVISIBLE);
	if (hangisi != 0)
	{
		if (hangisi == 1)
		{
			if (date2=="")
			{
				RadioButton txt = (RadioButton) findViewById(R.id.widget46);
				txt.setText("Moby Proposal\n"+date1);
				txt.setVisibility(View.VISIBLE);
				txt.setOnClickListener(new View.OnClickListener() {
					public void onClick(View v)
					{   
					setContentView(R.layout.letter);
					String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/proposal.txt");
					TextView txt = (TextView) findViewById(R.id.text);
			        txt.setText(satr);
			        Date date = new Date();
			        date1 = date.toGMTString();
			        Button exitButton = (Button)findViewById(R.id.widget51);
			    	exitButton.setOnClickListener(new View.OnClickListener(){ 
			    		public void onClick(View v)
			    		{   openRecentDocuments();  }
			    		});}
					});
				RadioButton txt2 = (RadioButton) findViewById(R.id.widget47);
				txt2.setVisibility(View.INVISIBLE);
			}
			else
			{
				RadioButton txt2 = (RadioButton) findViewById(R.id.widget46);
				txt2.setText("Moby Proposal\n"+date1);
				txt2.setVisibility(View.VISIBLE);
				txt2.setOnClickListener(new View.OnClickListener() {
				public void onClick(View v)
				{   
				setContentView(R.layout.letter);
				String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/proposal.txt");
				TextView txt = (TextView) findViewById(R.id.text);
		        txt.setText(satr);
		        Date date = new Date();
		        date1 = date.toGMTString();
		        Button exitButton = (Button)findViewById(R.id.widget51);
		    	exitButton.setOnClickListener(new View.OnClickListener(){ 
		    		public void onClick(View v)
		    		{   openRecentDocuments();  }
		    		});}
				});
				RadioButton txt = (RadioButton) findViewById(R.id.widget47);
				txt.setText("Reference Letter by Rusen AKTAS\n"+date2);
				txt.setVisibility(View.VISIBLE);
				txt.setOnClickListener(new View.OnClickListener() {
					public void onClick(View v)
					{   
					setContentView(R.layout.letter);
					String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/ref.txt");
					TextView txt = (TextView) findViewById(R.id.text);
			        txt.setText(satr);
			        Date date = new Date();
			        date2 = date.toGMTString();
			        Button exitButton = (Button)findViewById(R.id.widget51);
			    	exitButton.setOnClickListener(new View.OnClickListener(){ 
			    		public void onClick(View v)
			    		{   openRecentDocuments();  }
			    		});}
					});
			}
		}
		else if (hangisi == 2)
		{
			if (date1=="")
			{
				RadioButton txt = (RadioButton) findViewById(R.id.widget46);
				txt.setText("Reference Letter by Rusen AKTAS\n"+date2);
				txt.setVisibility(View.VISIBLE);
				txt.setOnClickListener(new View.OnClickListener() {
					public void onClick(View v)
					{   
					setContentView(R.layout.letter);
					String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/ref.txt");
					TextView txt = (TextView) findViewById(R.id.text);
			        txt.setText(satr);
			        Date date = new Date();
			        date2 = date.toGMTString();
			        Button exitButton = (Button)findViewById(R.id.widget51);
			    	exitButton.setOnClickListener(new View.OnClickListener(){ 
			    		public void onClick(View v)
			    		{   openRecentDocuments();  }
			    		});}
					});
				RadioButton txt2 = (RadioButton) findViewById(R.id.widget47);
				txt2.setVisibility(View.INVISIBLE);
			}
			else
			{
				RadioButton txt2 = (RadioButton) findViewById(R.id.widget46);
				txt2.setText("Reference Letter by Rusen AKTAS\n"+date2);
				txt2.setVisibility(View.VISIBLE);
				txt2.setOnClickListener(new View.OnClickListener() {
					public void onClick(View v)
					{   
					setContentView(R.layout.letter);
					String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/ref.txt");
					TextView txt = (TextView) findViewById(R.id.text);
			        txt.setText(satr);
			        Date date = new Date();
			        date2 = date.toGMTString();
			        Button exitButton = (Button)findViewById(R.id.widget51);
			    	exitButton.setOnClickListener(new View.OnClickListener(){ 
			    		public void onClick(View v)
			    		{   openRecentDocuments();  }
			    		});}
					});
				RadioButton txt = (RadioButton) findViewById(R.id.widget47);
				txt.setText("Moby Proposal\n"+date1);
				txt.setVisibility(View.VISIBLE);
				txt.setOnClickListener(new View.OnClickListener() {
					public void onClick(View v)
					{   
					setContentView(R.layout.letter);
					String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/proposal.txt");
					TextView txt = (TextView) findViewById(R.id.text);
			        txt.setText(satr);
			        Date date = new Date();
			        date1 = date.toGMTString();
			        Button exitButton = (Button)findViewById(R.id.widget51);
			    	exitButton.setOnClickListener(new View.OnClickListener(){ 
			    		public void onClick(View v)
			    		{   openRecentDocuments();  }
			    		});}
					});
			}
		}
	}
	
	Button exitButton = (Button)findViewById(R.id.widget51);
	exitButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   quitApp();  }
		});
   }
   
   private void openAllDocuments()
   {
	   setContentView(R.layout.alldocuments);
	   
 	Button letter = (Button)findViewById(R.id.widget47);
	letter.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   if (hangisi == 0)
			hangisi = 2;
			setContentView(R.layout.letter);
			String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/ref.txt");
		TextView txt = (TextView) findViewById(R.id.text);
        txt.setText(satr);
        Date date = new Date();
        date2 = date.toGMTString();
    	Button exitButton = (Button)findViewById(R.id.widget51);
    	exitButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{   openAllDocuments();  }
    		});}
		});
	Button proposal = (Button)findViewById(R.id.widget46);
	proposal.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   
			if (hangisi == 0)
				hangisi = 1;
			setContentView(R.layout.letter);
			String satr = DownloadText("http://www.ceng.metu.edu.tr/~e1502061/proposal.txt");
		TextView txt = (TextView) findViewById(R.id.text);
        txt.setText(satr);
        Date date = new Date();
        date1 = date.toGMTString();
    	Button exitButton = (Button)findViewById(R.id.widget51);
    	exitButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{   openAllDocuments();  }
    		});}
		});
  	Button mButton = (Button)findViewById(R.id.widget29);
	mButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   moveToMainMenu();  }
		});
	Button exitButton = (Button)findViewById(R.id.widget51);
	exitButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   quitApp();  }
		});
   }
   
   private void popDocumentsMenu()
   {
	   setContentView(R.layout.clickdocuments);
   	Button projectsButton = (Button)findViewById(R.id.widget29);
	projectsButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{ ProjectMenu project=new ProjectMenu();
		
		}
		});
	Button documentsButton = (Button)findViewById(R.id.widget30);
	documentsButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   moveToMainMenu();  }
		});
	Button messagesButton = (Button)findViewById(R.id.widget31);
	messagesButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   popMessagesMenu();  }
		});
   	Button recentdocumentsButton = (Button)findViewById(R.id.widget63);
   	recentdocumentsButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   openRecentDocuments();  }
		});
   	Button notificationsButton = (Button)findViewById(R.id.widget64);
   	notificationsButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   openAllDocuments();  }
		});
	Button exitButton = (Button)findViewById(R.id.widget51);
	exitButton.setOnClickListener(new View.OnClickListener(){ 
		public void onClick(View v)
		{   quitApp();  }
		});
   }
    public void moveToMainMenu() {
    	if (userID==1)
    		isAdmin = true;
    	else
    		isAdmin = false;
    	setContentView(R.layout.mainmenu);
    	TextView user = (TextView)findViewById(R.id.user);
    	DBAdapter.open();
    	Cursor c = DBAdapter.getUser(userID);
    	DBAdapter.close();
    	user.setText(c.getString(1) + " " + c.getString(2));
    	
    	Button projectsButton = (Button)findViewById(R.id.projectsButton);
    	projectsButton.setOnClickListener(new View.OnClickListener(){ 
    	
    		public void onClick(View v)
    		{ 
				Bundle bundle = new Bundle();
				
				bundle.putLong("user", userID);
				
				Intent newIntent = new Intent(v.getContext(), ProjectMenu.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
			
    		}
    		});
    	
    	
    	
    	Button docButton = (Button)findViewById(R.id.documentsButton);
    	docButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{ 
    			//TODO create documents Menu.
    			
    		}
    		});

    	RadioGroup group=(RadioGroup) findViewById(R.id.messagesselection);
    	group.setVisibility(4);
    	
    	Button messages = (Button)findViewById(R.id.personalMessages);
    	messages.setVisibility(4);
    	messages.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{   
    			//no need for a bundle, userID is static.
    			
    			 Intent myIntent = new Intent(v.getContext(), MessageMenu.class);
                 startActivityForResult(myIntent, 0);
                 
     			RadioGroup group=(RadioGroup) findViewById(R.id.messagesselection);	
    			group.setVisibility(4);
    			Button messages = (Button)findViewById(R.id.personalMessages);
    			messages.setVisibility(4);
    			Button notifications = (Button)findViewById(R.id.notifications);
    			notifications.setVisibility(4);
                 
    		}
    		});

    	Button notifications = (Button)findViewById(R.id.notifications);
    	notifications.setVisibility(4);
    	notifications.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{   
    			//TODO create NotificationMenu.
    			Bundle bundle=new Bundle();
    			bundle.putLong("name", userID);
    			
    			Intent myIntent = new Intent(v.getContext(), NotificationMenu.class);
    			myIntent.putExtras(bundle);
                 startActivityForResult(myIntent, 0);
    			
    			RadioGroup group=(RadioGroup) findViewById(R.id.messagesselection);	
    			group.setVisibility(4);
    			Button messages = (Button)findViewById(R.id.personalMessages);
    			messages.setVisibility(4);
    			Button notifications = (Button)findViewById(R.id.notifications);
    			notifications.setVisibility(4);
    		}
    		});
    	
    	Button mButton = (Button)findViewById(R.id.messagesButton);
    	mButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{   
   
    			RadioGroup group=(RadioGroup) findViewById(R.id.messagesselection);	
    			if (group.getVisibility()==0)	group.setVisibility(4);
    			else group.setVisibility(0);
    			Button messages = (Button)findViewById(R.id.personalMessages);
    			if (messages.getVisibility()==0)	messages.setVisibility(4);
    			else messages.setVisibility(0);
    			Button notifications = (Button)findViewById(R.id.notifications);
    			if (notifications.getVisibility()==0)	notifications.setVisibility(4);
    			else notifications.setVisibility(0);
    			
    		}
    		});
    	
    	Button eButton = (Button)findViewById(R.id.eventsButton);
    	eButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{   
    			Bundle bundle=new Bundle();
    			bundle.putLong("name", userID);
				bundle.putLong("projevent",10);
				
				Intent newIntent = new Intent(v.getContext(), EventMenu.class);
				
				newIntent.putExtras(bundle);
				
				startActivityForResult(newIntent, 0);
    		}
    		});
    	
    	Button exitButton = (Button)findViewById(R.id.exitButton);
    	exitButton.setOnClickListener(new View.OnClickListener(){ 
    		public void onClick(View v)
    		{   quitApp();  }
    		});
    	   }
    	private void quitApp() {
    		
    	//	DBAdapter.open();
    	//	DBAdapter.delete();
    	//	DBAdapter.close();
    		this.finish();
    	}
    
    private InputStream OpenHttpConnection(String urlString) 
    throws IOException
    {
        InputStream in = null;
        int response = -1;
               
        URL url = new URL(urlString); 
        URLConnection conn = url.openConnection();
                 
        if (!(conn instanceof HttpURLConnection))                     
            throw new IOException("Not an HTTP connection");
        
        try{
            HttpURLConnection httpConn = (HttpURLConnection) conn;
            httpConn.setAllowUserInteraction(false);
            httpConn.setInstanceFollowRedirects(true);
            httpConn.setRequestMethod("GET");
            httpConn.connect(); 

            response = httpConn.getResponseCode();                 
            if (response == HttpURLConnection.HTTP_OK) {
            	//setContentView(R.layout.test);
                in = httpConn.getInputStream();                                 
            }                     
        }
        catch (Exception ex)
        {
            throw new IOException("Error connecting");            
        }
        return in;     
    }
    
    private String DownloadText(String URL)
    {
        int BUFFER_SIZE = 2000;
        InputStream in = null;
        try {
            in = OpenHttpConnection(URL);
        } catch (IOException e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
            return "";
        }
        
        InputStreamReader isr = new InputStreamReader(in);
        int charRead;
          String str = "";
          char[] inputBuffer = new char[BUFFER_SIZE];          
        try {
            while ((charRead = isr.read(inputBuffer))>0)
            {                    
                //---convert the chars to a String---
                String readString = 
                    String.copyValueOf(inputBuffer, 0, charRead);                    
                str += readString;
                inputBuffer = new char[BUFFER_SIZE];
            }
            in.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
            return "";
        }
        return str;        
    }
    
    protected void onActivityResult(int a, int result, Intent data)
	{
    	if (result==11){
		//	 Intent intent = new Intent();
		     //      setResult(11, intent);	// 11 signals exit.
		           finish();		
		}
	}

}
