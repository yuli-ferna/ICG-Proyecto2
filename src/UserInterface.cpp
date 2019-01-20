#include "UserInterface.h"
#include "Windows.h"
#include <iostream> 
#include <fstream> 
using namespace std;
extern int gWidth, gHeight;
void TW_CALL CallbackLoad(void *clientData);
string loadPath();
void load(string path);

void loadArch(string path);
// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance() 
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		 mInterface = new CUserInterface();
 
   return mInterface;
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Model");

	TwDefine("Model refresh = '0.0001f'");
	TwDefine("Model resizable = false");
	TwDefine("Model fontresizable = false");
	TwDefine("Model movable = false");
	TwDefine("Model position = '20 20'");
	TwDefine("Model size = '220 520'");

	//Inicializamos valores
	TwEnumVal displaysEV[] = { { GLBGLE, "gl Begin gl End" },{ LIST, "List" },{VP, "Vertex Pointer"},{ VBO, "VBO" } };
	disp = GLBGLE;
	displayType = TwDefineEnum("displayType", displaysEV, 3);
	rotSpeed = 0;


	//Elementos de la interfaz

	TwAddButton(mUserInterface, "Load", CallbackLoad, NULL, " label='Load' ");
	TwAddVarRW(mUserInterface, "Figura", TW_TYPE_UINT32, &figura, "label='Model Select' min=0 max=10");
	TwAddVarRW(mUserInterface, "Display", displayType, &disp, NULL);
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Bounding Box", TW_TYPE_BOOLCPP, &bbox, "group='Shows'");
	TwAddVarRW(mUserInterface, "Points", TW_TYPE_BOOLCPP, &point, "group='Shows'");
	TwAddVarRW(mUserInterface, "Mayado", TW_TYPE_BOOLCPP, &may, "group='Shows'");
	TwAddVarRW(mUserInterface, "Normal", TW_TYPE_BOOLCPP, &norm, "group='Shows'");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "X", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Y", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Z", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Translation' step=0.01 ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Sc X", TW_TYPE_FLOAT, &mModelScale[0], " group='Scale' step=0.01 ");
	TwAddVarRW(mUserInterface, "Sc Y", TW_TYPE_FLOAT, &mModelScale[1], " group='Scale' step=0.01 ");
	TwAddVarRW(mUserInterface, "Sc Z", TW_TYPE_FLOAT, &mModelScale[2], " group='Scale' step=0.01 ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Rotation", TW_TYPE_QUAT4F, &mModelRotate, "");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Model", TW_TYPE_COLOR3F, &mainColor[0], "label = 'Model' colormode=rgb ");
	TwAddVarRW(mUserInterface, "Bounding Box ", TW_TYPE_COLOR3F, &bboxColor[0], "label = 'Bounding Box' colormode=rgb ");
	TwAddVarRW(mUserInterface, "Points ", TW_TYPE_COLOR3F, &pointColor[0], "label = 'Points' colormode=rgb ");
	TwAddVarRW(mUserInterface, "Mayado ", TW_TYPE_COLOR3F, &mayColor[0], "label = 'Mesh'  colormode=rgb ");
	TwAddVarRW(mUserInterface, "Normal ", TW_TYPE_COLOR3F, &normColor[0], "label = 'Normal'  colormode=rgb ");

}

void CUserInterface::updateInterface()
{
	
}

void CUserInterface::setBBox(bool b)
{
	bbox = b;
}

bool CUserInterface::getBBox()
{
	return bbox;
}

void CUserInterface::setPoint(bool p)
{
	point = p;
}

bool CUserInterface::getPoint()
{
	return point;
}

void CUserInterface::setMay(bool m)
{
	may = m;
}

bool CUserInterface::getMay()
{
	return may;
}

void CUserInterface::setNorm(bool m)
{
	norm = m;
}

bool CUserInterface::getNorm()
{
	return norm;
}


void CUserInterface::setBBoxColor(float * b)
{
	bboxColor[0] = b[0];
	bboxColor[1] = b[1];
	bboxColor[2] = b[2];
}

float * CUserInterface::getBBoxColor()
{
	return bboxColor;
}

void CUserInterface::setPointColor(float * p)
{
	pointColor[0] = p[0];
	pointColor[1] = p[1];
	pointColor[2] = p[2];
}

float * CUserInterface::getPointColor()
{
	return pointColor;
}

void CUserInterface::setMayColor(float * m)
{
	mayColor[0] = m[0];
	mayColor[1] = m[1];
	mayColor[2] = m[2];
}

float * CUserInterface::getMayColor()
{
	return mayColor;
}

void CUserInterface::setNormColor(float * m)
{
	normColor[0] = m[0];
	normColor[1] = m[1];
	normColor[2] = m[2];
}

float * CUserInterface::getNormColor()
{
	return normColor;
}

void CUserInterface::setMainColor(float * m)
{
	mainColor[0] = m[0];
	mainColor[1] = m[1];
	mainColor[2] = m[2];
}

float * CUserInterface::getMainColor()
{
	return mainColor;
}
CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}


void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setModelTranslation(glm::vec3 modelTranslation)
{
	mModelTranslation[0] = modelTranslation.x;
	mModelTranslation[1] = modelTranslation.y;
	mModelTranslation[2] = modelTranslation.z;
}

glm::vec3 CUserInterface::getModelTranslation()
{
	return mModelTranslation;
}

void CUserInterface::setModelScale(glm::vec3 modelScale)
{
	mModelScale[0] = modelScale.x;
	mModelScale[1] = modelScale.y;
	mModelScale[2] = modelScale.z;
}

glm::vec3 CUserInterface::getModelScale()
{
	return mModelScale;
}

unsigned int CUserInterface::getSelectModel()
{
	return figura;
}

void CUserInterface::setNumModel(unsigned int num)
{

	figuraMax = num;
}

glm::vec4 CUserInterface::getModelRotate()
{
	return mModelRotate;
}

void CUserInterface::setModelRotate(glm::vec4 q)
{
	mModelRotate = q;
}

string loadPath()
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "OBJ Files(.obj)\0*.obj\0OFF Files(.off)\0*.off";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

void TW_CALL CallbackLoad(void *clientData)
{
	string path = loadPath();
	if (path != "")
		loadArch(path);

}

void load(string path) {
	std::ifstream infile(path);
	while (true) {
		if (infile.eof()) break;
	}
}

int CUserInterface::getDisplayType() 
{
	if (disp == GLBGLE) return 0;
	if (disp == LIST) return 1;
	if (disp == VBO) return 2;
	if (disp == VP) return 3;
	return NULL;
}