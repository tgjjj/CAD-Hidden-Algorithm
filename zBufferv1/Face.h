#pragma once

#include "Tools.h"
#include "Vertex.h"

class Face
{
public:
	Face();
	Face(Vertex _a, Vertex _b, Vertex _c, unsigned char _color[], int _colorSize);
	~Face();
	static vector<double> point3ToFaceEquation(Vertex a, Vertex b, Vertex c);
	string toString();
	int maxY();
	int minY();

public:
	Vertex a;
	Vertex b;
	Vertex c;
	vector<double> equation;
	unsigned char color[Tools::colorSize];
};

