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

//bool Obj::LoadObjFile() {
//
//	string line;
//	ifstream f;
//	f.open(filename);
//	while (getline(f, line))
//	{
//		string s, s1,s2, s3,s4,s5;
//		istringstream iss(line);
//		
//		iss >> s>>s1 >> s2 >> s3>>s4>>s5;
//
//		if (s == "v")
//		{
//			Vec3f p;
//			p.x = atof(s1.c_str());
//			p.y = atof(s2.c_str());
//			p.z = atof(s3.c_str());
//			points_.push_back(p);
//
//			//// sum x,y,z
//			//barycentre_.x += p.x;
//			//barycentre_.y += p.y;
//			//barycentre_.z += p.z;
//		}
//		else if (s == "vt")
//		{
//			Vec3f temp;
//			temp.x = atoi(s1.c_str());
//			temp.y = atoi(s2.c_str());
//			temp.z = atoi(s3.c_str());
//			vt_.push_back(temp);
//		}
//		else if (s=="vn")
//		{
//			Vec3f temp;
//			temp.x = atoi(s1.c_str());
//			temp.y = atoi(s2.c_str());
//			temp.z = atoi(s3.c_str());
//			vn_.push_back(temp);
//		}
//		else if (s == "f")
//		{
//			TrianglePatch tp;
//			int vertex_id1, normal_id1, texture_id1;
//			int vertex_id2, normal_id2, texture_id2;
//			int vertex_id3, normal_id3, texture_id3;
//			int vertex_id4, normal_id4, texture_id4;
//			int vertex_id5, normal_id5, texture_id5;
//
//			if (s1.find("/")!=string::npos)
//			// vertex/texture/normal
//			{
//				fun(s1, vertex_id1, texture_id1, normal_id1);
//				fun(s2, vertex_id2, texture_id2, normal_id2);
//				fun(s3, vertex_id3, texture_id3, normal_id3);	
//				if(s4!="")
//					fun(s4, vertex_id4, u1, u2);
//				if (s5 != "")
//					fun(s5, vertex_id5, u1, u2);
//			}
//			else
//			// only vertex
//			{
//				id1 = atoi(s1.c_str());
//				id2 = atoi(s2.c_str());
//				id3 = atoi(s3.c_str());
//				if (s4 != "")
//					id4 = atoi(s4.c_str());
//				if (s5 != "")
//					id5 = atoi(s5.c_str());
//			}
//
//
//			tp.vertex_id_.push_back(id1-1);
//			tp.vertex_id_.push_back(id2-1);
//			tp.vertex_id_.push_back(id3-1);
//			if (s4 != "")
//			{
//				tp.vertex_id_.push_back(id4 - 1);				
//			}				
//			if (s5 != "")
//			{
//				tp.vertex_id_.push_back(id5 - 1);
//			}							
//		}
//
//	}
//
//	//cacluate initial scale
//	Init();
//	return true;
//}


 bool Obj::LoadObjFile() {

	 string line;
	 ifstream f;
	 f.open(filename);
	// int k = 0;

	 while (getline(f, line))
	 {	
		 string str_type;
	/*	 k++;
		 cout << k << endl;*/

		 // remove backspace
		while (line[0] == ' ') line.erase(0, 1);

		// determine the type
		for (int i = 0; i < line.size() && line[i] !=' '; i++)
		{
			str_type.push_back(line[i]);
		}
		line.erase(0, str_type.size());
		while (line[0] == ' ') line.erase(0, 1);
		// deal with different type
		
		if (str_type == "f")
		{		
			Patch patch_temp;
			while (line.size()>0)
			{
				// find vertex_id/texture_id/normal_id
				string str_vtn;
				int i;
				for ( i= 0; i < line.size() && line[i] != ' '; i++)
				{
					str_vtn.push_back(line[i]);
				}
				
				// delete str_vtn in line
				if (i != line.size())
					line.erase(0, str_vtn.size() + 1);
				else
					line.erase(0, str_vtn.size());

				// deal with str_vtn
				string str_int;				
				// vertex_id
				for (i = 0; i < str_vtn.size() && str_vtn[i] != '/'; i++)
				{
					str_int.push_back(str_vtn[i]);
				}
				/// add vertex_id
				patch_temp.vertex_id_.push_back(atoi(str_int.c_str()) - 1);
				/// delete vertex_id from str_vtn
				str_vtn.erase(0, str_int.size() + 1);
				/// clear str_int
				str_int.clear();

				// '/' is exist
				if (i < str_vtn.size())
				{
					string temp;
					/// find texture_id
					for (int j = 0; str_vtn[j] != '/'; j++) { str_int.push_back(str_vtn[j]); }
					/// add texture_id
					patch_temp.texture_id_.push_back(atoi(str_int.c_str()) - 1);
					/// delete texture_id
					str_vtn.erase(0, str_int.size() + 1);
					/// str_int clear
					str_int.clear();

					/// add normal_id
					patch_temp.normal_id_.push_back(atoi(str_vtn.c_str()) - 1);
				}											
			}
			// add patch
			faces_.push_back(patch_temp);
		}
		else if( str_type=="v" || str_type == "vn" || str_type == "vt")
		{
			int i = 0;
			Vec3f p;
			string str;

			/// x axis
			while (line[i] != ' ') str.push_back(line[i++]);
			p.x = atof(str.c_str());
			i++;
			str.clear();

			/// y axis
			while (line[i] != ' ') str.push_back(line[i++]);
			p.y = atof(str.c_str());
			i++;
			str.clear();

			/// z axis
			while (i < line.size()) str.push_back(line[i++]);
			p.z = atof(str.c_str());

			// add to vertex
			if (str_type == "v")  points_.push_back(p);
			if (str_type == "vn") vn_.push_back(p);
			if (str_type == "vt") vt_.push_back(p);
			
		}
	 }

	 //cacluate initial scale
	 Init();
	 return true;
 }

