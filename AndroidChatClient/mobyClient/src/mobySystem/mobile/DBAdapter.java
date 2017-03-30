package mobySystem.mobile;


import java.util.Date;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class DBAdapter 
{
		//PROJECTS TABLE FIELDS
	public static final String KEY_PROJECTID = "projectid";
	public static final String PROJECTNAME = "projectname";
	public static final String STARTDATE = "startdate";
	public static final String DEADLINE = "deadline";
	
	//EVENTS TABLE FIELDS
	public static final String KEY_EVENTID = "eventid";
	public static final String EVENTNAME = "eventname";
	public static final String EVENTDATE = "eventdate";
	public static final String EVENTADDRESS = "eventaddress";
	
	//USERS FIELDS
    public static final String KEY_USERNAME = "username";
    public static final String NAME = "name";
    public static final String SURNAME = "surname";
    public static final String PASSWORD = "password";   
    public static final String EMAIL = "email";
    public static final String PHONE = "phone";
    public static final String POSITION = "position";
    
    //DOCUMENTS FIELDS
    public static final String KEY_DOCUMENTID="documentid";
    public static final String DOCUMENTNAME="documentname";
    public static final String DOCUMENTPATH="documentpath";
    
    //PERSONALMESSAGES FIELDS
    public static final String MESSAGEUNREAD = "messageunread";
    public static final String KEY_MESSAGEID="messageid";
    public static final String MESSAGETYPE="messagetype";
    public static final String MESSAGEPATH="messagepath";
    public static final String SENDER = "sender";
    
    //NOTIFICATIONS FIELDS
    public static final String KEY_NOTIFICATIONID="notificationid";
    public static final String NOTIFICATIONTYPE="notificationtype";
    public static final String TEXT = "text";
    public static final String ALAN="alan";
    public static final String ALANID="alanid";
    public static final String MESSAGETEXT="messagetext";
    
    //AUXILLARY FIELDS ARE EXPLAINED BELOW//
    //
    
    public static final String DCDATE="dcdate";
    public static final String DUDATE="dudate";
    public static final String ECDATE="ecdate";
    public static final String EUDATE="eudate";
    public static final String TIME="time";
    public static final String MCDATE="mcdate";
    public static final String SINCE="since";
    
    
    
    private static final String TAG = "DBAdapter";
    private static final String DATABASE_NAME = "MobyLocalDatabase";
    private static final int DATABASE_VERSION = 1;
    
    private static final String DOCUMENT_TABLE = "documents";
    private static final String EVENT_TABLE = "events";
    private static final String USER_TABLE = "users";
    private static final String PROJECT_TABLE = "projects";
    private static final String PERSONALMESSAGE_TABLE = "personalmessages";
    private static final String NOTIFICATION_TABLE = "notifications";

    private static final String DCREATEINFO_TABLE = "dcreateinfo";
    private static final String DUPDATEINFO_TABLE = "dupdateinfo";
    private static final String ECREATEINFO_TABLE = "ecreateinfo";
    private static final String EUPDATEINFO_TABLE = "eupdateinfo";
    private static final String HASEVENT_TABLE = "hasevent";
    private static final String HASNOTIFICATION_TABLE = "hasnotification";
    private static final String HASPERSONALMESSAGE_TABLE = "haspersonalmessage";
    private static final String HASDOCUMENT_TABLE = "hasdocument";
    private static final String WORKSIN_TABLE = "worksin";
    private static final String MESSAGECREATE_TABLE = "messagecreate";
    private static final String PARTICIPANTS_TABLE = "participants";
    private static final String PCREATEINFO_TABLE = "pcreateinfo";
    
    
    private static final String USER_CREATE =
        
    	"create table users (username long primary key, " +
    			"name text not null, " +
    			"surname text not null, " +
        		"password text not null, " +
        		"email text not null, phone text not null, " +
        		"position text not null);" ;	
    		
    		//Telling we have two keys.
        	/*		
        		+
  
                
        "create table ecreateinfo(username long" +
        		"eventID long primary key" +
        		"ecdate text); "+
        
        "create table eupdateinfo(username long primary key" +
        		"eventID long primary key" +
        		"eudate text); "+
        		
        "create table dcreateinfo(username long primary key" +
             	"documentID long primary key" +
          		"dcdate text); "+
                		
        "create table dupdateinfo(username long primary key" +
        		"documentID long primary key" +
        		"dudate text); "+
        		
        "create table pcreateinfo(username long primary key" +
        		"projectID long primary key); "
        		
        		
        ;
        */
        		
        		
    private static final String PROJECT_CREATE = 
    	"create table projects (projectid long primary key,"
    	+ "projectName text not null," +
    		"startdate text not null, " +
       		"deadline text);";
    private static final String EVENT_CREATE =
    	"create table events (eventid long primary key,"
        + "eventName text not null," +
        "eventDate text not null, " +
        "eventAddress text);";
    private static final String PERSONALMESSAGE_CREATE=
    	"create table personalmessages (messageid integer primary key autoincrement,"
        +"messagetype long not null," +
        "messagetext text," +
        "sender long not null,"+
        "messagepath text," +
        "messageunread integer not null, time text not null);";
    private static final String NOTIFICATION_CREATE = 
    	"create table notifications (notificationid integer primary key	autoincrement,"
        + "text text not null, notificationtype text not null, alan text not null, alanid long not null);";
    private static final String WORKSIN_CREATE = 
    	"create table worksin (wid integer primary key autoincrement, username long not null ,"
        + "projectid long not null);";
    private static final String HASEVENT_CREATE = 
    	"create table hasevent (eventid long primary key not null ,"
        + "projectid long not null);";
    private static final String HASPERSONALMESSAGE_CREATE = 
    	"create table haspersonalmessage (username long not null ,"
        + "messageid long primary key not null);";
    private static final String PARTICIPANTS_CREATE = 
    	"create table participants (parid integer primary key autoincrement, username long not null, " +
		"eventid long not null);";
    private static final String HASNOTIFICATION_CREATE = 
    	"create table hasnotification (username long,"
        + "notificationid long primary key," +
        "time text);";
    
    
    
    private static Context context; 
    private static DatabaseHelper DBHelper;
    private static SQLiteDatabase db;
    
    public DBAdapter(Context ctx) 
    {
        context = ctx;
        DBHelper = new DatabaseHelper(context);
    }
        
    private static class DatabaseHelper extends SQLiteOpenHelper 
    {
        DatabaseHelper(Context context) 
        {
            super(context, DATABASE_NAME, null, DATABASE_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) 
        {	
            db.execSQL(USER_CREATE);
            db.execSQL(PROJECT_CREATE);
            db.execSQL(EVENT_CREATE);
            db.execSQL(PERSONALMESSAGE_CREATE);
            db.execSQL(NOTIFICATION_CREATE);
            db.execSQL(WORKSIN_CREATE);
            db.execSQL(HASEVENT_CREATE);
            db.execSQL(HASPERSONALMESSAGE_CREATE);
            db.execSQL(HASNOTIFICATION_CREATE);
            db.execSQL(PARTICIPANTS_CREATE);
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, 
        int newVersion) 
        {
            Log.w(TAG, "Upgrading database from version " + oldVersion 
                    + " to "
                    + newVersion + ", which will destroy all old data");
            delete();

            onCreate(db);
        }
    }    
    
    public static void delete() throws SQLException
    {
        db.execSQL("DROP TABLE IF EXISTS users");
        db.execSQL("DROP TABLE IF EXISTS events");
        db.execSQL("DROP TABLE IF EXISTS projects");
        db.execSQL("DROP TABLE IF EXISTS notifications");
        db.execSQL("DROP TABLE IF EXISTS personalmessages");
        db.execSQL("DROP TABLE IF EXISTS haspersonalmessage");
        db.execSQL("DROP TABLE IF EXISTS ecreateinfo");
        db.execSQL("DROP TABLE IF EXISTS eupdateinfo");
        db.execSQL("DROP TABLE IF EXISTS dcreateinfo");
        db.execSQL("DROP TABLE IF EXISTS dupdateinfo");
        db.execSQL("DROP TABLE IF EXISTS pcreateinfo");
        db.execSQL("DROP TABLE IF EXISTS worksin");
    	
    }
    
    //---opens the database---
    public static DBAdapter open() throws SQLException 
    {
        db = DBHelper.getWritableDatabase();
        return null;
    }
    
    //---closes the database---    
    public static void close() 
    {
        DBHelper.close();
    }
    
    //---insert a USER into the database---
    public static long insertUser(long userName, String name, 
    		String surname, String password, String email, String phone,
    		String position) 
    {
        ContentValues initialValues = new ContentValues();
        initialValues.put(KEY_USERNAME, userName);
        initialValues.put(NAME, name);
        initialValues.put(SURNAME, surname);
        initialValues.put(PASSWORD, password);
        initialValues.put(EMAIL, email);
        initialValues.put(PHONE, phone);
        initialValues.put(POSITION, position);
        return db.insert(USER_TABLE, null, initialValues);
        
    
    }

    //---deletes a particular USER---
    public static boolean deleteUser(long userName) 
    {
        return db.delete(USER_TABLE, KEY_USERNAME + 
        		"=" + userName, null) > 0;
    }

    
    //---insert a PROJECT into the database---
    public static long insertProject(long projectID, String projectName, 
    		String startDate, String deadline) 
    {
        ContentValues initialValues = new ContentValues();
        initialValues.put(KEY_PROJECTID, projectID);
        initialValues.put(PROJECTNAME, projectName);
        initialValues.put(STARTDATE, startDate);
        initialValues.put(DEADLINE, deadline);
        db.insert(PROJECT_TABLE, null, initialValues);
        return projectID;
    }

    
    public static Cursor getProjectPeople(long projectID){
    	Cursor people = db.query(true, WORKSIN_TABLE, new String[] {
        		KEY_USERNAME,
        		KEY_PROJECTID},
        		KEY_PROJECTID + "=" + projectID, 
        		null,
        		null, 
        		null, 
        		null, 
        		null);
    	
    	 if (people != null) {
             people.moveToFirst();
         } 
    	 
    	return people;
    	
    }
    
    
    public static long addUserToProject(long userName,long projectID){
    	
    	ContentValues initialValues = new ContentValues();
        initialValues.put(KEY_USERNAME, userName);
        initialValues.put(KEY_PROJECTID, projectID);
        return db.insert(WORKSIN_TABLE, null, initialValues);	
    }
    
    
    
    //---deletes a particular PROJECT---
    public static boolean deleteProject(long projectID) 
    {
        return db.delete(PROJECT_TABLE, KEY_PROJECTID + 
        		"=" + projectID, null) > 0;
    }
    
    public static Cursor getEvent(long eventID) throws SQLException 
    {
        Cursor mCursor =
                db.query(true, EVENT_TABLE, new String[] {
                		KEY_EVENTID,
                		EVENTNAME, 
                		EVENTDATE,
                		EVENTADDRESS
                		},
                		KEY_EVENTID + "=" + eventID, 
                		null,
                		null, 
                		null, 
                		null, 
                		null);
        
        if (mCursor != null) {
            mCursor.moveToFirst();
        }
        return mCursor;
    }

    public static Cursor getEventPeople(long eventID){
    	Cursor people = db.query(true, PARTICIPANTS_TABLE, new String[] {
        		KEY_USERNAME,
        		KEY_EVENTID},
        		KEY_EVENTID + "=" + eventID, 
        		null,
        		null, 
        		null, 
        		null, 
        		null);
    	
    	 if (people != null) {
             people.moveToFirst();
         } 
    	 
    	return people;
    	
    }
    
    public static Cursor getProjectEvents(long projectID){
    	Cursor people = db.query(true, HASEVENT_TABLE, new String[] {
        		KEY_EVENTID,
        		KEY_PROJECTID},
        		KEY_PROJECTID + "=" + projectID, 
        		null,
        		null, 
        		null, 
        		null, 
        		null);
    	
    	 if (people != null) {
             people.moveToFirst();
         } 
    	 
    	return people;
    	
    }
    
    //---insert a EVENT into the database---
   

    public static long addEventToProject(long eventid,long projectID){
    	
    	ContentValues initialValues = new ContentValues();
        initialValues.put(KEY_EVENTID, eventid);
        initialValues.put(KEY_PROJECTID, projectID);
        return db.insert(HASEVENT_TABLE, null, initialValues);	
    }
    
  //---insert a EVENT into the database---
    public static long insertEvent(long eventID, String eventName, 
    		String eventDate, String eventAddress) 
    {
        ContentValues initialValues = new ContentValues();
        initialValues.put(EVENTNAME, eventName);
        initialValues.put(KEY_EVENTID, eventID);
        initialValues.put(EVENTDATE, eventDate);
        initialValues.put(EVENTADDRESS, eventAddress);
        db.insert(EVENT_TABLE, null, initialValues);
        return eventID;
    }
    
    //---deletes a particular EVENT---
    public static boolean deleteEvent(long eventID) 
    {
        return db.delete(EVENT_TABLE, KEY_EVENTID + 
        		"=" + eventID, null) > 0;
    }
    
    //---insert a DOCUMENT into the database---
    public static long insertDocument(long documentID, String documentName, 
    		String documentPath) 
    {
        ContentValues initialValues = new ContentValues();
        initialValues.put(KEY_DOCUMENTID, documentID);
        initialValues.put(DOCUMENTNAME, documentName);
        initialValues.put(DOCUMENTPATH, documentPath);
        db.insert(DOCUMENT_TABLE, null, initialValues);
        return documentID;
    }

    //---deletes a particular DOCUMENT---
    public static boolean deleteDocument(long documentID)   {
        return db.delete(DOCUMENT_TABLE, KEY_DOCUMENTID + 
        		"=" + documentID, null) > 0;
    }
    
    public static long markRead(long messageID){
		
    	ContentValues updatedValues = new ContentValues();
    	
    	updatedValues.put(MESSAGEUNREAD, 0);
		
    	long rows = db.update(PERSONALMESSAGE_TABLE, updatedValues, 
				KEY_MESSAGEID + "=" + messageID, 
				null);
    	
		Log.v("Moby", "Read:"+messageID);
		
		return rows;
	}
    
    //---insert a PERSONAL MESSAGE into the database---
    public static long insertPersonalMessage(String messageText, 
    		long sender,long receiver) 
    {	
    	Date date = new Date();
    	
    	 String zaman = date.toGMTString();
        ContentValues initialValues = new ContentValues();
        initialValues.put(MESSAGETYPE, 0);	//TextMessage
        initialValues.put(MESSAGETEXT, messageText);
        initialValues.put(SENDER, sender);
        initialValues.put(MESSAGEPATH, "");
        initialValues.put(MESSAGEUNREAD,1);	//1 means unread. 0 means read.
        initialValues.put(TIME,zaman);
        long messageID = db.insert(PERSONALMESSAGE_TABLE, null, initialValues);
        
        ContentValues relationalValues =  new ContentValues();
        relationalValues.put(KEY_USERNAME,receiver);
        relationalValues.put(KEY_MESSAGEID,messageID);
        long relationID=db.insert(HASPERSONALMESSAGE_TABLE, null, relationalValues);
        Log.v("Moby", "Relation no:"+relationID);
        
        return messageID;
    }
    
    public static Cursor getMessages(long username){
    	
    	Cursor messages = db.query(true, HASPERSONALMESSAGE_TABLE, new String[]{
    				KEY_MESSAGEID		
    				}, 
    				KEY_USERNAME+"="+username, 
    				null, 
    				null, 
    				null, 
    				null, 
    				null);
 
    	if (messages != null) {
    		messages.moveToFirst();
    	}
    	return messages;
  	
    }

    public static Cursor getPersonalMessage(long messageID){
    	
    	Cursor message = db.query(true, PERSONALMESSAGE_TABLE, new String[]{
    				MESSAGETEXT,
    				SENDER,
    				MESSAGEUNREAD,
    				TIME
    				}, 
    				KEY_MESSAGEID+"="+messageID, 
    				null, 
    				null, 
    				null, 
    				null, 
    				null);
 
    	if (message != null) {
    		message.moveToFirst();
    	}
    	return message;
  	
    }
    
    
    
  //---deletes a particular DOCUMENT---
    public static boolean deletePersonalMessage(long messageID)   {
        return db.delete(PERSONALMESSAGE_TABLE, KEY_MESSAGEID + 
        		"=" + messageID, null) > 0 && 
        		db.delete(HASPERSONALMESSAGE_TABLE, KEY_MESSAGEID + "=" + messageID,	null)>0;
    }

  //---deletes a particular DOCUMENT---
    public static boolean deleteNotification(long notificationID)   {
        return db.delete(NOTIFICATION_TABLE, KEY_NOTIFICATIONID + 
        		"=" + notificationID, null) > 0;
    }


 
    //GETTERS
    
    
    public static Cursor getUser(long userName) throws SQLException 
    {
        Cursor mCursor =
                db.query(true, USER_TABLE, new String[] {
                		KEY_USERNAME,
                		NAME, 
                		SURNAME,
                		PASSWORD,
                		EMAIL,
                		PHONE,
                		POSITION
                		},
                		KEY_USERNAME + "=" + userName, 
                		null,
                		null, 
                		null, 
                		null, 
                		null);
        
        if (mCursor != null) {
            mCursor.moveToFirst();
        }
        return mCursor;
    }
    
    public static Cursor getUserName(long userName) throws SQLException 
    {
        Cursor mCursor =
                db.query(true, USER_TABLE, new String[] {
                		NAME, 
                		SURNAME
                		},
                		KEY_USERNAME + "=" + userName, 
                		null,
                		null, 
                		null, 
                		null, 
                		null);
        
        if (mCursor != null) {
            mCursor.moveToFirst();
        }
        return mCursor;
    }
    
    
    public static Cursor getProject(long projectID) throws SQLException 
    {
        Cursor mCursor =
                db.query(true, PROJECT_TABLE, new String[] {
                		KEY_PROJECTID,
                		PROJECTNAME, 
                		STARTDATE,
                		DEADLINE
                		},
                		KEY_PROJECTID + "=" + projectID, 
                		null,
                		null, 
                		null, 
                		null, 
                		null);
        
        if (mCursor != null) {
            mCursor.moveToFirst();
        }
        return mCursor;
    }

    public static Cursor getAllProjects() 
    {
        return db.query(PROJECT_TABLE, new String[] {
        		KEY_PROJECTID,
        		PROJECTNAME,
        		STARTDATE,
        		DEADLINE}, 
                null, 
                null, 
                null, 
                null, 
                null);
    }
    
    //UPDATERS//
    public static boolean updateUser(long userName, String name, 
    String surname, String password) 
    {
        ContentValues args = new ContentValues();
        args.put(NAME, name);
        args.put(SURNAME, surname);
        args.put(PASSWORD, password);
        return db.update(USER_TABLE, args, 
                         KEY_USERNAME + "=" + userName, null) > 0;
    }
    
    public static boolean updateProject(long projectID, String name, 
    	    String startDate, String deadline) 
    {
    	        ContentValues args = new ContentValues();
    	        args.put(PROJECTNAME, projectID);
    	        args.put(STARTDATE, startDate);
    	        args.put(PASSWORD, deadline);
    	        return db.update(USER_TABLE, args, 
    	                         KEY_PROJECTID + "=" + projectID, null) > 0;
    }
    
	public static void addUsers(){
		
		//Here I add sample users into the scene.
    	open();
        long id;
        Cursor c = getUser(1);
        if (c.getCount()==0)
        {
        	 id = insertUser(
             		1502954,
             		"Cem",
             		"Ozturan",
             		"mezun",
             		"cemos@gmail.com",
             		"05542782662",
             		"Engineer");        
             id = insertUser(
             		1502061,
             		"Rusen",
             		"Aktas",
             		"gripple",
             		"rusi@yahoo.com",
             		"05059482095",
             		"Lawyer");
             id = insertUser(
             		1502111,
             		"Pelin",
             		"Atici",
             		"mezun",
             		"pelinatici@gmail.com",
             		"05057823995",
             		"Secretary");
             id = insertUser(
             		1502939,
             		"Osman",
             		"Bugra",
             		"mezun",
             		"pilav@gmail.com",
             		"05057823995",
             		"Salesman");
             id = insertUser(
             		1502058,
             		"Gizem",
             		"Albayrak",
             		"mezun",
             		"gizemalbayrk@gmail.com",
             		"05056532882",
             		"Security");
             id = insertUser(
             		1112,
             		"Drow",
             		"Ranger",
             		"Trax",
             		"gosugamer@gmail.com",
             		"05056532882",
             		"Master");
             id = insertUser(
             		1,
             		"Admin",
             		"Admin",
             		"admin",
             		"admin@admin.com",
             		"05056532882",
             		"Admin");
             
             id = insertProject(1, "The Tribute", "04/03/2007", "14/10/2012");
             id = insertProject(2, "The Warsim", "05/04/2007", "11/11/2010");
             id = insertProject(3, "The Auss", "06/07/2007", "12/11/2018");
             id = insertProject(5, "The New", "06/07/2007", "12/11/2018");
             
             addUserToProject(1502061, 1);
             addUserToProject(1502954, 2);
             addUserToProject(1112, 1);
             addUserToProject(1502111, 2);
             addUserToProject(1502058, 3);
             addUserToProject(1502939, 3);
             addUserToProject(1502061, 5);
             addUserToProject(1502058, 5);
           
             long hop = insertPersonalMessage("Selam, istifa dilekcenizi en kisa zamanda masamda istiyorum.",1502061,1);
             long hop2 = insertPersonalMessage("Sistem harika, tebrikler :P",1502111,1);
             
             Cursor mesaj1 = getPersonalMessage(hop);
             Log.v("Moby", "Message:"+mesaj1.getString(0)+" from: "+mesaj1.getLong(1));
             Cursor mesaj2 = getPersonalMessage(hop2);
             Log.v("Moby", "Message:"+mesaj2.getString(0)+" from: "+mesaj2.getLong(1));
             
           //  Log.v("Moby", "Marked Read;"+markRead(1));
             
             id = insertEvent(1,"Ayran Gunu", "01/06/2010", "B.A.L.");
             addEventToProject(1,1);
             id = insertEvent(2,"Aylik Toplanti", "19/06/2010", "Oval Ofis");
             addEventToProject(2,1);
             id = insertEvent(3,"Mali Kurul", "07/07/2010", "A-105");
             addEventToProject(3,2);
             id = insertEvent(4,"Proje Degerlendirmesi", "11/06/2010", "Yedek Salon");
             addEventToProject(4,2);
             id = insertEvent(5,"Bowling Gecesi", "12/07/2010", "Ankuva");
             addEventToProject(5,3);
             id = insertEvent(6,"Test Edelim", "21/06/2010", "Software Room");
             addEventToProject(6,3);
             id = insertEvent(7,"CENG140 Final", "11/06/2010", "BMB-1");
             addEventToProject(7,5);
             id = insertEvent(8,"Mezuniyet", "04/07/2010", "Devrim");
             addEventToProject(8,5);
             
             addUserToEvent(1,1502111);
             addUserToEvent(1,1502954);
        }
        db.close();
	}
	
	// HAS NOTIFICATION *******************************
    //---insert a hasnotification into hasnotification table---
      public static long insertHasNotification(long notificationID, long userName, String time) 
      {
          ContentValues initialValues = new ContentValues();
          initialValues.put(KEY_NOTIFICATIONID, notificationID);
          initialValues.put(KEY_USERNAME, userName);
          initialValues.put(TIME, time);
          long id=db.insert(HASNOTIFICATION_TABLE, null, initialValues);
          Log.v("Moby", "into notification table:"+id);
          return notificationID;
      }

      //---deletes a hasnotification from hasnotification table---
      public boolean deleteHasNotification(int notificationID,long userName) 
      {
          return db.delete(HASNOTIFICATION_TABLE, KEY_NOTIFICATIONID + 
          		"=" + notificationID, null) > 0;
      }

      //---retrieves all notifications of a user---
      public static Cursor getAllHasNotifications(long userName) 
      {
          return db.query(HASNOTIFICATION_TABLE, new String[] {
          		KEY_NOTIFICATIONID, 
          		KEY_USERNAME,
          		TIME}, 
          		KEY_USERNAME + "=" + userName, 
                  null, 
                  null, 
                  null, 
                  null);
      }

      // HAS NOTIFICATION BITTI **************

      //add a user to an event
      public static long addUserToEvent(long eventID, long userName) 
      {
          ContentValues initialValues = new ContentValues();
          initialValues.put(KEY_EVENTID, eventID);
          initialValues.put(KEY_USERNAME, userName);
          String Event = getEvent(eventID).getString(1);
          long id = insertNotification("New Event", "You are required to attend to this event.", Event, userName, eventID);
      Log.v("Moby", "it returns:"+id);
          //   insertHasNotification(id, userName, "time");
      //    return userName;
         return db.insert(PARTICIPANTS_TABLE, null, initialValues);
      }
      
      // insert a notification
      public static long insertNotification(String type, String text, String alan, long userName, long eventID) 
      {
    	  long id;
          ContentValues initialValues = new ContentValues();
          initialValues.put(TEXT, text);
          initialValues.put(NOTIFICATIONTYPE, type);
          initialValues.put(ALAN, alan);
          initialValues.put(ALANID, eventID);
          id = db.insert(NOTIFICATION_TABLE, null, initialValues);
          Log.v("Moby", "into notification table:"+id);
          insertHasNotification(id, userName, "time");
          return id;
      }

      public static Cursor getNotification(long notificationID) throws SQLException 
      {
          Cursor mCursor =
                  db.query(true, NOTIFICATION_TABLE, new String[] {
                  		KEY_NOTIFICATIONID,
                  		NOTIFICATIONTYPE,
                  		TEXT,
                  		ALAN,
                  		ALANID},
                  		KEY_NOTIFICATIONID + "=" + notificationID, 
                  		null,
                  		null, 
                  		null, 
                  		null, 
                  		null);
          if (mCursor != null) {
              mCursor.moveToFirst();
          }
          return mCursor;
      }

      public static boolean removeUserFromProject(long userName,long projectID){
        	
        	return db.delete(WORKSIN_TABLE, KEY_PROJECTID + 
            		"=" + projectID + " AND " + KEY_USERNAME + "=" + userName , null) > 0;
        }
      
      public static boolean removeUserFromEvent(long userName,long eventID){
    	  ContentValues initialValues = new ContentValues();
          initialValues.put(KEY_EVENTID, eventID);
          initialValues.put(KEY_USERNAME, userName);
    	  String Event = getEvent(eventID).getString(1);
          long id = insertNotification("Removal", "You are removed from the participants list of this event.", Event, userName, eventID);
       //   insertHasNotification(id, userName, "time");
      //    return userName;
         db.insert(PARTICIPANTS_TABLE, null, initialValues);
      	return db.delete(PARTICIPANTS_TABLE, KEY_EVENTID + 
          		"=" + eventID + " AND " + KEY_USERNAME + "=" + userName , null) > 0;
      }
      
      public static Cursor getUserByName(String name,String surname) throws SQLException 
      {		
          Cursor mCursor =
                  db.query(true, USER_TABLE, new String[] {
                  		KEY_USERNAME
                  		},
                  		//NAME + " " + SURNAME + "=" + name,
                  		NAME + "=" + name + " AND " + SURNAME + "=" + surname,
                  		null,
                  		null, 
                  		null, 
                  		null, 
                  		null);
          
          if (mCursor != null) {
              mCursor.moveToFirst();
          }
          return mCursor;
          
      }
      
      public static Cursor getUserEvents(long userName){
      	Cursor people = db.query(true, PARTICIPANTS_TABLE, new String[] {
      			KEY_EVENTID,
      			KEY_USERNAME},
          		KEY_USERNAME + "=" +userName, 
          		null,
          		null, 
          		null, 
          		null, 
          		null);
      	
      	 if (people != null) {
               people.moveToFirst();
           } 
      	 
      	return people;
      	
      }
      
}


