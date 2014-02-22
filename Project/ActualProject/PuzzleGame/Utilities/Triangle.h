#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

#include "Edge.h"

class Triangle
{
public:
	Triangle(void);
	~Triangle(void);

	Edge myEdges[3];
};

#endif