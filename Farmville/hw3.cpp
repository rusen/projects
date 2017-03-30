//1560333 Ali Karakaya
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include "BMPLoader.h"

#define PI 3.14151
#define WIDTH  800
#define HEIGHT 800

#define wid 420
#define heg 240
#define len 420


using namespace std;

bool multiple[6]={false};
bool globalLight=true;
typedef struct img
{
	GLuint texture;
	int listLight;
	int listOr;
}imgs;

int list2;
int CameraMode,CameraPos;
float Xcoor,Ycoor,Zcoor,Angle;
imgs *images;
int external[12][4]={
	{1,40,1,120},
	{1,160,1,240},
	{1,280,1,360},
	{40,1,120,1},
	{160,1,240,1},
	{280,1,360,1},
	{419,40,419,120},
	{419,160,419,240},
	{419,280,419,360},
	{40,419,120,419},
	{160,419,240,419},
	{280,419,360,419}
};

int lightFrame[12][2]={
	{410,80},
	{410,200},
	{410,320},
	{80,410},
	{200,410},
	{320,410},
	{10,80},
	{10,200},
	{10,320},
	{80,10},
	{200,10},
	{320,10}
};

void initGL()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_SMOOTH);
	
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glClearDepth(1.0f);
    
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 10000);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}

void initiateRoom()
{
	glPushMatrix();
	if(CameraMode==0)
	{
		switch(CameraPos) {
		case 0:
			gluLookAt(0,len/2.0,heg,wid,len/2.0,0,0,0,1);
			break;
		case 1:
			gluLookAt(0,0,heg,wid,len,0,0,0,1);
			break;
		case 2:
			gluLookAt(wid/2.0,0,heg,wid/2.0,len,0,0,0,1);
			break;
		case 3:
			gluLookAt(wid,0,heg,0,len,0,0,0,1);
			break;
		case 4:
			gluLookAt(wid,len/2.0,heg,0,len/2.0,0,0,0,1);
			break;
		case 5:
			gluLookAt(wid,len,heg,0,0,0,0,0,1);
			break;
		case 6:
			gluLookAt(wid/2.0,len,heg,wid/2.0,0,0,0,0,1);
			break;
		case 7:
			gluLookAt(0,len,heg,wid,0,0,0,0,1);
			break;
		}
	}
	else
		gluLookAt(Xcoor,Ycoor,120,Xcoor+10*cos(Angle*PI/180),Ycoor+10*sin(Angle*PI/180),Zcoor,0,0,1);
	
	if (globalLight) {
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		GLfloat position[] = { -500.0, 500.0, 500.0, 0.0 }; 
		GLfloat blackColor[] = { 0.0, 0.0, 0.0, 1.0 }; 
		GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 1.0 }; 
		glLightfv(GL_LIGHT0, GL_POSITION, position); 
		glLightfv(GL_LIGHT0, GL_AMBIENT, blackColor); 
		glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
		glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}
	
	for(int i=0;i<12;i++)
	{
	glPushMatrix();
	if(!globalLight)
		glCallList(images[i].listLight);
	else 
		glCallList(images[i].listOr);
	glPopMatrix();
	}
	glCallList(list2);
	
	glBegin(GL_QUADS);
		glColor3f(238/255.0,169/255.0,184/255.0);

		glVertex3f(0.0,0.0,0.0);
		glVertex3f(wid,0.0,0.0);
		glVertex3f(wid,len,0.0);
		glVertex3f(0.0,len,0.0);

		glColor3f(138/255.0,43/255.0,226/255.0);

		glVertex3f(0.0,0.0,heg);
		glVertex3f(wid,0.0,heg);
		glVertex3f(wid,len,heg);
		glVertex3f(0.0,len,heg);

		glColor3f(124/255.0,252/255.0,0/255.0);

		glVertex3f(wid,0.0,0.0);
		glVertex3f(wid,len,0.0);
		glVertex3f(wid,len,heg);
		glVertex3f(wid,0.0,heg);

		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,len,0.0);
		glVertex3f(0.0,len,heg);
		glVertex3f(0.0,0.0,heg);

		glColor3f(205/255.0,201/255.0,165/255.0);

		glVertex3f(0.0,len,0.0);
		glVertex3f(wid,len,0.0);
		glVertex3f(wid,len,heg);
		glVertex3f(0.0,len,heg);

		glVertex3f(0.0,0.0,0.0);
		glVertex3f(wid,0.0,0.0);
		glVertex3f(wid,0.0,heg);
		glVertex3f(0.0,0.0,heg);

	glEnd();
	glPopMatrix();
}

void DISPLAY (void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	initiateRoom();
	glutSwapBuffers();
	glPopMatrix();
	
}

