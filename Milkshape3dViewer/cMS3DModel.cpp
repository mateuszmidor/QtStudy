// cMS3DModel.cpp: implementation of the CMS3DModel class.
//
//////////////////////////////////////////////////////////////////////

/*
	Data:
		2006, wrzesieñ

	Klasa:
		CMS3DModel

	Opis:
		Klasa zapewniaj¹ca obs³ugê animowanych modeli w formacie MilkShape3D


	Autor:
		Mateusz Midor

	MailTo:
		3dmaniac@epf.pl
*/

#include <cstring>
#include <GL/gl.h>
#include "cMS3DModel.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
CMS3DModel::CMS3DModel()
{
	vertices = NULL;
	numVertices = 0;
	triangles = NULL;
	numTriangles = 0;
	groups = NULL;
	numGroups = 0;
	materials = NULL;
	numMaterials = 0;
	joints = NULL;
	bones = NULL;
	numJoints = 0;

	animationFPS = 0;
	currFrame = 0;
	totalFrames = 0;
}

//------------------------------------------------------------------------------
CMS3DModel::~CMS3DModel()
{
	Release();
}

//------------------------------------------------------------------------------
// FUNKCJE PRYWATNE
//------------------------------------------------------------------------------
//	Funkcja znajduje jointa po nazwie
int CMS3DModel::FindJointByName(char *name)
{
	for (int i = 0; i < numJoints; i++)
		if (!strcmp(name, joints[i].name))
			return i;

	return -1;
}

//------------------------------------------------------------------------------
//	Funkcja buduje strukture macierzy przekszta³ceñ dla animacji szkieletowej
void CMS3DModel::SetupBones()
{
	// bones = macierze przekszta³ceñ
	// ka¿demu po³¹czeniu dwóch koœci w animacji szkieletowej
	// przyporz¹dkowany jest zestaw macierzy przekszta³ceñ (staw ;p)

	int numBones = numJoints;
	bones = new TMS3DBone[numBones];

	int i;
	for (i = 0; i < numBones; i++)
	{
		TMS3DJoint *joint = &joints[i];
		TMS3DVec3 vRot;
		vRot[0] = joint->rotation[0] * 180.0f / (float) Q_PI;
		vRot[1] = joint->rotation[1] * 180.0f / (float) Q_PI;
		vRot[2] = joint->rotation[2] * 180.0f / (float) Q_PI;
		AngleMatrix(vRot, bones[i].mRelative);

		bones[i].mRelative[0][3] = joint->position[0];
		bones[i].mRelative[1][3] = joint->position[1];
		bones[i].mRelative[2][3] = joint->position[2];

		int nParent = FindJointByName(joint->parentName);
		if (nParent != -1)
		{
			R_ConcatTransforms(bones[nParent].mAbsolute, bones[i].mRelative, bones[i].mAbsolute);
            memcpy(bones[i].mFinal, bones[i].mAbsolute, sizeof(TMatrix3x4));
		}
		else
		{
            memcpy(bones[i].mAbsolute, bones[i].mRelative, sizeof (TMatrix3x4));
            memcpy(bones[i].mFinal, bones[i].mRelative, sizeof(TMatrix3x4));
		}
	}

	for (i = 0; i < numVertices; i++)
	{
		
		TMS3DVertex *vertex = &vertices[i];
		if (vertex->boneId != -1)
		{
			vertex->vertex[0] -= bones[vertex->boneId].mAbsolute[0][3];
			vertex->vertex[1] -= bones[vertex->boneId].mAbsolute[1][3];
			vertex->vertex[2] -= bones[vertex->boneId].mAbsolute[2][3];
			TMS3DVec3 vTmp;
			VectorIRotate(vertex->vertex, bones[vertex->boneId].mAbsolute, vTmp);
			CopyVec3(vertex->vertex, vTmp);
		}
	}

	for (i = 0; i < numTriangles; i++)
	{
		TMS3DTriangle *triangle = &triangles[i];

		for (int l = 0; l < 3; l++)
		{
			TMS3DVertex *vertex = &vertices[triangle->vertexIndices[l]];
			if (vertex->boneId != -1)
			{
				TMS3DVec3 vTmp;
				VectorIRotate(triangle->vertexNormals[l], bones[vertex->boneId].mAbsolute, vTmp);
				CopyVec3(triangle->vertexNormals[l], vTmp);
			}
		}
	}


}

