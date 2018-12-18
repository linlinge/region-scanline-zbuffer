#include "region_scan_line.h"
#include "load_obj.h"
#include <math.h>
AreaScanLines scan_lines;

//test
void test_fun()
{
	// tri1
	//obj1.points_[0].x = 100; 
	//obj1.points_[0].y = 100;
	//obj1.points_[0].z = 100;

	//obj1.points_[1].x = 50;
	//obj1.points_[1].y = 200;
	//obj1.points_[1].z = 100;

	//obj1.points_[2].x = 250;
	//obj1.points_[2].y = 200;
	//obj1.points_[2].z = 100;

	obj1.points_[0].x = 100.0f;
	obj1.points_[0].y = 100.0f;
	obj1.points_[0].z = 300.0f;

	obj1.points_[1].x = 50.0f;
	obj1.points_[1].y = 200.0f;
	obj1.points_[1].z = 300.0f;

	obj1.points_[2].x = 150.0f;
	obj1.points_[2].y = 200.0f;
	obj1.points_[2].z = 300.0f;

	// tri2
	obj1.points_[3].x = 200.0f;
	obj1.points_[3].y = 100.0f;
	obj1.points_[3].z = 200.0f;

	obj1.points_[4].x = 50.0f;
	obj1.points_[4].y = 250.0f;
	obj1.points_[4].z = 200.0f;

	obj1.points_[5].x = 250.0f;
	obj1.points_[5].y = 250.0f;
	obj1.points_[5].z = 200.0f;
}

