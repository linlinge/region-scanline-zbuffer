#include "my_opengl.h"
#include <math.h>
#include <GL/glh_glut.h>
#include <time.h>
#include "region_subdivision.h"


using namespace glh;

glut_simple_mouse_interactor object;
Vector2D g_vector2D = { -0.2f,0.2f };
Buffer buf;

Buffer::Buffer()
{
	for (int i= 0; i< ROWS; i++)
	{
		float color = S2N(i) / 2.0 + 0.5;
		Color3f color_temp;
		color_temp.r = pow(color, 2);
		color_temp.g = color;
		color_temp.b = color;

		frame_buffer_[i].r = color_temp.r;
		frame_buffer_[i].g = color_temp.g;
		frame_buffer_[i].b = color_temp.b;

	}
	//memset(z_buffer_, 0, sizeof(float)*ROWS*COLS);
}



void OpenglFunc(int argc, char** argv)
{
	clock_t start, stop;
	start = clock();
	obj1.Init("./dataset/duck.obj");
	stop = clock();
	cout << (stop - start) / 1000.00 << "s" << endl;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);			//set window size
	glutInitWindowPosition(50, 50);		//set window position
	glutCreateWindow(obj1.filename.data());		//window name
	glutDisplayFunc(DisplayFunc);//屏幕显示的回调函数
	glutIdleFunc(IdleFunc);//闲置时回调函数（当没有消息时调用）
	glutKeyboardFunc(KeyboardFunc);//数字、字母键的按键检测的回调函数
	glutSpecialFunc(SpecialFunc);//特殊按键检测（F1~F12，控制键）
	glutMouseFunc(MouseFunc);//鼠标检测
	glutMotionFunc(MotionFunc);//鼠标按着拖动检测
	glutPassiveMotionFunc(PassiveMotionFunc);//鼠标移动检测
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
	//for (float posY = -1.0f; posY <= 1.0f; posY += 0.001f)
	for (int i=0;i<ROWS;i++)
	{	
		glColor3f(buf.frame_buffer_[i].r, buf.frame_buffer_[i].g, buf.frame_buffer_[i].b);
		glVertex2f(-1,S2N(i));
		glVertex2f(1,S2N(i));
	}
	glEnd();

	scan_lines.Init();
	scan_lines.Algorithm();
	
	//for (int i = 0; i < obj1.points_.size(); i++)
	//{
	//	glBegin(GL_POINTS);

	//	float new_x = cos(sign_flag)*obj1.points_[i].x - sin(sign_flag)*obj1.points_[i].y;
	//	float new_y = sin(sign_flag)*obj1.points_[i].x + cos(sign_flag)*obj1.points_[i].y;

	//	glVertex2f(new_x/obj1.scale_current_, new_y/obj1.scale_current_);
	//	glEnd();
	//}

	//for (int i = 0; i < obj1.faces_.size(); i++)
	//{
	//	
	//	glBegin(GL_TRIANGLES);
	//	int id1 = obj1.faces_[i].id1;
	//	int id2 = obj1.faces_[i].id2;
	//	int id3 = obj1.faces_[i].id3;

	//	glColor3f(obj1.points_[id1].z/2.0+0.5, 0,0);

	//	glVertex2f(obj1.points_[id1].x,obj1.points_[id1].y);
	//	glVertex2f(obj1.points_[id2].x, obj1.points_[id2].y);
	//	glVertex2f(obj1.points_[id3].x, obj1.points_[id3].y);
	//	glEnd();
	//}

	glutSwapBuffers();	//swap buffer
}


//闲置时调用的函数
void IdleFunc()
{
	glutPostRedisplay();//重新绘制（即调用DisplayFunc()函数）
}


//数字、字母键按键检测
void KeyboardFunc(unsigned char Key, int x, int y)
{
	if (Key == 'w' || Key == 'W')
	{
		if (g_vector2D.fY < 1.0f)//界限判定
		{
			g_vector2D.fY += 0.05f;
			cout << "w" << endl;
		}
	}

	if (Key == 's' || Key == 'S')
	{
		if (g_vector2D.fY - 0.4f > -1.0f)//界限判定
			g_vector2D.fY -= 0.05f;
	}

	if (Key == 'a' || Key == 'A')
	{
		if (g_vector2D.fX > -1.0f)//界限判定
			g_vector2D.fX -= 0.05f;
	}

	if (Key == 'd' || Key == 'D')
	{
		if (g_vector2D.fX + 0.4f < 1.0f)//界限判定
			g_vector2D.fX += 0.05f;
	}
}
//F1~F12、控制键检测
void SpecialFunc(int Key, int x, int y)
{
	if (Key == GLUT_KEY_UP)
	{
		if (g_vector2D.fY < 1.0f)//界限判定
			g_vector2D.fY += 0.05f;
	}

	if (Key == GLUT_KEY_DOWN)
	{
		if (g_vector2D.fY - 0.4f > -1.0f)//界限判定
			g_vector2D.fY -= 0.05f;
	}

	if (Key == GLUT_KEY_LEFT)
	{
		if (g_vector2D.fX > -1.0f)//界限判定
			g_vector2D.fX -= 0.05f;
	}

	if (Key == GLUT_KEY_RIGHT)
	{
		if (g_vector2D.fX + 0.4f < 1.0f)//界限判定
			g_vector2D.fX += 0.05f;
	}
}
//鼠标检测
void MouseFunc(int button, int state, int x, int y)
{
	//button  鼠标按键 0 -- 左键    1 -- 中键   2 -- 右键
	//state  鼠标状态  0 -- 按下  1 -- 抬起
	//x,y  鼠标的像素点坐标（以窗口的左上角为原点的坐标系）
	//std::cout << "鼠标的坐标：x = " << x << " ,y = " << y << std::endl;

	if (button == 0)
	{
		if (state == 0)
		{
			//鼠标左键按下
		}

		if (state == 1)
		{
			//鼠标左键抬起
		}
	}

	if (button == 1)
	{
		if (state == 0)
		{
			//鼠标中键按下
		}
		if (state == 1)
		{
			//鼠标中键抬起
		}
	}
	if (button == 2)
	{
		if (state == 0)
		{
			//鼠标右键按下

		}
		if (state == 1)
		{
			//鼠标右键抬起

		}
	}
}
//鼠标按着拖动
int old_x;
float sign_flag = 0;
void MotionFunc(int x, int y)
{
	//x,y  鼠标的像素点坐标（以窗口的左上角为原点的坐标系）
	//鼠标按着拖动的坐标

	int temp = x - old_x;
	if (temp > 0)
	{
		sign_flag += 0.1;
	}
	else
	{
		sign_flag -= 0.1;
	}

	old_x = x;


}
//鼠标移动
void PassiveMotionFunc(int x, int y)
{
	//x,y  鼠标的像素点坐标（以窗口的左上角为原点的坐标系）
	//鼠标移动的坐标

}


int N2S(float data,float scale)
{
	return ((data+ 1)*ROWS / 2);
}
float S2N(int data,float scale)
{
	return	(2.0 / ROWS * data - 1);
}