//------------------------------------------------------------------------------
//	Funkcja odpowiada za animacje
void CMS3DModel::AdvanceFrame(float deltaTime)
{
	currFrame += deltaTime / 2.0f;
	if (currFrame > (float)totalFrames / animationFPS )
		currFrame = 0.0f;

	int numBones = numJoints;
	int i, j;
	for (i = 0; i < numBones; i++)
	{
		TMS3DJoint *joint = &joints[i];
		int numPositionKeys = joint->numPositionKeys;
		int numRotationKeys = joint->numRotationKeys;
		if ((numPositionKeys == 0) && (numRotationKeys == 0))
		{
            memcpy(bones[i].mFinal, bones[i].mAbsolute, sizeof(TMatrix3x4));
		}
		else
		{
			TMS3DVec3 vPos;
			TMS3DVec3 vRot;
			//
			// search for the adjaced position keys
			//
			TMS3DKeyframePos *lastPositionKey = NULL;
			TMS3DKeyframePos *thisPositionKey = NULL;

			for (j = 0; j < numPositionKeys; j++)
			{
				TMS3DKeyframePos *positionKey = &joint->positionKeys[j];
				if (positionKey->time >= currFrame)
				{
					thisPositionKey = positionKey;
					break;
				}
				lastPositionKey = positionKey;
			}
			if ((lastPositionKey != NULL) && (thisPositionKey != NULL))
			{
				float d = thisPositionKey->time - lastPositionKey->time;
				float s = (currFrame - lastPositionKey->time) / d;
				vPos[0] = lastPositionKey->position[0] + (thisPositionKey->position[0] - lastPositionKey->position[0]) * s;
				vPos[1] = lastPositionKey->position[1] + (thisPositionKey->position[1] - lastPositionKey->position[1]) * s;
				vPos[2] = lastPositionKey->position[2] + (thisPositionKey->position[2] - lastPositionKey->position[2]) * s;
			}
			else if (lastPositionKey == NULL)
			{
				CopyVec3(vPos, thisPositionKey->position);
			}
			else if (thisPositionKey == NULL)
			{
				CopyVec3(vPos, lastPositionKey->position);
			}
			//
			// search for the adjaced rotation keys
			//
			TMatrix3x4 m;
			TMS3DKeyframeRot *lastRotationKey = NULL;
			TMS3DKeyframeRot *thisRotationKey = NULL;

			for (j = 0; j < numRotationKeys; j++)
			{
				TMS3DKeyframeRot *rotationKey = &joint->rotationKeys[j];
				if (rotationKey->time >= currFrame)
				{
					thisRotationKey = rotationKey;
					break;
				}
				lastRotationKey = rotationKey;
			}
			if ((lastRotationKey != NULL) && (thisRotationKey != NULL))
			{
				float d = thisRotationKey->time - lastRotationKey->time;
				float s = (currFrame - lastRotationKey->time) / d;

				TMS3DVec4 q1, q2, q;
				AngleQuaternion(lastRotationKey->rotation, q1);
				AngleQuaternion(thisRotationKey->rotation, q2);
				QuaternionSlerp(q1, q2, s, q);
				QuaternionMatrix(q, m);
			}
			else if (lastRotationKey == NULL)
			{
				vRot[0] = thisRotationKey->rotation[0] * 180.0f / (float) Q_PI;
				vRot[1] = thisRotationKey->rotation[1] * 180.0f / (float) Q_PI;
				vRot[2] = thisRotationKey->rotation[2] * 180.0f / (float) Q_PI;
				AngleMatrix(vRot, m);
			}
			else if (thisRotationKey == NULL)
			{
				vRot[0] = lastRotationKey->rotation[0] * 180.0f / (float) Q_PI;
				vRot[1] = lastRotationKey->rotation[1] * 180.0f / (float) Q_PI;
				vRot[2] = lastRotationKey->rotation[2] * 180.0f / (float) Q_PI;
				AngleMatrix(vRot, m);
			}
			m[0][3] = vPos[0];
			m[1][3] = vPos[1];
			m[2][3] = vPos[2];
			R_ConcatTransforms(bones[i].mRelative, m, bones[i].mRelativeFinal);

			int nParent = FindJointByName(joint->parentName);
			if (nParent == -1)
			{
                memcpy(bones[i].mFinal, bones[i].mRelativeFinal, sizeof(TMatrix3x4));
			}
			else
			{
				R_ConcatTransforms(bones[nParent].mFinal, bones[i].mRelativeFinal, bones[i].mFinal);
			}
		}
	}
}

