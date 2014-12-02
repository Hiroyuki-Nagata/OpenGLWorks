//-------------------------------------------------------------
// File : PMDLoader.h
//
// XXXX
//
// Author : Hiroyuki Nagata
//--------------------------------------------------------------

#ifndef _PMD_LOADER_H_
#define _PMD_LOADER_H_

#include "clsPMDFile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

//
// forward declarations
//
class XFace;
class XMesh;
class XMaterial;
class XModel;

//
// XVector2 struct
//
struct XVector2
{
	float x, y; 
	operator float* () { return (float*)&x; }
	operator const float*() const { return (const float*)&x; }
};

//
// XVector3 struct
//
struct XVector3
{ 
	float x, y, z; 
	operator float*() { return (float*)&x; }
	operator const float*() const { return (const float*)&x; }
};

//
// XColor struct
//
struct XColor 
{
	float r, g, b, a; 
	operator float*() { return (float*)&r; }
	operator const float*() const { return (const float*)&r; }
};

//
// XBoundingSphere struct
//
struct XBoundingSphere
{
	XVector3 center;
	float radius;
};

//
// XBoundingBox struct
//
struct XBoundingBox
{
	XVector3 min;
	XVector3 max;
};

//
// XFace class
//
class XFace
{
public :
	int element;
	int indexMaterial;
	int indexVertices[4];
	int indexNormals[4];
	int indexTexCoords[4];
	XFace &operator = (XFace &ob);
	XFace();
	void SetVertexIndex(int index[]);
	void SetNormalIndex(int index[]);
	void SetTexCoordIndex(int index[]);
};

//
// XMaterial class
//
class XMaterial
{
public :
	char name[MAX_PATH];
	XColor ambient;
	XColor diffuse;
	XColor specular;
	XColor emissive;
	float power;
	char textureFileName[MAX_PATH];
	XMaterial &operator = (XMaterial &ob);
	XMaterial();
	void SetName(char *str);
	void SetTextureFileName(char *str);
};

//
// XMesh class
//
class XMesh
{
public :
	char name[MAX_PATH];
	int numVertices;
	int numNormals;
	int numTexCoords;
	int numFaces;
	XVector3* vertex;
	XVector3* normal;
	XVector2* texcoord;
	XFace* face;
	XMesh &operator = (XMesh &ob);
	XMesh();
	int AddVertex(XVector3 &ob);
	int AddNormal(XVector3 &ob);
	int AddTexCoord(XVector2 &ob);
	int AddFace(XFace &ob);
	void Release();
	void SetName(char *str);
};

//
// XModel class
//
class XModel
{
private:
	void ComputeBoundingSphere();
	void ComputeBoundingBox();

public:
	int numMeshes;
	int numMaterials;
	XMesh *mesh;
	XMaterial *material;
	XBoundingSphere sphere;
	XBoundingBox box;

	bool Load(const char *filename);
	void Release();
	void Render(int index, float scale=1.0f);
	void Render(float scale=1.0f);
	int AddMesh(XMesh ob);
	int AddMaterial(XMaterial ob);
	XModel();
};

/**
// Disable Warning C4996
#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif
#ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

//
// include
//
#ifdef _WIN32
   #include <windows.h>
   #include <cstdio>
   using std::sprintf;
#else
   #define __USE_POSIX          1   // needed for limits.h
   #define __USE_XOPEN2K        1
   #define __STDC_FORMAT_MACROS 1   // needed for unix formatting output
   #include <cstdio>
   #include <cstdarg>
   #include <cstring>
   #include <unistd.h>
   #include <limits.h>
   #include <errno.h>
   typedef unsigned long DWORD;
   typedef void*	 HANDLE;
#endif

//
// define
//
#ifndef _SAFE_DELETE
#define SafeDelete(x) { if (x) { delete x; x = NULL; } }
#endif
#ifndef _SAFE_DELETEARRAY
#define SafeDeleteArray(x) { if (x) { delete [] x; x = NULL; } }
#endif

*/

#endif	//Å@_PMD_LOADER_H_