void pushImages(int id,string file,int cer[],int lfr[])
{
	BMPClass bmpLoader;
	BMPLoad(file,bmpLoader);

	glGenTextures(1, &images[id].texture);
    glBindTexture( GL_TEXTURE_2D, images[id].texture );

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );	
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );	
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, true ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, true ? GL_REPEAT : GL_CLAMP );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, bmpLoader.width, bmpLoader.height, GL_RGB, GL_UNSIGNED_BYTE, bmpLoader.bytes);
    
    images[id].listOr = glGenLists(1);
    glNewList(images[id].listOr,GL_COMPILE);
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, images[id].texture);
	
	glBegin(GL_QUADS);
		glColor3f(255/255.0,0/255.0,0/255.0);
		if(cer[0]==1)
		{
		glVertex3f(cer[0]-0.5,cer[1]-10,80.0f);
		glVertex3f(cer[2]-0.5,cer[3]+10,80.0f);
		glVertex3f(cer[2]-0.5,cer[3]+10,160.0f);
		glVertex3f(cer[0]-0.5,cer[1]-10,160.0f);
		}
		else if(cer[0]==419)
		{
		glVertex3f(cer[0]+0.5,cer[1]-10,80.0f);
		glVertex3f(cer[2]+0.5,cer[3]+10,80.0f);
		glVertex3f(cer[2]+0.5,cer[3]+10,160.0f);
		glVertex3f(cer[0]+0.5,cer[1]-10,160.0f);
		}
		else if(cer[1]==1)
		{
		glVertex3f(cer[0]-10,cer[1]-0.5,80.0f);
		glVertex3f(cer[2]+10,cer[3]-0.5,80.0f);
		glVertex3f(cer[2]+10,cer[3]-0.5,160.0f);
		glVertex3f(cer[0]-10,cer[1]-0.5,160.0f);	
		}
		else if(cer[1]==419)
		{
		glVertex3f(cer[0]-10,cer[1]+0.5,80.0f);
		glVertex3f(cer[2]+10,cer[3]+0.5,80.0f);
		glVertex3f(cer[2]+10,cer[3]+0.5,160.0f);
		glVertex3f(cer[0]-10,cer[1]+0.5,160.0f);	
		}
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(1.0f,1.0f,1.0f);
		glTexCoord3d(0.0,0.0,0.0); glVertex3f(cer[0],cer[1],90.0f);
		glTexCoord3d(1.0,0.0,0.0); glVertex3f(cer[2],cer[3],90.0f);
		glTexCoord3d(1.0,1.0,0.0); glVertex3f(cer[2],cer[3],150.0f);
		glTexCoord3d(0.0,1.0,0.0); glVertex3f(cer[0],cer[1],150.0f);
	glEnd();
	
	int angle;
	if(id<3)
		angle=90;
	else if(id<6)
		angle=180;
	else if(id<9)
		angle=270;
	else
		angle=0;
	glDisable(GL_TEXTURE_2D);
    glEndList();
    
    images[id].listLight = glGenLists(1);
    glNewList(images[id].listLight,GL_COMPILE);
    glPushMatrix();
    glTranslatef(lfr[0],lfr[1],0);
    glRotatef(angle,0,0,1);
	glEnable(GL_LIGHT1);
	GLfloat position[] = {0.0f,-20.0f,120,1.0};
	GLfloat direction[] = {0.0,1.0,0.0};
	GLfloat blackColor[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteColor);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,direction);
	glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,75.0);
	glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,3);
	glPopMatrix();
	
    glCallList(images[id].listOr);
    glDisable(GL_LIGHT1);
    glEndList();

}

void KEYBOARD_SPECIAL(int key, int x, int y) { 
	switch (key) {
	case GLUT_KEY_UP:
		multiple[2]=true;
		
		break;
	case GLUT_KEY_DOWN:
		multiple[3]=true;
		
		break;
	case GLUT_KEY_LEFT:
		multiple[0]=true;
		break;
	case GLUT_KEY_RIGHT:
		multiple[1]=true;
		break;
	}
	if(Xcoor>=410) Xcoor=410;
	if(Ycoor>=410) Ycoor=410;
	if(Xcoor<=10) Xcoor=10;
	if(Ycoor<=10) Ycoor=10;
	glutPostRedisplay();
}

void Room2(const char *st)
{
	int counter=0;
	Xcoor=211;
	Ycoor=50;
	Zcoor=120;
	images=(imgs *)malloc(sizeof(img)*13);


		pushImages(counter++,"paintings/davinci.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/lastsupper.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/john.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/painting2.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/picasso1.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/barney-stinson.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/zar.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/kedi.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/erol.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/fener.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/sabri.bmp",external[counter],lightFrame[counter]);
		pushImages(counter++,"paintings/ayi.bmp",external[counter],lightFrame[counter]);
}

