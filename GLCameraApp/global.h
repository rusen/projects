#ifndef GLOBAL_H
#define	GLOBAL_H

#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

typedef struct vector_t
{
	float x,y,z;
} vector_t;

typedef struct triangle_t
{
	vector_t vertex[3];
} triangle_t;

string fileName;

bool MODE1, MODE2;
bool hMODE, cMODE;

bool flagVer = true;
bool flagHor = true;
bool flagSca = true;

float posX, posY, posZ;
float centerX, centerY, centerZ;
float upX, upY, upZ;
float rotX, rotY, rotZ;

float angleCam		= 0.0f;
float angleRotate	= 0.0f;
float fraction		= 0.01f;
float zoomFactor	= 1.5f;
float slideFactor	= 0.02f;

bool keyCheck[256];
bool keySpeCheck[256];

vector<triangle_t> triangles;
vector_t *normalArray = NULL;

#endif
