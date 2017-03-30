

#include "GL/gl.h"
#include "GL/glut.h"
#include "GL/glu.h"

#include "global.h"

using namespace std;

void ruleKeys( void );
// Sets Camera Values as pos, center, up
void setCameraValues( float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3 )
{
	posX	= x1; posY		= y1; posZ  = z1;
	centerX = x2; centerY = y2; centerZ = z2;
	upX		= x3; upY		= y3; upZ   = z3;
}

// normalize(); - normalizes vector 
void normalize( vector_t *normal )
{
	float length = sqrt( (normal->x * normal->x) + (normal->y * normal->y) + (normal->z * normal->z) );
	normal->x /= length;
	normal->y /= length;
	normal->z /= length;
}

// normal(); - finds a normal vector and normalizes it
void normalCalculate( vector_t vec[3], vector_t *normal )
{
    vector_t a, b;

    // calculate the vectors A and B
    // note that vec[3] is defined with counterclockwise winding in mind
    // a
	a.x = vec[0].x - vec[1].x; 
	a.y = vec[0].y - vec[1].y;
	a.z = vec[0].z - vec[1].z;
    // b
	b.x = vec[1].x - vec[2].x; 
	b.y = vec[1].y - vec[2].y;
	b.z = vec[1].z - vec[2].z;

    // calculate the cross product and place the resulting vector
    // into the address specified by vertex_t *normal
	normal->x = (a.y * b.z) - (a.z * b.y);
	normal->y = (a.z * b.x) - (a.x * b.z);
	normal->z = (a.x * b.y) - (a.y * b.x);

    // normalize operation
	normalize( normal );
}

// draw a triangle with vertices at (x1, y1), (x2, y2) 
// and (x3, y3) at z units away from the origin.
void drawTriangle ( size_t index )
{
   //vector_t normal;

   glBegin( GL_TRIANGLES );
   //normalCalculate( t->vertex, &normal );
	   //glNormal3f( t->vertex[0].x + normal.x, t->vertex[0].y + normal.y, t->vertex[0].z + normal.z );
   glNormal3f( normalArray[index*3].x,normalArray[index*3].y,normalArray[index*3].z );
	   glVertex3f( triangles[index].vertex[0].x, triangles[index].vertex[0].y, triangles[index].vertex[0].z );
	glNormal3f( normalArray[index*3+1].x,normalArray[index*3+1].y,normalArray[index*3+1].z );
	   glVertex3f( triangles[index].vertex[1].x, triangles[index].vertex[1].y, triangles[index].vertex[1].z );
	glNormal3f( normalArray[index*3+2].x,normalArray[index*3+2].y,normalArray[index*3+2].z );
	   glVertex3f( triangles[index].vertex[2].x, triangles[index].vertex[2].y, triangles[index].vertex[2].z );
   glEnd();
}

void readInput( void )
{
    ifstream inputFile;
	inputFile.open( fileName.c_str() );

	while( !inputFile.eof() )
	{
		triangle_t myTriangle;
		float x, y, z;

		inputFile >> x >> y >> z;
		myTriangle.vertex[0].x = x;
		myTriangle.vertex[0].y = y;
		myTriangle.vertex[0].z = z;
		inputFile >> x >> y >> z;
		myTriangle.vertex[1].x = x;
		myTriangle.vertex[1].y = y;
		myTriangle.vertex[1].z = z;
		inputFile >> x >> y >> z;
		myTriangle.vertex[2].x = x;
		myTriangle.vertex[2].y = y;
		myTriangle.vertex[2].z = z;

		triangles.push_back( myTriangle );
	}
	
	size_t size = triangles.size();
	normalArray = new vector_t[ (size * 3) ];
	for( size_t i = 0; i < size; i++ )
	{
		for( int j = 0; j < 3; j++ )
		{
			vector_t tempVector = {0,0,0};
			int counter = 0;
			for( size_t k = 0; k < size; k++ )
			{
				bool bFound = false;
				for( int l = 0; l< 3; l++ )
				{
					if( triangles[ i ].vertex[j].x == triangles[ k].vertex[l].x &&
						triangles[ i ].vertex[j].y == triangles[ k].vertex[l].y &&
						triangles[ i ].vertex[j].z == triangles[ k].vertex[l].z		)
					{
						bFound = true;
						break;
					}
				}
				if( bFound == true )
				{
					vector_t normal;
					normalCalculate( triangles[ k ].vertex, &normal );
					tempVector.x += normal.x;
					tempVector.y += normal.y;
					tempVector.z += normal.z;
					counter++;
				}
			}
			normalArray[ i*3 + j ].x = tempVector.x / counter + triangles[ i ].vertex[j].x;
			normalArray[ i*3 + j ].y = tempVector.y / counter + triangles[ i ].vertex[j].y;
			normalArray[ i*3 + j ].z = tempVector.z / counter + triangles[ i ].vertex[j].z;
		}
	}
}

