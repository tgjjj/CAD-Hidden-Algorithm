#include "pch.h"
#include "Vertex.h"


Vertex::Vertex() = default;

Vertex::Vertex(int _x, int _y, int _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}


Vertex::~Vertex()
{
}

string Vertex::toString()
{
	ostringstream oss;
	oss << "Vertex { x = " << this->x << ", y = " << this->y << ", z = " << this->z << " }" << endl;
	string str = oss.str();
	return str;
}

bool Vertex::sortByYDescend(Vertex a, Vertex b)
{
	return a.y > b.y;
}