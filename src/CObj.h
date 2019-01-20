#pragma once
#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;


class CObj : public CModel
{
	
	vector<glm::ivec3> faces;
	glm::vec3 min, max; //Minimo y maximo de todos los vertices
	glm::vec3 mit; //Mitad de todo

	public:
		CObj();
		~CObj();
		bool load(string path);
		void Max(glm::vec3 a);
		void Min(glm::vec3 a);
		void display();
		void normalize();
		void drawBoundingBox();
		int extractIndices(string vert);
};

