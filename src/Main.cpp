#include "Main.h"
#include "Model.h"
#include "SOff.h"
#include "Off.h"
#include "CObj.h"
#include "UserInterface.h"
#include <iostream> 
#include <fstream> 
using namespace std;

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
CUserInterface * userInterface;
vector <CModel *> models;
int picked;

void updateUserInterface()
{
	if (picked > -1)
		models[picked]->setTranslation(userInterface->getModelTranslation());
	//mIENTRAS PUEDO TOMAR DEL TWEACKBAR EL NUM DE LA FIGURA
	//input de tipo enterio con restriccion
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (unsigned int i = 0; i < models.size(); i++)
	{	
		glm::vec3 translation = models[i]->getTranslation();

		glPushMatrix();
			glTranslatef(translation.x, translation.y, translation.z);
			models[i]->display();
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
	if(!soff->load("../files/cube.soff"))
		return false;
	models.push_back(soff);

	if (!obj->load("../files/house3.obj"))
		return false;
	models.push_back(obj);

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

void beginLoad(string path) {
	//ifstream infile(path);
	string aux = path;
	string extension = aux.erase(0, aux.find(".") + 1);
	cout << "extension: " << extension << endl;
	//Caso archivo OFF:
	if (extension == "off" || extension == "OFF") {
		cout << "hola mal" << endl;
		COff* coff = new COff();
		if (!coff->load(path))
			return;
		models.push_back(coff);
	}
	//Caso archivo OBJ:
	else if (extension == "obj" || extension == "OBJ") {
		cout << "hola asdad" << endl;
		CObj* cobj = new CObj();
		if (!cobj->load(path))
			return;
		models.push_back(cobj);
	}
}

string extractString(string source, string start, string end) {
	size_t startIndex = source.find(start);
	size_t endIndex;
	startIndex += start.length();
	endIndex = source.find(end, startIndex);
	return source.substr(startIndex, endIndex - startIndex);
}

