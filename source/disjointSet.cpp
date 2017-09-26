
#include "header/disjointSet.h"


Universe::Universe(int _NUM_ELEMENTS)
{
	Universe::NUM_ELEMENTS = _NUM_ELEMENTS;
	Universe::UniverseElements = new Elements[NUM_ELEMENTS];
	
	for(int i = 0; i < NUM_ELEMENTS; i++)
	{
		UniverseElements[i].ID = i;
		UniverseElements[i].rank = 0;
		UniverseElements[i].itsParent = i;
	}
}

Universe::~Universe()
{
	delete UniverseElements;
}

int Universe::findParentOf(int inputNode) const
{
	int varNode = inputNode;
	
	//repeat until the parent of Node points to itself, traverse up the tree
	while(varNode != UniverseElements[varNode].itsParent)
		varNode = UniverseElements[varNode].itsParent;
	//after parentNode is found, assign it as the required parent
	UniverseElements[inputNode].itsParent = varNode;
	return varNode;
}

void Universe::joinNodes(int x, int y)
{
	if (UniverseElements[x].rank > UniverseElements[y].rank) 
	{
    UniverseElements[y].itsParent = x;				//x now points to y
    UniverseElements[x].size += UniverseElements[y].size;	//increase size of x
    UniverseElements[x].rank++;
	} 
	else
	{							//if x.rank <= y.rank, make y parent of x
    UniverseElements[x].itsParent = y;
    UniverseElements[y].size += UniverseElements[x].size;
    UniverseElements[y].rank++;
	}
}




