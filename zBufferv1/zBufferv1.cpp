// zBufferv1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "NodeCPT.h"
#include "NodeCST.h"
#include "Obj.h"
#include "Tools.h"

int main()
{
    //std::cout << "Hello World!\n"; 
	//unsigned char color[3] = { 10, 10, 10 };
	//NodeCPT *a = new NodeCPT(1, 2, 3, 4, 5, 6, color, 3);
	//cout << a->toString() << endl;
	//NodeCST *b = new NodeCST(1, 2.0, 3, 4);
	//cout << b->toString() << endl;
	//Obj a;
	//string input = "ahhhhhh";
	//vector<string> result = Tools::split(input, ' ');
	//cout << "Mario Sailor" << endl;
	//cout << input.substr(0, 0) << endl;
	/*for (auto s : result) {
		cout << s << endl;
	}*/
	while (1) {
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "Please enter \".obj\" file path and several parameters." << endl;
		cout << "Form: <objpath> <scale>  <resolutionX> <resolutionY> <offsetX> <offsetY> <view>" << endl;
		cout << "Type: <string>  <double> <int>         <int>         <int>     <int>     <0 for front, 1 for side and 2 for top>" << endl;
		cout << "For example: E:/homework/CAD/repo/zBufferv1/horse.obj 0.2 1000 1000 500 500 1" << endl;
		cout << "Enter \"#\" to let the program calculate the appropriate parameters for you." << endl;
		string path;
		double scale;
		int resolutionX, resolutionY, offsetX, offsetY;
		int view;
		cin >> path;
		if (path == "#") {
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Please enter \".obj\" file path. Enter \"#\" to use the default \"horse.obj\" model and its default settings." << endl;
			cout << "Please note that there shouldn't be any space(\" \") in your file path, or the program might not be able to find the correct file." << endl;
			cin >> path;
			if (path == "#") {
				//Obj a("E:/homework/CAD/repo/zBufferv1/horse.obj", 0.2, 1000, 1000, 500, 500, false);
				path = "./horse.obj";
				scale = 0.36;
				resolutionX = 1000;
				resolutionY = 1000;
				offsetX = 500;
				offsetY = 200;
				view = 1;
			}
			else {
				scale = 0;
				resolutionX = 0;
				resolutionY = 0;
				offsetX = 0;
				offsetY = 0;
				view = 0;
				cout << "-------------------------------------------------------------------------" << endl;
				cout << "Please choose a perspective. \"0\" for front view, \"1\" for side view and \"2\" for top view." << endl;
				cin >> view;
			}
		}
		else {
			cin >> scale >> resolutionX >> resolutionY >> offsetX >> offsetY >> view;
		}
		Obj a(path, scale, resolutionX, resolutionY, offsetX, offsetY, view);
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "Please choose render mode: 0 for scan line and 1 for region scan line algorithm. Enter -1 to skip." << endl;
		int mode = 0;
		cin >> mode;
		if (mode == -1) {
			continue;
		}
		int runTimes = 1;
		clock_t start = clock();
		//clock_t pause0 = clock();
		Mat result = a.render(mode);
		//clock_t pause1 = clock();
		//cout << "Time " << i << ": " << pause1 - pause0 << " ms" << endl;
		//pause0 = pause1;
		for (int i = 1; i < runTimes; i++) {
			Mat result = a.render(mode);
			//clock_t pause1 = clock();
			//cout << "Time " << i << ": " << pause1 - pause0 << " ms" << endl;
			//pause0 = pause1;
		}
		clock_t end = clock();
		cout << "Time spent on rendering " << runTimes << " times" << ": " << end - start << "ms" << endl;
		if (mode == 0) {
			//imwrite("SLZBuffer.jpg", result);
			imshow("Render by Scanline ZBuffer", result);
		}
		else {
			//imwrite("RegionSLZBuffer.jpg", result);
			imshow("Render by Region Scanline ZBuffer", result);
		}
		waitKey(0);
	}
	
	//cout << Tools::rounding(7.5) << endl;
	
	/*Face face;
	face.a.x = 1;
	face.a.y = 7;
	face.a.z = 4;
	face.b.x = 5;
	face.b.y = 1;
	face.b.z = 0;
	face.c.x = 0;
	face.c.y = 0;
	face.c.z = 1;
	vector<double> planeEquation = Obj::point3ToPlaneEquation(face);
	cout << planeEquation[0] << "x + " << planeEquation[1] << "y + " << planeEquation[2] << "z + " << planeEquation[3] << " = 0" << endl;*/
	
	/*vector<unsigned char> unsignedChar = Tools::randomUnsignedChar(100);
	for (auto c : unsignedChar) {
		cout << int(c) << endl;
	}*/

	/*Mat img(300, 200, CV_8UC3, Scalar(0, 0, 255));
	imshow("test", img);
	waitKey(0);*/

	/*Mat img = a.render(0);
	imshow("img", img);
	waitKey(0);*/

	//cout << numeric_limits<double>::max() << endl;
	/*double b = 0;
	double a = -1.0 / b;
	cout << a << endl;
	if (isinf(a)) {
		cout << "Get DA*ZE" << endl;
	}*/

	/*vector<int> a = { 1, 2, 3, 4 };
	for (auto &i : a) {
		if (i == 3) {
			swap(i, a[a.size()-1]);
		}
	}
	a.pop_back();
	for (auto i : a) {
		cout << i << endl;
	}*/
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件