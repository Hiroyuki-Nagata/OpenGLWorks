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
// define
//
#ifndef _SAFE_DELETE
#define SafeDelete(x) { if (x) { delete x; x = NULL; } }
#endif
#ifndef _SAFE_DELETEARRAY
#define SafeDeleteArray(x) { if (x) { delete [] x; x = NULL; } }
#endif

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
	void SetName(const char *str);
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
	void SetName(const char *str);
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

     int GetVersion();
     void SetVersion(int ver);

     const char* GetHeaderString();
     void SetHeaderString(const char* name);

     const char* GetActor();
     void SetActor(const char* name );

     int GetVertexChunkSize();
     void SetVertexChunkSize(int size);
     PMD_VERTEX_CHUNK& GetVertexChunk();

     int GetIndexChunkSize();
     void SetIndexChunkSize(int size);
     PMD_INDEX_CHUNK& GetIndexChunk();

/**

     int		GetBoneChunkSize();
     void	SetBoneChunkSize(int size);
     PMD_BONE_CHUNK& GetBoneChunk();

     int		GetIKChunkSize();
     void	SetIKChunkSize(int size);
     PMD_IK_CHUNK& GetIKChunk();
*/
     int GetMaterialChunkSize();
     void SetMaterialChunkSize(int size);
     PMD_MATERIAL_CHUNK& GetMaterialChunk();
/**
     int		GetMorpChunkSize();
     void	SetMorpChunkSize(int size);
     PMD_MORP_CHUNK& GetMorpChunk();

     int		GetCtrlChunkSize();
     void	SetCtrlChunkSize(int size);
     PMD_CTRL_CHUNK& GetCtrlChunk();

     int		GetGrpNameChunkSize();
     void	SetGrpNameChunkSize(int size);
     PMD_GRP_NAME_CHUNK& GetGrpNameChunk();

     int		GetGrpChunkSize();
     void	SetGrpChunkSize(int size);
     PMD_GRP_CHUNK& GetGrpChunk();
*/
public:
     PMD_HEADER			m_header;
     PMD_VERTEX_CHUNK		m_vertexs;
     PMD_INDEX_CHUNK		m_indexs;
     PMD_MATERIAL_CHUNK		m_materials;
/**
     PMD_BONE_CHUNK		m_bones;
     PMD_IK_CHUNK		m_ikbones;
     PMD_MORP_CHUNK		m_morps;
     PMD_CTRL_CHUNK		m_ctrls;
     PMD_GRP_NAME_CHUNK         m_grp_name;
     PMD_GRP_CHUNK		m_grp;
*/
};

#endif	//　_PMD_LOADER_H_
