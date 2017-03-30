#include <iostream>
#include <fstream>

using namespace std;
int main() {
		fstream filestr1;
		fstream filestr2;
		filestr1.open("venusm.txt",fstream::in);
		filestr2.open("venusmscene.txt",fstream::out);
		
		while(!filestr1.eof()) 
			{		
			char type1[256];
			char type2[256];
			char type3[256];
			filestr1.getline(type1,256);
			filestr1.getline(type2,256);
			filestr1.getline(type3,256);						
			filestr2<<"#Triangle"<<endl;
			filestr2<<type1<<" "<<type2<<" "<<type3<<" 1"<<endl;				
			}
}
