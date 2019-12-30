#include "pch.h"
#include "NodeCPT.h"

using namespace std;

NodeCPT::NodeCPT() = default;

NodeCPT::NodeCPT(double _a, double _b, double _c, double _d, int _id, int _dy, unsigned char _color[], int _colorSize)
{
	this->a = _a;
	this->b = _b;
	this->c = _c;
	this->d = _d;
	this->id = _id;
	this->dy = _dy;
	for (int i = 0; i < _colorSize; i ++) {
		this->color[i] = _color[i];
	}
	//this->nextNode = NULL;
}

NodeCPT::~NodeCPT()
{
}

string NodeCPT::toString()
{
	ostringstream oss;
	oss << "NodeCPT { a = " << this->a << ", b = " << this->b << ", c = " << this->c << ", d = " << this->d
		<< ", id = " << this->id << ", dy = " << this->dy << ", color = ( " << (int) this->color[0] << ", " << (int) this->color[1]
		<< ", " << (int) this->color[2] 
		<< " )"
		//<< ", next = " << (this->nextNode != NULL) 
		<< " }" << endl;
	string str = oss.str();
	return str;
}

/*
int NodeCPT::link(NodeCPT *next)
{
	this->nextNode = next;
	return 0;
}
*/