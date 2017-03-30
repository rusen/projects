#include "Parser.h"

using namespace std;

Parser::Parser() {};
void Parser :: Parsefile(const char * filename) {

		fstream filestr;
		filestr.open(filename,fstream::in);
		
		filestr>>width;
		filestr>>height;
		filestr>>tmin;
		filestr>>reflectc;
		
		int i = 0;
		
	while(!filestr.eof()) {
		cout<<i<<endl;
		i++;
		char type[256];
		filestr.getline(type,256);
		if (strcmp(type,"#Material") == 0 ) {
		
			float a1,a2,a3,d1,d2,d3,s1,s2,s3,exp,r1,r2,r3;
			filestr>>a1>>a2>>a3>>d1>>d2>>d3>>s1>>s2>>s3>>exp>>r1>>r2>>r3;
			struct Material mat;
			mat.diffuse = Vector3(d1,d2,d3);
			mat.specular = Vector3(s1,s2,s3);
			mat.ambient = Vector3(a1,a2,a3);
			mat.reflectance = Vector3(r1,r2,r3);
			mat.specexp = exp;
			materials.push_back(mat);
		}
		else if(strcmp(type,"#Camera") == 0 ) {
			
			float o1,o2,o3,g1,g2,g3,u1,u2,u3,l,r,b,t,d;
			filestr>>o1>>o2>>o3>>g1>>g2>>g3>>u1>>u2>>u3>>l>>r>>b>>t>>d;
			Camera tempcam(Vector3(o1,o2,o3),Vector3(g1,g2,g3),Vector3(u1,u2,u3),l,r,b,t,d);
			cam = tempcam;
		} 
		else if(strcmp(type,"#Triangle") == 0 ) {
			
			float x1,y1,z1,x2,y2,z2,x3,y3,z3;
			int id;
			filestr>>x1>>y1>>z1>>x2>>y2>>z2>>x3>>y3>>z3>>id; 
			shapes.push_back(new Triangle(Vector3(x1,y1,z1),Vector3(x2,y2,z2),Vector3(x3,y3,z3),materials[id]));			
		}
		else if(strcmp(type,"#Sphere") == 0 ) {
			
			float x1,y1,z1,rad;
			int id;
			filestr>>x1>>y1>>z1>>rad>>id; 
			shapes.push_back(new Sphere(Vector3(x1,y1,z1),rad,materials[id]));				
		}
		else if(strcmp(type,"#Light") == 0 ) {
			
			float x,y,z,i1,i2,i3;
			filestr>>x>>y>>z>>i1>>i2>>i3;
			lights.push_back(new Light(Vector3(x,y,z),Vector3(i1,i2,i3)));
		}
		else if(strcmp(type,"#Ambient") == 0 ) {
			float i1,i2,i3;
			filestr>>i1>>i2>>i3;
			Vector3 temp(i1,i2,i3);
			ambient = temp;
		}
		else if(strcmp(type,"#Background") == 0 ) {
			float r,g,b;
			filestr>>r>>g>>b;
			Vector3 temp(r,g,b);			
			back = temp;
		}
		

	}


}
Scene Parser :: ConstructScene(char* input){
	Image tempim(width,height);
	im = tempim;
	
	Scene s1(shapes,lights,cam,im,reflectc,ambient,back,tmin,input);
	return s1;
}

