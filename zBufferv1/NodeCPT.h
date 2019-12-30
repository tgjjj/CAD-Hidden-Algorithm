#pragma once

#include "Tools.h"

using namespace std;

class NodeCPT
{
public:
	NodeCPT();
	NodeCPT(double _a, double _b, double _c, double _d, int _id, int _dy, unsigned char _color[], int _colorSize);
	~NodeCPT();
	virtual string toString();
	//int link(NodeCPT *next);

public:
	double a;
	double b;
	double c;
	double d;
	int id;
	int dy;
	unsigned char color[Tools::colorSize];
	//NodeCPT *nextNode;
};

