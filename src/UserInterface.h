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
	glm::vec3 mModelScale;
	glm::vec4 mModelRotate;
	
	unsigned int figura;
	unsigned int figuraMax;
	typedef enum { GLBGLE, LIST, VBO } Displays;
	TwType displayType;
	Displays disp;
	float rotSpeed;

	
public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(float *modelTranslation);
	glm::vec3 getModelTranslation();
	void setModelScale(float * modelScale);
	glm::vec3 getModelScale();
	unsigned int getSelectModel();
	void setNumModel(unsigned int num);
	glm::vec4 getModelRotate();
	void setModelRotate(glm::vec4 q);
	int getDisplayType();
	void updateInterface();

private:
	///Private constructor
	CUserInterface();
};