// drawScene draws 4 triangles and a wire frame
// which represents the viewing volume.
void drawScene( void )
{
	size_t size = triangles.size();
	for( size_t i = 0; i < size; i++ )
		drawTriangle( i );
}

void init( void ) 
{
	//any initialization before the main loop of GLUT goes here
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	//// SET CAMERA
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, 4.0/3.0, 0.1, 100.0); // You may change parameters w.r.t. your needs.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// SET LIGHTING
	glEnable(GL_LIGHTING);
	GLfloat position[]   = {1000.0, 1000.0 , 1000.0, 0.0};
	GLfloat blackColor[] = {0.1 , 0.1 , 0.1 , 1.0};
	GLfloat whiteColor[] = {1.0 , 1.0 , 1.0 , 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  blackColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	glEnable(GL_LIGHT0);
	
	if( MODE1 )
	{
		setCameraValues(1.0, 0, 1.0, 0.0, 0, 0.0, 0, 1, 0);
		gluLookAt(posX, posY, posZ, centerX, centerY, centerZ, upX, upY, upZ); // You may change parameters w.r.t. your needs.

		// RESET GLOBALS
		angleCam	   = 0.0f;
		angleRotate    = 0.0f;
		zoomFactor	   = 1.1f;
		flagVer		   = true;
		flagHor		   = true;
		flagSca		   = true;
	}
	else if( MODE2 )
	{
		rotX = 0.0;
		rotY = 3.0;
	    rotZ = -11.0;
		setCameraValues(-0.997259, 0, 0.895328, 0.0, 0, 0.0, 0, 1, 0);
	}
}

void cameraRotate( void )
{
	if( hMODE && MODE1 )
	{	
		angleCam += (fraction * 180 / 3.14);

		posX = cos(angleCam);
		posZ = sin(angleCam);

		glutPostRedisplay();
	}
}

void display( void )
{
	ruleKeys();
	if( MODE1 )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset transformations
		glLoadIdentity();
		// Set the camera
		gluLookAt(posX, posY, posZ, centerX, centerY, centerZ, upX, upY, upZ);

		glScalef( zoomFactor, zoomFactor, zoomFactor );
		glRotatef( angleRotate, 0, 1, 0 );

		drawScene();
		glutSwapBuffers();
	
		glutIdleFunc(cameraRotate);
	}
	else if( MODE2 )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		glRotatef(rotX,1.0,0.0,0.0);
		glRotatef(rotY,0.0,1.0,0.0);
		glRotatef(rotZ,0.0,0.0,1.0);
		glTranslated( -posX, -posY, -posZ );

		glPushMatrix();
		glTranslated(-1, 0, -1);
		drawScene();
		glPopMatrix();

		glutSwapBuffers();
	}
	usleep(100000);
}