void Obj::Init()
{
	Vec3f s0;
	float max_radius = 0.0f;
	for (auto &p : points_)
	{
		float dist = s0.DistanceXY(p);
		max_radius = max_radius > dist ? max_radius : dist;
	}

	// coordnite_source -> coordinate_world -> coordinate_screen
	for (auto &p : points_)
	{		
		p.x = 0.5f*(p.x / max_radius+1)*WIDTH;
		p.y = 0.5f*(-p.y / max_radius+1)*HEIGHT;
		p.z = 0.5f*(p.z / max_radius+1);
	}	

	ofstream f("../output/all_triangles.txt");
	for (int i=0;i<faces_.size();i++)
	{
		int &id1 = faces_[i].vertex_id_[0];
		int &id2 = faces_[i].vertex_id_[1];
		int &id3 = faces_[i].vertex_id_[2];

		f << i << " " << points_[id1].x << " " << points_[id1].y << " " << points_[id1].z
			<< " " << points_[id2].x << " " << points_[id2].y << " " << points_[id2].z
			<< " " << points_[id3].x << " " << points_[id3].y << " " << points_[id3].z << endl;
	}
	f.close();
}


//void Obj::SetColor() {
//	auto face_num = faces_.size();
//	auto light_color = Vec3f(0.4, 0.4, 0.0);
//	auto ambient_color = Vec3f(0.1, 0.1, 0.0);
//	auto light0 = Vec3f(WIDTH / 2, HEIGHT / 2, 10000.0f);
//
//	for (auto &face : faces_) {
//		face.color = Vec3f();
//		for (auto &vertex : face.m_vertexes) {
//			Vec3f ray_direction = Normalize(light_position - vertex);
//			Vec3f &normal = face.m_normal;
//			float cosine = std::abs(Dot(ray_direction, normal));
//			face.m_color += cosine * light_color;
//			face.m_color += ambient_color;
//		}
//		Vec3f ray_direction;
//		Vec3f normal;
//
//		Vec3f& p1 = points_[face.id1];
//		ray_direction = light0 - p1;
//		normal
//
//		face.m_color /= face.m_vertexes.size();
//		face.m_color.Clip(0.0f, 1.0f);
//		face.m_color *= 255;
//	}
//}