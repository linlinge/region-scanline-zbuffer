#include "load_obj.h"
#include "my_opengl.h"

Obj obj1;

Obj::Obj(string filename) {
	this->filename = filename;
	LoadObjFile();
}

void Obj::Init(string filename) {
	this->filename = filename;
	LoadObjFile();
}

//bool Obj::LoadObjFile() {
//	//define
//	fstream f;
//	string line;
//	f.open(filename.data(), ios::in); //open
//
//	if (!f.is_open()) {
//		cout << "Something Went Wrong When Opening Objfiles" << endl;
//		return false;
//	}
//
//	while (!f.eof()) {
//		getline(f, line);//拿到obj文件中一行，作为一个字符串
//		vector<string>parameters;
//		string tailMark = " ";
//		string ans = "";
//
//		line = line.append(tailMark);
//		for (int i = 0; i < line.length(); i++) {
//			char ch = line[i];
//			if (ch != ' ') {
//				ans += ch;
//			}
//			else {
//				parameters.push_back(ans); //取出字符串中的元素，以空格切分
//				ans = "";
//			}
//		}
//
//		if (parameters.size() == 4 ) {
//			if (parameters[0] == "v") {   //如果是顶点的话
//				Vertex3f p;
//				p.x = atof(parameters[1].c_str());
//				p.y = atof(parameters[2].c_str());
//				p.z = atof(parameters[3].c_str());
//				points_.push_back(p);
//			}
//			else if (parameters[0] == "f") 
//			{   //如果是面的话，存放三个顶点的索引	
//				
//				int temp[4];
//
//				for (int i = 1; i < 4; i++) {
//					string x = parameters[i];
//					string ans = "";
//					for (int j = 0; j < x.length(); j++) {   //跳过‘/’
//						char ch = x[j];
//						if (ch != '/') {
//							ans += ch;
//						}
//						else {
//							break;
//						}
//					}
//					int index = atof(ans.c_str());
//					index = index--;//因为顶点索引在obj文件中是从1开始的，而我们存放的顶点vector是从0开始的，因此要减1
//
//					temp[i] = index;
//						
//				}
//
//				if (points_[temp[1]].x > points_[temp[2]].x)
//				{
//					int t = temp[1];
//					temp[1] = temp[2];
//					temp[2] = t;
//				}
//				if (points_[temp[2]].x > points_[temp[3]].x)
//				{
//					int t = temp[2];
//					temp[2] = temp[3];
//					temp[3] = t;
//				}
//				if (points_[temp[1]].x > points_[temp[2]].x)
//				{
//					int t = temp[1];
//					temp[1] = temp[2];
//					temp[2] = t;
//				}
//
//				TrianglePatch tp;
//				tp.id1 = temp[1];
//				tp.id2 = temp[2];
//				tp.id3 = temp[3];
//				tp.norm_x1 = points_[temp[1]].x;
//				tp.norm_x2 = points_[temp[2]].x;
//				tp.norm_x3 = points_[temp[3]].x;
//				tp.norm_y1 = points_[temp[1]].y;
//				tp.norm_y2 = points_[temp[2]].y;
//				tp.norm_y3 = points_[temp[3]].y;
//				tp.norm_z1 = points_[temp[1]].z;
//				tp.norm_z2 = points_[temp[2]].z;
//				tp.norm_z3 = points_[temp[3]].z;
//
//				tp.norm_kxy12 = (points_[temp[1]].y - points_[temp[2]].y) / (points_[temp[1]].x - points_[temp[2]].x);
//				tp.norm_kxy13 = (points_[temp[1]].y - points_[temp[3]].y) / (points_[temp[1]].x - points_[temp[3]].x);
//				tp.norm_kxy23 = (points_[temp[2]].y - points_[temp[3]].y) / (points_[temp[2]].x - points_[temp[3]].x);
//
//				tp.norm_kyz12 = (points_[temp[1]].z - points_[temp[2]].z) / (points_[temp[1]].y - points_[temp[2]].y);
//				tp.norm_kyz13 = (points_[temp[1]].z - points_[temp[3]].z) / (points_[temp[1]].y - points_[temp[3]].y);
//				tp.norm_kyz23 = (points_[temp[2]].z - points_[temp[3]].z) / (points_[temp[2]].y - points_[temp[3]].y);
//
//				faces_.push_back(tp);
//			}
//		}
//	}
//	f.close();
//	return true;
//}


void fun(string &str, int &x, int &y, int &z)
{
	string s1, s2, s3;
	int i = 0;
	while (str[i] != '/') {
		s1.push_back(str[i]);
		i++;
	}
	i++;
	while (str[i] != '/') {
		s2.push_back(str[i]);
		i++;
	}
	i++;
	while (i<str.size()) {
		s3.push_back(str[i]);
		i++;
	}

	x = atoi(s1.c_str());
	y = atoi(s2.c_str());
	z = atoi(s3.c_str());

 }

bool Obj::LoadObjFile() {

	string line;
	ifstream f;
	f.open(filename);
	while (getline(f, line))
	{
		string s, s1,s2, s3;
		istringstream iss(line);
		
		iss >> s>>s1 >> s2 >> s3;

		if (s == "v")
		{
			Vec3f p;
			p.x = atof(s1.c_str());
			p.y = atof(s2.c_str());
			p.z = atof(s3.c_str());
			points_.push_back(p);
		}
		else if (s == "f")
		{
			TrianglePatch tp;
			int id1, id2, id3;
			int u1, u2;
			if (s1.find("/")!=string::npos)
			{
				fun(s1, id1, u1, u2);
				fun(s2, id2, u1, u2);
				fun(s3, id3, u1, u2);				
			}
			else
			{
				id1 = atoi(s1.c_str());
				id2 = atoi(s2.c_str());
				id3 = atoi(s3.c_str());
			}
			id1 -= 1;
			id2 -= 1;
			id3 -= 1;
			tp.id1 = id1;
			tp.id2 = id2;
			tp.id3 = id3;
			faces_.push_back(tp);			
		}

	}

	//cacluate initial scale
	Init();
	return true;
}


void Obj::Init()
{
	float max_radius = 0;
	for (auto &p : points_)
	{
		float r = centre_.DistanceXY(p);
		max_radius = max_radius > r ? max_radius : r;
	}

	// coordnite_source -> coordinate_world -> coordinate_screen
	for (auto &p : points_)
	{		
		p.x = W2S(p.x / max_radius);
		p.y = W2S(p.y / max_radius);
		p.z = W2S(p.z / max_radius);
	}
}