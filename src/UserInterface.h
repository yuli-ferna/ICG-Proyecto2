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
	unsigned int figura;
	unsigned int figuraMax;
public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(float *modelTranslation);
	glm::vec3 getModelTranslation();
	unsigned int getSelectModel();
	void setNumModel(unsigned int num);

private:
	///Private constructor
	CUserInterface(); 
};