#include "pch.h"
#include "Obj.h"

Obj::Obj() = default;

Obj::Obj(string _fileName, double _scale, int _resolutionX, int _resolutionY, int _offsetX, int _offsetY, int _sideView)
{
	vector<Vertex> vertices;
	vector<Face> faces;
	double scale = _scale;
	int offsetX = _offsetX;
	int offsetY = _offsetY;
	bool openFailedFlag = false;
	bool incorrectViewFlag = false;
	if (_resolutionX == 0) {
		double maxX = 0;
		double maxY = 0;
		double minX = 0;
		double minY = 0;
		fstream fin;
		fin.open(_fileName, ios::in);
		if (fin) {
			string temp;
			while (getline(fin, temp)) {
				//cout << temp << endl;
				if (temp[0] == 'v' && temp[1] == ' ') {
					vector<string> tempv = Tools::split(temp, ' ');
					double x;
					double y;
					if (_sideView == 0) {
						x = atof(tempv[1].c_str());
						y = atof(tempv[2].c_str());
					}
					else if (_sideView == 1) {
						x = atof(tempv[3].c_str());
						y = atof(tempv[2].c_str());
					}
					else if (_sideView == 2) {
						x = atof(tempv[1].c_str());
						y = (-1) * atof(tempv[3].c_str());
					}
					else {
						cout << "Incorrect View Number!" << endl;
						incorrectViewFlag = true;
					}
					if (x > maxX) {maxX = x;}
					else if (x < minX) { minX = x;}
					if (y > maxY) { maxY = y;}
					else if (y < minY) { minY = y;}
				}
			}
			double spanX = maxX - minX;
			double spanY = maxY - minY;
			double centerX = (maxX + minX) / 2;
			double centerY = (maxY + minY) / 2;
			if (spanX > spanY) {
				this->resolutionX = 1000;
				this->resolutionY = Tools::rounding(800 * spanY / spanX) + 200;
				scale = 800.0 / spanX;
			}
			else {
				this->resolutionY = 1000;
				this->resolutionX = Tools::rounding(800 * spanX / spanY) + 200;
				scale = 800.0 / spanY;
			}
			centerX *= scale;
			centerY *= scale;
			offsetX = Tools::rounding(this->resolutionX / 2 - centerX);
			offsetY = Tools::rounding(this->resolutionY / 2 - centerY);
		}
		else {
			cout << "File does not exist!" << endl;
			openFailedFlag = true;
		}
	}
	else {
		this->resolutionX = _resolutionX;
		this->resolutionY = _resolutionY;
	}
	if (!openFailedFlag && !incorrectViewFlag) {
		this->CPT.resize(resolutionY);
		this->CST.resize(resolutionY);
		cout << "Called with args: " << "ResolutionX = " << this->resolutionX << ", ResolutionY = " << this->resolutionY
			<< "\nScale = " << scale << ", OffsetX = " << offsetX << ", OffsetY = " << offsetY << endl;
		loadObj(faces, vertices, this->resolutionX, this->resolutionY, scale, _fileName, offsetX, offsetY, _sideView);
		createCTs(faces, this->resolutionX, this->resolutionY);
	}
}

Obj::~Obj()
{
}

