#include "header/meshLoader.h"

extern SDL_Surface* gScreenSurface;
meshLoader::meshLoader()
{

g_VertexData.reserve(4);
vertexData tempVData;
textureData tempTexData;

tempVData.position.change(-1.0,1.0,-1);
tempVData.U = 0;
tempVData.V = 0;
g_VertexData.push_back(tempVData);

tempVData.position.change(-1.0,-1.0,-1);
tempVData.U = 0;
tempVData.V = 1;
g_VertexData.push_back(tempVData);

tempVData.position.change(1.0,-1.0,-1);
tempVData.U = 1;
tempVData.V = 1;
g_VertexData.push_back(tempVData);

tempVData.position.change(1.0,1.0,-1);
tempVData.U = 1;
tempVData.V = 0;
g_VertexData.push_back(tempVData);

//for a triangle ID = 3

g_Index.reserve(4);

g_Index.push_back(0);
g_Index.push_back(1);
g_Index.push_back(2);

g_Index.push_back(0);
g_Index.push_back(2);
g_Index.push_back(3);

tempTexData.id = 0;		//needs to be initialize to a texture using loadTexture func()
tempTexData.type = 0;
g_TexData.push_back(tempTexData);
g_Mesh = new mesh(&g_VertexData, &g_Index, &g_TexData);

}

void meshLoader::loadImage(std::string file_name)
{
	g_Mesh->getTextureID() = loadTexture(file_name);
}

unsigned int meshLoader::loadTexture(std::string file_name)
{
	unsigned int num;
	glGenTextures(1,&num);
	SDL_Surface* imgs=IMG_Load(file_name.c_str());
	if(imgs==NULL)
	{
		//std::cout << "img was not loaded" << std::endl;
		return -1;
	}
	//SDL_PixelFormat form={NULL,32,4,0,0,0,0,0,0,0,0,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
	SDL_Surface* img2=SDL_ConvertSurface( imgs, gScreenSurface->format,0 );

	if(img2==NULL)
	{
		//std::cout << "img2 was not loaded" << std::endl;
		return -1;		
	}
	glBindTexture(GL_TEXTURE_2D,num);		

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_BGRA,GL_UNSIGNED_BYTE,img2->pixels);

/*	unsigned char *pixels = (unsigned char *) img2->pixels;
	unsigned char pixelVal;
		

	for(int y = 0; y < img2->h/20; y++)
	{
		for(int x = 0; x < img2->h/20; x++)
		{
			for(int c = 0; c < 4; c++)
			{
			 pixels[4 * (y * img2 -> w + x) + c] = 255;
			 std::cout<<" c "<<c<<(int)pixelVal<<"  ";
			}
		}
	
	}
*/

	SDL_FreeSurface(imgs);
	SDL_FreeSurface(img2);
	glBindTexture(GL_TEXTURE_2D,0);
	return num;	
}

meshLoader::~meshLoader()
{
	delete g_Mesh;
}

void meshLoader::draw(unsigned int programId)
{
	g_Mesh->draw(programId);
}