//------------------------------------------------------------------------------
// FUNKCJE PUBLICZNE
//------------------------------------------------------------------------------
//	Funkcja tworzy nowy model
bool CMS3DModel::New()
{
	Release();
	return true;
}

//------------------------------------------------------------------------------
//	Funkcja zwalnia pamiêc
void CMS3DModel::Release()
{
    currFrame = 0.0f;
    totalFrames = 0;

	// wierzcho³ki
	delete vertices;
	vertices = NULL;
	numVertices = 0;

	// trójk¹ty
	delete triangles;
	triangles = NULL;
	numTriangles = 0;

	// grupy
	int i;
	for (i = 0; i < numGroups; i++)
		delete groups[i].triangleIndices;
	delete groups;
	groups = NULL;
	numGroups = 0;

	// szkielet
	for (i = 0; i < numJoints; i++)
	{
		delete joints[i].positionKeys;
		delete joints[i].rotationKeys;
	}
	delete joints;
	joints = NULL;
	numJoints = 0;

	delete bones;
	bones = NULL;
}

//------------------------------------------------------------------------------
//	Funkcja wczytuje model ze strumienia otwartego do odczytu
bool CMS3DModel::Load(ifstream &stream)
{
	Release();

	// wczytujemy nag³ówek
	TMS3DHeader header;

	stream.read((char*)&header.id, sizeof(header.id));
	stream.read((char*)&header.version, sizeof(header.version));

	// sprawdzamy poprawnoœæ nag³ówka
	// niezgodny format
	if (strncmp(header.id, MS3D_ID, sizeof(MS3D_ID)))
	{
        //char *id = new char[sizeof(MS3D_ID) + 1]; // ostatni na NULL
        //ZeroMemory(id, sizeof(MS3D_ID) + 1);
        //CopyMemory(id, header.id, sizeof(MS3D_ID));
        //CInfoLog::AddErrorLog("CMS3DModel::Load: not a MS3D model", id);
        //delete id;
		return false;
	}

	// niezgodna wersja
	if ((header.version != MS3D_VER3) && (header.version != MS3D_VER4))
	{
        //char ver[10];
        //itoa(header.version, (char*)ver, sizeof(ver));
        //CInfoLog::AddErrorLog("CMS3DModel::Load: invalid MS3D model version", ver);
		return false;
	}


// ----------------------------------------------------- £ADOWANIE WIERZCHO£KÓW 
	stream.read((char*)&numVertices, sizeof(numVertices));
	vertices = new TMS3DVertex[numVertices];
	int i;
	for (i = 0; i < numVertices; i++)
	{
		TMS3DVertex *vert = &vertices[i];

		stream.read((char*)&vert->flags, sizeof(vert->flags));
		stream.read((char*)&vert->vertex, sizeof(vert->vertex));
		stream.read((char*)&vert->boneId, sizeof(vert->boneId));
		stream.read((char*)&vert->refCount, sizeof(vert->refCount));
	}


// -------------------------------------------------------- £ADOWANIE TRÓJK¥TÓW 
	stream.read((char*)&numTriangles, sizeof(numTriangles));
	triangles = new TMS3DTriangle[numTriangles];
	for (i = 0; i < numTriangles; i++)
	{
		TMS3DTriangle *tri = &triangles[i];

		stream.read((char*)&tri->flags, sizeof(tri->flags));
		stream.read((char*)&tri->vertexIndices, sizeof(tri->vertexIndices));
		stream.read((char*)&tri->vertexNormals, sizeof(tri->vertexNormals));
		
		stream.read((char*)&tri->texcoords_s, sizeof(tri->texcoords_s));
		stream.read((char*)&tri->texcoords_t, sizeof(tri->texcoords_t));

		stream.read((char*)&tri->smoothingGroup, sizeof(tri->smoothingGroup));
		stream.read((char*)&tri->groupIndex, sizeof(tri->groupIndex));
	}

// ------------------------------------------------------------- £ADOWANIE GRUP 
	stream.read((char*)&numGroups, sizeof(numGroups));
    groups = new TMS3DGroup[numGroups];
	for (i = 0; i < numGroups; i++)
	{
		TMS3DGroup *group = &groups[i];
		stream.read((char*)&group->flags, sizeof(group->flags));
        stream.read((char*)&group->name, sizeof(group->name));
        stream.read((char*)&group->numTriangles, sizeof(group->numTriangles));
        
		group->triangleIndices = new TMS3DULongIndex[group->numTriangles];
		stream.read((char*)group->triangleIndices, sizeof(TMS3DULongIndex) * group->numTriangles);
		stream.read((char*)&group->materialIndex, sizeof(group->materialIndex));
	}


// ------------------------------------------------------- £ADOWANIE MATERIA£ÓW 
	stream.read((char*)&numMaterials, sizeof(numMaterials));
    materials = new TMS3DMaterial[numMaterials];
	for (i = 0; i < numMaterials; i++)
	{
		TMS3DMaterial *mat = &materials[i];
		stream.read((char*)&mat->name, sizeof(mat->name));
		stream.read((char*)&mat->ambient, sizeof(mat->ambient));
		stream.read((char*)&mat->diffuse, sizeof(mat->diffuse));
		stream.read((char*)&mat->specular, sizeof(mat->specular));
		stream.read((char*)&mat->emissive, sizeof(mat->emissive));
		stream.read((char*)&mat->shininess, sizeof(mat->shininess));
		stream.read((char*)&mat->transparency, sizeof(mat->transparency));
		stream.read((char*)&mat->mode, sizeof(mat->mode));
		stream.read((char*)&mat->packageName, sizeof(mat->packageName));
		stream.read((char*)&mat->materialName, sizeof(mat->materialName));
	}


// ------------------------------------------------------- INFORMACJE O ANIMACJI 
	stream.read((char*)&animationFPS, sizeof(animationFPS));	
	stream.read((char*)&currFrame, sizeof(currFrame));	
	stream.read((char*)&totalFrames, sizeof(totalFrames));	


// -------------------------------------------------------- £ADOWANIE SZKIELETU 
	stream.read((char*)&numJoints, sizeof(numJoints));
    joints = new TMS3DJoint[numJoints];
    for (i = 0; i < numJoints; i++)
	{
		TMS3DJoint *joint = &joints[i];
		stream.read((char*)&joint->flags, sizeof(joint->flags));
		stream.read((char*)&joint->name, sizeof(joint->name));
		stream.read((char*)&joint->parentName, sizeof(joint->parentName));
		stream.read((char*)&joint->rotation, sizeof(joint->rotation));
		stream.read((char*)&joint->position, sizeof(joint->position));
		
		stream.read((char*)&joint->numRotationKeys, sizeof(joint->numRotationKeys));
		joint->rotationKeys = new TMS3DKeyframeRot[joint->numRotationKeys];

		stream.read((char*)&joint->numPositionKeys, sizeof(joint->numPositionKeys));
		joint->positionKeys = new TMS3DKeyframePos[joint->numPositionKeys];

		stream.read((char*)joint->rotationKeys, sizeof(TMS3DKeyframeRot) * joint->numRotationKeys);
		stream.read((char*)joint->positionKeys, sizeof(TMS3DKeyframePos) * joint->numPositionKeys);
	}

	SetupBones();

	return (!stream.fail());
}

