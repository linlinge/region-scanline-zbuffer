#include "region_subdivision.h"
ScanLines scan_lines;

void ScanLines::Init()
{
	//test whether the obj load or not
	if (obj1.faces_.size() == 0)
	{
		cout << "Load obj failed!" << endl;
		return;
	}

	//the vertexs have been sorted
	for (int i = 0; i < obj1.faces_.size(); i++)
	{
		bunch bunch_temp;
		int y;
		int sign, num;
		int y_start, y_end;
		int edge_status;


		

		//add P1
		y = round(N2S(obj1.faces_[i].norm_y1));
		bunch_temp.aet_norm_x = obj1.faces_[i].norm_x1;
		bunch_temp.aet_norm_z = obj1.faces_[i].norm_z1;
		if(IS_SINGULAR(obj1.faces_[i].norm_y1, obj1.faces_[i].norm_y2, obj1.faces_[i].norm_y3))
			bunch_temp.flag = status::singular;
		else
			bunch_temp.flag = status::in;

		bunch_temp.faces_id = i;
		scan_lines_[y].bunch_.push_back(bunch_temp);

		//add P2
		y = round(N2S(obj1.faces_[i].norm_y2));
		bunch_temp.aet_norm_x = obj1.faces_[i].norm_x2;
		bunch_temp.aet_norm_z = obj1.faces_[i].norm_z2;
		if (IS_SINGULAR(obj1.faces_[i].norm_y2, obj1.faces_[i].norm_y1, obj1.faces_[i].norm_y3))
			bunch_temp.flag = status::singular;
		else
			bunch_temp.flag = status::in;
		bunch_temp.faces_id = i;
		scan_lines_[y].bunch_.push_back(bunch_temp);

		//add P3
		y = round(N2S(obj1.faces_[i].norm_y3));
		bunch_temp.aet_norm_x = obj1.faces_[i].norm_x3;
		bunch_temp.aet_norm_z = obj1.faces_[i].norm_z3;
		if (IS_SINGULAR(obj1.faces_[i].norm_y3, obj1.faces_[i].norm_y1, obj1.faces_[i].norm_y2))
			bunch_temp.flag = status::singular;
		else
			bunch_temp.flag = status::out;

		bunch_temp.faces_id = i;
		scan_lines_[y].bunch_.push_back(bunch_temp);

		// P1P2		
		sign = obj1.faces_[i].norm_kxy12 > 0 ? 1 : -1; //if sign==0, how to deal with this situation
		edge_status = IS_IN(obj1.faces_[i].norm_x1, obj1.faces_[i].norm_y1, obj1.faces_[i].norm_x2, obj1.faces_[i].norm_y2, obj1.faces_[i].norm_x3, obj1.faces_[i].norm_y3);//use vertexs to check edge status
		if (sign > 0)
		{
			y_start = ceil(N2S(obj1.faces_[i].norm_y1));
			y_end = floor(N2S(obj1.faces_[i].norm_y2));
		}
		else
		{
			y_start = floor(N2S(obj1.faces_[i].norm_y1));
			y_end = ceil(N2S(obj1.faces_[i].norm_y2));
		}
		num = abs(y_end - y_start) + 1;
		for (int j = 0; j < num; j++)
		{
			int current_line = y_start + sign * j;				
			bunch_temp.aet_norm_x = obj1.faces_[i].norm_x1 + (j + 1) *abs(NORM_DY / obj1.faces_[i].norm_kxy12);//calculate current x
			bunch_temp.aet_norm_y = S2N(current_line);														   //calculate current y
			bunch_temp.aet_norm_z = obj1.faces_[i].norm_z1 + (j + 1) *abs(NORM_DY * obj1.faces_[i].norm_kyz12);//calculate current z
			if (edge_status) 
			{
				bunch_temp.flag = status::in;
			}				
			else
			{
				bunch_temp.flag = status::out;					
			}					
			bunch_temp.faces_id = i;
			scan_lines_[current_line].bunch_.push_back(bunch_temp);
		}

		// P1P3
		sign = obj1.faces_[i].norm_kxy13 > 0 ? 1 : -1;
		edge_status = IS_IN(obj1.faces_[i].norm_x1, obj1.faces_[i].norm_y1, obj1.faces_[i].norm_x3, obj1.faces_[i].norm_y3, obj1.faces_[i].norm_x2, obj1.faces_[i].norm_y2);
		if (sign>0)
		{
			y_start= ceil(N2S(obj1.faces_[i].norm_y1));
			y_end = floor(N2S(obj1.faces_[i].norm_y3));	
		}
		else
		{
			y_start = floor(N2S(obj1.faces_[i].norm_y1));
			y_end = ceil(N2S(obj1.faces_[i].norm_y3));
		}	
		num = abs(y_end - y_start) + 1;
		for (int j =0; j < num; j++)
		{	
			int current_line = y_start + sign * j;
			bunch_temp.aet_norm_x = obj1.faces_[i].norm_x1 + (j + 1)*abs(NORM_DY / obj1.faces_[i].norm_kxy13);
			bunch_temp.aet_norm_y = S2N(current_line);
			bunch_temp.aet_norm_z = obj1.faces_[i].norm_z1 + (j + 1)*abs(NORM_DY * obj1.faces_[i].norm_kyz13);
			if (edge_status)
			{
				bunch_temp.flag = status::in;
			}
			else
			{
				bunch_temp.flag = status::out;
			}
			bunch_temp.faces_id = i;
			scan_lines_[current_line].bunch_.push_back(bunch_temp);
		}
		
		// P2P3
		sign = obj1.faces_[i].norm_kxy23 > 0 ? 1 : -1;
		edge_status = IS_IN(obj1.faces_[i].norm_x2, obj1.faces_[i].norm_y2, obj1.faces_[i].norm_x3, obj1.faces_[i].norm_y3, obj1.faces_[i].norm_x1, obj1.faces_[i].norm_y1);
		if (sign > 0)
		{
			y_start = ceil(N2S(obj1.faces_[i].norm_y2));
			y_end = floor(N2S(obj1.faces_[i].norm_y3));
		}
		else
		{
			y_start = floor(N2S(obj1.faces_[i].norm_y2));
			y_end = ceil(N2S(obj1.faces_[i].norm_y3));
		}
		num = abs(y_end - y_start) + 1;
		for (int j = 0; j < num; j++)
		{
			int current_line = y_start + sign*j;
			bunch_temp.aet_norm_x = obj1.faces_[i].norm_x2 + j * abs(NORM_DY / obj1.faces_[i].norm_kxy23);
			bunch_temp.aet_norm_y = S2N(current_line);
			bunch_temp.aet_norm_z = obj1.faces_[i].norm_z2 + j * abs(NORM_DY / obj1.faces_[i].norm_kyz23);
			if (edge_status)
			{
				bunch_temp.flag = status::in;
			}
			else
			{
				bunch_temp.flag = status::out;
			}
			bunch_temp.faces_id = i;
			scan_lines_[current_line].bunch_.push_back(bunch_temp);
		}
		
	}


}

