#pragma once

#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;

class COff : public CModel
{
	vector<glm::ivec3> faces;


public:
	COff();
	~COff();
	bool load(string path);
	void display();
};