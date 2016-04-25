// cMS3DModel.h: interface for the CMS3DModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMS3DMODEL_H__EF8D85EE_734B_4F0F_B921_7954EC274F42__INCLUDED_)
#define AFX_CMS3DMODEL_H__EF8D85EE_734B_4F0F_B921_7954EC274F42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------------------------------

#include <fstream>
#include "uMS3D_mathlib.h"

//------------------------------------------------------------------------------

// flags
#define MS3D_SELECTED		1
#define MS3D_HIDDEN			2
#define MS3D_SELECTED2		4
#define MS3D_DIRTY			8
#define MS3D_AVERAGED		16
#define MS3D_UNUSED			32

const int MS3D_VER3	= 3;
const int MS3D_VER4	= 4;

const char MS3D_ID[10]	= {'M', 'S', '3', 'D', '0', '0', '0', '0', '0', '0'};


typedef uint16_t	TMS3DLongFlags;
typedef uint8_t     TMS3DShortFlags;

typedef uint16_t	TMS3DULongIndex;
typedef char	TMS3DShortIndex;
typedef uint8_t	TMS3DUShortIndex;

typedef int		TMS3DFrameCount;
typedef uint16_t	TMS3DItemCount;


struct TMS3DBone
{
	TMatrix3x4	mRelative;
	TMatrix3x4	mAbsolute;
	TMatrix3x4	mRelativeFinal;
	TMatrix3x4	mFinal;
};

struct TMS3DHeader 
{
	char	id[10];		// MS3D000000 
	int		version;	// 4
};

struct TMS3DVertex 
{
	TMS3DShortFlags	flags;		// ukryty, zaznaczony itd.
	TMS3DVec3	vertex;     // wspó³rzêdne wierzcho³ka
	TMS3DShortIndex	boneId;		// -1 to brak przypisanej koœci
    uint8_t	refCount;
};

struct TMS3DTriangle
{
	TMS3DLongFlags	flags;				// ukryty, zaznaczony
	TMS3DULongIndex	vertexIndices[3];	// 3 indexy do wierzcho³ków
	TMS3DVec3	vertexNormals[3];	// 3 wektory normalne
	TMS3DFloat	texcoords_s[3];		// wsp³. tekstury
	TMS3DFloat	texcoords_t[3];		// wsp³. tekstury
	TMS3DUShortIndex	smoothingGroup;		// grupa trójk¹tów dla których s¹ obliczane wypadkowe normalne
	TMS3DUShortIndex	groupIndex;			// index grupy, do której nale¿y
};

struct TMS3DGroup
{
	TMS3DShortFlags	flags;
	char	name[32];       // nazwa grupy
	TMS3DItemCount	numTriangles;	// iloœæ trójk¹tów w grupie
	TMS3DULongIndex	*triangleIndices;	// indeksy trójk¹tów
	TMS3DShortIndex	materialIndex;	// index materia³u, jak -1 to brak
};

struct TMS3DMaterial
{
	char	name[32];	// nazwa materia³u
	TMS3DFloat	ambient[4]; // parametry materia³u
	TMS3DFloat	diffuse[4];
	TMS3DFloat	specular[4];
	TMS3DFloat	emissive[4];
	TMS3DFloat	shininess;	// 0.0 - 128.0
	TMS3DFloat	transparency;	// 0.0 - 1.0
	char	mode;		// np. Sphere Mapping
	char	packageName[128];	//	nazwa biblioteki materia³ów	// {Texture}
	char	materialName[128];	//	nazwa materia³u w bibliotece	// {AlphaMap}
};

struct TMS3DKeyframeRot 
{
	TMS3DFloat	time;		
    TMS3DVec3	rotation;	// obrót
};

struct TMS3DKeyframePos 
{
	TMS3DFloat	time;		
    TMS3DVec3	position;   // przesuniêcie
};

struct TMS3DJoint 
{
	TMS3DShortFlags	flags;
    char	name[32];
	char	parentName[32];
	TMS3DVec3	rotation;
	TMS3DVec3	position;
	TMS3DItemCount	numRotationKeys;
	TMS3DItemCount	numPositionKeys;
	TMS3DKeyframeRot	*rotationKeys;
	TMS3DKeyframePos	*positionKeys;
};
	

class CMS3DModel  
{
protected:
	TMS3DItemCount		numVertices;
	TMS3DVertex	*vertices;
	
	TMS3DItemCount		numTriangles;
	TMS3DTriangle	*triangles;

	TMS3DItemCount		numGroups;
	TMS3DGroup	*groups;

	TMS3DItemCount		numMaterials;
	TMS3DMaterial	*materials;

	TMS3DItemCount		numJoints;
	TMS3DJoint	*joints;	// ka¿demu po³¹czeniu opisuj¹cemu przesuniêcie i obrót
	TMS3DBone	*bones;		// odpowiada jedna "koœc" która zawiera wynikowe
							// macierze transformacji 
	
	TMS3DFloat	animationFPS;
	TMS3DFloat	currFrame;
	TMS3DFrameCount	totalFrames;
private:
//	Funkcja znajduje jointa po nazwie
	int FindJointByName(char *name);

//	Funkcja buduje strukture macierzy przekszta³ceñ dla animacji szkieletowej
	void SetupBones(void);

//	Funkcja odpowiada za animacje
	void AdvanceFrame(float deltaTime);

public:


	CMS3DModel();
	virtual ~CMS3DModel();

//	Funkcja tworzy nowy model
	virtual bool New();

//	Funkcja zwalnia pamiêc
	virtual void Release(void); 

//	Funkcja wczytuje model ze strumienia otwartego do odczytu
    virtual bool Load(std::ifstream &stream);

//	Funkcja wczytuje model z pliku	
	virtual bool Load(char *filename);

//	Funkcja zapisuje model do strumienia otwartego do zapisu
    virtual bool Save(std::ofstream &stream);

//	Funkcja zapisuje model do pliku
	virtual bool Save(char *filename); 

//	Animacja
	virtual void Prepare(float deltaTime)
	{	AdvanceFrame(deltaTime);	}

//	Funkcja rysuje model
	virtual void Draw(void); 
};


#endif // !defined(AFX_CMS3DMODEL_H__EF8D85EE_734B_4F0F_B921_7954EC274F42__INCLUDED_)
