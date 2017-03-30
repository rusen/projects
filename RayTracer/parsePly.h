#ifndef __PARSEPLY_H__
#define __PARSEPLY_H__

/**
***************************************************************************************
* Vertex
*
* @brief
*	  A simple vertex struct with three coordinates.
**************************************************************************************
*/
struct Vertex
{
    float x;
    float y;
    float z;
};

/**
***************************************************************************************
* Triangle
*
* @brief
*	  A simple triangle struct with three vertices.
**************************************************************************************
*/
struct Triangle
{
    Vertex a;
    Vertex b;
    Vertex c;
};

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
    const char* filename,      ///< [in]  Name of the PLY file to parse
    int&        numVertices,   ///< [out] Number of vertices
    int&        numTriangles); ///< [out] Number of triangles

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
    struct Triangle* triangles);   ///< [out] An array of trianles

#endif // __PARSEPLY_H__
