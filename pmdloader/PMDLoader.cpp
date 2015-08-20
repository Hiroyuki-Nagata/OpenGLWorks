#include "PMDLoader.h"

////////////////////////////////////////////////////////////////////////
// XFace class
////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Name : XFace()
// Desc : コンストラクタ
//-------------------------------------------------------------------------------------------------
XFace::XFace()
{
	element = 0;
	indexMaterial = -1;
	for(int i=0; i<4; i++ )
	{
		indexVertices[i] = -1;
		indexNormals[i] = -1;
		indexTexCoords[i] = -1;
	}
}

//--------------------------------------------------------------------------------------------------
// operator =
//--------------------------------------------------------------------------------------------------
XFace& XFace::operator =(XFace &ob)
{
	element = ob.element;
	indexMaterial = ob.indexMaterial;
	for(int i=0; i<4; i++ )
	{
		indexVertices[i] = ob.indexVertices[i];
		indexNormals[i] = ob.indexNormals[i];
		indexTexCoords[i] = ob.indexTexCoords[i];
	}
	return (*this);
}

//--------------------------------------------------------------------------------------------------
// Name : SetVertexIndex()
// Desc : 頂点インデックスをセットする
//--------------------------------------------------------------------------------------------------
void XFace::SetVertexIndex(int index[])
{
	for ( int i=0; i<4; i++ ) indexVertices[i] = index[i];
}

//--------------------------------------------------------------------------------------------------
// Name : SetNormalIndex()
// Desc : 法線インデックスをセットする
//--------------------------------------------------------------------------------------------------
void XFace::SetNormalIndex(int index[])
{
	for ( int i=0; i<4; i++ ) indexNormals[i] = index[i];
}

//--------------------------------------------------------------------------------------------------
// Name : SetTexCoordIndex()
// Desc : テクスチャ座標インデックスをセットする
//--------------------------------------------------------------------------------------------------
void XFace::SetTexCoordIndex(int index[])
{
	for ( int i=0; i<4; i++ ) indexTexCoords[i] = index[i];
}

////////////////////////////////////////////////////////////////////////
// XMaterial class
////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------
// Name : XMaterial()
// Desc : コンストラクタ
//--------------------------------------------------------------------------------------------------
XMaterial::XMaterial()
{
	strcpy(name, "null");
	ambient.r = 0.0f;	ambient.g = 0.0f;	ambient.b = 0.0f;	ambient.a = 0.0f;
	diffuse.r = 0.0f;	diffuse.g = 0.0f;	diffuse.b = 0.0f;	diffuse.a = 0.0f;
	specular.r = 0.0f;	specular.g = 0.0f;	specular.b = 0.0f;	specular.a = 0.0f;
	emissive.r = 0.0f;	emissive.g = 0.0f;	emissive.g = 0.0f;	emissive.a = 0.0f;
	power = 0.0f;
	strcpy(textureFileName, "null");
}

//--------------------------------------------------------------------------------------------------
// operator =
//--------------------------------------------------------------------------------------------------
XMaterial& XMaterial::operator =(XMaterial &ob)
{
	strcpy(name, ob.name);
	ambient = ob.ambient;
	diffuse = ob.diffuse;
	specular = ob.specular;
	emissive = ob.emissive;
	power = ob.power;
	strcpy(textureFileName, ob.textureFileName);
	return (*this);
}

//--------------------------------------------------------------------------------------------------
// Name : SetName()
// Desc : 名前をセットする
//--------------------------------------------------------------------------------------------------
void XMaterial::SetName(const char *str)
{
	strcpy(name, str);
}

//--------------------------------------------------------------------------------------------------
// Name : SetTextureFileName()
// Desc : テクスチャファイル名をセットする
//--------------------------------------------------------------------------------------------------
void XMaterial::SetTextureFileName(char *str)
{
	strcpy(textureFileName, str);
}

