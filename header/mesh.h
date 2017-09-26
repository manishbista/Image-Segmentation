#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>
#include <vector>
#include <string>

#include "meshData.h"

class mesh{
	std::vector<vertexData> data;
	std::vector<textureData> textures;
	std::vector<unsigned int> indices;
	unsigned int VBO;
	unsigned int IND;
	public:
		mesh(std::vector<vertexData>* vd,std::vector<unsigned int>* id,std::vector<textureData>* td=NULL);
		~mesh()
		{
		glDeleteBuffers(1,&VBO);	
		glDeleteBuffers(1,&IND);
		}
		unsigned int& getTextureID() { return textures[0].id;}
		void draw(unsigned int programId);
};
#endif
