#include "parsePly.h"
#include <cstdio>
int main(int argc, char* argv[])
{
    const char* filename = argv[1];

    int numVertices, numTriangles;

    parsePlyHeader(filename, numVertices, numTriangles);

   // printf("numVertices = %d numTriangles = %d\n", numVertices, numTriangles);

    struct Triangle* triangles = new Triangle [numTriangles];

    parsePly(filename, numVertices, numTriangles, triangles);

   for(int i= 0; i<numTriangles; i++ ) {
    printf("#Triangle\n");
    printf("%.3f %.3f %.3f ", triangles[i].a.x, triangles[i].a.y,  triangles[i].a.z);
    printf("%.3f %.3f %.3f ", triangles[i].b.x, triangles[i].b.y,  triangles[i].b.z);
    printf("%.3f %.3f %.3f 1\n", triangles[i].c.x, triangles[i].c.y,  triangles[i].c.z);
}
    delete[] triangles;

    return 0;
} 
