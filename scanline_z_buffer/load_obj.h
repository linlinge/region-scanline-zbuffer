#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "main.hpp"
using namespace std;

class Patch {
public:
	//int id1, id2, id3,id4,id5;
	vector<int> vertex_id_;
	vector<int> texture_id_;
	vector<int> normal_id_;
	Vec3f color_;
};

class Obj {	
	void Init();// compute Initial scale
public:
	string filename;
	vector<Vec3f> points_;
	vector<Patch> faces_;
	vector<Vec3f> vn_;
	vector<Vec3f> vt_;
	Obj(string filename);
	void Init(string filename);
	Obj() {};
	bool LoadObjFile();
	void SetColor();
};

extern Obj obj1;