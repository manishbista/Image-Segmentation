
#include "header/segment.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <time.h>
#include <algorithm>

extern SDL_Surface* gScreenSurface;

bool operator<(const Edge& a, const Edge& b) { return a.weight < b.weight; }

Segment::Segment(const int _SCREEN_WIDTH, const int _SCREEN_HEIGHT, const int _NUM_SEGMENTS, const int _DEGREE)
{
	Segment::SCREEN_WIDTH = _SCREEN_WIDTH;
	Segment::SCREEN_HEIGHT = _SCREEN_HEIGHT;
	Segment::NUM_SEGMENTS = _NUM_SEGMENTS;
	Segment::DEGREE = _DEGREE;

	//Initialize Flags indicating initialization of memory to false
	//change to True if successfully initialized memory
	UNIVERSE_CREATED = false;
	EDGE_CREATED = false; 
	THRESHOLD_LOADED = false;
	IMAGE_LOADED = false;
	OUTPUT_BUFFER_LOADED = false;


	Uni = new Universe(SCREEN_WIDTH * SCREEN_HEIGHT);
	UNIVERSE_CREATED = true;

	Segment::threshold = new float[SCREEN_WIDTH * SCREEN_HEIGHT];
	THRESHOLD_LOADED = true;

	segmentImageBuffer = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT * RGBA];
	OUTPUT_BUFFER_LOADED = true;

	PrepareEdges();
}


bool Segment::loadImage(std::string imageName)
{
	SDL_Surface copyScreenSurface = *gScreenSurface;
	SDL_Surface* imgs = IMG_Load(imageName.c_str());

	if(imgs == NULL)
	{
		std::cout<<" Image for Segmentation "<<imageName<<" couldn't load"<<std::endl;
		return false;
	}
	SDL_Surface* img2 = SDL_ConvertSurface(imgs, copyScreenSurface.format, 0);

	if(img2 == NULL)
	{
		std::cout<<" Image for Segmentation "<<imageName<<" couldn't convert"<<std::endl;
		return false;
	}

	SDL_Rect stretchRect;
	stretchRect.x = 0.0;
	stretchRect.y = 0.0;
	stretchRect.w = Segment::SCREEN_WIDTH;
	stretchRect.h = Segment::SCREEN_HEIGHT;
	
	SDL_BlitScaled( img2, NULL, &copyScreenSurface, &stretchRect);	
		

	//buffer to store pixel values has been loaded, pixel range [0, 255] converted using GL_UNSIGNED_BYTE
	//pointer to memory, which holds rgb values, is passed to colorImageBuffer, thus eliminating 
	//need to reserve memory beforehand
	Segment::colorImageBuffer = (unsigned char*) copyScreenSurface.pixels;
	SDL_FreeSurface(imgs);
	SDL_FreeSurface(img2);
	SDL_FreeSurface(&copyScreenSurface);

	Segment::IMAGE_LOADED = true;	
	return true;

}

bool Segment::PrepareEdges()
{
	Segment::pEdge = new Edge[SCREEN_WIDTH*SCREEN_HEIGHT*NEIGHBOURS];
	EDGE_CREATED = true;
	//co-ordinates of grid[i, j]	
	int left, right, bottom, top, current;

	for(int j = 0; j < SCREEN_HEIGHT; j++)
	{
		top = j+1;
		bottom = j-1;
		if(top >= SCREEN_HEIGHT) top = 0;
		else top = 1;
		if(bottom < 0) bottom = 0;
		else bottom = 1;

		for(int i = 0; i < SCREEN_WIDTH; i++)
		{
			right = i+1;
			left = i-1;
			if(right >= SCREEN_WIDTH) right = 0;
			else right = 1;
			if(left < 0) left = 0;
			else left = 1;
		
			current = j*SCREEN_WIDTH + i;
			//One of the nodes of edge is the current pixel position ID
			for(int k = 0; k < NEIGHBOURS; k++)
				pEdge[NEIGHBOURS * current + k].nodeA = current;		

			if(top and left) pEdge[NEIGHBOURS * current + TOP_LEFT].nodeB = current + SCREEN_WIDTH - 1;
			else pEdge[NEIGHBOURS * current + TOP_LEFT].nodeB = -1;

			if(top) pEdge[NEIGHBOURS * current + TOP_CENTER].nodeB = current + SCREEN_WIDTH;
			else pEdge[NEIGHBOURS * current + TOP_CENTER].nodeB = -1;

			if(top and right) pEdge[NEIGHBOURS * current + TOP_RIGHT].nodeB = current + SCREEN_WIDTH + 1;
			else pEdge[NEIGHBOURS * current + TOP_RIGHT].nodeB = -1;

			if(right) pEdge[NEIGHBOURS * current + MIDDLE_RIGHT].nodeB = current + 1;
			else pEdge[NEIGHBOURS * current + MIDDLE_RIGHT].nodeB = -1;

			if(bottom and right) pEdge[NEIGHBOURS * current + BOTTOM_RIGHT].nodeB = current - SCREEN_WIDTH + 1;
			else pEdge[NEIGHBOURS * current + BOTTOM_RIGHT].nodeB = -1;

			if(bottom) pEdge[NEIGHBOURS * current + BOTTOM_CENTER].nodeB = current - SCREEN_WIDTH;
			else pEdge[NEIGHBOURS * current + BOTTOM_CENTER].nodeB = -1;
 
			if(bottom and left) pEdge[NEIGHBOURS * current + BOTTOM_LEFT].nodeB = current - SCREEN_WIDTH - 1;
			else pEdge[NEIGHBOURS * current + BOTTOM_LEFT].nodeB = -1;

			if(left) pEdge[NEIGHBOURS * current + MIDDLE_LEFT].nodeB = current - 1;
			else pEdge[NEIGHBOURS * current + MIDDLE_LEFT].nodeB = -1;

		}
	}
	//Nodes for edges:pEdge of Disjoint Tree: Uni has been populated
	return true;
}