int Obj::loadObj(vector<Face> &faces, vector<Vertex> &vertices, int resolutionX, int resolutionY, double scale, string fileName, int offsetX, int offsetY, int view)
{
	if (Tools::colorSize != 3) {
		cout << "Warning: Code in function \"renderCurrentLine\" need to be changed before changing colorSize" << endl;
		exit(14);
	}
	fstream fin;
	fin.open(fileName, ios::in);
	if (fin) {
		cout << "File open succeed" << endl;
	}
	else {
		cout << "File does not exist!" << endl;
		return 1;
	}
	string temp;
	while (getline(fin, temp)) {
		//cout << temp << endl;
		if (temp[0] == 'v' && temp[1] == ' ') {
			vector<string> tempv = Tools::split(temp, ' ');
			if (view == 0) {
				Vertex vertex(Tools::rounding(atof(tempv[1].c_str()) * scale) + offsetX,
					Tools::rounding(atof(tempv[2].c_str()) * scale) + offsetY,
					Tools::rounding(atof(tempv[3].c_str()) * scale));
				if (vertex.x >= resolutionX || vertex.y >= resolutionY || vertex.x < 0 || vertex.y < 0) {
					cout << "Vertex out of screen!" << endl;
					cout << vertex.toString() << endl;
					return 2;
				}
				vertices.push_back(vertex);
			}
			else if (view == 1) {
				Vertex vertex(Tools::rounding(atof(tempv[3].c_str()) * scale) + offsetX,
					Tools::rounding(atof(tempv[2].c_str()) * scale) + offsetY,
					Tools::rounding(atof(tempv[1].c_str()) * scale));
				if (vertex.x >= resolutionX || vertex.y >= resolutionY || vertex.x < 0 || vertex.y < 0) {
					cout << "Vertex out of screen!" << endl;
					cout << vertex.toString() << endl;
					return 2;
				}
				vertices.push_back(vertex);
			}
			else if (view == 2) {
				Vertex vertex(Tools::rounding(atof(tempv[1].c_str()) * scale) + offsetX,
					(-1) * Tools::rounding(atof(tempv[3].c_str()) * scale) + offsetY,
					Tools::rounding(atof(tempv[2].c_str()) * scale));
				if (vertex.x >= resolutionX || vertex.y >= resolutionY || vertex.x < 0 || vertex.y < 0) {
					cout << "Vertex out of screen!" << endl;
					cout << vertex.toString() << endl;
					return 2;
				}
				vertices.push_back(vertex);
			}
			else {
				cout << "Incorrect View Number!" << endl;
				return 3;
			}
		}
		else if (temp[0] == 'f' && temp[1] == ' ') {
			vector<string> tempf = Tools::split(temp, ' ');
			/*int a = atoi(Tools::split(tempf[1], '/')[0].c_str()) - 1;
			int b = atoi(Tools::split(tempf[2], '/')[0].c_str()) - 1;
			int c = atoi(Tools::split(tempf[3], '/')[0].c_str()) - 1;
			if (a == b || a == c || b == c) {
				cout << temp << endl;
				exit(1);
			}*/
			unsigned char color[Tools::colorSize];
			vector<unsigned char> unsignedChar = Tools::randomUnsignedChar(Tools::colorSize);
			for (int i = 0; i < Tools::colorSize; i++) {
				color[i] = unsignedChar[i];
			}
			Face face(vertices[atoi(Tools::split(tempf[1], '/')[0].c_str()) - 1], 
				vertices[atoi(Tools::split(tempf[2], '/')[0].c_str()) - 1], 
				vertices[atoi(Tools::split(tempf[3], '/')[0].c_str()) - 1],
				color, Tools::colorSize);
			faces.push_back(face);
			//cout << tempf.size() << endl;
			if (tempf.size() == 5) {
				Face face2(vertices[atoi(Tools::split(tempf[1], '/')[0].c_str()) - 1],
					vertices[atoi(Tools::split(tempf[3], '/')[0].c_str()) - 1],
					vertices[atoi(Tools::split(tempf[4], '/')[0].c_str()) - 1],
					color, Tools::colorSize);
				faces.push_back(face2);
			}
		}
		else {
			continue;
		}
	}
	/*int iface = 0;
	for (auto face : faces) {
		cout << iface << endl;
		cout << face.toString() << endl;
		iface++;
	}*/
	return 0;
}

int Obj::createCTs(vector<Face> faces, int resolutionX, int resolutionY)
{
	int faceID = 0;
	//cout << "Start creating CTs" << endl;
	cout << "Total Faces: " << faces.size() << endl;
	for (auto face : faces) {
		//cout << faceID << endl;
		int faceMaxY = face.maxY();
		int faceMinY = face.minY();
		
		NodeCPT nodeCPT(face.equation[0], face.equation[1], face.equation[2], face.equation[3], 
			faceID, faceMaxY - faceMinY, face.color, Tools::colorSize);
		if (nodeCPT.c == 0) {
			//cout << "No need" << endl;
			continue;
		}
		CPT[faceMaxY].push_back(nodeCPT);
		faceTable.push_back(nodeCPT);
		vector<Vertex> face3Vertex = { face.a, face.b, face.c };
		sort(face3Vertex.begin(), face3Vertex.end(), Vertex::sortByYDescend);
		NodeCST nodeCST0(face3Vertex[0], face3Vertex[1], faceID);
		NodeCST nodeCST1(face3Vertex[0], face3Vertex[2], faceID);
		NodeCST nodeCST2(face3Vertex[1], face3Vertex[2], faceID);
		CST[face3Vertex[0].y].push_back(nodeCST0);
		CST[face3Vertex[0].y].push_back(nodeCST1);
		CST[face3Vertex[1].y].push_back(nodeCST2);
		faceID++;
	}
	/*for (auto line : CPT) {
		//cout << (int)line.size() << endl;
		for (auto node : line) {
			cout << node.toString() << endl;
		}
		cout << "-------------------------------------" << endl;
	}*/
	/*for (auto line : CST) {
		//cout << (int)line.size() << endl;
		for (auto node : line) {
			cout << node.toString() << endl;
		}
		cout << "-------------------------------------" << endl;
	}*/
	return 0;
}

