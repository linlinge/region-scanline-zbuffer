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
	int id1, id2, id3,id4,id5;
};

class Obj {	
	void Init();// compute Initial scale
public:
	Vec3f barycentre_;

	string filename;
	vector<Vec3f> points_;
	vector<TrianglePatch> faces_;
	Obj(string filename);
	void Init(string filename);
	Obj() {};
	bool LoadObjFile();
};

extern Obj obj1;