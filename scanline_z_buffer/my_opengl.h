#pragma once
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "main.hpp"

extern Vec3f  frame_buffer[HEIGHT]; //store the texture information for one frame
extern int old_x;
extern float sign_flag;
extern float y_world[HEIGHT];

extern void OpenglFunc(int argc, char** argv);
void DisplayFunc();//显示函数
void IdleFunc();//闲置时调用的函数
void KeyboardFunc(unsigned char Key, int x, int y);//数字、字母键按键检测
void SpecialFunc(int Key, int x, int y);//F1~F12、控制键检测
void MouseFunc(int button, int state, int x, int y);//鼠标检测
void MotionFunc(int x, int y);//鼠标按着拖动
void PassiveMotionFunc(int x, int y);//鼠标移动