Mat Obj::render(int mode)
{
	Mat frameBuffer(this->resolutionY, this->resolutionX, CV_8UC3, Scalar(255, 255, 255));
	vector<NodeACPT> ACPT;
	vector<NodeACST> ACST;
	double updateTime = 0;
	double newNodesTime = 0;
	double renderTime = 0;
	double partTime = 0;
	for (int currentY = this->resolutionY - 1; currentY >= 0; currentY--) {
		//clock_t oneRoundStart = clock();
		updateOldNodes(currentY, ACPT, ACST);
		//clock_t updateDone = clock();
		loadNewNodes(currentY, ACPT, ACST);
		//clock_t newNodesDone = clock();
		int onePartTime = renderCurrentLine(frameBuffer, currentY, ACPT, ACST, mode);
		//clock_t renderDone = clock();
		//updateTime += updateDone - oneRoundStart;
		//newNodesTime += newNodesDone - updateDone;
		//renderTime += renderDone - newNodesDone;
		//partTime += onePartTime;
		//cout << "ACPT: " << ACPT.size() << endl;
		//cout << "ACST: " << ACST.size() << endl;
		/*for (auto nodeACST : ACST) {
			cout << nodeACST.toString() << endl;
		}*/
		/*for (int i = 0; i < ACPT.size(); i++) {
			if (ACPT[i].id != ACST[i].id) {
				cout << ACPT[i].toString() << endl;
				cout << ACST[i].toString() << endl;
				exit(10);
			}
		}*/
	}
	/*for (auto nodeACPT : ACPT) {
		cout << nodeACPT.toString() << endl;
	}*/
	/*for (auto nodeACST : ACST) {
		cout << nodeACST.toString() << endl;
	}*/
	//cout << "Update time: " << updateTime << " ms" << endl;
	//cout << "New    time: " << newNodesTime << " ms" << endl;
	//cout << "Render time: " << renderTime << " ms" << endl;
	//cout << "Part time: " << partTime << " ms" << endl;
	return frameBuffer;
}

int Obj::loadNewNodes(int currentY, vector<NodeACPT> &ACPT, vector<NodeACST> &ACST)
{
	auto iterCST = CST[currentY].begin();
	for (auto &nodeCPT : this->CPT[currentY]) {
		NodeACPT nodeACPT(nodeCPT);
		ACPT.push_back(nodeACPT);
		while (iterCST->id != nodeACPT.id && iterCST != CST[currentY].end()) {
			iterCST++;
		}
		if (iterCST == CST[currentY].end()) {
			exit(1);
		}
		else if (iterCST->id != (iterCST + 1)->id) {
			exit(2);
		}
		else if (isinf(iterCST->dx)) {
			if ((*(iterCST + 1)).x < (*(iterCST + 2)).x) {
				NodeACST nodeACST(*(iterCST + 1), *(iterCST + 2), nodeACPT, currentY);
				ACST.push_back(nodeACST);
			}
			else if ((*(iterCST + 1)).x > (*(iterCST + 2)).x) {
				NodeACST nodeACST(*(iterCST + 2), *(iterCST + 1), nodeACPT, currentY);
				ACST.push_back(nodeACST);
			}
			else {
				exit(3);
			}
		}
		else if (isinf((iterCST + 1)->dx)) {
			if ((*(iterCST)).x < (*(iterCST + 2)).x) {
				NodeACST nodeACST(*(iterCST), *(iterCST + 2), nodeACPT, currentY);
				ACST.push_back(nodeACST);
			}
			else if ((*(iterCST)).x > (*(iterCST + 2)).x) {
				NodeACST nodeACST(*(iterCST + 2), *(iterCST), nodeACPT, currentY);
				ACST.push_back(nodeACST);
			}
			else {
				exit(4);
			}
		}
		else {
			if ((*(iterCST)).x < (*(iterCST + 1)).x) {
				NodeACST nodeACST(*(iterCST), *(iterCST + 1), nodeACPT, currentY);
				ACST.push_back(nodeACST);
			}
			else if ((*(iterCST)).x > (*(iterCST + 1)).x) {
				NodeACST nodeACST(*(iterCST + 1), *(iterCST), nodeACPT, currentY);
				ACST.push_back(nodeACST);
			}
			else {
				if ((*(iterCST)).dx < (*(iterCST + 1)).dx) {
					NodeACST nodeACST(*(iterCST), *(iterCST + 1), nodeACPT, currentY);
					ACST.push_back(nodeACST);
				}
				else if ((*(iterCST)).dx > (*(iterCST + 1)).dx) {
					NodeACST nodeACST(*(iterCST + 1), *(iterCST), nodeACPT, currentY);
					ACST.push_back(nodeACST);
				}
				else {
					exit(5);
				}
			}
		}
	}
	return 0;
}