////////////////////////////////////////////////////////////////////////
// XMesh class
////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------
// Name : XMesh()
// Desc : コンストラクタ
//---------------------------------------------------------------------------------------------------
XMesh::XMesh()
{
	strcpy(name, "null");
	numVertices = 0;
	numNormals = 0;
	numTexCoords = 0;
	numFaces = 0;
	vertex = (XVector3*)malloc(1*sizeof(XVector3));
	normal = (XVector3*)malloc(1*sizeof(XVector3));
	texcoord = (XVector2*)malloc(1*sizeof(XVector2));
	face = (XFace*)malloc(1*sizeof(XFace));
}

//--------------------------------------------------------------------------------------------------
// operator =
//--------------------------------------------------------------------------------------------------
XMesh& XMesh::operator= (XMesh &ob)
{
	strcpy(name, ob.name);
	numVertices = ob.numVertices;
	numNormals = ob.numNormals;
	numTexCoords = ob.numTexCoords;
	numFaces = ob.numFaces;

	vertex = (XVector3*)malloc(numVertices*sizeof(XVector3));
	normal = (XVector3*)malloc(numNormals*sizeof(XVector3));
	texcoord = (XVector2*)malloc(numTexCoords*sizeof(XVector2));
	face = (XFace*)malloc(numFaces*sizeof(XFace));

	for(int i=0; i<numVertices; i++ )		vertex[i] = ob.vertex[i];
	for(int i=0; i<numNormals; i++ )		normal[i] = ob.normal[i];
	for(int i=0; i<numTexCoords; i++)		texcoord[i] = ob.texcoord[i];
	for(int i=0; i<numFaces; i++ )		face[i] = ob.face[i];
	
	return (*this);
}

//--------------------------------------------------------------------------------------------------
// Name : AddVertex()
// Desc : 頂点を追加する
//--------------------------------------------------------------------------------------------------
int XMesh::AddVertex(XVector3 &ob)
{
	numVertices++;
	vertex = (XVector3*)realloc(vertex, numVertices*sizeof(XVector3));
	vertex[numVertices-1] = ob;
	return numVertices;
}

//--------------------------------------------------------------------------------------------------
// Name : AddNormal()
// Desc : 法線を追加する
//--------------------------------------------------------------------------------------------------
int XMesh::AddNormal(XVector3 &ob)
{
	numNormals++;
	normal = (XVector3*)realloc(normal, numNormals*sizeof(XVector3));
	normal[numNormals-1] = ob;
	return numNormals;
}

//--------------------------------------------------------------------------------------------------
// Name : AddTexCoord()
// Desc : テクスチャ座標を追加する
//--------------------------------------------------------------------------------------------------
int XMesh::AddTexCoord(XVector2 &ob)
{
	numTexCoords++;
	texcoord = (XVector2*)realloc(texcoord, numTexCoords*sizeof(XVector2));
	texcoord[numTexCoords-1] = ob;
	return numTexCoords;
}

//--------------------------------------------------------------------------------------------------
// Name : AddFace()
// Desc : 面を追加する
//--------------------------------------------------------------------------------------------------
int XMesh::AddFace(XFace &ob)
{
	numFaces++;
	face = (XFace*)realloc(face, numFaces*sizeof(XFace));
	face[numFaces-1] = ob;
	return numFaces;
}

//--------------------------------------------------------------------------------------------------
// Name : Release()
// Desc : 確保したメモリを解放する
//--------------------------------------------------------------------------------------------------
void XMesh::Release()
{
	if ( vertex )
	{
		free((XVector3*)vertex);
		vertex = NULL;
	}

	if ( normal )
	{
		free((XVector3*)normal);
		normal = NULL;
	}

	if ( texcoord )
	{
		free((XVector2*)texcoord);
		texcoord = NULL;
	}

	if ( face )
	{
		free((XFace*)face);
		face = NULL;
	}

	numVertices = 0;
	numNormals = 0;
	numTexCoords = 0;
	numFaces = 0;
}

