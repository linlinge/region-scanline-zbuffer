#include "my_opengl.h"
#include <math.h>
#include <GL/glh_glut.h>
#include <time.h>
#include "area_scan_line.h"
#include "load_obj.h"
#include "main.hpp"
using namespace glh;
glut_simple_mouse_interactor object;
Vec3f  frame_buffer[HEIGHT];
float y_world[HEIGHT];

void Init()
{
	for (int i= 0; i< HEIGHT; i++)
	{
		float color = S2W(i) / 2.0 + 0.5;
		Vec3f color_temp;
		color_temp.r = pow(color, 2);
		color_temp.g = color;
		color_temp.b = color;

		frame_buffer[i].r = color_temp.r;
		frame_buffer[i].g = color_temp.g;
		frame_buffer[i].b = color_temp.b;

		y_world[i] = S2W(i);
	}
	//memset(z_buffer_, 0, sizeof(float)*ROWS*COLS);
}



void OpenglFunc(int argc, char** argv)
{
	// Initial Area
	obj1.Init("./dataset/test1.obj");
	//scan_lines.BuildTables();
	Init();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowSize(WIDTH,HEIGHT);			//set window size
	glutInitWindowPosition(50, 50);		//set window position
	glutCreateWindow(obj1.filename.data());		//window name
	glutDisplayFunc(DisplayFunc);//��Ļ��ʾ�Ļص�����
	glutIdleFunc(IdleFunc);//����ʱ�ص���������û����Ϣʱ���ã�
	glutKeyboardFunc(KeyboardFunc);//���֡���ĸ���İ������Ļص�����
	glutSpecialFunc(SpecialFunc);//���ⰴ����⣨F1~F12�����Ƽ���
	glutMouseFunc(MouseFunc);//�����
	glutMotionFunc(MotionFunc);//��갴���϶����
	glutPassiveMotionFunc(PassiveMotionFunc);//����ƶ����
	glutMainLoop();
}



void DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear color buffer
	glDisable(GL_DEPTH_TEST | GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.6f, 0.6f, 0.6f, 0.1);	//can set the background

	float color = 0.0f;
	glBegin(GL_LINES);
	for (int i=0;i<HEIGHT;i++)
	{	
		glColor3f(frame_buffer[i].r, frame_buffer[i].g, frame_buffer[i].b);
		glVertex2f(-1,y_world[i]);
		glVertex2f(1,y_world[i]);
	}
	glEnd();

	scan_lines.BuildTables();
	scan_lines.Render();
	
	//for (int i = 0; i < obj1.points_.size(); i++)
	//{
	//	glBegin(GL_POINTS);

	//	float new_x = cos(sign_flag)*obj1.points_[i].ToWorldX() - sin(sign_flag)*obj1.points_[i].ToWorldY();
	//	float new_y = sin(sign_flag)*obj1.points_[i].ToWorldX() + cos(sign_flag)*obj1.points_[i].ToWorldY();

	//	glVertex2f(new_x*obj1.scale_, new_y*obj1.scale_);
	//	glEnd();
	//}

	/*Vec3f light_source(500,500,500);
	for (auto & face : obj1.faces_)
	{		
		glBegin(GL_TRIANGLES);
		int id1 = face.id1;
		int id2 = face.id2;
		int id3 = face.id3;
		glColor3f(0, 0, light_source.Distance(obj1.points_[id1])/500.0);

		glVertex2f(obj1.points_[id1].ToWorldX(), obj1.points_[id1].ToWorldY());
		glVertex2f(obj1.points_[id2].ToWorldX(), obj1.points_[id2].ToWorldY());
		glVertex2f(obj1.points_[id3].ToWorldX(), obj1.points_[id3].ToWorldY());
		glEnd();
	}*/

	glutSwapBuffers();	//swap buffer
}


//����ʱ���õĺ���
void IdleFunc()
{
	glutPostRedisplay();//���»��ƣ�������DisplayFunc()������
}


//���֡���ĸ���������
void KeyboardFunc(unsigned char Key, int x, int y)
{
	if (Key == 'w' || Key == 'W')
	{

	}

	if (Key == 's' || Key == 'S')
	{

	}

	if (Key == 'a' || Key == 'A')
	{
		sign_flag += 0.1;
	}

	if (Key == 'd' || Key == 'D')
	{
		sign_flag -= 0.1;
	}

	//zoom in
	if (Key == 'i' || Key == 'I')
	{
		//if(obj1.scale_<=0.9)
			obj1.scale_ += 0.01;
	}

	if (Key == 'o' || Key == 'O')
	{
		if(obj1.scale_>0.01)
			obj1.scale_ -= 0.01;
	}
}
//F1~F12�����Ƽ����
void SpecialFunc(int Key, int x, int y)
{
	if (Key == GLUT_KEY_UP)
	{

	}

	if (Key == GLUT_KEY_DOWN)
	{

	}

	if (Key == GLUT_KEY_LEFT)
	{

	}

	if (Key == GLUT_KEY_RIGHT)
	{

	}
}
//�����
//���»����ͷŲ��ܴ���
void MouseFunc(int button, int state, int x, int y)
{
	//button  ��갴�� 0 -- ���    1 -- �м�   2 -- �Ҽ�
	//state  ���״̬  0 -- ����  1 -- ̧��
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	//std::cout << "�������꣺x = " << x << " ,y = " << y << std::endl;


	if (button == 0)
	{
		if (state == 0)
		{
			//����������
		}

		if (state == 1)
		{
			//������̧��
		}
	}

	if (button == 1)
	{
		if (state == 0)
		{
			//����м�����
		}
		if (state == 1)
		{
			//����м�̧��
		}


	}
	if (button == 2)
	{
		if (state == 0)
		{
			//����Ҽ�����

		}
		if (state == 1)
		{
			//����Ҽ�̧��

		}
	}
}
//��갴���϶�
float sign_flag = 0;
void MotionFunc(int x, int y)
{
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	//��갴���϶�������



}
//����ƶ�
void PassiveMotionFunc(int x, int y)
{
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	//����ƶ�������

}


