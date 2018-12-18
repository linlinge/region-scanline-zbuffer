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
		string s, s1,s2, s3,s4,s5;
		istringstream iss(line);
		
		iss >> s>>s1 >> s2 >> s3>>s4>>s5;

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
			int id1, id2, id3,id4,id5;
			int u1, u2;
			if (s1.find("/")!=string::npos)
			{
				fun(s1, id1, u1, u2);
				fun(s2, id2, u1, u2);
				fun(s3, id3, u1, u2);	
				if(s4!="")
					fun(s4, id4, u1, u2);
				if (s5 != "")
					fun(s5, id5, u1, u2);
			}
			else
			{
				id1 = atoi(s1.c_str());
				id2 = atoi(s2.c_str());
				id3 = atoi(s3.c_str());
				if (s4 != "")
					id4 = atoi(s4.c_str());
				if (s5 != "")
					id5 = atoi(s5.c_str());
			}
			id1 -= 1;
			id2 -= 1;
			id3 -= 1;
			if (s4 != "")
				id4 -= 1;
			if (s5 != "")
				id5 -= 1;

			tp.id1 = id1;
			tp.id2 = id2;
			tp.id3 = id3;
			if(s4!="")
				tp.id4 = id4;
			if(s5!="")
				tp.id5 = id5;
			faces_.push_back(tp);			
		}

	}

	//cacluate initial scale
	Init();
	return true;
}


void Obj::Init()
{
	float max_radius = 0.0f;
	barycentre_.x = 0.0f;
	barycentre_.y = 0.0f;
	barycentre_.z = 0.0f;



	for (auto &p : points_)
	{
		float r = centre_.DistanceXY(p);
		max_radius = max_radius > r ? max_radius : r;

		barycentre_.x += p.x;
		barycentre_.y += p.y;
		barycentre_.z += p.z;
	}
	barycentre_.x = barycentre_.x / points_.size();
	barycentre_.y = barycentre_.y / points_.size();
	barycentre_.z = barycentre_.z / points_.size();

	// coordnite_source -> coordinate_world -> coordinate_screen
	for (auto &p : points_)
	{		
		p.x = 2.0f*(p.x / max_radius) - 1;
		p.y = 2.0f*(p.y / max_radius)-1;
		p.z = 2.0f*(p.z / max_radius)-1;
	}

	ofstream f("../output/test_in_or_out_of_triangle.txt");
	for (auto & face : faces_)
	{
		f << points_[face.id1].x << " " << points_[face.id1].y << " " <<
			points_[face.id2].x << " " << points_[face.id2].y << " " <<
			points_[face.id3].x << " " << points_[face.id3].y << endl;
	}
	f.close();
}