bool Segment::AssignEdgeWeight()
{
	//if pEdge has not been initialized yet, return false
	//or, if image has not been loaded yet, return false
	if(not EDGE_CREATED) 
	{
		std::cout<<"ERROR: Attempt to use pEdge without initializing memory";
		return false;
	}
	if(not IMAGE_LOADED)
	{
		std::cout<<"ERROR: Flag IMAGE_LOADED = FALSE, Problem with initializing memory for image";
		return false;
	}

	int posA, posB;
	float diffR, diffG, diffB, weight;
	for(int k = 0; k < SCREEN_WIDTH *SCREEN_HEIGHT *NEIGHBOURS; k++)
	{
		//if it doesn't have nodes off the image boundary
		if(pEdge[k].nodeA != -1 and pEdge[k].nodeB != -1)
		{
			//calculate intensity difference from colorImageBuffer
			//uniformly normalize weights to have "weight" range from [0 to 255]
			posA = pEdge[k].nodeA;
			posB = pEdge[k].nodeB;	
			diffR = (float)(colorImageBuffer[RGBA * posA + R] - colorImageBuffer[RGBA * posB + R])/255.0;
			diffG = (float)(colorImageBuffer[RGBA * posA + G] - colorImageBuffer[RGBA * posB + G])/255.0;
			diffB = (float)(colorImageBuffer[RGBA * posA + B] - colorImageBuffer[RGBA * posB + B])/255.0;

			weight = sqrt(pow(diffR, 2) + pow(diffG, 2) + pow(diffB, 2));
			pEdge[k].weight = weight;
		}			
	}

    return true;
}


void Segment::segmentGraph()
{
	//initialize threshold
	for(int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
		threshold[i] = calculateThreshold(1, Segment::DEGREE);

	//sort list of edges based on weights
	//edges with highest similarity value are paired first 
	std::sort(pEdge, pEdge + (SCREEN_WIDTH*SCREEN_HEIGHT*NEIGHBOURS));

	int parentA, parentB;
	Edge* mEdge;
	for(int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT*NEIGHBOURS; i++)
	{	
		mEdge = &pEdge[i];
		if(mEdge->nodeA != -1 and mEdge->nodeB != -1)
		{
			parentA = Uni->findParentOf(mEdge->nodeA);
			parentB = Uni->findParentOf(mEdge->nodeB);
			
			//if both of them do not aleady point to the same segment
			if(parentA != parentB)
			{
				//if External Boundary Dissimilarity: weight is less than that within the boundary: threshold, join the nodes
				if( (mEdge->weight <= threshold[parentA]) and (mEdge->weight <= threshold[parentB]) )
				{
					Uni->joinNodes(parentA, parentB);
					parentA = Uni->findParentOf(parentA);
					//increase Dissimilarity within the segment
					threshold[parentA] = mEdge->weight + calculateThreshold(Uni->size(parentA), DEGREE);
				}
			}
		}
	}
	//End of Segmentation Process
	//However, Disjoint Forest is not reduced yet, final Parent Assignment needed
	for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
		Uni->findParentOf(i);
}


void Segment::fillSegmentationBuffer()
{
	int parentNode;
	for(int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
	{
		parentNode = Uni->findParentOf(i);
		segmentImageBuffer[RGBA*i + R] = colorImageBuffer[RGBA*parentNode + R];
		segmentImageBuffer[RGBA*i + G] = colorImageBuffer[RGBA*parentNode + G];
		segmentImageBuffer[RGBA*i + B] = colorImageBuffer[RGBA*parentNode + B];
	}
}

void Segment::createSegmentationTexture(unsigned char* buf)
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &segmentationTexture);
	glBindTexture(GL_TEXTURE_2D, segmentationTexture);
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,0);	
}

void Segment::segmentImage(std::string imageName)
{
	//initializations finished
	//Session Inclusive Operations follow
	loadImage(imageName);
	AssignEdgeWeight();
	segmentGraph();
	fillSegmentationBuffer();
	createSegmentationTexture(segmentImageBuffer);
}

Segment::~Segment()
{
	if(UNIVERSE_CREATED) delete Uni;
	if(EDGE_CREATED) delete pEdge;
	if(THRESHOLD_LOADED) delete threshold;
	if(OUTPUT_BUFFER_LOADED) delete segmentImageBuffer;
}





