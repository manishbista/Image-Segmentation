
/**************************************************************************************************
Image Segmentation using opengGL Shading Language
Program Description
Input: Name of Image File stored in models/texture/
Output: Segmented Image
Process: Graph based segmentation using Disjoint set forests
TIme complexity: O(n logn), for n number of pixels
**************************************************************************************************/

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "header/meshLoader.h"
#include "header/shader.h"
#include "header/matrices.h"
#include "header/flag.h"
#include "header/segment.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow;
SDL_Surface* gScreenSurface;

matrices pipeline;

mesh *quad, *quadInverted;

shader* displayShades;

unsigned int createTexture(int w, int h);

void init()
{
	//initialize projection matrix: orthographic view with a box of [-1, 1]
	pipeline.matrixMode(PROJECTION_MATRIX);
	pipeline.loadIdentity();
	pipeline.ortho(-1.0, 1.0, -1.0, 1.0, 1, 100);



	//shader initializations
	displayShades = new shader("../v_shader/displayShader.vs","../f_shader/displayShader.frag");


	{
		std::vector<unsigned int> indices;
		std::vector<vertexData> vertices;
		vertexData tmp;
		//1.
		tmp.position.change(-1.0,1.0,-1.0);
		tmp.U=0;
		tmp.V=1;
		vertices.push_back(tmp);
		//2.
		tmp.position.change(-1.0,-1.0,-1.0);
		tmp.U=0;
		tmp.V=0;
		vertices.push_back(tmp);
		//3.
		tmp.position.change(1.0,-1.0,-1.0);
		tmp.U=1;
		tmp.V=0;
		vertices.push_back(tmp);
		//4.
		tmp.position.change(1.0,1.0,-1.0);
		tmp.U=1;
		tmp.V=1;
		vertices.push_back(tmp);
		
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);		
		
		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
		quad=new mesh(&vertices,&indices);
	}

	{
		std::vector<unsigned int> indices;
		std::vector<vertexData> vertices;
		vertexData tmp;
		//1.
		tmp.position.change(-1.0,1.0,-1.0);
		tmp.U=0;
		tmp.V=0;
		vertices.push_back(tmp);
		//2.
		tmp.position.change(-1.0,-1.0,-1.0);
		tmp.U=0;
		tmp.V=1;
		vertices.push_back(tmp);
		//3.
		tmp.position.change(1.0,-1.0,-1.0);
		tmp.U=1;
		tmp.V=1;
		vertices.push_back(tmp);
		//4.
		tmp.position.change(1.0,1.0,-1.0);
		tmp.U=1;
		tmp.V=0;
		vertices.push_back(tmp);
		
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);		
		
		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
		quadInverted=new mesh(&vertices,&indices);
	}

}


	//take image and draw it in a framebuffer with texture as render target
	//free memory and reuse textures
	meshLoader* scene;
	Segment* segmentationGraph;
	unsigned int segmentTexture;

void preprocessImage(std::string imageName)
{
	scene = new meshLoader();
	scene->loadImage(imageName);

	glClearColor(0.25, 0.25, 0.25, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	pipeline.matrixMode(MODEL_MATRIX);
	pipeline.loadIdentity();

	displayShades->useShader();
	pipeline.updateMatrices(displayShades->getProgramId());
	scene->draw(displayShades->getProgramId());
	displayShades->delShader();

	const int NUM_SEGMENTS = 25;
	const int DEGREE = 20;
	segmentationGraph = new Segment(SCREEN_WIDTH, SCREEN_HEIGHT, NUM_SEGMENTS, DEGREE);
	segmentationGraph->segmentImage(imageName);
	segmentTexture = segmentationGraph->getSegmentationMap();
}


void display()
{

	//display ouput, less changes on produced results

	displayShades->useShader();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, segmentTexture);
	glUniform1i(glGetUniformLocation(displayShades->getProgramId(),"texture0"),0);
	pipeline.updateMatrices(displayShades->getProgramId());
	quadInverted->draw(displayShades->getProgramId());
	displayShades->delShader();
}


int main(int argc, char* argv[])
{

    //initialize SDL and OpenGLSL context
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	gWindow = SDL_CreateWindow("IMAGE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext gContext = SDL_GL_CreateContext(gWindow);
	glewExperimental = GL_TRUE;
	glewInit();
	SDL_GL_SetSwapInterval( 1 );
	gScreenSurface = SDL_GetWindowSurface(gWindow);


	//fetch and display arguments
	//Display help if the fetched argument is -h or --help
	if(argc > 1 and (std::string(argv[1]) == "-h" or std::string(argv[1]) == "--help"))
	{
		std::cout<<std::endl<<"Usage: a.out [--image ../models/textures/example.jpg]"<<std::endl;	
	}

    //parameters should be initialized to default values
    std::string imageName = "../models/textures/airplane.png";
    std::string checkName = "True";

	//FlagList is a database to store flags
    std::vector<Flag>FlagList;
    FlagList.clear();
    FlagList.push_back(Flag("--image", &imageName, "image to render"));
    FlagList.push_back(Flag("--check", &checkName, "only to check"));

	//Update FlagList with command line arguments, if any and relevant
    FlagUsage(&FlagList, argv, argc);


	bool running=true;
	SDL_Event event;	
	init();

    preprocessImage(imageName);

	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				running = false;
				break;
	
				case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							running=false;
							break;
						
					}
	
			}
		}

		display();
		SDL_GL_SwapWindow(gWindow);

	}
	delete scene;
	delete displayShades;
	delete segmentationGraph;

	SDL_FreeSurface(gScreenSurface);
	SDL_GL_DeleteContext(gContext);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
	return 0;
}

unsigned int createTexture(int w,int h)
{
	unsigned int textureId;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1,&textureId);
	glBindTexture(GL_TEXTURE_2D,textureId);
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
	
	int i;
	i=glGetError();
	if(i!=0)
		std::cout << "Error happened while loading the texture: " << gluErrorString(i) << std::endl;
	glBindTexture(GL_TEXTURE_2D,0);
	return textureId;
}