void ruleKeys( void )
{

    if( keyCheck[ '1' ] )	//	Select Camera Mode 1
	{
		 if( !MODE1 )
		 {
			 MODE1 = true;
			 MODE2 = false;
			 hMODE = true;
			 glutSetWindowTitle("Mode 1");
			 init();
			 glutIdleFunc(display);
		 }
	}

	if( keyCheck[ '2' ] )	//	Select Camera Mode 2
	{
		if( !MODE2 )
		{
			MODE1 = false;
			MODE2 = true;
			hMODE = false;
			glutSetWindowTitle("Mode 2");
			init();
			glutIdleFunc(display);
		}
	}

	if( keyCheck[ ' ' ] )	//	Close Current Camere Mode, Initialize, 'space' Press
	{
		if( MODE1 )
			hMODE = true;
		init();
		glutIdleFunc(display);
	}

	if( keyCheck[ 'h' ] )	//	In Mode 1, Change Camera's Current State, Stop | Turn
	{
		if( hMODE )
			hMODE = false;
		else
			hMODE = true;
	}

	if( keyCheck[ 'z' ] )	//	In Mode 1, Do Harmonic Vertical Movement
	{
        if( MODE1 )
		{
		if( flagVer && centerY <= 0.2)
		{
			centerY += slideFactor;
			flagVer  = true;
		}
		else
		{
			flagVer  = false;
			centerY -= slideFactor;
			if( centerY <= -0.2 )
				flagVer  = true;
		}
		glutPostRedisplay();
		}
	}

	if( keyCheck[ 'x' ] )	//	In Mode 1, Do Harmonic Horizontal Movement
	{
         if( MODE1 )
		 {
			if( flagHor && centerX <= 0.2)
			{
				centerX += slideFactor;
				flagHor  = true;
			}
			else
			{
				flagHor  = false;
				centerX -= slideFactor;
				if( centerX <= -0.2 )
					flagHor  = true;
			}
			glutPostRedisplay();
		 }
	} 

	if( keyCheck[ 'c' ] )		//	In Mode 1, Rotate
	{
		if( MODE1 )
		{
			angleRotate += 60.0f;
			glutPostRedisplay();
		}
	} 

	 if( keyCheck[ 'v' ] )	//	In Mode 1, Scale, Enlarge and Shrink
	 {
        if( MODE1 )
		{
			if( flagSca && zoomFactor <= 2.0 )
			{	
				zoomFactor += 0.1;
				flagSca     = true;
			}
			else
			{
				flagSca     = false;
				zoomFactor -= 0.1;
				if( zoomFactor <= 1.0 )
					flagSca     = true;
			}
			glutPostRedisplay();
		}
	 }

     if( keyCheck[ 'w' ] )	//	In Mode 2, Move Camera Forward
	 {
		if(MODE2)
		{
			float xrad, yrad;
			xrad = (rotX / 180 * 3.141592654f);
			yrad = (rotY / 180 * 3.141592654f);

			posX += float(sin(yrad)) * 0.1;
			posZ -= float(cos(yrad)) * 0.1;
			posY -= float(sin(xrad)) * 0.1;	

			glutPostRedisplay();
		}
	 }

     if( keyCheck[ 's' ] )	//	In Mode 2, Move Camera Backward
	 {
		if(MODE2)
		{
			float xrad, yrad;
			xrad = (rotX / 180 * 3.141592654f);
			yrad = (rotY / 180 * 3.141592654f);

			posX -= float(sin(yrad)) * 0.1;
			posZ += float(cos(yrad)) * 0.1;
			posY += float(sin(xrad)) * 0.1;

			glutPostRedisplay();
		}
	 }

     if( keyCheck[ 'a' ] )	//	In Mode 2, Slide Camera Left
	 {
		if(MODE2)
		{
			float yrad;
			yrad = (rotY / 180 * 3.141592654f);

			posX -= float(cos(yrad)) * 0.02;
			posZ -= float(sin(yrad)) * 0.02;

			glutPostRedisplay();
		}
	 }

     if( keyCheck[ 'd' ] )	//	In Mode 2, Slide Camera Right
	 {
		if(MODE2)
		{
			float yrad;
			yrad = (rotY / 180 * 3.141592654f);

			posX += float(cos(yrad)) * 0.02;
			posZ += float(sin(yrad)) * 0.02;

			glutPostRedisplay();
		}
	 }

     if( keyCheck[ 'r' ] )	//	In Mode 2, Rotate Up and Right Side Vector in Counter-Clokwise
	 {
        if(MODE2)
		{
		rotZ += 1.0;
		if( rotZ > 360 )
			rotZ -= 360;

		glutPostRedisplay();
		}
	 }

     if( keyCheck[ 'e' ] )	//	In Mode 2, Rotate Up and Right Side Vector in Clokwise
	 {
        if(MODE2)
		{
		rotZ -= 1.0;
		if( rotZ < -360 )
			rotZ += 360;

		glutPostRedisplay();
		}
	 }

	 if( keyCheck[ 'q' ] )	//	Quit
		exit(0);

	 if( keySpeCheck[ GLUT_KEY_UP ] )		//	In Mode 2, Rotate Up and View Vector Counter-Clokwise
	 {
		if(MODE2)
		{
			rotX -= 1.0f;
			if( rotX < -360 )
				rotX += 360;

			glutPostRedisplay();
		}
	 }

	 if( keySpeCheck[ GLUT_KEY_DOWN ] )		//	In Mode 2, Rotate Up and View Vector Clokwise
	 {
		if(MODE2)
		{
			rotX += 1.0f;
			if( rotX  > 360 )
				rotX -= 360;

			glutPostRedisplay();
		}
	 }

	 if( keySpeCheck [GLUT_KEY_RIGHT] )		//	In Mode 2, Rotate Direction and Right Side Vector in Clokwise
	 {
		if(MODE2)
		{
			rotY += 1.0f;
			if( rotY  > 360 )
				rotY -= 360;

			glutPostRedisplay();		 
		}
	 }

	 if( keySpeCheck[ GLUT_KEY_LEFT] )	//	In Mode 2, Rotate Direction and Right Side Vector in Counter-Clokwise
	 {
		if(MODE2)
		{
			rotY -= 1.0f;
			if( rotY  < -360 )
				rotY += 360;

			glutPostRedisplay();		
		}
	 }
}

