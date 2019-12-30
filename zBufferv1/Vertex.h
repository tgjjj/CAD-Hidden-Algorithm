#pragma once

#include "Tools.h"

class Vertex
{
public:
	Vertex();
	Vertex(int _x, int _y, int _z);
	~Vertex();
	string toString();
	static bool sortByYDescend(Vertex a, Vertex b);

	int x;
	int y;
	int z;
};

