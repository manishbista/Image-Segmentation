
#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <iostream>

struct Elements{
   int ID;
   int rank;
   int itsParent;
   int size;
};

class Universe{
	public:
		Universe(int _NUM_ELEMENTS);
		int findParentOf(int inputNode) const;
		int size(int node) { return UniverseElements[node].size; }
		void joinNodes(int nodeA, int nodeB);
		~Universe();

	private:
		int NUM_ELEMENTS;
		Elements* UniverseElements;

};

#endif
