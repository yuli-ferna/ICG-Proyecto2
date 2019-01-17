#pragma once
#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;


class CObj : public CModel
{
	
	vector<glm::ivec3> faces;

	public:
		CObj();
		~CObj();
		bool load(string path);

		bool checkValidToken(string token);

		void display();

		int extractIndices(string vert);

};

