#pragma once

#include "../headers/AntTweakBar.h"
#include "../headers/glm/glm.hpp"
#include "Windows.h"
#include <iostream>
#include <string>
#include <fstream> 

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	glm::vec3 mModelTranslation;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(float *modelTranslation);
	glm::vec3 getModelTranslation();

	/*string loadPath();

	void TW_CALL CallbackLoad();

	void TW_CALL CallbackLoad(void * clientData);

	void load(string path);*/


private:
	///Private constructor
	CUserInterface(); 
};