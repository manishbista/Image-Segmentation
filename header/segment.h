
#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include "disjointSet.h"


//An Edge structure represents branch in disjoint forest
//Initialized to point to invalid nodes and have max dissimilarity
//Nodes ranging from [0, wXh] are valid nodes
//Max Dissimilairty gives such nodes less priority while sorting
struct Edge{
	float weight;
	int nodeA, nodeB;
	Edge(): weight(7.5), nodeA(-1), nodeB(-1) {}

};


class Segment
{
	private:

		//constants
		int SCREEN_WIDTH, SCREEN_HEIGHT;
		int NUM_SEGMENTS, DEGREE;

		//buffer to hold image to segment
		unsigned char* colorImageBuffer;	
		bool loadImage(std::string imageName);
		bool IMAGE_LOADED;

		//Disjoint Forest
		Universe* Uni;
		bool UNIVERSE_CREATED;

		//Edges of Tree
		Edge* pEdge;
		bool EDGE_CREATED;
		bool PrepareEdges();
		bool AssignEdgeWeight();
		enum{
			TOP_LEFT,
			TOP_CENTER,
			TOP_RIGHT,
			MIDDLE_RIGHT,
			BOTTOM_RIGHT,
			BOTTOM_CENTER,
			BOTTOM_LEFT,
			MIDDLE_LEFT,
			NEIGHBOURS
		
		};

		enum{
			R,
			G,
			B,
			A,
			RGBA
		};


		//Segmentation
		void segmentGraph();
		float* threshold;
		bool THRESHOLD_LOADED;
 		float calculateThreshold(int size, int c){ return (float)c/size;}

		//Get Segmentation Map as texture to display
		unsigned char* segmentImageBuffer;
		unsigned int segmentationTexture;
		bool OUTPUT_BUFFER_LOADED;
		void fillSegmentationBuffer();
		void createSegmentationTexture(unsigned char* buf);


	public:
		Segment(const int _SCREEN_WIDTH, const int _SCREEN_HEIGHT, const int _NUM_SEGMENTS, const int _DEGREE);
		void segmentImage(std::string imageName);
		unsigned int getSegmentationMap() const { return segmentationTexture; }
		~Segment();


};


#endif
