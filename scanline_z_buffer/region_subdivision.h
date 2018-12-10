#pragma once
#include <vector>
#include "my_opengl.h"
#include "load_obj.h"
#include <algorithm>
#define IS_SINGULAR(a,b,c)  (((a>b)&&(a>c)) || ((a<b)&&(a<c)))
#define IS_IN(x1,y1,x2,y2,x3,y3)  (((x2-x1)*(y3-y1)-(y1-y2)*(x3-x1))<0)

using namespace std;

enum status {in,singular,out};
class bunch
{
public:

	//IPL 
	int faces_id;	
	
	//AET
	status flag;
	float aet_norm_x,aet_norm_y,aet_norm_z;


	bool operator ==(bunch & ist)
	{
		return ((aet_norm_x == ist.aet_norm_x)&&(flag==ist.flag));
	}
	bool operator <(bunch & ist)
	{
		return aet_norm_x < ist.aet_norm_x;
	}
	bool operator >(bunch & ist)
	{
		return aet_norm_x > ist.aet_norm_x;
	}
};
class ScanLine
{
public:
	vector<bunch> bunch_;
};

class ScanLines
{
public:
	ScanLine scan_lines_[ROWS];
	void Init();
	void Algorithm();
};

extern ScanLines scan_lines;






