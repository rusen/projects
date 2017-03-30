#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include "parsePly.h"

/**
***************************************************************************************
* parsePlyHeader
*
* @brief
*     Reads the header of the given PLY file to extract the number of vertices
*     and triangles. For details of the format see:
*     http://paulbourke.net/dataformats/ply/.
*
* @return
*	  true if successful, false otherwise
**************************************************************************************
*/
bool parsePlyHeader(
    const char* filename,     ///< [in]  Name of the PLY file to parse
    int&        numVertices,  ///< [out] Number of vertices
    int&        numTriangles) ///< [out] Number of triangles
{
    FILE* fp = fopen(filename, "r");

    if (!fp)
    {
        return false;
    }

    char* line = NULL;
    size_t n = 0;
    int number;
    bool numVerticesFound = false, numTrianglesFound = false;

    // Read the file until we find "end_header" and extract
    // the number of vertices and number of triangles.

    while (1) 
    {
        if (getline(&line, &n, fp) < 0)
        {
            break;
        }

        if (!strncmp(line, "end_header", strlen("end_header")))
        {
            break;
        }

        if (sscanf(line, "element vertex %d", &number) == 1)
        {
            numVertices = number;
            numVerticesFound = true;
        }
        else if (sscanf(line, "element face %d", &number) == 1)
        {
            numTriangles = number;
            numTrianglesFound = true;
        }

        // Free the allocation made by "getline".

        assert(line);
        free(line);
        line = NULL;
    }

    if (line)
    {
        free(line);
    }

    fclose(fp);

    if (!numVerticesFound || !numTrianglesFound)
    {
        return false;
    }

    return true;
}

/**
***************************************************************************************
* parsePly
*
* @brief
*     Extracts the triangles from the given PLY file into a triangle struct. The
*     triangles array should be allocated by the caller.
*
* @return
*	  true if successful, false otherwise
**************************************************************************************
*/
bool parsePly(
    const char*      filename,     ///< [in]  Name of the PLY file
    int              numVertices,  ///< [in]  Number of vertices
    int              numTriangles, ///< [in]  Number of triangles
    struct Triangle* triangles)    ///< [out] An array of trianles
{
    if (!triangles)
    {
        // This should be allocated by the caller.

        return false;
    }

    FILE* fp = fopen(filename, "r");

    if (!fp)
    {
        return false;
    }

    char* line = NULL;
    size_t n = 0;
    bool endHeaderFound = false;

    // Consume the file till the end of "end_header". This will 
    // be followed by the vertex data and then the triangle indices.

    while (1) 
    {
        if (getline(&line, &n, fp) < 0)
        {
            break;
        }

        if (!strncmp(line, "end_header", strlen("end_header")))
        {
            endHeaderFound = true;
         //   printf("Geldim\n");
            break;
        }
    }

    if (!endHeaderFound)
    {
        return false;
    }

    // First, read off the vertex data.

    struct Vertex* vertices = new Vertex [numVertices];

    if (!vertices)
    {
        return false;
    }

    for (int i = 0; i < numVertices; ++i)
    {
	float intensity,confidence;
        fscanf(fp, "%f %f %f %f %f", &vertices[i].x, &vertices[i].y, &vertices[i].z, &intensity ,&confidence);
       //  printf("%lf %lf %lf \n",vertices[i].x,vertices[i].y,vertices[i].z);
    }

    // Then, construct the triangles using the given indices
    // and the vertex data we read above.

	//printf("Geldim\n");
    int tmp, indexA, indexB, indexC;
    for (int i = 0; i < numTriangles; ++i)
    {
        // Ignore the first element, which always indicates the number
        // of indices that follow. It will always be 3 in our case.
        //printf("%d\n",i);
        fscanf(fp, "%d %d %d %d ", &tmp, &indexA, &indexB, &indexC);
		// printf("%d %d %d %d \n",tmp,indexA,indexB,indexC);
        memcpy(&(triangles[i].a), &(vertices[indexA]), sizeof(struct Vertex));
        memcpy(&(triangles[i].b), &(vertices[indexB]), sizeof(struct Vertex));
        memcpy(&(triangles[i].c), &(vertices[indexC]), sizeof(struct Vertex));
    }

    delete[] vertices;

    fclose(fp);
}
