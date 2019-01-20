#include "Main.h"
#include "Model.h"
#include "SOff.h"
#include "Off.h"
#include "CObj.h"
#include "UserInterface.h"
#include <iostream> 
#include <fstream> 
#include <set>
#define GL_B_GL_E 0
#define LIST 1
#define VBO 2
#define VP 3
using namespace std;

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
CUserInterface * userInterface;
vector <CModel *> models;
int picked;
int modeDisplay = 0;
void quatToMatrix(glm::vec4 quat, float *matrix);
int antPicked = -1;
set<int> vPick;

void updateUserInterface()
{
	if (models.size() > 0)
	{
		picked = userInterface->getSelectModel();
		if (picked >= models.size())
		{
			picked = models.size() - 1;
		}
		if (picked < 0)
		{
			picked = 0;

		}
		
		if (antPicked != picked)
		{
			//Es nueva
			cout << "hola" << endl;
			userInterface->setModelTranslation(models[picked]->getTranslation());
			userInterface->setModelScale(models[picked]->getScale());
			userInterface->setModelRotate(models[picked]->getRotate());
			userInterface->setBBox(models[picked]->getboundBox());
			userInterface->setPoint(models[picked]->getPointV());
			userInterface->setMay(models[picked]->getMay());
			userInterface->setNorm(models[picked]->getNormV());
			
			userInterface->setMainColor(models[picked]->getMainColor());
			userInterface->setBBoxColor(models[picked]->getBBoxColor());
			userInterface->setPointColor(models[picked]->getPointColor());
			userInterface->setMayColor(models[picked]->getMayColor());
			userInterface->setNormColor(models[picked]->getNormColor());

			//cout << "Picked: " << picked << " " << models[picked]->getTranslation().x << endl;
			antPicked = picked;
			for (int i = 0; i < models.size(); i++)
			{
				cout << "Picked: " << i << " x: " << models[i]->getTranslation().x << endl;

			}
		}
		userInterface->setNumModel(models.size() - 1);
		modeDisplay = userInterface->getDisplayType();
		//cout << modeDisplay << endl;
		//if (picked > -1)
		//Transformamos modelo
		models[picked]->setTranslation(userInterface->getModelTranslation());
		models[picked]->setScale(userInterface->getModelScale());
		models[picked]->setRotate(userInterface->getModelRotate());
		models[picked]->setboundBox(userInterface->getBBox());
		models[picked]->setPointV(userInterface->getPoint());
		models[picked]->setMay(userInterface->getMay());
		models[picked]->setNormV(userInterface->getNorm());

		models[picked]->setMainColor(userInterface->getMainColor());
		models[picked]->setBBoxColor(userInterface->getBBoxColor());
		models[picked]->setPointColor(userInterface->getPointColor());
		models[picked]->setMayColor(userInterface->getMayColor());
		models[picked]->setNormColor(userInterface->getNormColor());

	}
	
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (unsigned int i = 0; i < models.size(); i++)
	{	
		glm::vec3 translation = models[i]->getTranslation();
		glm::vec3 scale = models[i]->getScale();
		glm::vec4 rotat = models[i]->getRotate();
		glPushMatrix();
			glTranslatef(translation.x, translation.y, translation.z);
			glScalef(scale.x, scale.y, scale.z);
			float matrix[16];
			quatToMatrix(rotat, matrix);
			glMultMatrixf(matrix);
			if (modeDisplay == GL_B_GL_E)
			{
				models[i]->display();
			}
			else if (modeDisplay == LIST)
			{
				models[i]->createList();
				models[i]->displayList();
			}
			else if(modeDisplay == VBO)
			{

			}
			else if (modeDisplay == VP)
			{

			}


		glPopMatrix();

		

	}
		
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < models.size(); i++)
		delete models[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Proyecto 2 Yuliana Fernandez 26.838.996", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

bool initScene()
{
	CSOff* soff = new CSOff();
	COff* off = new COff();
	CObj* obj = new CObj();
	/*
	if (!off->load("../files/Apple.off"))
		return false;
	models.push_back(off);*/
	/*if(!soff->load("../files/cube.soff"))
		return false;
	models.push_back(soff);*/
	/*if (!obj->load("../files/Batman.obj"))
		return false;
	models.push_back(obj);*/
	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	picked = 0;

	if (!initGlfw() || !initScene() || !initUserInterface())
		return EXIT_FAILURE;

	glEnable(GL_DEPTH_TEST);

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}

void loadArch(string path) {

	string aux = path;
	string type = aux.substr(aux.size() - 4, aux.size() - 1);
	cout << "type: " << type << endl;
	// Cargar archivo OFF
	if (type == ".off" || type == ".OFF") {
	
		COff* coff = new COff();
		if (!coff->load(path))
			return;
		models.push_back(coff);
	}
	// Cargar archivo OBJ
	else if (type == ".obj" || type == ".OBJ") {

		CObj* cobj = new CObj();
		if (!cobj->load(path))
			return;
		models.push_back(cobj);
	}
}


void quatToMatrix(glm::vec4 quat, float *matrix)
{
	float yy2 = 2.0f * quat[1] * quat[1];
	float xy2 = 2.0f * quat[0] * quat[1];
	float xz2 = 2.0f * quat[0] * quat[2];
	float yz2 = 2.0f * quat[1] * quat[2];
	float zz2 = 2.0f * quat[2] * quat[2];
	float wz2 = 2.0f * quat[3] * quat[2];
	float wy2 = 2.0f * quat[3] * quat[1];
	float wx2 = 2.0f * quat[3] * quat[0];
	float xx2 = 2.0f * quat[0] * quat[0];
	matrix[0 * 4 + 0] = -yy2 - zz2 + 1.0f;
	matrix[0 * 4 + 1] = xy2 + wz2;
	matrix[0 * 4 + 2] = xz2 - wy2;
	matrix[0 * 4 + 3] = 0;
	matrix[1 * 4 + 0] = xy2 - wz2;
	matrix[1 * 4 + 1] = -xx2 - zz2 + 1.0f;
	matrix[1 * 4 + 2] = yz2 + wx2;
	matrix[1 * 4 + 3] = 0;
	matrix[2 * 4 + 0] = xz2 + wy2;
	matrix[2 * 4 + 1] = yz2 - wx2;
	matrix[2 * 4 + 2] = -xx2 - yy2 + 1.0f;
	matrix[2 * 4 + 3] = 0;
	matrix[3 * 4 + 0] = matrix[3 * 4 + 1] = matrix[3 * 4 + 2] = 0;
	matrix[3 * 4 + 3] = 1;
}