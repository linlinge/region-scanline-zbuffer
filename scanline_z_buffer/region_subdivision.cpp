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
		int y_start = round(N2S(obj1.faces_[i].norm_y1));
		int y_end = round(N2S(obj1.faces_[i].norm_y2));	
		int sign,num;
		if (y_start != y_end)
		{
			sign = obj1.faces_[i].norm_kxy12 > 0 ? 1 : -1;
			y_start = y_start + sign;
			y_end = y_end - sign;
			num = abs(y_end - y_start) + 1;
			for (int j = 0; j < num; j++)
			{
				bunch_temp.aet_norm_x = obj1.faces_[i].norm_x1 + (j + 1) *abs(DY / obj1.faces_[i].norm_kxy12);//calculate next x
				bunch_temp.aet_norm_y = S2N(i);
				bunch_temp.aet_norm_z = obj1.faces_[i].norm_z1 + (j + 1) *abs(DY * obj1.faces_[i].norm_kyz12);//calculate next z
				if(IS_IN(obj1.faces_[i].norm_x1, obj1.faces_[i].norm_y1,
					obj1.faces_[i].norm_x2, obj1.faces_[i].norm_y2,
					obj1.faces_[i].norm_x3, obj1.faces_[i].norm_y3))
					bunch_temp.flag = status::in;
				else
					bunch_temp.flag = status::out;
				bunch_temp.faces_id = i;
				if (i == 67583)
					i = 67583;

				int temp = y_start + sign * j;
				scan_lines_[y_start + sign * j].bunch_.push_back(bunch_temp);
			}
		}

		// P1P3
		y_start= round(N2S(obj1.faces_[i].norm_y1));
		y_end = round(N2S(obj1.faces_[i].norm_y3));		
		if (y_start != y_end)
		{
			sign = obj1.faces_[i].norm_kxy13 > 0 ? 1 : -1;
			y_end = y_end - sign;
			num = abs(y_end - y_start) + 1;
			for (int j =0; j < num; j++)
			{				
				bunch_temp.aet_norm_x = obj1.faces_[i].norm_x1 + (j + 1)*abs(DY / obj1.faces_[i].norm_kxy13);
				bunch_temp.aet_norm_y = S2N(i);
				bunch_temp.aet_norm_z = obj1.faces_[i].norm_z1 + (j + 1)*abs(DY * obj1.faces_[i].norm_kyz13);
				if(IS_IN(obj1.faces_[i].norm_x1, obj1.faces_[i].norm_y1,
					obj1.faces_[i].norm_x3, obj1.faces_[i].norm_y3,
					obj1.faces_[i].norm_x2, obj1.faces_[i].norm_y2))
					bunch_temp.flag = status::in;
				else
					bunch_temp.flag = status::out;
				bunch_temp.faces_id = i;
				if (i == 67583)
					i = 67583;
				int temp = y_start + sign * j;
				scan_lines_[y_start + sign * j].bunch_.push_back(bunch_temp);
			}
		}
		
		// P2P3
		y_start = round(N2S(obj1.faces_[i].norm_y2));
		y_end= round(N2S(obj1.faces_[i].norm_y3));		
		if (y_start != y_end)
		{
			sign = obj1.faces_[i].norm_kxy23 > 0 ? 1 : -1;
			y_start += sign;
			y_end -= sign;
			num = abs(y_end - y_start) + 1;
			for (int j = 0; j < num; j++)
			{
				bunch_temp.aet_norm_x = obj1.faces_[i].norm_x2 + j * abs(DY / obj1.faces_[i].norm_kxy23);
				bunch_temp.aet_norm_y = S2N(i);
				bunch_temp.aet_norm_z = obj1.faces_[i].norm_z2 + j * abs(DY / obj1.faces_[i].norm_kyz23);
				if(IS_IN(obj1.faces_[i].norm_x2, obj1.faces_[i].norm_y2,
					obj1.faces_[i].norm_x3, obj1.faces_[i].norm_y3,
					obj1.faces_[i].norm_x1, obj1.faces_[i].norm_y1))
					bunch_temp.flag = status::in;
				else
					bunch_temp.flag = status::out;

				bunch_temp.faces_id = i;
				if (i == 67583)
					i = 67583;
				int temp = y_start + sign * j;
				scan_lines_[y_start + sign * j].bunch_.push_back(bunch_temp);
			}
		}
	}


}

void ScanLines::Algorithm()
{
	//ofstream f;
	//f.open("./1.txt", fstream::out);

	for (int i = 0; i < ROWS; i++)
	{
		if (scan_lines_[i].bunch_.size() != 0)
		{
			//remove repeat vertex
			sort(scan_lines_[i].bunch_.begin(), scan_lines_[i].bunch_.end());
			/*vector<bunch>::iterator it=unique(scan_lines_[i].bunch_.begin(), scan_lines_[i].bunch_.end());
			scan_lines_[i].bunch_.erase(it, scan_lines_[i].bunch_.end());*/

			//
			for (int j = 0; j < scan_lines_[i].bunch_.size()-1;j++)
			{
				if (scan_lines_[i].bunch_[j].flag == status::in)
				{

					float t = scan_lines_[i].bunch_[j].aet_norm_z;
					t = (t + 1)*0.5;
					glColor3f(t,t,t);
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
		/*else
			f << "null" << endl;*/
	}

	//f.close();
}