void ScanLines::Algorithm()
{
	for (int i = 0; i < ROWS; i++)
	{
		if (scan_lines_[i].bunch_.size() != 0)
		{
			//remove repeat vertex
			//sort(scan_lines_[i].bunch_.begin(), scan_lines_[i].bunch_.end());
			/*vector<bunch>::iterator it=unique(scan_lines_[i].bunch_.begin(), scan_lines_[i].bunch_.end());
			scan_lines_[i].bunch_.erase(it, scan_lines_[i].bunch_.end());*/
			// test
			int sum = 0;
			for (int k = 0; k < scan_lines_[i].bunch_.size(); k++)
			{
				sum += scan_lines_[i].bunch_[k].flag;
			}
			cout << sum << " ";

			for (int j = 0; j < scan_lines_[i].bunch_.size()-1;j++)
			{
				if (scan_lines_[i].bunch_[j].flag == status::in)
				{
					float t = scan_lines_[i].bunch_[j].aet_norm_z;
					float et = exp(t);

					glColor3f(0.5*(et/(1+et)+1),t, 0.5*(-et / (1 + et) + 1));
					glBegin(GL_LINES);
					glVertex2f(scan_lines_[i].bunch_[j].aet_norm_x, S2N(i));
					glVertex2f(scan_lines_[i].bunch_[j+1].aet_norm_x, S2N(i));
					glEnd();
				}
				else if(scan_lines_[i].bunch_[j].flag == status::singular)
				{
					glBegin(GL_POINTS);
					glVertex2f(scan_lines_[i].bunch_[j].aet_norm_x, S2N(i));
					glEnd();
					
				}

			}			
		}
	}
}