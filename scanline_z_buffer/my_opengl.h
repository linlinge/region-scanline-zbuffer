#pragma once
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "load_obj.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

// normalized coordinate system definition
#define NORM_MAX 1
#define NORM_MIN -1
#define NORM_DX 0.001
#define NORM_DY 0.0001

// self-defined coordinate, relay on normalized coordinate
#define ROWS (int)(2.0/NORM_DY)
#define COLS (int)(2.0/NORM_DX)



extern void OpenglFunc(int argc,char** argv);
struct Vector2D
{
	float fX;
	float fY;
};
class Color3f
{
public:
	float r, g, b;
	Color3f & operator=(Color3f & obj)
	{
		if (this != &obj)
		{
			r = obj.r;
			g = obj.g;
			b = obj.b;
		}
		return (*this);
	}
};

class Buffer
{
public:
	Color3f  frame_buffer_[ROWS]; //store the texture information for one frame
	//float z_buffer_[ROWS*COLS];	//store the z value
	Buffer();
};

extern Vector2D g_vector2D;
extern int old_x;
extern float sign_flag;
extern Buffer buf;

void DisplayFunc();//��ʾ����
void IdleFunc();//����ʱ���õĺ���
void KeyboardFunc(unsigned char Key, int x, int y);//���֡���ĸ���������
void SpecialFunc(int Key, int x, int y);//F1~F12�����Ƽ����
void MouseFunc(int button, int state, int x, int y);//�����
void MotionFunc(int x, int y);//��갴���϶�
void PassiveMotionFunc(int x, int y);//����ƶ�
int N2S(float data);
float S2N(int data);
