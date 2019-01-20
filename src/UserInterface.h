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
	typedef enum { GLBGLE, LIST, VP, VBO } Displays;
	TwType displayType;
	Displays disp;
	float rotSpeed;
	bool bbox, point, may, norm;
	float bboxColor[3], pointColor[3], mayColor[3], normColor[3], mainColor[3];
	
public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(glm::vec3 modelTranslation);
	glm::vec3 getModelTranslation();
	void setModelScale(glm::vec3 modelScale);
	glm::vec3 getModelScale();
	unsigned int getSelectModel();
	void setNumModel(unsigned int num);
	glm::vec4 getModelRotate();
	void setModelRotate(glm::vec4 q);
	int getDisplayType();
	//Shows bool
	void setBBox(bool b);
	bool getBBox();
	void setPoint(bool p);
	bool getPoint();
	void setMay(bool m);
	bool getMay();
	void setNorm(bool m);
	bool getNorm();
	//Colors
	void setBBoxColor(float* b);
	float* getBBoxColor();
	void setPointColor(float* p);
	float* getPointColor();
	void setMayColor(float* m);
	float* getMayColor();
	void setNormColor(float* m);
	float* getNormColor();
	void setMainColor(float* m);
	float* getMainColor();
	void updateInterface();

private:
	///Private constructor
	CUserInterface();
};