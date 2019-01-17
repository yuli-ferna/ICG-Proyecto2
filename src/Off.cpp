#include "Off.h"
#include <stdio.h>

COff::COff()
{
}

COff::~COff()
{
}

bool COff::load(string path)
{
	fstream file;
	string token, nV1, nV2, nV3, n, trash;
	
	file.open(path, std::ios::in);

	file >> token;

	if (token != "OFF")
	{
		file.close();
		return false;
	}
	else
	{
		file >> token;

		mNumOfVertices = atoi(token.c_str());

		file >> token;

		mNumOfFaces = atoi(token.c_str());

		file >> token;

		mNumOfAristas = atoi(token.c_str());

		std::cout << mNumOfVertices << " " << mNumOfFaces << " " << mNumOfAristas << std::endl;

		for (int i = 0; i < mNumOfVertices; i++)
		{
			file >> nV1;
			file >> nV2;
			file >> nV3;
			
			mVertices.push_back(glm::vec3((atof(nV1.c_str())), (atof(nV2.c_str())), (atof(nV3.c_str()))));
		}
		/*for (int i = 0; i < vertex.size(); i++)
		{
			std::cout << i << " " << vertex[i].x << " " << vertex[i].y << " " << vertex[i].z << " " << std::endl;
		}*/
		int NF =0; //Numero de caras reales
		for (int i = 0; i < mNumOfFaces; i++)
		{
			
			file >> n;
			int num = (atoi(n.c_str()));
			file >> nV1;
			int vert1 = atoi(nV1.c_str());

			file >> nV2;
			int vert2 = atoi(nV2.c_str());
			for (unsigned int i = 0; i < num-2; i++)
			{
				file >> nV3;
				faces.push_back(glm::ivec3(vert1, vert2, (atoi(nV3.c_str()))));
				vert2 = atoi(nV3.c_str());
				NF++;
			}
			getline(file, trash);
		}
		mNumOfFaces = NF;
		faces.clear();
		file.close();
		return true;
	}
}


void COff::display() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//cout << "iteracion: " << i << endl;
	for (int i = 0; i < mNumOfFaces; i++) {

		glBegin(GL_TRIANGLES);
		glVertex3f(mVertices[faces[i].x].x, mVertices[faces[i].x].y, mVertices[faces[i].x].z);
		glVertex3f(mVertices[faces[i].y].x, mVertices[faces[i].y].y, mVertices[faces[i].y].z);
		glVertex3f(mVertices[faces[i].z].x, mVertices[faces[i].z].y, mVertices[faces[i].z].z);
		glEnd();
	}
}