void processNormalKeys( unsigned char key, int x, int y )
{
   char temp = 1;

   switch(key) 
   {
      case '1':	//	Select Camera Mode 1
		  keyCheck[ '1' ] = true;
		  break;

      case '2':	//	Select Camera Mode 2
		  keyCheck[ '2' ] = true;
          break;

	  case ' ':	//	Close Current Camere Mode, Initialize, 'space' Press
		 keyCheck[ ' ' ] = true;
         break;

      case 'h':	//	In Mode 1, Change Camera's Current State, Stop | Turn
		keyCheck[ 'h' ] = true;
        break;

      case 'z':	//	In Mode 1, Do Harmonic Vertical Movement
		 keyCheck[ 'z' ] = true;
         break;

      case 'x':	//	In Mode 1, Do Harmonic Horizontal Movement
		 keyCheck[ 'x' ] = true;
         break;	  

      case 'c':	//	In Mode 1, Rotate
		 keyCheck[ 'c' ] = true;
         break;	  

      case 'v':	//	In Mode 1, Scale, Enlarge and Shrink
		 keyCheck[ 'v' ] = true;
         break;

      case 'w':	//	In Mode 2, Move Camera Forward
		 keyCheck[ 'w' ] = true;
         break;

      case 's':	//	In Mode 2, Move Camera Backward
		 keyCheck[ 's' ] = true;
         break;

      case 'a':	//	In Mode 2, Slide Camera Left
		 keyCheck[ 'a' ] = true;
         break;

      case 'd':	//	In Mode 2, Slide Camera Right
		 keyCheck[ 'd' ] = true;		 
         break;

      case 'r':	//	In Mode 2, Rotate Up and Right Side Vector in Counter-Clokwise
		 keyCheck[ 'r' ] = true;
         break;

      case 'e':	//	In Mode 2, Rotate Up and Right Side Vector in Clokwise
		 keyCheck[ 'e' ] = true;
         break;

	  case 'q':	//	Quit
		 keyCheck[ 'q' ] = true;
		 break;

	  default:
		  temp = 0;
	}
    if( temp )
		glutPostRedisplay();
}

