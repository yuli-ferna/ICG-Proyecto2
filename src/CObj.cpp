#include "CObj.h"
#include <iostream>
#include <string>
using namespace std;
CObj::CObj()
{
}


CObj::~CObj()
{
}

bool CObj::load(string path) {
	fstream file;
	string token, v1, v2, v3, trash;
	file.open(path, std::ios::in);

	file >> token;
	while (!file.eof()) {

		if (token == "v") {
			file >> v1;
			file >> v2;
			file >> v3;
			mVertices.push_back(glm::vec3((atof(v1.c_str())), (atof(v2.c_str())), (atof(v3.c_str()))));
		}
		//No me interesa para nada vn y vt
		else if (token == "f") {

			int ver1, ver2, ver3;
			file >> v1;
			file >> v2;
			file >> v3;
			ver1 = extractIndices(v1);
			ver2 = extractIndices(v2);
			ver3 = extractIndices(v3);
			//cout << ver1 << ' ' << ver2 << ' ' << ver3 << endl;
			faces.push_back(glm::ivec3(ver1, ver2, ver3));
		}
		else
		{
			getline(file, trash);
			//cout << token << " " << trash << endl;
		}
		//getline(file, trash);

		file >> token;


	}
	return true;
}

bool CObj::checkValidToken(string token) {
	if (token == "v"/* || token == "vn" || token == "vt" */ || token == "f")
		return true;
	return false;
}

void CObj::display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//cout << "iteracion: " << i << endl;
	for (unsigned int i = 0; i < faces.size(); i++) {

		glBegin(GL_TRIANGLES);
		glVertex3f(mVertices[faces[i].x - 1].x, mVertices[faces[i].x - 1].y, mVertices[faces[i].x - 1].z);
		glVertex3f(mVertices[faces[i].y - 1].x, mVertices[faces[i].y - 1].y, mVertices[faces[i].y - 1].z);
		glVertex3f(mVertices[faces[i].z - 1].x, mVertices[faces[i].z - 1].y, mVertices[faces[i].z - 1].z);
		glEnd();
	}
}

int CObj::extractIndices(string vert)
{
	string delimiter = "/";
	string token = vert.substr(0, vert.find(delimiter));

	return atoi(token.c_str());
}