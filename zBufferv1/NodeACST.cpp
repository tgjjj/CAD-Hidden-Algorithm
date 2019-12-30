#include "pch.h"
#include "NodeACST.h"


NodeACST::NodeACST() = default;

NodeACST::NodeACST(NodeCST left, NodeCST right, NodeACPT face, int y)
{
	this->xl = left.x;
	this->dxl = left.dx;
	this->dyl = left.dy;
	this->xr = right.x;
	this->dxr = right.dx;
	this->dyr = right.dy;
	this->zl = (this->xl * face.a + y * face.b + face.d) * (-1) / face.c;
	this->dzx = (-1) * face.a / face.c;
	this->dzy = face.b / face.c;
	this->id = face.id;
}

NodeACST::~NodeACST() = default;

string NodeACST::toString()
{
	ostringstream oss;
	oss << "NodeACST { ( xl = " << this->xl << ", dxl = " << this->dxl << ", dyl = " << this->dyl
		<< " ), ( xr = " << this->xr << ", dxr = " << this->dxr << ", dyr = " << this->dyr
		<< " ), ( zl = " << this->zl << ", dzx = " << this->dzx << ", dzy = " << this->dzy << ", id = " << this->id << " ) }" << endl;
	string str = oss.str();
	return str;
}

bool NodeACST::nextLine()
{
	this->dyl--;
	this->dyr--;
	this->xl += this->dxl;
	this->xr += this->dxr;
	this->zl += this->dzx * this->dxl + this->dzy;
	if (dyl < 0 || dyr < 0) {
		//cout << this->toString() << endl;
		exit(6);
	}
	else if (dyl * dyr == 0 && dyl + dyr != 0) {
		return true;
	}
	return false;
}

int NodeACST::sideRelay(vector<NodeCST> lineCST)
{
	int nodeIndex = NodeCST::binarySearchByID(lineCST, this->id);
	if (this->dyl == 0) {
		this->dxl = lineCST[nodeIndex].dx;
		this->dyl = lineCST[nodeIndex].dy;
	}
	else if (this->dyr == 0) {
		this->dxr = lineCST[nodeIndex].dx;
		this->dyr = lineCST[nodeIndex].dy;
	}
	else {
		exit(7);
	}
	return 0;
}

NodeRSLPatchACST::NodeRSLPatchACST() = default;

NodeRSLPatchACST::NodeRSLPatchACST(double _x, int _id, bool _right)
{
	this->x = _x;
	this->id = _id;
	this->right = _right;
}

string NodeRSLPatchACST::toString()
{
	ostringstream oss;
	oss << "RSLPatchACST { x = " << this->x << ", id = " << this->id << ", right = " << this->right << " }" << endl;
	string str = oss.str();
	return str;
}

bool NodeRSLPatchACST::sortByXAscend(NodeRSLPatchACST &a, NodeRSLPatchACST &b)
{
	const double epsilon = 0.00001;
	if (fabs(a.x - b.x) < epsilon)
		return (!(a.right)) && (b.right);
	return a.x < b.x;
}