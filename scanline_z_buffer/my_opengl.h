#pragma once
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "load_obj.h"

#define WIDTH 600
#define HEIGHT 600

#define ROWS	5000

#define S_MAX 1
#define S_MIN -1

#define N2S(DATA) ((DATA+1)*ROWS/2)
#define S2N(DATA) (2.0/ROWS*DATA-1)
#define DY 0.001

extern void OpenglFunc(int argc,char** argv);
struct Vector2D
{
	float fX;
	float fY;
};

extern Vector2D g_vector2D;
extern int old_x;
extern float sign_flag;


void DisplayFunc();//��ʾ����
void IdleFunc();//����ʱ���õĺ���
void KeyboardFunc(unsigned char Key, int x, int y);//���֡���ĸ���������
void SpecialFunc(int Key, int x, int y);//F1~F12�����Ƽ����
void MouseFunc(int button, int state, int x, int y);//�����
void MotionFunc(int x, int y);//��갴���϶�
void PassiveMotionFunc(int x, int y);//����ƶ�
