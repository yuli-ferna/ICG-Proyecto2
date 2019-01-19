#include "Model.h"

CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
	mScale[0] = mScale[1] = mScale[2] = 1.0f;
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