void AreaScanLines::BuildTables()
{
	//test_fun();
	PT_.clear();
	for (auto & edge : ET_)
	{
		edge.clear();
	}
	PT_.resize(obj1.faces_.size());
	//the vertexs have been sorted
	for (int i=0; i<obj1.faces_.size();i++)
	{
		// Init 
		EdgeElement edge_temp,edge_temp1, edge_temp2;
		PolygonElement polygon_temp;
		vector<Vec3f> p;
		p.push_back(obj1.points_[obj1.faces_[i].id1]);
		p.push_back(obj1.points_[obj1.faces_[i].id2]);
		p.push_back(obj1.points_[obj1.faces_[i].id3]);
		/// sort by y value 
		sort(p.begin(), p.end(), [](const Vec3f&e1, const Vec3f &e2) { return e1.y < e2.y; });
		/// p1.y < p2.y < p3.y
		Vec3f &p1 = p[0];
		Vec3f &p2 = p[1];
		Vec3f &p3 = p[2];
		/// define y_max y_min
		int y_min, y_max;
		/// define slope
		float k = 0;

		// P3
		edge_temp.x = p3.x;
		edge_temp.dy = 1;
		edge_temp.dy_max = 1;
		edge_temp.id = i;
		ET_[ROUND(p3.y)].push_back(edge_temp);
		ET_[ROUND(p3.y)].push_back(edge_temp);

		// P1P2 ->  ET, PT
		edge_temp.x = p1.x;
		k = (p1.y - p2.y) / (p1.x - p2.x);
		if (abs(k) > EPS)
		{
			edge_temp.dx = -1.0f / k;
			y_min = ROUND(p1.y);
			y_max = ROUND(p2.y);
			edge_temp.dy = y_max - y_min ;
			edge_temp.dy_max = edge_temp.dy;
			edge_temp.flag = IS_IN(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
			edge_temp.id = i;
			ET_[y_min].push_back(edge_temp);
		}
		// special condition: horizontal line
		else
		{
			edge_temp1.x = p1.x; edge_temp2.x = p2.x;
			edge_temp1.dx = INT_MAX; edge_temp2.dx = INT_MAX;
			edge_temp1.dy_max = 1; edge_temp2.dy_max = 1;
			edge_temp1.dy = 1; edge_temp2.dy = 1;
			edge_temp1.id = i; edge_temp2.id = i;
			/// flag will be determined laterly
			ET_[ROUND(p1.y)].push_back(edge_temp1);
			ET_[ROUND(p1.y)].push_back(edge_temp2);
		}

		// P1P3 -> ET
		edge_temp.x = p1.x;
		k = (p1.y - p3.y) / (p1.x - p3.x);
		if (abs(k) > EPS)
		{
			edge_temp.dx = -1.0f / k;
			y_min = ROUND(p1.y);
			y_max = ROUND(p3.y);
			edge_temp.dy = y_max - y_min;
			edge_temp.dy_max = edge_temp.dy;
			edge_temp.flag = IS_IN(p1.x, p1.y, p3.x, p3.y, p2.x, p2.y);
			edge_temp.id = i;
			ET_[y_min].push_back(edge_temp);
		}
		else
		// horizontal line
		{
			edge_temp1.x = p1.x; edge_temp2.x = p3.x;
			edge_temp1.dx = INT_MAX; edge_temp2.dx = INT_MAX;
			edge_temp1.dy_max = 1; edge_temp2.dy_max = 1;
			edge_temp1.dy = 1; edge_temp2.dy = 1;
			edge_temp1.id = i; edge_temp2.id = i;
			/// flag will be determined laterly
			ET_[ROUND(p1.y)].push_back(edge_temp1);
			/// P3 has been added, so no need to added again						
		}

		// P2P3 -> ET
		edge_temp.x = p2.x;
		k = (p2.y - p3.y) / (p2.x - p3.x);
		if (abs(k) > EPS)
		{
			edge_temp.dx = -1.0f / k;
			y_min = ROUND(p2.y);
			y_max = ROUND(p3.y);
			edge_temp.dy = y_max - y_min ;
			edge_temp.dy_max = edge_temp.dy;
			edge_temp.flag = IS_IN(p2.x, p2.y, p3.x, p3.y, p1.x, p1.y);
			edge_temp.id = i;
			ET_[y_min].push_back(edge_temp);
		}		
		else
		// horizontal line
		{
			edge_temp1.x = p2.x; edge_temp2.x = p3.x;
			edge_temp1.dx = INT_MAX; edge_temp2.dx = INT_MAX;
			edge_temp1.dy_max = 1; edge_temp2.dy_max = 1;
			edge_temp1.dy = 1; edge_temp2.dy = 1;
			edge_temp1.id = i; edge_temp2.id = i;
			/// flag will be determined laterly
			ET_[ROUND(p2.y)].push_back(edge_temp1);
			/// P3 has been added, so no need to added again			
		}

		// build PT
		polygon_temp.a = (p2.y - p1.y)*(p3.z - p1.z) - (p3.y - p1.y)*(p2.z - p1.z);
		polygon_temp.b = (p2.z - p1.z)*(p3.x - p1.x) - (p3.z - p1.z)*(p2.x - p1.x);
		polygon_temp.c = (p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y);
		polygon_temp.d = -polygon_temp.a*p1.x - polygon_temp.b*p1.y - polygon_temp.c*p1.z;
		polygon_temp.id = i;

		Vec3f light_source(100.0f, 100.0f, 500.0f);
		float dist = p1.Distance(light_source)/500.0f;
		polygon_temp.color = Vec3f(0.0f,dist, 0.0f);
		PT_[i] = polygon_temp;
	}		
}

void AreaScanLines::Render()
{
	AET_.clear();
	for (int i = 0; i < HEIGHT; i++)
	{
		// insert to AET
		if (ET_[i].size() != 0)
		{
			AET_.insert(AET_.end(), ET_[i].begin(), ET_[i].end());		
		}		
		// are there any available AET
		if (AET_.size() != 0)
		{
			// caculate x for current line
			for (auto & edge : AET_)
			{
				edge.xc = edge.x - edge.dx*(edge.dy_max - edge.dy);
			}

			// sort AET_ with x data
			sort(AET_.begin(), AET_.end(), [](EdgeElement &e1, EdgeElement &e2) {return e1.xc < e2.xc; });

			// adjust in and out
			for (int j = 0; j < AET_.size(); j++)
			{
				EdgeElement & edge1 = AET_[j];
				for (int k = j+1; k < AET_.size(); k++)
				{
					EdgeElement & edge2 = AET_[k];
					if (edge1.id == edge2.id)
					{
						edge1.flag = status::in;
						edge2.flag = status::out;
						continue;
					}
				}
			}

			// find all solid points
			vector<int> idx;
			/// the first point must be the solid point
			idx.push_back(0);
			for (int j = 1; j < AET_.size(); j++)
			{
				// Define
				EdgeElement &edge1 = AET_[idx.back()];
				EdgeElement &edge2 = AET_[j];					

				if (i == 345 )
				{
					i = 345;
				}


				if (edge1.id==edge2.id)
				// condition1: points in the same plane
				{
					idx.push_back(j);
					continue;
				}
				else 
				// condition2: points in diffrent plane, (in,in)
				{	
					if (edge1.flag == status::in && edge2.flag == status::in)
					// (in,in)
					{
						/// Define
						PolygonElement& plane1 = PT_[edge1.id];
						PolygonElement& plane2 = PT_[edge2.id];
						/// Caculate z1,z2 in edge2
						float z1 = -((plane1.a*edge2.xc + plane1.b*edge2.xc + plane1.d) / plane1.c);
						float z2 = -((plane2.a*edge2.xc + plane2.b*edge2.xc + plane2.d) / plane2.c);
						/// judge is it a solid point
						if (z2 >= z1)
							// this is a solid point
						{
							idx.push_back(j);
							continue;
						}
					}
					else if(edge1.flag == status::out )
					// (out,in)
					{
						idx.push_back(j);
						continue;
					}
					
				}				
			}


			// draw
			for (int j = 0; j < idx.size() -1; j++)
			{
				EdgeElement& edge1 = AET_[idx[j]];
				EdgeElement& edge2 = AET_[idx[j + 1]];					
				
				// plane1 covered plane2
				if (edge1.flag == status::in)
				{
					Vec3f &color_temp = PT_[edge1.id].color;
					glColor3f(color_temp.r, color_temp.g, color_temp.b);
					glBegin(GL_LINES);
					glVertex2f(X_S2W(edge1.xc, y_world[i]), y_world[i]);
					glVertex2f(X_S2W(edge2.xc, y_world[i]), y_world[i]);
					glEnd();
					continue;
				}

				if (edge1.id != edge2.id && edge1.flag == status::out && edge2.flag == status::out)
				{
					Vec3f &color_temp = PT_[edge2.id].color;
					glColor3f(color_temp.r, color_temp.g, color_temp.b);
					glBegin(GL_LINES);
					glVertex2f(X_S2W(edge1.xc, y_world[i]), y_world[i]);
					glVertex2f(X_S2W(edge2.xc, y_world[i]), y_world[i]);
					glEnd();
					continue;
				}				
			}

			// update dy and caculate number of dy=0
			int y_zero_count = 0;
			for (auto & edge : AET_)
			{
				edge.dy -= 1;
				if (edge.dy <= 0)
					y_zero_count++;
			}
			// delete edge which dy=0
			sort(AET_.begin(), AET_.end(), [](EdgeElement &e1, EdgeElement &e2) {return e1.dy > e2.dy; });
			AET_.resize(AET_.size() - y_zero_count);
		}
	}
}