//------------------------------------------------------------------------------
//	Funkcja wczytuje model z pliku
bool CMS3DModel::Load(char *filename)
{
	ifstream stream(filename, ios::in | ios::binary);
	if (!stream)
	{
        //CInfoLog::AddErrorLog("CMS3DModel::Load: could not open file", filename);
		return false;
	}

	if (!Load(stream))
	{
        //CInfoLog::AddErrorLog("CMS3DModel::Load: MS3D file reading error", filename);
		stream.close();
		return false;
	}

	stream.close();
	return true;
}

//------------------------------------------------------------------------------
//	Funkcja zapisuje model do strumienia otwartego do zapisu
bool CMS3DModel::Save(ofstream &stream)
{
	// zapisujemy nag³ówek
	stream.write((char*)&MS3D_ID, sizeof(MS3D_ID));
	stream.write((char*)&MS3D_VER4, sizeof(MS3D_VER4));


// ----------------------------------------------------- ZAPIS WIERZCHO£KÓW 
	stream.write((char*)&numVertices, sizeof(numVertices));
	int i;
	for (i = 0; i < numVertices; i++)
	{
		TMS3DVertex *vert = &vertices[i];
		stream.write((char*)&vert->flags, sizeof(vert->flags));
		stream.write((char*)&vert->vertex, sizeof(vert->vertex));
		stream.write((char*)&vert->boneId, sizeof(vert->boneId));
		stream.write((char*)&vert->refCount, sizeof(vert->refCount));
	}


// -------------------------------------------------------- ZAPIS TRÓJK¥TÓW 
	stream.write((char*)&numTriangles, sizeof(numTriangles));
	for (i = 0; i < numTriangles; i++)
	{
		TMS3DTriangle *tri = &triangles[i];

		stream.write((char*)&tri->flags, sizeof(tri->flags));
		stream.write((char*)&tri->vertexIndices, sizeof(tri->vertexIndices));
		stream.write((char*)&tri->vertexNormals, sizeof(tri->vertexNormals));
		stream.write((char*)&tri->texcoords_s, sizeof(tri->texcoords_s));
		stream.write((char*)&tri->texcoords_t, sizeof(tri->texcoords_t));
		stream.write((char*)&tri->smoothingGroup, sizeof(tri->smoothingGroup));
		stream.write((char*)&tri->groupIndex, sizeof(tri->groupIndex));
	}

// ------------------------------------------------------------- ZAPIS GRUP 
	stream.write((char*)&numGroups, sizeof(numGroups));
	for (i = 0; i < numGroups; i++)
	{
		TMS3DGroup *group = &groups[i];
		stream.write((char*)&group->flags, sizeof(group->flags));
        stream.write((char*)&group->name, sizeof(group->name));
        stream.write((char*)&group->numTriangles, sizeof(group->numTriangles));
        
		stream.write((char*)group->triangleIndices, sizeof(TMS3DULongIndex) * group->numTriangles);
		stream.write((char*)&group->materialIndex, sizeof(group->materialIndex));
	}


// ------------------------------------------------------- ZAPIS MATERIA£ÓW 
	stream.write((char*)&numMaterials, sizeof(numMaterials));
	for (i = 0; i < numMaterials; i++)
	{
		TMS3DMaterial *mat = &materials[i];
		stream.write((char*)&mat->name, sizeof(mat->name));
		stream.write((char*)&mat->ambient, sizeof(mat->ambient));
		stream.write((char*)&mat->diffuse, sizeof(mat->diffuse));
		stream.write((char*)&mat->specular, sizeof(mat->specular));
		stream.write((char*)&mat->emissive, sizeof(mat->emissive));
		stream.write((char*)&mat->shininess, sizeof(mat->shininess));
		stream.write((char*)&mat->transparency, sizeof(mat->transparency));
		stream.write((char*)&mat->mode, sizeof(mat->mode));
		stream.write((char*)&mat->packageName, sizeof(mat->packageName));
		stream.write((char*)&mat->materialName, sizeof(mat->materialName));
	}


// ------------------------------------------------------- INFORMACJE O ANIMACJI 
	stream.write((char*)&animationFPS, sizeof(animationFPS));	
	stream.write((char*)&currFrame, sizeof(currFrame));	
	stream.write((char*)&totalFrames, sizeof(totalFrames));	


// -------------------------------------------------------- ZAPIS SZKIELETU 
	stream.write((char*)&numJoints, sizeof(numJoints));
    for (i = 0; i < numJoints; i++)
	{
		TMS3DJoint *joint = &joints[i];
		stream.write((char*)&joint->flags, sizeof(joint->flags));
		stream.write((char*)&joint->name, sizeof(joint->name));
		stream.write((char*)&joint->parentName, sizeof(joint->parentName));
		stream.write((char*)&joint->rotation, sizeof(joint->rotation));
		stream.write((char*)&joint->position, sizeof(joint->position));
		
		stream.write((char*)&joint->numRotationKeys, sizeof(joint->numRotationKeys));
		stream.write((char*)&joint->numPositionKeys, sizeof(joint->numPositionKeys));

		stream.write((char*)joint->rotationKeys, sizeof(TMS3DKeyframeRot) * joint->numRotationKeys);
		stream.write((char*)joint->positionKeys, sizeof(TMS3DKeyframePos) * joint->numPositionKeys);
	}


	return (!stream.fail());
}

