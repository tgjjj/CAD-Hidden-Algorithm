#pragma once

#include "NodeCST.h"
#include "NodeCPT.h"
#include "Tools.h"
#include "Face.h"
#include "NodeACPT.h"
#include "NodeACST.h"
//#include "NodeRegionACST.h"

class Obj
{
public:
	Obj();
	Obj(string _fileName, double _scale, int _resolutionX, int _resolutionY, int _offsetX, int _offsetY, int _sideView);
	~Obj();
	int loadObj(vector<Face> &faces, vector<Vertex> &vertices, int resolutionX, int resolutionY, double scale, string fileName, int offsetX, int offsetY, int view);
	int createCTs(vector<Face> faces, int resolutionX, int resolutionY);
	Mat render(int mode);
	int loadNewNodes(int currentY, vector<NodeACPT> &ACPT, vector<NodeACST> &ACST);
	int updateOldNodes(int currentY, vector<NodeACPT> &ACPT, vector<NodeACST> &ACST);
	int renderCurrentLine(Mat frameBuffer, int currentY, vector<NodeACPT> &ACPT, vector<NodeACST> &ACST, int mode);

private:
	vector<vector<NodeCST>> CST;
	vector<vector<NodeCPT>> CPT;
	int resolutionX;
	int resolutionY;
	vector<NodeCPT> faceTable;
};


