#pragma once
#include <math.h>
// window's width and height
#define WIDTH 600
#define HEIGHT 600

// normalized coordinate system definition
#define NORM_MAX 1.0f
#define NORM_MIN -1.0f
#define DX 0.001.0f
#define DY 0.00001.0f

// transformation between normlized coordinate and screen coordinate
#define XS(DATA)	((DATA+1)*WIDTH/2.0)
#define YS(DATA)	((-DATA+1)*HEIGHT/2.0)

#define XW(DATA)	(2.0*DATA/WIDTH-1.0f)
#define YW(DATA)	(1.0f-2.0f*DATA/HEIGHT)

// use to judge float equivalence
#define EPS 0.000001f

#define ROUND(DATA) ((int)(DATA+0.5f))

#define MAX2(D1,D2)	(D1>D2 ? D1: D2)
#define MAX3(D1,D2,D3) (MAX2(MAX2(D1,D2),D3))

#define MIN2(D1,D2) (D1<D2 ? D1:D2)
#define MIN3(D1,D2,D3) (MIN2(MIN2(D1,D2),D3))

//#define DEBUG

#define BACKGROUND INT_MAX-1

class Vec3f
{
public:
	union {
		struct {
			float r, g, b;
		};
		struct {
			float x, y, z;
		};
	};
	Vec3f() :r(0.0f), g(0.0f), b(0.0f) {};
	Vec3f(float r1,float g1, float b1)
	{
		r = r1;
		g = g1;
		b = b1;
	};
	Vec3f & operator=(const Vec3f & obj)
	{
		r = obj.r;
		g = obj.g;
		b = obj.b;
		return (*this);
	}

	float DistanceXY(Vec3f & dat)
	{
		return sqrt(pow(x-dat.x, 2.0f) + pow(y-dat.y, 2.0f));
	}
	float Distance(Vec3f & dat)
	{
		return sqrt(pow(x - dat.x, 2.0f) + pow(y - dat.y, 2.0f)+pow(z-dat.z,2.0f));
	}

	Vec3f& operator *(float scale)
	{
		x = x * scale;
		y = y * scale;
		z = z * scale;
		return *this;
	}
	Vec3f& operator /(float scale)
	{
		x = x / scale;
		y = y / scale;
		z = z / scale;
		return *this;
	}
	Vec3f& operator +(Vec3f & dat)
	{
		x = x + dat.x;
		y = y + dat.y;
		z = z + dat.z;
		return *this;
	}

	float GetArc(Vec3f& dat)
	{
		float arc = x * dat.x + y * dat.y + z * dat.z;
		return arc / sqrt(x*x + y * y + z * z) / sqrt(dat.x*dat.x+dat.y*dat.y+dat.z*dat.z);
	}

	static Vec3f GetNorm(Vec3f& dat)
	{
		Vec3f norm=dat;
		float a = sqrt(dat.x*dat.x + dat.y * dat.y + dat.z * dat.z);
		return norm / a;
	}

	static Vec3f Dot(Vec3f& dat1, Vec3f& dat2)
	{
		Vec3f rst;
		rst.x = dat1.y * dat2.z - dat2.y * dat1.z;
		rst.y = dat2.x * dat1.z - dat1.x * dat2.z;
		rst.z = dat1.x * dat2.y - dat2.x * dat1.y;
	}

};
extern float scale;