//---------------------------------------------------------------------------------------------------
// Name : SetName()
// Desc : 名前をセットする
//---------------------------------------------------------------------------------------------------
void XMesh::SetName(const char *str)
{
	strcpy(name, str);
}

////////////////////////////////////////////////////////////////////////
// XModel class
////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------
// Name : XModel()
// Desc : コンストラクタ
//---------------------------------------------------------------------------------------------------
XModel::XModel()
{
	numMeshes = 0;
	numMaterials = 0;
	mesh = (XMesh*)malloc(1*sizeof(XMesh));
	material = (XMaterial*)malloc(1*sizeof(XMaterial));
}

//--------------------------------------------------------------------------------------------------
// Name : AddMesh()
// Desc : メッシュを追加する
//--------------------------------------------------------------------------------------------------
int XModel::AddMesh(XMesh ob)
{
	numMeshes++;
	mesh = (XMesh*)realloc(mesh, numMeshes*sizeof(XMesh));
	mesh[numMeshes-1] = ob;
	return numMeshes;
}

//--------------------------------------------------------------------------------------------------
// Name : AddMaterial()
// Desc : マテリアルを追加する
//--------------------------------------------------------------------------------------------------
int XModel::AddMaterial(XMaterial ob)
{
	numMaterials++;
	material = (XMaterial*)realloc(material, numMaterials*sizeof(XMaterial));
	material[numMaterials-1] = ob;
	return numMaterials;
}

//--------------------------------------------------------------------------------------------------
// Name : Release()
// Desc : 確保したメモリを解放する
//--------------------------------------------------------------------------------------------------
void XModel::Release()
{
	if ( material )
	{
		free((XMaterial*)material);
		material = NULL;
	}
	if ( mesh )
	{
		free((XMesh*)mesh);
		mesh = NULL;
	}
	numMaterials = 0;
	numMeshes = 0;
}

//--------------------------------------------------------------------------------------------------
// Name : ComputeBoundingSphere()
// Desc : バウンディングスフィアを計算する
//--------------------------------------------------------------------------------------------------
void XModel::ComputeBoundingSphere()
{
	int count = 0;
	float tempRadius = 0.0f;
	XVector3 tempCenter;
	tempCenter.x = 0.0f;
	tempCenter.y = 0.0f;
	tempCenter.z = 0.0f;

	//　中心座標の算出
	for ( int i=0; i<numMeshes; i++ )
	{
		for ( int j=0; j<mesh[i].numVertices; j++ )
		{
			tempCenter.x += mesh[i].vertex[j].x;
			tempCenter.y += mesh[i].vertex[j].y;
			tempCenter.z += mesh[i].vertex[j].z;
			count++;
		}
	}
	tempCenter.x /= (float)count;
	tempCenter.y /= (float)count;
	tempCenter.z /= (float)count;

	//　半径の算出
	for (int i=0; i<numMeshes; i++ )
	{
		for ( int j=0; j<mesh[i].numVertices; j++ )
		{
			float d = 0.0f;
			XVector3 temp;
			temp.x = mesh[i].vertex[j].x - tempCenter.x;
			temp.y = mesh[i].vertex[j].y - tempCenter.y;
			temp.z = mesh[i].vertex[j].z - tempCenter.z;
			d = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
			tempRadius = (tempRadius < d ) ? d : tempRadius;
		}
	}

	//　結果を格納
	sphere.center = tempCenter;
	sphere.radius = tempRadius;
}

