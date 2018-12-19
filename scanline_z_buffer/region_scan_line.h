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
	float x;	// x coordinate for up end
	float xc;	// x coordinate for current line 
	float dx;	// x error for adjacent scan line
	int dy;		// number of  scan lines which coverd by one edge
	int dy_max;	// the capacity of dy
	int id;		// identifier of this polygon
	int flag;	// status of edge

	void CopyTo(EdgeElement& dat)
	{
		dat.x=x;	
		dat.xc=xc;	
		dat.dx=dx;	
		dat.dy=dy;	
		dat.dy_max=dy_max;	
		dat.id=id;
		dat.flag=flag;	
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

	void BuildTables();
	void Render();
};
extern AreaScanLines scan_lines;






