#include "pch.h"
#include "NodeACPT.h"

NodeACPT::NodeACPT() = default;

NodeACPT::NodeACPT(NodeCPT node)
{
	this->a = node.a;
	this->b = node.b;
	this->c = node.c;
	this->d = node.d;
	this->dy = node.dy;
	this->id = node.id;
	for (int i = 0; i < 3; i++) {
		this->color[i] = node.color[i];
	}
}

NodeACPT::~NodeACPT() = default;

string NodeACPT::toString()
{
	ostringstream oss;
	oss << "NodeACPT { a = " << this->a << ", b = " << this->b << ", c = " << this->c << ", d = " << this->d
		<< ", id = " << this->id << ", dy = " << this->dy << ", color = ( " << (int)this->color[0] << ", " << (int)this->color[1]
		<< ", " << (int)this->color[2]
		<< " )"
		//<< ", next = " << (this->nextNode != NULL) 
		<< " }" << endl;
	string str = oss.str();
	return str;
}

bool NodeACPT::nextLine()
{
	this->dy--;
	return dy < 0;
}