//--------------------------------------------------------------------------------------------------
// Name : ComputeBoundingBox()
// Desc : バウンディングボックスを計算する
//--------------------------------------------------------------------------------------------------
void XModel::ComputeBoundingBox()
{
	XVector3 tempMin, tempMax;

	//　最初の頂点で初期化
	tempMin = tempMax = mesh[0].vertex[0];

	for ( int i=0; i<numMeshes; i++ )
	{
		for ( int j=0; j<mesh[i].numVertices; j++ )
		{
			//　x成分
			if ( tempMin.x > mesh[i].vertex[j].x ) tempMin.x = mesh[i].vertex[j].x;
			if ( tempMax.x < mesh[i].vertex[j].x ) tempMax.x = mesh[i].vertex[j].x;

			//　y成分
			if ( tempMin.y > mesh[i].vertex[j].y ) tempMin.y = mesh[i].vertex[j].y;
			if ( tempMax.y < mesh[i].vertex[j].y ) tempMax.y = mesh[i].vertex[j].y;

			//　z成分
			if ( tempMin.z > mesh[i].vertex[j].z ) tempMin.z = mesh[i].vertex[j].z;
			if ( tempMax.z < mesh[i].vertex[j].z ) tempMax.z = mesh[i].vertex[j].z;
		}
	}

	//　結果を格納
	box.min = tempMin;
	box.max = tempMax;
}

