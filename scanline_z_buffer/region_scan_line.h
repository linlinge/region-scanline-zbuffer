#pragma once
#include <vector>
#include "my_opengl.h"

#include <algorithm>
#define IS_SINGULAR(a,b,c)  (((a>b)&&(a>c)) || ((a<b)&&(a<c)))
#define IS_IN(x1,y1,x2,y2,x3,y3)  (((x2-x1)*(y3-y1)+(y1-y2)*(x3-x1))*(y2-y1)/abs(y2-y1)<0)
using namespace std;
enum status {in=1,out=0,singular=-1};

class EdgeElement
{
public:
	float x;	// x coordinate for up endpoint
	float xc;	// x coordinate for current line 
	float dx;	// x error for adjacent scan line
	int dy;		// number of  scan lines which coverd by one edge
	int dy_max;	// the capacity of dy
	int id;		// identifier of this polygon

	void CopyTo(EdgeElement& dat)
	{
		dat.x=x;	
		dat.xc=xc;	
		dat.dx=dx;	
		dat.dy=dy;	
		dat.dy_max=dy_max;	
		dat.id=id;
	}

	static void swap(EdgeElement& edge1, EdgeElement& edge2)
	{
		float temp_x;	
		float temp_xc;	
		float temp_dx;	
		int   temp_dy;		
		int   temp_dy_max;	
		int   temp_id;

		temp_x = edge1.x; edge1.x = edge2.x; edge2.x = temp_x;
		temp_xc = edge1.xc; edge1.xc = edge2.xc; edge2.xc = temp_xc;
		temp_dx = edge1.dx; edge1.dx = edge2.dx; edge2.dx = temp_dx;
		temp_dy = edge1.dy; edge1.dy = edge2.dy; edge2.dy = temp_dy;
		temp_dy_max = edge1.dy_max; edge1.dy_max = edge2.dy_max; edge2.dy_max = temp_dy_max;
		temp_id = edge1.id; edge1.id = edge2.id; edge2.id = temp_id;
	}
};

class PolygonElement
{
public:
	float a, b, c, d;	// parameters of this polygon plan
	int id;				// identifier of this polygon
	Vec3f color;		// color of this polygon
};



class AreaScanLines
{
public:
	vector<EdgeElement> ET_[HEIGHT];
	vector<PolygonElement> PT_;

	vector<EdgeElement> AET_;
	vector<PolygonElement> APT_;
	vector<float> xc_;
	vector<int> id_;

	void BuildTables();
	void Render();
	int ZCompare(int id1,int id2,float x,float y);
};
extern AreaScanLines scan_lines;
void FindLR(vector<float> &dat, int x1, int x2, int& left1, int &left2, int& right1, int& right2);






