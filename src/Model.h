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
	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void display();
		void setTranslation(glm::vec3 translation);
		glm::vec3 getTranslation();
		void setScale(glm::vec3 Scale);
		glm::vec3 getScale();
		void setRotate(glm::vec4 rotate);
		glm::vec4 getRotate();
		void createList();
		void displayList();
		void displayVBO();
};