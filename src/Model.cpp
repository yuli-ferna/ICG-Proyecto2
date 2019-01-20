#include "Model.h"

CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
	mScale[0] = mScale[1] = mScale[2] = 1.0f;
	mRotate = glm::vec4(glm::vec3(0.0f), 1.0f);
	boundBox = true;
	pointV = false;
	mayV = false;
	normV = false;
	//Colors
	mainColor[0] = mainColor[1] = mainColor[2] = 1.0f;
	bboxColor[0] = bboxColor[1] = bboxColor[2] = 0.7f;
	mayColor[0] = mayColor[1] = mayColor[2] = 0.7f;
	normColor[0] = normColor[1] = normColor[2] = 0.7f;
	pointColor[0] = pointColor[1] = pointColor[2] = 0.7f;
	createList();
}

CModel::~CModel()
{
	mVertices.clear();
}

void CModel::display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i = 0; i < mNumOfVertices; i += 3)
	{
		glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f(mVertices[i + 1].x, mVertices[i + 1].y, mVertices[i + 1].z);
			glVertex3f(mVertices[i + 2].x, mVertices[i + 2].y, mVertices[i + 2].z);
		glEnd();
		//Cambio pendiente
	}
}

void CModel::setboundBox(bool boundBo)
{
	boundBox = boundBo;
}

bool CModel::getboundBox()
{
	return boundBox;
}

void CModel::setPointV(bool p)
{
	pointV = p;
}

bool CModel::getPointV()
{
	return pointV;
}

void CModel::setMay(bool m)
{
	mayV = m;
}

bool CModel::getMay()
{
	return mayV;
}

void CModel::setNormV(bool m)
{
	normV = m;
}

bool CModel::getNormV()
{
	return normV;
}


void CModel::setTranslation(glm::vec3 translation)
{
	mTranslation = translation;
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

void CModel::setScale(glm::vec3 Scale)
{
	mScale = Scale;
}

glm::vec3 CModel::getScale()
{
	return mScale;
}

void CModel::setRotate(glm::vec4 rotate)
{
	mRotate = rotate;

}

glm::vec4 CModel::getRotate()
{
	return mRotate;
}

void CModel::createList() {

	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	//glColor3fv(color);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
	glBegin(GL_POINTS);
	display();
	glEnd();
	glEndList();
}

void CModel::displayList() {
	glCallList(list);
	glDeleteLists(list, 1);
}

void CModel::setBBoxColor(float * b)
{
	bboxColor[0] = b[0];
	bboxColor[1] = b[1];
	bboxColor[2] = b[2];
}

float * CModel::getBBoxColor()
{
	return bboxColor;
}

void CModel::setPointColor(float * p)
{
	pointColor[0] = p[0];
	pointColor[1] = p[1];
	pointColor[2] = p[2];
}

float * CModel::getPointColor()
{
	return pointColor;
}

void CModel::setMayColor(float * m)
{
	mayColor[0] = m[0];
	mayColor[1] = m[1];
	mayColor[2] = m[2];
}

float * CModel::getMayColor()
{
	return mayColor;
}

void CModel::setNormColor(float * m)
{
	normColor[0] = m[0];
	normColor[1] = m[1];
	normColor[2] = m[2];
}

float * CModel::getNormColor()
{
	return normColor;
}

void CModel::setMainColor(float * m)
{
	mainColor[0] = m[0];
	mainColor[1] = m[1];
	mainColor[2] = m[2];
}

float * CModel::getMainColor()
{
	return mainColor;
}

/*
void CModel::displayVBO() {
	glGenBuffers(1, &vbo);    // for vertex buffer
	glGenBuffers(1, &vindex);    // for index buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);
	glDrawElements(GL_TRIANGLES, mNumOfVertices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


// create VBOs
glGenBuffers(1, &vboId);    // for vertex buffer
glGenBuffers(1, &iboId);    // for index buffer

size_t vSize = sizeof vertices;
size_t nSize = sizeof normals;
size_t cSize = sizeof colors;
size_t tSize = sizeof texCoords;

// copy vertex attribs data to VBO
glBindBuffer(GL_ARRAY_BUFFER, vboId);
glBufferData(GL_ARRAY_BUFFER, vSize+nSize+cSize+tSize, 0, GL_STATIC_DRAW); // reserve space
glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, vertices);                  // copy verts at offset 0
glBufferSubData(GL_ARRAY_BUFFER, vSize, nSize, normals);               // copy norms after verts
glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize, cSize, colors);          // copy cols after norms
glBufferSubData(GL_ARRAY_BUFFER, vSize+nSize+cSize, tSize, texCoords); // copy texs after cols
glBindBuffer(GL_ARRAY_BUFFER, 0);

// copy index data to VBO
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
*/

/*Calculate normals

float* cross(float* v1, float* v2)
{

}
*/
