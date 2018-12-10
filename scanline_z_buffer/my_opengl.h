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


void DisplayFunc();//显示函数
void IdleFunc();//闲置时调用的函数
void KeyboardFunc(unsigned char Key, int x, int y);//数字、字母键按键检测
void SpecialFunc(int Key, int x, int y);//F1~F12、控制键检测
void MouseFunc(int button, int state, int x, int y);//鼠标检测
void MotionFunc(int x, int y);//鼠标按着拖动
void PassiveMotionFunc(int x, int y);//鼠标移动
