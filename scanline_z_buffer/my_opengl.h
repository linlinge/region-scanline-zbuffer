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
void DisplayFunc();//��ʾ����
void IdleFunc();//����ʱ���õĺ���
void KeyboardFunc(unsigned char Key, int x, int y);//���֡���ĸ���������
void SpecialFunc(int Key, int x, int y);//F1~F12�����Ƽ����
void MouseFunc(int button, int state, int x, int y);//�����
void MotionFunc(int x, int y);//��갴���϶�
void PassiveMotionFunc(int x, int y);//����ƶ�
