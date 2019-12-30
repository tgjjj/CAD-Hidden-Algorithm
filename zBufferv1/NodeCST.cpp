#include "pch.h"
#include "NodeCST.h"

NodeCST::NodeCST() = default;

NodeCST::NodeCST(int _x, double _dx, int _dy, int _id)
{
	this->x = _x;
	this->dx = _dx;
	this->dy = _dy;
	this->id = _id;
	//this->nextNode = NULL;
}

NodeCST::NodeCST(Vertex a, Vertex b, int faceID)
{
	this->x = a.x;
	this->dx = (double)(b.x - a.x) / (double)(a.y - b.y);
	this->dy = a.y - b.y;
	this->id = faceID;
}

NodeCST::~NodeCST() = default;

string NodeCST::toString()
{
	ostringstream oss;
	oss << "NodeCST {x = " << this->x << ", dx = " << this->dx << ", dy = " << this->dy << ", id = " << this->id 
		//<< ", next = " << (this->nextNode != NULL) 
		<< "}" << endl;
	string str = oss.str();
	return str;
}

int NodeCST::binarySearchByID(const vector<NodeCST> vectorNodeCST, const int faceID) {
	int low, mid, high;
	low = 0;
	high = vectorNodeCST.size() - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (vectorNodeCST[mid].id < faceID) {
			low = mid + 1;
		}
		else if (vectorNodeCST[mid].id > faceID) {
			high = mid - 1;
		}
		else {
			return mid;
		}
	}

	return -1;
}

/*
int NodeCST::link(NodeCST * next)
{
	this->nextNode = next;
	return 0;
}
*/