void processNormalKeysUP( unsigned char key, int x, int y )
{
   char temp = 1;	 
   switch(key) 
   {
      case '1':	//	Select Camera Mode 1
		  keyCheck[ '1' ] = false;
		  break;

      case '2':	//	Select Camera Mode 2
		  keyCheck[ '2' ] = false;
          break;

	  case ' ':	//	Close Current Camere Mode, Initialize, 'space' Press
		 keyCheck[ ' ' ] = false;
         break;

      case 'h':	//	In Mode 1, Change Camera's Current State, Stop | Turn
		keyCheck[ 'h' ] = false;
        break;

      case 'z':	//	In Mode 1, Do Harmonic Vertical Movement
		 keyCheck[ 'z' ] = false;
         break;

      case 'x':	//	In Mode 1, Do Harmonic Horizontal Movement
		 keyCheck[ 'x' ] = false;
         break;	  

      case 'c':	//	In Mode 1, Rotate
		 keyCheck[ 'c' ] = false;
         break;	  

      case 'v':	//	In Mode 1, Scale, Enlarge and Shrink
		 keyCheck[ 'v' ] = false;
         break;

      case 'w':	//	In Mode 2, Move Camera Forward
		 keyCheck[ 'w' ] = false;
         break;

      case 's':	//	In Mode 2, Move Camera Backward
		 keyCheck[ 's' ] = false;
         break;

      case 'a':	//	In Mode 2, Slide Camera Left
		 keyCheck[ 'a' ] = false;
         break;

      case 'd':	//	In Mode 2, Slide Camera Right
		 keyCheck[ 'd' ] = false;		 
         break;

      case 'r':	//	In Mode 2, Rotate Up and Right Side Vector in Counter-Clokwise
		 keyCheck[ 'r' ] = false;
         break;

      case 'e':	//	In Mode 2, Rotate Up and Right Side Vector in Clokwise
		 keyCheck[ 'e' ] = false;
         break;

	  case 'q':	//	Quit
		 keyCheck[ 'q' ] = false;
		 break;

	  default:
		  temp = 0;
	}
    if( temp )
	  glutPostRedisplay();
}

void processSpecialKeys( int key, int x, int y )
{
	char temp = 1;
	switch (key) 
	{
	  case GLUT_KEY_UP:		//	In Mode 2, Rotate Up and View Vector Counter-Clokwise
		 keySpeCheck[ GLUT_KEY_UP ] = true;
         break;
      case GLUT_KEY_DOWN:	//	In Mode 2, Rotate Up and View Vector Clokwise
		 keySpeCheck[ GLUT_KEY_DOWN] = true;
         break;
      case GLUT_KEY_RIGHT:	//	In Mode 2, Rotate Direction and Right Side Vector in Clokwise
		 keySpeCheck[ GLUT_KEY_RIGHT ] = true;
         break;
	  case GLUT_KEY_LEFT:	//	In Mode 2, Rotate Direction and Right Side Vector in Counter-Clokwise
		 keySpeCheck[ GLUT_KEY_LEFT ] = true;
         break;
	  default:
		 temp = 0;
	}
    if( temp )
	  glutPostRedisplay();
}

void processSpecialKeysUP( int key, int x, int y )
{
	char temp = 1;
	switch (key) 
	{
	  case GLUT_KEY_UP:		//	In Mode 2, Rotate Up and View Vector Counter-Clokwise
		 keySpeCheck[ GLUT_KEY_UP ] = false;
         break;
      case GLUT_KEY_DOWN:	//	In Mode 2, Rotate Up and View Vector Clokwise
		 keySpeCheck[ GLUT_KEY_DOWN] = false;
         break;
      case GLUT_KEY_RIGHT:	//	In Mode 2, Rotate Direction and Right Side Vector in Clokwise
		 keySpeCheck[ GLUT_KEY_RIGHT ] = false;
         break;
	  case GLUT_KEY_LEFT:	//	In Mode 2, Rotate Direction and Right Side Vector in Counter-Clokwise
		 keySpeCheck[ GLUT_KEY_LEFT ] = false;
         break;
	  default:
		 temp = 0;
	}
    if( temp )
	  glutPostRedisplay();
}

// Main Loop
int main( int argc, char** argv )
{
	fileName = argv[1];
	readInput();

	MODE1	= true;
	MODE2	= false;
	hMODE	= true;
	cMODE	= false;

	for( int i=0; i<256; i++ )
		keyCheck[ i ] = false;

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(75, 75);
	glutInitWindowSize(600, 600);
	glutCreateWindow(argv[0]);
	glutSetWindowTitle("Mode 1");
	init();

	glutDisplayFunc(display);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(processNormalKeysUP);
	glutSpecialFunc(processSpecialKeys);
	glutSpecialUpFunc(processSpecialKeysUP);

	glutMainLoop();

	return 0;
}

