#pragma once

#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

class CModel
{
	protected:
		vector<glm::vec3> mVertices;
		glm::vec3 mTranslation;
		glm::vec3 mScale;
		glm::vec4 mRotate;
		int mNumOfVertices;
		int mNumOfFaces;
		int mNumOfAristas;
		GLuint list;
		bool boundBox, pointV, mayV, normV;
		float bboxColor[3], pointColor[3], mayColor[3], normColor[3], mainColor[3];

	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void display();
		//Show bools
		void setboundBox(bool boundBo);
		bool getboundBox();
		void setPointV(bool p);
		bool getPointV();
		void setMay(bool m);
		bool getMay();
		void setNormV(bool m);
		bool getNormV();
		//Translatios, Scale, Rotate
		void setTranslation(glm::vec3 translation);
		glm::vec3 getTranslation();
		void setScale(glm::vec3 Scale);
		glm::vec3 getScale();
		void setRotate(glm::vec4 rotate);
		glm::vec4 getRotate();
		//Display mode
		void createList();
		void displayList();
		void displayVBO();
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
};