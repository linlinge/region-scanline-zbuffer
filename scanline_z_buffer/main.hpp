#pragma once
#include <math.h>
// window's width and height
#define WIDTH 600
#define HEIGHT 600

// normalized coordinate system definition
#define NORM_MAX 1
#define NORM_MIN -1
#define DX 0.001
#define DY 0.00001

// transformation between normlized coordinate and screen coordinate
#define W2S(DATA)	((DATA + 1)*HEIGHT / 2)
#define S2W(DATA)	(2.0 / HEIGHT * DATA - 1)

// use to judge float equivalence
#define EPS 0.000001

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
	Vec3f() :r(0), g(0), b(0) {};
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
		return sqrt(pow(x-dat.x, 2) + pow(y-dat.y, 2));
	}
	float Distance(Vec3f & dat)
	{
		return sqrt(pow(x - dat.x, 2) + pow(y - dat.y, 2)+pow(z-dat.z,2));
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
	
	float ToWorldX()
	{
		return  (2.0 / HEIGHT * x - 1);
	}
	float ToWorldY()
	{
		return  (2.0 / HEIGHT * y - 1);
	}
	float ToWorldZ()
	{
		return  (2.0 / HEIGHT * z - 1);
	}
};
