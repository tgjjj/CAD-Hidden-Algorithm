#include "pch.h"
#include "Tools.h"


Tools::Tools() = default;

Tools::~Tools()
{
	srand(time(NULL));
}

vector<string> Tools::split(string str, char c)
{
	vector<string> vstr;
	int pos = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == c) {
			if (pos != i) {
				vstr.push_back(str.substr(pos, i - pos));
			}
			pos = i + 1;
		}
	}
	if (pos < str.length())
		vstr.push_back(str.substr(pos, str.length() - pos));
	return vstr;
}

int Tools::rounding(double num)
{
	return num >= 0 ? (num >= floor(num) + 0.5 ? ceil(num) : floor(num)) : (num <= floor(num) + 0.5 ? floor(num) : ceil(num));
}

int Tools::max3(int a, int b, int c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int Tools::min3(int a, int b, int c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

vector<unsigned char> Tools::randomUnsignedChar(int num)
{
	
	vector<unsigned char> unsignedChar;
	for (int i = 0; i < num; i++) {
		unsignedChar.push_back(rand() % 56 + 150);
	}
	
	return unsignedChar;
}