int Obj::updateOldNodes(int currentY, vector<NodeACPT> &ACPT, vector<NodeACST> &ACST)
{
	/*int iterACPT = 0;
	while(iterACPT < ACPT.size()) {
		if (ACPT[iterACPT].nextLine()) {
			std::swap(ACPT[iterACPT], ACPT[ACPT.size() - 1]);
			ACPT.pop_back();
		}
		else {
			iterACPT++;
		}
	}
	int iterACST = 0;
	while(iterACST < ACST.size()) {
		int nextLineCase = ACST[iterACST].nextLine();
		if (nextLineCase == 1) {
			std::swap(ACST[iterACST], ACST[ACST.size() - 1]);
			ACST.pop_back();
		}
		else if (nextLineCase == 2) {
			ACST[iterACST].sideRelay(this->CST[currentY]);
			iterACST++;
		}
		else {
			iterACST++;
		}
	}*/
	int iter = 0;
	while (iter < ACPT.size()) {
		if (ACPT[iter].nextLine()) {
			std::swap(ACPT[iter], ACPT[ACPT.size() - 1]);
			ACPT.pop_back();
			std::swap(ACST[iter], ACST[ACST.size() - 1]);
			ACST.pop_back();
		}
		else if (ACST[iter].nextLine()) {
			ACST[iter].sideRelay(this->CST[currentY]);
			iter++;
		}
		else {
			iter++;
		}
	}
	return 0;
}