//--------------------------------------------------------------------------------------------------
// Name : Load()
// Desc : バイナリフォーマットのPMDファイルをロードする
//--------------------------------------------------------------------------------------------------
bool XModel::Load(const char *filename)
{
     BYTE   size_b;
     WORD   size_w;
     size_t size;
     std::fstream fs;

#ifdef _WIN32
     fs.open( filename,std::ios::in | std::ios::binary,_SH_SECURE );
#else
     fs.open( filename,std::ios::in | std::ios::binary);
#endif
     if ( fs.bad() || fs.fail() )
	  return false;

     // ヘッダの読み込み
     fs.read( (char*)&m_header,sizeof(m_header) );

     // 頂点リスト
     fs.read( (char*)&size,sizeof(size) );
     SetVertexChunkSize(size);
     if ( size )
	  fs.read( (char*)&GetVertexChunk()[0],size*sizeof(PMD_VERTEX_RECORD) );

     // 面頂点リスト
     fs.read( (char*)&size,sizeof(size) );
     SetIndexChunkSize(size);
     if ( size )
	  fs.read( (char*)&GetIndexChunk()[0],size*sizeof(WORD) );

     // 材質リスト
     fs.read( (char*)&size,sizeof(size) );
     SetMaterialChunkSize(size);
     if ( size )
	  fs.read( (char*)&GetMaterialChunk()[0],size*sizeof(PMD_MATERIAL_RECORD) );

     // clsPMDFile -> XModel
     XFace* tempFace;
     XMesh tempMesh;

     // モデル名
     tempMesh.SetName(GetActor());

     // 頂点リスト
     for( int i = 0; i < m_vertexs.size(); i++ )
     {
	  //　コンテナから頂点データを取得
	  XVector3 tempVertex;
	  tempVertex.x = m_vertexs.at(i).x;
	  tempVertex.y = m_vertexs.at(i).y;
	  tempVertex.z = m_vertexs.at(i).z;
	  // コンテナから法線データを取得
	  XVector3 tempNormal;
	  tempNormal.x = m_vertexs.at(i).nx;
	  tempNormal.y = m_vertexs.at(i).ny;
	  tempNormal.z = m_vertexs.at(i).nz;
	  //　コンテナからテクスチャ座標データを取得
	  XVector2 tempUV;
	  tempUV.x = m_vertexs.at(i).tx;
	  tempUV.y = m_vertexs.at(i).ty;

	  //　頂点データを追加
	  tempMesh.AddVertex(tempVertex);
	  //　法線データを追加
	  tempMesh.AddNormal(tempNormal);
	  //　テクスチャ座標データを追加
	  tempMesh.AddTexCoord(tempUV);
     }

     //　頂点数をチェック
     if ( tempMesh.numVertices != m_vertexs.size() )
     {
	  std::cout << "[Error] : 頂点数が一致していません\n";
	  return false;
     }
     else
     {
	  std::cout << "[Info] : 頂点数" << tempMesh.numVertices <<  "\n";
     }

     // 面数
     const int faceCount = m_indexs.size();
     std::cout << "[Info] : 面数" << faceCount <<  "\n";

     tempFace = new XFace[faceCount];

     for( int i = 0; i < m_vertexs.size(); i++ )
     {
	  int tempIndex[4] = { -1, -1, -1, -1 };
	  tempFace[i].element = 0;
	  tempFace[i].indexMaterial = -1;
			
	  //　要素数は3にする
	  tempFace[i].element = 3;

	  //　コンテナから頂点インデックスを取得
	  tempIndex[0] = m_vertexs.at(i).x;
	  tempIndex[1] = m_vertexs.at(i).y;
	  tempIndex[2] = m_vertexs.at(i).z;
	  //　4番目のインデックスには-1を格納
	  tempIndex[3] = -1;

	  //　頂点インデックスをセット
	  tempFace[i].SetVertexIndex(tempIndex);
	  //　法線インデックスをセット
	  tempFace[i].SetNormalIndex(tempIndex);
	  //　テクスチャ座標インデックスをセット
	  tempFace[i].SetTexCoordIndex(tempIndex);
	  //tempFace[i].indexMaterial(tempIndex);
     }

     //　面データを追加
     for ( int i=0; i<faceCount; i++ )
	  tempMesh.AddFace(tempFace[i]);

     // 材質データを設定
     for ( int i = 0; i < m_materials.size(); i++ )
     {
	  XMaterial tempMaterial;

	  // Name
	  tempMaterial.SetName(m_materials.at(i).textureFileName);
	  // Ambient Color
	  tempMaterial.ambient.r = m_materials.at(i).ambient.r; 
	  tempMaterial.ambient.g = m_materials.at(i).ambient.g; 
	  tempMaterial.ambient.g = m_materials.at(i).ambient.b; 
	  tempMaterial.ambient.a = 1.0f;

	  // Diffuse Color
	  tempMaterial.diffuse.r = m_materials.at(i).diffuse.r; 
	  tempMaterial.diffuse.g = m_materials.at(i).diffuse.g; 
	  tempMaterial.diffuse.b = m_materials.at(i).diffuse.b; 
	  tempMaterial.diffuse.a = m_materials.at(i).diffuse.a; 

	  // Shiness
	  tempMaterial.power = m_materials.at(i).shininess;

	  // Specular Color
	  tempMaterial.specular.r = m_materials.at(i).specular.r;
	  tempMaterial.specular.g = m_materials.at(i).specular.g;
	  tempMaterial.specular.b = m_materials.at(i).specular.b;
	  tempMaterial.specular.a = 1.0f;

	  // Emissive Color
	  /**
	  tempMaterial.emissive.r = GetFloatToken();
	  tempMaterial.emissive.g = GetFloatToken();
	  tempMaterial.emissive.b = GetFloatToken();
	  tempMaterial.emissive.a = 1.0f;
	  */
	  //　マテリアルデータを追加
	  AddMaterial(tempMaterial);
     }
		
     //　メッシュデータを追加
     AddMesh(tempMesh);
     //　確保したメモリを解放
     SafeDeleteArray(tempFace);
     //　バウンディングスフィアを計算
     ComputeBoundingSphere();
     //　バウンディングボックスを計算
     ComputeBoundingBox();


     return true;
}

int XModel::GetVersion()
{
     return 0;
}

void XModel::SetVersion(int ver)
{
}

const char* XModel::GetHeaderString()
{
     return m_header.header1;
}

void XModel::SetHeaderString(const char* name)
{
/**---------------------------------------------------

void *memcpy(         errno_t memcpy_s(	    
   void *dest,		 void *dest,	    
   const void *src,	 size_t sizeInBytes,
   size_t count		 const void *src,   
);			 size_t count	      
		      );		   
------------------------------------------------------*/

#ifdef _WIN32
     memcpy_s( (char*)&m_header, sizeof(m_header)-1,name, _TRUNCATE );
#else
     memcpy( (char*)&m_header, name, sizeof(m_header)-1);
#endif
}

