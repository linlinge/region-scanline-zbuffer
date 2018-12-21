#include "my_opengl.h"
#include <math.h>
#include <GL/glh_glut.h>
#include <time.h>
#include "region_scan_line.h"
#include "load_obj.h"
#include "main.hpp"
using namespace glh;
glut_simple_mouse_interactor object;
Vec3f  frame_buffer[HEIGHT];
float y_world[HEIGHT];


ofstream f;
void Init()
{
	for (int i= 0; i< HEIGHT; i++)
	{
		float color = 1-(float)i/HEIGHT;
		Vec3f color_temp;
		color_temp.r = pow(color, 2);
		color_temp.g = color;
		color_temp.b = color;

		/*frame_buffer[i].r = color_temp.r;
		frame_buffer[i].g = color_temp.g;
		frame_buffer[i].b = color_temp.b;*/

		frame_buffer[i].r = 0;
		frame_buffer[i].g = 0;
		frame_buffer[i].b = 0; 

		y_world[i] = YW(i);

	}
	f.open("../output/time.txt");
	//memset(z_buffer_, 0, sizeof(float)*ROWS*COLS);
}

void OpenglFunc(int argc, char** argv)
{
	// Initial Area
	obj1.Init("./dataset/cat.obj");
	Init();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowSize(WIDTH,HEIGHT);			//set window size
	glutInitWindowPosition(100, 100);		//set window position
	glutCreateWindow(obj1.filename.data());		//window name
	glutDisplayFunc(DisplayFunc);//��Ļ��ʾ�Ļص�����
	glutIdleFunc(IdleFunc);//����ʱ�ص���������û����Ϣʱ���ã�
	glutKeyboardFunc(KeyboardFunc);//���֡���ĸ���İ������Ļص�����
	glutSpecialFunc(SpecialFunc);//���ⰴ����⣨F1~F12�����Ƽ���
	glutMouseFunc(MouseFunc);//�����
	glutMotionFunc(MotionFunc);//��갴���϶����
	glutPassiveMotionFunc(PassiveMotionFunc);//����ƶ����
	glutMainLoop();
	f.close();
}



void DisplayFunc()
{
	clock_t t0, t1;
	t0 = clock();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear color buffer
	glDisable(GL_DEPTH_TEST | GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.6f, 0.6f, 0.6f, 0.1f);	//can set the background

	float color = 0.0f;
	glBegin(GL_LINES);
	for (int i=0;i<HEIGHT;i++)
	{	
		glColor3f(frame_buffer[i].r, frame_buffer[i].g, frame_buffer[i].b);
		if (i == 240)
			glColor3f(255, 0, 255);

		glVertex2f(-1.0f,y_world[i]);
		glVertex2f(1.0f,y_world[i]);
	}
	glColor3f(230, 0,0);
	float col = 188.0f;
	glVertex2f(YW(col), -1.0f);
	glVertex2f(YW(col), 1.0f);
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

	//Vec3f light_source(500,500,500);
	//for (auto & face : obj1.faces_)
	//{		
	//	glBegin(GL_TRIANGLES);
	//	int id1 = face.id1;
	//	int id2 = face.id2;
	//	int id3 = face.id3;
	//	glColor3f(0, 0, light_source.Distance(obj1.points_[id1])/500.0);

	//	glVertex2f(XW(ROUND(obj1.points_[id1].x)), YW(ROUND(obj1.points_[id1].y)));
	//	glVertex2f(XW(ROUND(obj1.points_[id2].x)), YW(ROUND(obj1.points_[id2].y)));
	//	glVertex2f(XW(ROUND(obj1.points_[id3].x)), YW(ROUND(obj1.points_[id3].y)));
	//	glEnd();
	//}

	glutSwapBuffers();	//swap buffer
	t1 = clock();
	
	f << (t1 - t0)<<" "<<1000.0f/(t1-t0) << endl;
	//f.close();

	//cout << 1000.0 / (t1 - t0)<<"fps" << endl;
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
		/*sign_flag += 0.01;
		for (auto &point : obj1.points_)
		{
			point.x = cos(sign_flag)*(point.x - obj1.barycentre_.x) - sin(sign_flag)*(point.y - obj1.barycentre_.y) + obj1.barycentre_.x;
			point.y = cos(sign_flag)*(point.x - obj1.barycentre_.x) + cos(sign_flag)*(point.y - obj1.barycentre_.y) + obj1.barycentre_.y;
		}*/
			
	}

	if (Key == 'd' || Key == 'D')
	{
		/*sign_flag -= 0.01;
		for (auto &point : obj1.points_)
		{
			point.x = cos(sign_flag)*(point.x - obj1.barycentre_.x) - sin(sign_flag)*(point.y - obj1.barycentre_.y) + obj1.barycentre_.x;
			point.y = cos(sign_flag)*(point.x - obj1.barycentre_.x) + cos(sign_flag)*(point.y - obj1.barycentre_.y) + obj1.barycentre_.y;
		}*/
	}

	//zoom in
	if (Key == 'i' || Key == 'I')
	{
		scale += 0.01f;
	}

	if (Key == 'o' || Key == 'O')
	{
		scale -= 0.01f;
		if (scale <= 0)
			scale = scale + 0.01f;
			
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