//------------------------------------------------------------------------------
//	Funkcja zapisuje model do pliku
bool CMS3DModel::Save(char *filename)
{
	ofstream stream(filename, ios::out | ios::binary);
	if (!stream)
	{
        //CInfoLog::AddErrorLog("CMS3DModel::Save: file creating error", filename);
		return false;
	}

	if (!Save(stream))
	{
        //CInfoLog::AddErrorLog("CMS3DModel::Save: file savying error", filename);
		stream.close();
		return false;
	}

	stream.close();
	return true;
}

//------------------------------------------------------------------------------
//	Funkcja rysuje model
void CMS3DModel::Draw()
{
	//glDisable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);


	//glDisable(GL_TEXTURE_2D);

	for (int i = 0; i < numGroups; i++)
	{
		TMS3DGroup *group = &groups[i];

		//	BindMaterial(materials[group->materialIndex]);


		glBegin(GL_TRIANGLES);
		for (int j = 0; j < group->numTriangles; j++)
		{
			TMS3DTriangle *triangle = &triangles[group->triangleIndices[j]];

			for (int v = 0; v < 3; v++)
			{
				glTexCoord2f(triangle->texcoords_s[v], triangle->texcoords_t[v]);

				TMS3DVertex *vertex = &vertices[triangle->vertexIndices[v]];
				if (vertex->boneId == -1)
				{
					glNormal3fv(triangle->vertexNormals[v]);
					glVertex3fv(vertex->vertex);
				}
				else
				{
					TMS3DVec3 vert;
					TMS3DVec3 normal;
					VectorRotate(triangle->vertexNormals[v], bones[vertex->boneId].mFinal, normal);
					VectorRotate(vertex->vertex, bones[vertex->boneId].mFinal, vert);
					vert[0] += bones[vertex->boneId].mFinal[0][3];
					vert[1] += bones[vertex->boneId].mFinal[1][3];
					vert[2] += bones[vertex->boneId].mFinal[2][3];

					glNormal3fv(normal);
					glVertex3fv(vert);
				}
			}
		}
		glEnd ();
	}
}
