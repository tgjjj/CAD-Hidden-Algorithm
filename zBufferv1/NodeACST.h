#pragma once

#include "Tools.h"
#include "NodeCST.h"
#include "NodeACPT.h"

class NodeACST
{
public:
	NodeACST();
	NodeACST(NodeCST left, NodeCST right, NodeACPT face, int y);
	~NodeACST();
	string toString();
	bool nextLine();
	int sideRelay(vector<NodeCST> lineCST);
	

public:
	double xl;
	double dxl;
	int dyl;
	double xr;
	double dxr;
	int dyr;
	double zl;
	double dzx;
	double dzy;
	int id;
};

class NodeRSLPatchACST {
public:
	NodeRSLPatchACST();
	NodeRSLPatchACST(double _x, int _id, bool _right);
	string toString();
	static bool sortByXAscend(NodeRSLPatchACST &a, NodeRSLPatchACST &b);

public:	
	double x;
	int id;
	bool right;
};