#pragma once

#include "Tools.h"
#include "Vertex.h"

class NodeCST
{
public:
	NodeCST();
	NodeCST(int _x, double _dx, int _dy, int _id);
	NodeCST(Vertex a, Vertex b, int faceID);    //We assume that (Vertex a) has a larger y 
	~NodeCST();
	virtual string toString();
	static int binarySearchByID(const vector<NodeCST> vectorNodeCST, const int faceID);
	//int link(NodeCST *next);

public:
	int x;
	double dx;
	int dy;
	int id;
	//NodeCST *nextNode;
};

