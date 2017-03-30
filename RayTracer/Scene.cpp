#include "Scene.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

Scene::Scene() { }

Scene::Scene(const vector<Shape*> &s1, const vector<Light*> &l1, const Camera &c1, const Image &img, int cn, const Vector3& _ambientl, const Vector3& _backgroundcol, float _tmin,char* _name) {
	
	shapes = s1;
	lights = l1;
	cam = c1;
	im = img;
	reflectcount = cn;
	ambientl = _ambientl;
	backgroundcol = _backgroundcol;
	tmin = _tmin;
	name = (char*)malloc(sizeof(char) * 100);
	strcpy(name,_name);
}

void Scene::push_shape(Shape* s1) {

	shapes.push_back(s1);	

}
void Scene::push_light(Light* l1) {

	lights.push_back(l1);
}

void Scene::push_cam(Camera &c1) {

	cam = c1;

}

void Scene::set_image(Image &img) {

	im=img;
}

Vector3 Scene::sendRay(Ray& r,int count) {
	
	//tmax ı00000.0f
	//tmin 0.1f 
	
	HitRecord rec;
	bool is_a_hit;
	is_a_hit = false;
	HitRecord tmpRec;
	float closest = 1e16f;

	for (int k = 0; k<shapes.size();k++) {
		if(shapes[k]->intersect(r,tmin,tmpRec)){
			is_a_hit = true;
					
			if (tmpRec.t < closest)
			{
				closest = tmpRec.t;
				rec = tmpRec;
			}
		}
	}
			
	if(is_a_hit)
	{	
		//Vector3 color(20.0f,20.0f,20.0f); // Artık bu tanımlı ambient ışık olacak.
		
		Vector3 color = ambientl;
		
		color = multip(color,rec.material.ambient);
			 
		for(int litr = 0; litr<lights.size();litr++){
			
			Vector3 lvec = unitVector(lights[litr]->center - rec.point);
				
			Ray r2(rec.point,lvec);
					
			bool inShadow = false;
			for (int l = 0; l<shapes.size();l++) {
				if(shapes[l]->intersect(r2,tmin,tmpRec)){
					inShadow = true;
					break;
				}		
			}
				
			if (!inShadow)
			{
				Vector3 nvec = unitVector(rec.normal);
				Vector3 hvec = unitVector(lvec+nvec);
			
				color += multip(rec.material.diffuse,lights[litr]->color) * MAX(0,dot(nvec,lvec)) + multip(rec.material.specular,lights[litr]->color) * pow(MAX(0,dot(nvec,hvec)),rec.material.specexp) ;
			}
		}
		
		if (count) {
			Ray newRay(rec.point,-((2*dot(r.direction(),rec.normal))*rec.normal - r.direction()));
			Vector3 tempCol = sendRay(newRay,count-1);
			
			//color = multip((Vector3(1.0f,1.0f,1.0f) - rec.material.reflectance ),color)+multip((rec.material.reflectance),tempCol);
			color = color+multip((rec.material.reflectance),tempCol);
			
			
			
			
		}

		return color;
	}
			
	else{
			if (count == reflectcount)
				{Vector3 color=backgroundcol; 	return color;} // Bu background color olacak. (60.0f di)
			else
				{Vector3 color(0.0f,0.0f,0.0f); return color;}

			
	}

}

void Scene::Render() {

	int width = im.getWidth();
	int height = im.getHeight();
	
	for ( int i = 0; i<width; i++)
		{
			cout<<i<<endl;
		for( int j= 0; j<height; j++) {
			
			float i1,j1;
			
			i1 = (float)i/(float)width;
			j1 = (float)j/(float)height;
			
			Ray r = cam.getRay(i1,j1); 

			Vector3 color = sendRay(r,reflectcount);
						
				if (color.x()>255)
					color.setX(255);
				if (color.y()>255)
					color.setY(255);
				if (color.z()>255)
					color.setZ(255);									
						
			rgb cl((color.x()/255),(color.y()/255),(color.z()/255));
			
			im.set(i,j,cl);				
		
	}
		} 
		
		fstream filestr;
		
		char* outname = (char*) malloc(sizeof(char) * 150);
		
		strcpy(outname,name);
		outname[strlen(name)-3] = 0;
		strcat(outname,"ppm"); 
		
		filestr.open(outname,fstream::out);
		
		im.writePPM(filestr);					


}
