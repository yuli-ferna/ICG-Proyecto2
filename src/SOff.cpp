#include "SOff.h"
#include <stdio.h>
CSOff::CSOff()
{
}

CSOff::~CSOff()
{
}

bool CSOff::load(string path)
{
	fstream file;
	string token, nV1, nV2, nV3, n;
	//int vert1, vert2, vert3;
	xyz ind;

	file.open(path, std::ios::in);

	file >> token;

	if (token != "SOFF" && token != "OFF")
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
			ind.x = atof(nV1.c_str());
			ind.y = atof(nV2.c_str());
			ind.z = atof(nV3.c_str());

			vertex.push_back(ind);
			mVertices.push_back(glm::vec3((atof(nV1.c_str())), (atof(nV2.c_str())), (atof(nV3.c_str()))));
		}
		for (int i = 0; i < vertex.size(); i++)
		{
			std::cout << i << " " << vertex[i].x << " " << vertex[i].y << " " << vertex[i].z << " " << std::endl;
		}
		for (int i = 0; i < mNumOfFaces; i++)
		{
			int NV;
			xyz vert1, vert2, vert3;

			file >> n;
			file >> nV1;
			//Tomamos el primer vertice de la cara
			NV = atoi(nV1.c_str());
			vert1 = vertex[NV];
			
			file >> nV2;
			//Tomamos el segundo vertice de la cara
			NV = atoi(nV2.c_str());
			vert2 = vertex[NV];

			file >> nV3;
			//Tomamos el tercer vertice de la cara
			NV = atoi(nV3.c_str());
			vert3 = vertex[NV];

			if (atoi(n.c_str()) == 3)
			{
				//mVertices.push_back();
				face Face;
				Face.v1 = vert1;
				Face.v2 = vert2;
				Face.v3 = vert3;
				
				faces.push_back(Face);
			}
			//mVertices.push_back(glm::vec3((atof(v1.c_str())), (atof(v2.c_str())), (atof(v3.c_str()))));

		}
		for (int i = 0; i < 4; i++)
		{
			std::cout << i << " " << faces[i].v1.x << " " << faces[i].v1.y << " " << faces[i].v1.z << " " << std::endl;
			std::cout << i << " " << faces[i].v2.x << " " << faces[i].v2.y << " " << faces[i].v2.z << " " << std::endl;
			std::cout << i << " " << faces[i].v3.x << " " << faces[i].v3.y << " " << faces[i].v3.z << " " << std::endl;
		}
		/*freopen("myfile.txt", "w", stdout);
		printf("This sentence is redirected to a file.");
		fclose(stdout);*/
		vertex.clear();
		faces.clear();
		file.close();
		return true;
	}
}