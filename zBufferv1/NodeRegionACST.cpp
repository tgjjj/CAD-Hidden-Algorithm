#include "pch.h"
#include "NodeRegionACST.h"

string NodeRegionACST::toString()
{
	ostringstream oss;
	oss << "NodeRegionACST {x = " << this->x << ", dx = " << this->dx << ", dy = " << this->dy << ", id = " << this->id
		//<< ", next = " << (this->nextNode != NULL) 
		<< "}" << endl;
	string str = oss.str();
	return str;
}

bool NodeRegionACST::nextLine()
{
	this->x += this->dx;
	this->dy--;
	return dy < 0;
}