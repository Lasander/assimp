/*
Open Asset Import Library (ASSIMP)
----------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team
All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the 
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/
#ifndef ASSIMP_Q3BSPFILEDATA_H_INC
#define ASSIMP_Q3BSPFILEDATA_H_INC

#include <vector>

namespace Assimp
{
namespace Q3BSP
{

static const unsigned int CE_BSP_LIGHTMAPSIZE = 128*128*3;	///< = 128( width ) * 128 ( height ) * 3 ( channels / RGB ).
static const int VERION_Q3LEVEL = 46;					///< Supported version.

///	Integer vector.
struct ceVec3i 
{
    int x, y, z;
	ceVec3i(): x( 0 ), y( 0 ), z( 0 ) { /* empty */ }
	ceVec3i( int iX, int iY=0, int iZ=0) : x( iX ), y( iY ), z( iZ ) { /* empty */ }
};

///	Fileheader
struct sQ3BSPHeader 
{
	char strID[ 4 ];	//!< Should be "IBSP"
	int iVersion;	//!< 46 for standard levels
};

///	Descripes an entry.
struct sQ3BSPLump 
{
	int iOffset;	///< Offset from startpointer of file
	int iSize;		///< Size fo part
};

struct vec2f
{
	float x,y;
};

struct vec3f
{
	float x, y, z;
};

///	Vertex of a Q3 level
struct sQ3BSPVertex 
{
	vec3f vPosition;	///< Position of vertex
	vec2f vTexCoord;	///< (u,v) Texturecoordinate of detailtexture
	vec2f vLightmap;	///< (u,v) Texturecoordinate of lightmap
	vec3f vNormal;		///< vertex normale
	unsigned char bColor[ 4 ];			///< Color in RGBA
};

///	A face in bsp format info
struct sQ3BSPFace 
{
	int iTextureID;					///< Index in texture array
	int iEffect;					///< Index in effectarray (-1 = no effect)
	int iType;						///< 1=Polygon, 2=Patch, 3=Mesh, 4=Billboard
	int iVertexIndex;				///< Start index of polygon
	int iNumOfVerts;				///< Number of vertices
	int	iMeshVertexIndex;			///< Index of first mesh vertex
	int iNumOfMeshVerts;			///< Anzahl der Meshvertices
	int iLightmapID;				///< Index in das Lightmap array
	int iLMapCorner[ 2 ];			///< Die Ecke der Lightmap in der Textur
	int iLMapSize[ 2 ];				///< Size of the lightmap stored on the texture
	vec3f vLMapPos;					///< 3D-Ursprung der Lightmap
	vec3f vLMapVecs[ 2 ];			///< 3D-s-t-Vektoren
	vec3f vNormal;					///< Polygonnormale
	int patchWidth, patchHeight;	///< bezier patch
};

/// A quake3 texture name.
struct sQ3BSPTexture 
{
	char strName[ 64 ];		///< Name of the texture without extention
	int iFlags;				///< Not used
	int iContents;			///< Not used
};

///	A lightmap of the level, size 128 x 128, RGB components.
struct sQ3BSPLightmap 
{
	unsigned char bLMapData[CE_BSP_LIGHTMAPSIZE];
	sQ3BSPLightmap() {	memset(bLMapData, 0, CE_BSP_LIGHTMAPSIZE); }
};

struct sRenderVertex 
{
	vec3f vPosition;
	vec2f vTC;
	vec2f vTCLightmap;
};

struct SubPatch
{
	std::vector<sRenderVertex> controlPoints;
	std::vector<sRenderVertex> vertices;
	std::vector<size_t> indices;
	int lightmapID;
};

enum eLumps 
{
	kEntities = 0,
	kTextures,
	kPlanes,
	kNodes,
	kLeafs,
	kLeafFaces,
	kLeafBrushes,
	kModels,
	kBrushes,
	kBrushSides,
	kVertices,
	kMeshVerts,
	kShaders,
	kFaces,
	kLightmaps,
	kLightVolumes,
	kVisData,
	kMaxLumps
};

struct Q3BSPModel
{
	std::vector<unsigned char> m_Data;
	std::vector<sQ3BSPLump*> m_Lumps;
	std::vector<sQ3BSPVertex*> m_Vertices;
	std::vector<sQ3BSPFace*> m_Faces;
	std::vector<int> m_Indices;
	std::vector<sQ3BSPTexture*> m_Textures;
	std::vector<sQ3BSPLightmap*> m_Lightmaps;
	std::vector<char> m_EntityData;
	std::string m_ModelName;

	Q3BSPModel() :
		m_Data(),
		m_Lumps(),
		m_Vertices(),
		m_Faces(),
		m_Indices(),
		m_Textures(),
		m_Lightmaps(),
		m_EntityData()
	{
		// empty
	}
};

}
}

#endif // ASSIMP_Q3BSPFILEDATA_H_INC