void KEYBOARD_NORMAL(unsigned char key, int x, int y) {
	switch(key){
		case 'w' :
		case 'W' :
			multiple[4]=true;
		break;
		case 's' :
		case 'S' :
			multiple[5]=true;
		break;
		case 'l' :
		case 'L' :
		case 'I' :
		case 'i' :
		if(globalLight)
		globalLight=false;
		else
		globalLight=true;
		break;
		case 'q' :
		case 'Q' :
			exit(-1);
		break;
		case '1':
			if(CameraMode==0)
				CameraPos=(CameraPos+1)%8;
			else CameraMode=0;
		break;
		case '2':
			CameraMode=1;
		break;
	}
	glutPostRedisplay();
}

void KEYBOARD_SPECIAL_UP(int key, int x, int y) 
{
	
	if(key==GLUT_KEY_RIGHT)
	{
			multiple[1]=false;
	}
	if(key==GLUT_KEY_LEFT)
	{
			multiple[0]=false;
	}
	if(key==GLUT_KEY_UP)
	{
			multiple[2]=false;
	}
	if(key==GLUT_KEY_DOWN)
	{
			multiple[3]=false;
	}
}

void timer(int value) 
{	
	if(multiple[0])
	{
		Angle++;
		if(Angle>=360) Angle-=360;
	}
	if(multiple[1])
	{
		Angle--;
		if(Angle<0) Angle+=360;
	}
	if(multiple[2])
	{
		Xcoor+=cos(Angle*PI/180);	
		Ycoor+=sin(Angle*PI/180);
	}
	if(multiple[3])
	{
		Xcoor-=cos(Angle*PI/180);
		Ycoor-=sin(Angle*PI/180);
	}
	if(multiple[4])
	{
		Zcoor++;
		if(Zcoor>200) Zcoor=200;
	}
	if(multiple[5])
	{
		Zcoor--;
		if(Zcoor<10) Zcoor=10;
	}
	glutPostRedisplay();
	glutTimerFunc(50,timer,50);
}

void KEYBOARD_NORMAL_UP(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w':
		case 'W':
			multiple[4]=false;
		break;
		case 's':
		case 'S':
			multiple[5]=false;
		break;
	}
}

void Art(const char* filename)
{
	FILE *heightmapFile = fopen(filename, "r");
	char key;
    int r, g, b;
	int n,m;
	int dummy;
	int s,t;
    fscanf(heightmapFile, "%c%c", &key, &key);
    fscanf(heightmapFile, "%d%d", &n, &m);
    fscanf(heightmapFile, "%d", &dummy);

	float average;

	int **HMap = (int**)malloc(sizeof(int *)*n);
	
	for(int i=0;i<n;i++) 
	{
		HMap[i] = (int *)malloc(sizeof(int)*m);
		for(int j=0;j<n;j++) 
		{
			fscanf(heightmapFile,"%d%d%d",&r,&g,&b);
			average=(r+g+b)/3.0;
			HMap[i][j]=100*(average/255.0);
		}
	}
	
	list2 = glGenLists(1);
	glNewList(list2,GL_COMPILE);
	glColor3f(113/255.0,198/255.0,113/255.0);
	glPushMatrix();
	glTranslatef((wid-m)/2,(len-n)/2,1);
	for(int i=0;i<m;i++) 
	{
		s=m-1;
		for(int j=0;j<n;j++)
		{
			t=n-1;
			if(i!=s)
			{
				if(j!=t)
				{
				glBegin(GL_TRIANGLES);

				glVertex3f(i,j,HMap[i][j]);
				glVertex3f(i,j+1,HMap[i][j+1]);
				glVertex3f(i+1,j+1,HMap[i+1][j+1]);

				glVertex3f(i,j,HMap[i][j]);
				glVertex3f(i+1,j,HMap[i+1][j]);
				glVertex3f(i+1,j+1,HMap[i+1][j+1]);
				
				glVertex3f(i,j,HMap[i][j]);
				glVertex3f(i+1,j,HMap[i+1][j]);
				glVertex3f(i,j+1,HMap[i][j+1]);
				
				glEnd();
				}
			}
		}
	}
	glPopMatrix();
	glEndList();
}

int main(int argc, char** argv)
{
	CameraMode=0;
	CameraPos=1;
	Angle=90;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("Ceng477 Fall 2010 - HW3 [e1560333]");	
	Room2(argv[1]);
	initGL();
	Art(argv[1]);
	
	glutDisplayFunc(DISPLAY);
	glutKeyboardFunc(KEYBOARD_NORMAL);
	glutKeyboardUpFunc(KEYBOARD_NORMAL_UP);
	glutSpecialFunc(KEYBOARD_SPECIAL);
	glutSpecialUpFunc(KEYBOARD_SPECIAL_UP);
	timer(50);

	glutMainLoop();
	return 0;
}