const char* XModel::GetActor()
{
     return &m_header.header1[0x7];
}
void XModel::SetActor(const char* name )
{

#ifdef _WIN32
     strncpy_s( &m_header.header1[0x7],_countof(m_header.header1)-0x7,name,_TRUNCATE );
#else
     strncpy( &m_header.header1[0x7],name, countof(m_header.header1) - 0x7 );
#endif
}

int XModel::GetVertexChunkSize()
{
     return m_vertexs.size();
}

void XModel::SetVertexChunkSize(int size)
{
     m_vertexs.resize(size);
}

PMD_VERTEX_CHUNK& XModel::GetVertexChunk()
{
     return m_vertexs;
}

int XModel::GetIndexChunkSize()
{
     return m_indexs.size();
}

void XModel::SetIndexChunkSize(int size)
{
     m_indexs.resize(size);
}

PMD_INDEX_CHUNK& XModel::GetIndexChunk()
{
     return m_indexs;
}

int XModel::GetMaterialChunkSize()
{
     return m_materials.size();
}

void XModel::SetMaterialChunkSize(int size)
{
     m_materials.resize( size );
}

PMD_MATERIAL_CHUNK& XModel::GetMaterialChunk()
{
     return m_materials;
}

//---------------------------------------------------------------------------------------------------
// Name : Render()
// Desc : メッシュのインデックスを指定して描画
//---------------------------------------------------------------------------------------------------
void XModel::Render(int index, float scale)
{
	int pre_mat = -1;
	int cur_mat = 0;
	bool exist_material = false;
	bool exist_texcoord = false;
	bool exist_normal = false;

	if ( numMaterials > 0 ) exist_material = true;
	if ( mesh[index].numTexCoords > 0 ) exist_texcoord = true;
	if ( mesh[index].numNormals > 0 ) exist_normal = true;

	for ( int i=0; i<mesh[index].numFaces; i++ )
	{
		//　マテリアルが存在する場合
		if ( exist_material )
		{
			//　マテリアルインデックスを取得
			cur_mat = mesh[index].face[i].indexMaterial;

			//　マテリアルインデックスが異なる場合
			if ( cur_mat != pre_mat )
			{
				//　基本色
				glColor4fv(material[cur_mat].diffuse);

				//　Ambient Color
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material[cur_mat].ambient);

				//　Diffuse Color
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material[cur_mat].diffuse);

				//　Specular Color
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material[cur_mat].specular);

				//　Emissive Color
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material[cur_mat].emissive);

				//　Shininess
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material[cur_mat].power);

				//　マテリアルインデックスを更新
				pre_mat = cur_mat;
			}
		}

		//　要素数が3の場合
		if ( mesh[index].face[i].element == 3 ) 
			glBegin(GL_TRIANGLES);

		//　要素数が4の場合
		else if ( mesh[index].face[i].element == 4 )
			glBegin(GL_QUADS);

		for ( int j=0; j<mesh[index].face[i].element; j++ )
		{
			//　テクスチャ座標が存在する場合
			if ( exist_texcoord )
				glTexCoord2fv(mesh[index].texcoord[mesh[index].face[i].indexTexCoords[j]]);

			//　法線ベクトルが存在する場合
			if ( exist_normal )
				glNormal3fv(mesh[index].normal[mesh[index].face[i].indexNormals[j]]);
			
			//　頂点座標
			glVertex3f(
				mesh[index].vertex[mesh[index].face[i].indexVertices[j]].x * scale,
				mesh[index].vertex[mesh[index].face[i].indexVertices[j]].y * scale,
				mesh[index].vertex[mesh[index].face[i].indexVertices[j]].z * scale );
		}

		//　
		glEnd();
	}
}

//---------------------------------------------------------------------------------------------------
// Name : Render()
// Desc : 描画処理
//---------------------------------------------------------------------------------------------------
void XModel::Render(float scale)
{
	for ( int i=0; i<numMeshes; i++ )
	{
		Render(i, scale);
	}
}
