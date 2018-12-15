#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "main.hpp"
using namespace std;

class TrianglePatch {
public:
	int id1, id2, id3;
};

class Obj {	
	void Init();// compute Initial scale
public:
	float scale_ = 0.6;
	Vec3f centre_;

	string filename;
	vector<Vec3f> points_;
	vector<TrianglePatch> faces_;
	Obj(string filename);
	void Init(string filename);
	Obj() {};
	bool LoadObjFile();
};

extern Obj obj1;