#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class Tools
{
public:
	Tools();
	~Tools();

	static vector<string> split(string str, char c);
	static int rounding(double num);
	static int max3(int a, int b, int c);
	static int min3(int a, int b, int c);
	static vector<unsigned char> randomUnsignedChar(int num);
	
	static const int colorSize = 3;
};

