#include "UserInterface.h"
#include "Windows.h"
#include <iostream> 
#include <fstream> 
using namespace std;
extern int gWidth, gHeight;
void TW_CALL CallbackLoad(void *clientData);
string loadPath();
void load(string path);

void beginLoad(string path);
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
	TwDefine("Model size = '220 320'");

	//Inicializamos valores
	TwEnumVal displaysEV[] = { { GLBGLE, "gl Begin gl End" },{ LIST, "List" },{ VBO, "VBO" } };
	disp = GLBGLE;
	displayType = TwDefineEnum("displayType", displaysEV, 3);
	rotSpeed = 0;
	quat = glm::vec4(glm::vec3(0.0f), 1.0f);
	mModelTranslation[0] = 0.0f;
	mModelTranslation[1] = 0.0f;
	mModelTranslation[2] = 0.0f;
	mModelScale[0] = 1.0f;
	mModelScale[1] = 1.0f;
	mModelScale[2] = 1.0f;

	//Elementos de la interfaz
	//TwAddVarRW(mUserInterface, "Deploy", DeployTwType, &m_currentDeploy, NULL);
	TwAddButton(mUserInterface, "Load", CallbackLoad, NULL, " label='Cargar archivo' ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Figura", TW_TYPE_UINT32, &figura, "label='Figura Seleccionada' min=0 max=10");
	TwAddVarRW(mUserInterface, "Display", displayType, &disp, NULL);
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "X", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Y", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Z", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Translation' step=0.01 ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Sc X", TW_TYPE_FLOAT, &mModelScale[0], " group='Scale' step=0.01 ");
	TwAddVarRW(mUserInterface, "Sc Y", TW_TYPE_FLOAT, &mModelScale[1], " group='Scale' step=0.01 ");
	TwAddVarRW(mUserInterface, "Sc Z", TW_TYPE_FLOAT, &mModelScale[2], " group='Scale' step=0.01 ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Rotation", TW_TYPE_QUAT4F, &quat, "");

}

void CUserInterface::updateInterface()
{
	
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

void CUserInterface::setModelTranslation(float *modelTranslation)
{
	mModelTranslation[0] = modelTranslation[0];
	mModelTranslation[1] = modelTranslation[1];
	mModelTranslation[2] = modelTranslation[2];
}

glm::vec3 CUserInterface::getModelTranslation()
{
	return mModelTranslation;
}

void CUserInterface::setModelScale(float *modelScale)
{
	mModelScale[0] = modelScale[0];
	mModelScale[1] = modelScale[1];
	mModelScale[2] = modelScale[2];
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

glm::vec4 CUserInterface::getQuat()
{
	return quat;
}

void CUserInterface::setQuat(glm::vec4 q)
{
	quat = q;
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
		beginLoad(path);

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
	return NULL;
}