int Obj::renderCurrentLine(Mat frameBuffer, int currentY, vector<NodeACPT> &ACPT, vector<NodeACST> &ACST, int mode)
{
	int partTime = 0;
	clock_t s;
	clock_t e;
	if(mode == 0) {
		vector<double> zBuffer(this->resolutionX, (-1) * numeric_limits<double>::max());
		for (int i = 0; i < ACST.size(); i ++) {
			double z = ACST[i].zl;
			vector<unsigned char> color(Tools::colorSize);
			color[0] = ACPT[i].color[0];
			color[1] = ACPT[i].color[1];
			color[2] = ACPT[i].color[2];
			for (int x = ACST[i].xl; x <= ACST[i].xr; x++) {
				if (zBuffer[x] < z) {
					zBuffer[x] = z;
					frameBuffer.at<Vec3b>(this->resolutionY - currentY - 1, x)[0] = color[0];
					frameBuffer.at<Vec3b>(this->resolutionY - currentY - 1, x)[1] = color[1];
					frameBuffer.at<Vec3b>(this->resolutionY - currentY - 1, x)[2] = color[2];
				}
				z += ACST[i].dzx;
			}
		}
	}
	else if(mode == 1) {
		vector<int> IPL;
		vector<NodeRSLPatchACST> RSLPatchACST;
		for (auto nodeACST : ACST) {
			NodeRSLPatchACST leftNodeRSLPatchACST(nodeACST.xl, nodeACST.id, false);
			NodeRSLPatchACST rightNodeRSLPatchACST(nodeACST.xr, nodeACST.id, true);
			RSLPatchACST.push_back(leftNodeRSLPatchACST);
			RSLPatchACST.push_back(rightNodeRSLPatchACST);
		}
		sort(RSLPatchACST.begin(), RSLPatchACST.end(), NodeRSLPatchACST::sortByXAscend);
		/*cout << "-----------------------------------------" << endl;
		for (auto nodeRSLPatchACST : RSLPatchACST) {
			cout << nodeRSLPatchACST.toString() << endl;
		}*/
		double previousX = 0;
		double currentX = 0;
		double previousMaxZ = (-1) * numeric_limits<double>::max();
		int previousNearestIPid = -1;
		int newIPid = -1;
		unsigned char color[Tools::colorSize] = { 255, 255, 255 };
		for (auto &nodeRSLPatchACST : RSLPatchACST) {
			currentX = nodeRSLPatchACST.x;
			double midX = (currentX + previousX) / 2;
			double maxZ = (-1) * numeric_limits<double>::max();
			if (previousNearestIPid == -1) {
				if (IPL.size() == 0) {
					color[0] = 255;
					color[1] = 255;
					color[2] = 255;
				}
				else {
					for (auto IPid : IPL) {
						double currentZ = (-1) * (faceTable[IPid].a * midX + faceTable[IPid].b * currentY + faceTable[IPid].d) / faceTable[IPid].c;
						if (currentZ > maxZ) {
							previousNearestIPid = IPid;
							maxZ = currentZ;
							color[0] = faceTable[IPid].color[0];
							color[1] = faceTable[IPid].color[1];
							color[2] = faceTable[IPid].color[2];
						}
					}
				}
			}
			else {
				if (newIPid != -1) {
					double newZ = (-1) * (faceTable[newIPid].a * midX + faceTable[newIPid].b * currentY + faceTable[newIPid].d) / faceTable[newIPid].c;
					double oldZ = (-1) * (faceTable[previousNearestIPid].a * midX + faceTable[previousNearestIPid].b * currentY + faceTable[previousNearestIPid].d) / faceTable[previousNearestIPid].c;
					if (newZ > oldZ) {
						previousNearestIPid = newIPid;
						maxZ = newZ;
						color[0] = faceTable[newIPid].color[0];
						color[1] = faceTable[newIPid].color[1];
						color[2] = faceTable[newIPid].color[2];
					}
				}
				else {
					maxZ = (-1) * (faceTable[previousNearestIPid].a * midX + faceTable[previousNearestIPid].b * currentY + faceTable[previousNearestIPid].d) / faceTable[previousNearestIPid].c;
				}
			}
			/*if (IPL.size() == 0) {
				color[0] = 255;
				color[1] = 255;
				color[2] = 255;
			}
			else {
				for (auto IPid : IPL) {*/
					/*for (auto &nodeACPT : ACPT) {
						if (nodeACPT.id == IPid) {
							double currentZ = (-1) * (nodeACPT.a * midX + nodeACPT.b * currentY + nodeACPT.d) / nodeACPT.c;
							if (currentZ > maxZ) {
								maxZ = currentZ;
								color[0] = nodeACPT.color[0];
								color[1] = nodeACPT.color[1];
								color[2] = nodeACPT.color[2];
							}
						}
					}*/
					/*double currentZ = (-1) * (faceTable[IPid].a * midX + faceTable[IPid].b * currentY + faceTable[IPid].d) / faceTable[IPid].c;
					if (currentZ > maxZ) {
						maxZ = currentZ;
						color[0] = faceTable[IPid].color[0];
						color[1] = faceTable[IPid].color[1];
						color[2] = faceTable[IPid].color[2];
					}
				}
			}*/
			//s = clock();
			//Point pl((previousMaxZ < maxZ) ? previousX : (previousX + 1), this->resolutionY - currentY - 1);
			//Point pr(currentX, this->resolutionY - currentY - 1);
			for (int iterX = (previousMaxZ < maxZ) ? previousX : (previousX + 1); iterX <= currentX; iterX++) {
				frameBuffer.at<Vec3b>(this->resolutionY - currentY - 1, iterX)[0] = color[0];
				frameBuffer.at<Vec3b>(this->resolutionY - currentY - 1, iterX)[1] = color[1];
				frameBuffer.at<Vec3b>(this->resolutionY - currentY - 1, iterX)[2] = color[2];
			}
			previousMaxZ = maxZ; 
			//line(frameBuffer, pl, pr, Scalar(color[0], color[1], color[2]), 1);
			//e = clock();
			//partTime += e - s;
			previousX = currentX;
			if (nodeRSLPatchACST.right) {
				bool flagexit8 = true;
				int iterIPL = 0;
				while(iterIPL < IPL.size()){
					if (IPL[iterIPL] == nodeRSLPatchACST.id) {
						swap(IPL[iterIPL], IPL[IPL.size()-1]);
						IPL.pop_back();
						flagexit8 = false;
						newIPid = -1;
						if (previousNearestIPid == nodeRSLPatchACST.id) {
							previousNearestIPid = -1;
						}
						break;
					}
					iterIPL++;
				}
				if (flagexit8) {
					exit(8);
				}
			}
			else {
				IPL.push_back(nodeRSLPatchACST.id);
				newIPid = nodeRSLPatchACST.id;
			}
			/*for (auto nodeIPL : IPL) {
				cout << nodeIPL << " ";
			}
			cout << "#" << endl;*/
		}
		if (IPL.size() != 0) {
			exit(9);
		}
	}
	return partTime;
}