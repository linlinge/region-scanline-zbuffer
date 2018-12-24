#include "region_scan_line.h"
#include "load_obj.h"
#include <math.h>
#include "main.hpp"
AreaScanLines scan_lines;


void AreaScanLines::BuildTables()
{
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
		p.push_back(obj1.points_[obj1.faces_[i].vertex_id_[0]]);
		p.push_back(obj1.points_[obj1.faces_[i].vertex_id_[1]]);
		p.push_back(obj1.points_[obj1.faces_[i].vertex_id_[2]]);
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

		int int_y1 = ROUND(p1.y);
		int int_y2 = ROUND(p2.y);
		int int_y3 = ROUND(p3.y);
		//if (abs(p1.y - p2.y) <= 0.8)
		//{
		//	//int_y1 = ROUND(p1.y);
		//	int_y2 = int_y1;
		//}
		//if (abs(p2.y - p3.y) <= 0.8)
		//{
		//	int_y3 = int_y2;
		//}

#ifdef DEBUG
		/*f << i << " " << p1.x << " " << p1.y << " " << p1.z << " " <<
						 p2.x << " " << p2.y << " " << p2.z << " " <<
						 p3.x << " " << p3.y << " " << p3.z << endl;*/
#endif

		if (int_y1 == int_y3)
		/// triangle has converted to a line, insert p1 and p3
		{
			vector<Vec3f> p_temp;
			p_temp.push_back(p1);p_temp.push_back(p2);p_temp.push_back(p3);
			sort(p_temp.begin(), p_temp.end(), [](const Vec3f&e1, const Vec3f&e2) {return e1.x < e2.x; });
			edge_temp1.x = p_temp[0].x; edge_temp2.x = p_temp[2].x;			
			edge_temp1.dx = INT_MAX; edge_temp2.dx = INT_MAX;
			edge_temp1.dy_max = 1; edge_temp2.dy_max = 1;
			edge_temp1.dy = 1; edge_temp2.dy = 1;
			edge_temp1.id = i; edge_temp2.id = i;
			/// flag will be determined laterly
			ET_[int_y1].push_back(edge_temp1);
			ET_[int_y1].push_back(edge_temp2);
		}
		else if (int_y1 == int_y2 && int_y2 != int_y3)
		/// P1P2 is horizontal
		{			
			// add P1P3 (ordinary+1)
			edge_temp.x = p1.x;
			//k = (p1.y - p3.y) / (p1.x - p3.x);
			k = (int_y1 - int_y3) / (p1.x - p3.x);
			edge_temp.dx = -1.0f / k;
			edge_temp.dy = int_y3 - int_y1 + 1;
			edge_temp.dy_max = edge_temp.dy;
			edge_temp.id = i;
			ET_[int_y1].push_back(edge_temp);

			// add P2P3 (ordinary+1)
			edge_temp.x = p2.x;
			//k = (p2.y - p3.y) / (p2.x - p3.x);
			k = (int_y2 - int_y3) / (p2.x - p3.x);
			edge_temp.dx = -1.0f / k;
			edge_temp.dy = int_y3 - int_y2 + 1;
			edge_temp.dy_max = edge_temp.dy;
			edge_temp.id = i;
			ET_[int_y2].push_back(edge_temp);
		}
		else if (int_y1!= int_y2 && int_y2 == int_y3)
		// P2P3 is horizontal
		{			
			// P1P2-> ET (ordinary +1)
			edge_temp.x = p1.x;
			//k = (p1.y - p2.y) / (p1.x - p2.x);
			k = (int_y1 - int_y2) / (p1.x - p2.x);
			edge_temp.dx = -1.0f / k;
			edge_temp.dy = int_y2 - int_y1 + 1;
			edge_temp.dy_max = edge_temp.dy;		
			edge_temp.id = i;
			ET_[int_y1].push_back(edge_temp);

			// P1P3 -> ET ( ordinary + 1)
			edge_temp.x = p1.x;
			//k = (p1.y - p3.y) / (p1.x - p3.x);
			k = (int_y1 - int_y3) / (p1.x - p3.x);
			edge_temp.dx = -1.0f / k;
			edge_temp.dy = int_y3 - int_y1 + 1;
			edge_temp.dy_max = edge_temp.dy;		
			edge_temp.id = i;
			ET_[int_y1].push_back(edge_temp);
		}
		else
		// ordinary
		{
			// P1P2 -> ET (ordinary)
			edge_temp.x = p1.x;
			//k = (p1.y - p2.y) / (p1.x - p2.x);
			k = (int_y1 - int_y2) / (p1.x - p2.x);
			edge_temp.dx = -1.0f / k;
			edge_temp.dy = int_y2 - int_y1;
			edge_temp.dy_max = edge_temp.dy;		
			edge_temp.id = i;
			ET_[int_y1].push_back(edge_temp);

			// P2P3 -> ET (ordinary+1)
			edge_temp.x = p2.x;
			//k = (p2.y - p3.y) / (p2.x - p3.x);
			k = (int_y2 - int_y3) / (p2.x - p3.x);
			edge_temp.dx = -1.0f / k;
			edge_temp.dy = int_y3 - int_y2 + 1;
			edge_temp.dy_max = edge_temp.dy;			
			edge_temp.id = i;
			ET_[int_y2].push_back(edge_temp);

			// P1P3 -> ET (ordinary+1)
			edge_temp.x = p1.x;
			//k = (p1.y - p3.y) / (p1.x - p3.x);
			k = (int_y1 - int_y3) / (p1.x - p3.x);
			edge_temp.dx = -1.0f / k;
			edge_temp.dy = int_y3 - int_y1 + 1;
			edge_temp.dy_max = edge_temp.dy;		
			edge_temp.id = i;
			ET_[int_y1].push_back(edge_temp);
		}
		

		// build PT
		polygon_temp.a = (p2.y - p1.y)*(p3.z - p1.z) - (p3.y - p1.y)*(p2.z - p1.z);
		polygon_temp.b = (p2.z - p1.z)*(p3.x - p1.x) - (p3.z - p1.z)*(p2.x - p1.x);
		polygon_temp.c = (p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y);
		polygon_temp.d = -polygon_temp.a*p1.x - polygon_temp.b*p1.y - polygon_temp.c*p1.z;

		//polygon_temp.a = (int_y2 - int_y1)*(p3.z - p1.z) - (int_y3 - int_y1)*(p2.z - p1.z);
		//polygon_temp.b = (p2.z - p1.z)*(p3.x - p1.x) - (p3.z - p1.z)*(p2.x - p1.x);
		//polygon_temp.c = (p2.x - p1.x)*(int_y3 - int_y1) - (p3.x - p1.x)*(int_y2 - int_y1);
		//polygon_temp.d = -polygon_temp.a*p1.x - polygon_temp.b*int_y1 - polygon_temp.c*p1.z;
		polygon_temp.id = i;


		//Vec3f color(0.5f*(p1.z + 1), 0.5f*(p1.z +1), 0.5f*(p1.z + 1));
		Vec3f color(p1.z, p1.z, p1.z);
		polygon_temp.color = color;
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
			// init
			id_.clear();
			xc_.clear();


			/// caculate x for current line
			for (auto & edge : AET_)
			{
				edge.xc = edge.x - edge.dx*(edge.dy_max - edge.dy);
			}					
		
			/// sort AET_ with x data
			sort(AET_.begin(), AET_.end(), [](EdgeElement &e1, EdgeElement &e2) {return e1.id < e2.id; });


			// init
			/// id
			id_.push_back(BACKGROUND); //represent background
			/// xc
			xc_.push_back(0);
			xc_.push_back(WIDTH);	
			

			// fill zbuffer
			float posy = i;
			for (int j = 0; j < AET_.size(); j+=2)
			{
				// Debug
				//cout << "(" << i << "," << j << ")"<<endl;
				/*if (i == 202 && j == 4)
					j = 4;

				if (i == 450)
					i = 450;*/

				// init
				EdgeElement & edge1 = AET_[j];				
				EdgeElement & edge2 = AET_[j+1];
				if (edge1.xc != edge2.xc)
				{
					// adjust in and out
					if (edge1.xc >= edge2.xc) { EdgeElement::swap(edge1, edge2); }
					float& x1 = edge1.xc;
					float& x2 = edge2.xc;
					int left1, left2, right1, right2;
									
					// find left and right position
					FindLR(xc_, x1, x2, left1, left2, right1, right2);
					// Does it need to insert new point
					/// none
					if (left1 == left2 && right1 == right2)
					{
						/// pure
						if (left1 + 1 == right1)
						{
							if (id_[left1] != BACKGROUND)
							{
								int rst = ZCompare(edge1.id, id_[left1], edge1.xc, i);
								if (rst == 1)
								{
									id_[left1] = edge1.id;
								}
							}
							else 							
								id_[left1] = edge1.id;																	
						}
						/// not pure
						else
						{
							for (int k = xc_[left1]; k < right1; k++)
							{
								if (id_[k] != BACKGROUND)
								{
									int rst = ZCompare(edge1.id, id_[k], xc_[k], i);
									if (rst == 1)
									{
										id_[k] = edge1.id;
									}
									// attention: should we remove useless endpoint ?
								}
								else								
									id_[k] = edge1.id;								
							}
						}
					}
					/// one
					else if(left1 == left2)
					{
						/// pure
						if (left1 == right1)
						{
							if (id_[right1] != BACKGROUND)
							{
								int rst = ZCompare(edge1.id, id_[right1], xc_[right1], i);
								if (rst == 1)
								{
									/// id
									id_.insert(id_.begin() + right1, edge1.id);
									/// xc
									xc_.insert(xc_.begin() + right1 + 1, edge2.xc);
								}
							}
							else
							{
								/// id
								id_.insert(id_.begin() + right1, edge1.id);
								/// xc
								xc_.insert(xc_.begin() + right1 + 1, edge2.xc);
							}
						}
						/// not pure
						else
						{
							for (int k = left1; k < right1; k++)
							{
								if (id_[k] != BACKGROUND)
								{
									int rst = ZCompare(edge1.id, id_[k], xc_[k], i);
									if (rst == 1)
									{
										id_[k] = edge1.id;
									}
								}
								else
									id_[k] = edge1.id;
							}

							/// the last span
							if (id_[right1] != BACKGROUND)
							{
								int rst = ZCompare(edge1.id, id_[right1], xc_[right1], i);
								if (rst == 1)
								{
									/// id
									id_.insert(id_.begin() + right1, edge1.id);
									/// xc
									xc_.insert(xc_.begin() + right1 + 1, edge2.xc);
								}
							}
							else
							{
								/// id
								id_.insert(id_.begin() + right1, edge1.id);
								/// xc
								xc_.insert(xc_.begin() + right1 + 1, edge2.xc);
							}

						}
					}
					else if (right1 == right2)
					{
						/// pure
						if (left1+1 == right1)
						{
							if (id_[left1] != BACKGROUND)
							{
								int rst = ZCompare(edge1.id, id_[left1], edge1.xc, i);
								if (rst == 1)
								{ 
									/// id
									id_.insert(id_.begin() + left1 + 1, edge1.id);
									/// xc
									xc_.insert(xc_.begin() + left1 + 1, edge1.xc);
								}
							}
							else
							{
								/// id
								id_.insert(id_.begin() + left1 + 1, edge1.id);
								/// xc
								xc_.insert(xc_.begin() + left1 + 1, edge1.xc);
							}
						}
						/// not pure
						else
						{
							// first span
							if (id_[left1] != BACKGROUND)
							{
								int rst = ZCompare(edge1.id, id_[left1], edge1.xc, i);
								if (rst == 1)
								{
									/// id
									id_.insert(id_.begin() + left1 + 1, edge1.id);
									/// xc
									xc_.insert(xc_.begin() + left1 + 1, edge1.xc);
								}
							}
							else
							{
								/// id
								id_.insert(id_.begin() + left1 + 1, edge1.id);
								/// xc
								xc_.insert(xc_.begin() + left1 + 1, edge1.xc);
							}

							// normal span
							for (int k = left2; k < right2; k++)
							{
								if (id_[k] != BACKGROUND)
								{
									int rst = ZCompare(edge1.id, id_[k], xc_[k], i);
									if (rst == 1)
									{
										id_[k] = edge1.id;
									}
									// attention: should we remove useless endpoint ?
								}
								else
									id_[k] = edge1.id;
							}

						}
					}
					/// two
					else
					{
						/// pure
						if (left1 == right1)
						{
							if (id_[left1] != BACKGROUND)
							{
								int rst = ZCompare(edge1.id, id_[left1], edge1.xc, i);
								if (rst == 1)
								{
									/// id
									id_.insert(id_.begin() + left1 + 1, id_[left1]);
									id_.insert(id_.begin() + left1 + 1, edge1.id);
									/// xc
									xc_.insert(xc_.begin() + left1 + 1, edge2.xc);
									xc_.insert(xc_.begin() + left1 + 1, edge1.xc);
								}
							}
							else
							{
								/// id
								id_.insert(id_.begin() + left1 + 1, id_[left1]);
								id_.insert(id_.begin() + left1 + 1, edge1.id);
								/// xc
								xc_.insert(xc_.begin() + left1 + 1, edge2.xc);
								xc_.insert(xc_.begin() + left1 + 1, edge1.xc);								
							}
						}
						/// not pure
						else
						{
							/// fist span
							if (id_[left1] != BACKGROUND)
							{
								int rst = ZCompare(edge1.id, id_[left1], edge1.xc, i);
								if (rst == 1)
								{
									/// id
									id_.insert(id_.begin() + left1 + 1, edge1.id);
									/// xc
									xc_.insert(xc_.begin() + left1 + 1, edge1.xc);
									/// 
									right1++;
									right2++;
								}
							}
							else
							{
								/// id
								id_.insert(id_.begin() + left1 + 1, edge1.id);
								/// xc
								xc_.insert(xc_.begin() + left1 + 1, edge1.xc);
								///
								right1++;
								right2++;
							}
							/// middle span
							for (int k = left2; k < right1; k++)
							{
								if (id_[k] != BACKGROUND)
								{
									int rst = ZCompare(edge1.id, id_[k], xc_[k], i);
									if (rst == 1)
									{
										id_[k] = edge1.id;
									}
								}
								else
									id_[k] = edge1.id;
							}

							/// last span
							if (id_[right1] != BACKGROUND)
							{
								int rst = ZCompare(edge1.id, id_[right1], xc_[right1], i);
								if (rst == 1)
								{
									/// id
									id_.insert(id_.begin() + right1, edge1.id);
									/// xc
									xc_.insert(xc_.begin() + right1 + 1, edge2.xc);
								}
							}
							else
							{
								/// id
								id_.insert(id_.begin() + right1, edge1.id);
								/// xc
								xc_.insert(xc_.begin() + right1 + 1, edge2.xc);
							}
						}
					}
				}																					
			}			

			// draw
			for (int j = 1; j < id_.size()-1; j++)
			{								
				if (id_[j] != BACKGROUND)
				{
					glBegin(GL_LINES);
					Vec3f& color = PT_[id_[j]].color;
					glColor3f(color.r, color.g, color.b);
					glVertex2f(XW(xc_[j]), y_world[i]);
					glVertex2f(XW(xc_[j + 1]), y_world[i]);
					glEnd();
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


// assume the dat has been sorted, and val is not the smallest or largest
void FindLR(vector<float> &dat,int x1,int x2, int& left1,int &left2, int& right1,int& right2)
{
	// left
	for (int i = dat.size() - 2; i >= 0; i--)
	{
		if (dat[i] < x1 && x1 < dat[i + 1])
			/// middle
		{
			left1 = i;
			left2 = i + 1;
			break;
		}
		else if( dat[i]==x1)
			/// left endpoint
		{
			left1 = left2 = i;
			break;
		}
		else if (dat[i + 1] == x1)
			/// right endpoint
		{
			left1 = left2 = i + 1;
			break;
		}
	}

	// right
	for (int i = 0; i < dat.size() - 1; i++)
	{
		if (dat[i]< x2 && x2< dat[i+1])
			/// middle
		{
			right1 = i;
			right2 = i + 1;
			break;
		}
		else if(dat[i]==x2)
			/// left endpoint
		{
			right1 = right2 = i;
		}
		else if (dat[i + 1] == x2)
			/// right endpoint
		{
			right1 = right2 = i + 1;
		}
	}
}


int AreaScanLines::ZCompare(int id1, int id2, float x, float y)
{
	PolygonElement& plane1 = PT_[id1];
	PolygonElement& plane2 = PT_[id2];
	float z1 = -(plane1.a*x + plane1.b*y + plane1.d) / plane1.c;
	float z2 = -(plane2.a*x + plane2.b*y + plane2.d) / plane2.c;
	
	if (z1 > z2)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}