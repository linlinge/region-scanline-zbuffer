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
#define W2S(DATA)	((DATA + 1.0f)*HEIGHT / 2.0f)
#define S2W(DATA)	(2.0f / HEIGHT * DATA - 1.0f)

// use to judge float equivalence
#define EPS 0.000001f

#define ROUND(DATA) ((int)(DATA+0.5f))

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
	
	float ToWorldX()
	{
		return  (2.0f / HEIGHT * x - 1.0f);
	}
	float ToWorldY()
	{
		return  (2.0f / HEIGHT * y - 1.0f);
	}
	float ToWorldZ()
	{
		return  (2.0f / HEIGHT * z - 1.0f);
	}
};
