#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Vertex3f {
public:
	float x, y, z;
	Vertex3f& operator=(Vertex3f &vertex)
	{
		x = vertex.x;
		y = vertex.y;
		z = vertex.z;
	}
};

class TrianglePatch {
public:
	int id1, id2, id3;
	float norm_kxy12, norm_kxy13, norm_kxy23;
	float norm_kyz12, norm_kyz13, norm_kyz23;
	float norm_x1, norm_x2, norm_x3, norm_y1, norm_y2, norm_y3,norm_z1,norm_z2,norm_z3;
};

class Obj {
	float scale = 1.5;
public:
	float max_xyz_;
	float scale_current_;


	string filename;
	vector<Vertex3f> points_;
	vector<TrianglePatch> faces_;
	Obj(string filename);
	void Init(string filename);
	Obj() {};
	bool LoadObjFile();
};

extern Obj obj1;