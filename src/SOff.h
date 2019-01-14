#pragma once

#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;

class CSOff : public CModel
{
	struct xyz{
		float x; 
		float y;
		float z;
	};
	struct face {
		xyz v1;
		xyz v2;
		xyz v3;
	};


	vector<xyz> vertex;
	vector<face> faces;


	public:
		CSOff();
		~CSOff();
		bool load(string path);
};