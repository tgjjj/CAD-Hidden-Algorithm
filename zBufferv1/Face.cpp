#include "pch.h"
#include "Face.h"


Face::Face() = default;

Face::Face(Vertex _a, Vertex _b, Vertex _c, unsigned char _color[], int _colorSize)
{
	this->a = _a;
	this->b = _b;
	this->c = _c;
	this->equation = point3ToFaceEquation(_a, _b, _c);
	for (int i = 0; i < _colorSize; i++) {
		this->color[i] = _color[i];
	}
}


Face::~Face()
{
}

vector<double> Face::point3ToFaceEquation(Vertex _a, Vertex _b, Vertex _c)
{
	vector<double> planeEquation;
	double x1 = _a.x, y1 = _a.y, z1 = _a.z;
	double x2 = _b.x, y2 = _b.y, z2 = _b.z;
	double x3 = _c.x, y3 = _c.y, z3 = _c.z;
	double a = y1 * z2 - y1 * z3 - y2 * z1 + y2 * z3 + y3 * z1 - y3 * z2;
	double b = -x1 * z2 + x1 * z3 + x2 * z1 - x2 * z3 - x3 * z1 + x3 * z2;
	double c = x1 * y2 - x1 * y3 - x2 * y1 + x2 * y3 + x3 * y1 - x3 * y2;
	double d = -x1 * y2 * z3 + x1 * y3 * z2 + x2 * y1 * z3 - x2 * y3 * z1 - x3 * y1 * z2 + x3 * y2 * z1;
	planeEquation.push_back(a);
	planeEquation.push_back(b);
	planeEquation.push_back(c);
	planeEquation.push_back(d);
	return planeEquation;
}

string Face::toString()
{
	ostringstream oss;
	oss << "Face {" << endl
		<< "a : " << this->a.toString()
		<< "b : " << this->b.toString()
		<< "c : " << this->c.toString()
		<< "equation : " << this->equation[0] << "x + " << this->equation[1] << "y + " << this->equation[2] << "z + " << this->equation[3] << " = 0"
		<< endl;
	string str = oss.str();
	return str;
}

int Face::maxY()
{
	return Tools::max3(this->a.y, this->b.y, this->c.y);
}

int Face::minY()
{
	return Tools::min3(this->a.y, this->b.y, this->c.y);
}

