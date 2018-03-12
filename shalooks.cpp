#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <math.h>
using namespace std;

// will we need another declaration of some sort for the grid or can we accomodate the grid structure in the 2D linked list only

float total_cells;
float wire_length(int x1, int y1, int x2, int y2)
{
float length;
length = sqrt(pow((x1-x2),2)+pow((y1-y2),2));
return length;
}
float schedule(float temp,float alpha)
	{
        temp= alpha*temp;
	return temp;
	}
	

struct display_cell
{
	long int cname;
	int ap;
	int group;
	float x_offset;
	float y_offset;
	int height;
	int width;
	float weight;
        int placed;
	int node;
	string orientation; //which side of the partition the block is in
	struct display_cell * next;
	struct display_cell * down;
	
}display_cell_st;//structure declaration ends

struct unique_cell
{
int name;
int width;
int height;
int x_offset;
int y_offset;
	
} unique_cell_st;

unique_cell unique[161187];
	


int findOverlapArea(int x1, int y1, int x2, int y2){
int area = 0;
	for (int i = 0; i< 161187;i++)
	{
	int x5 = max(x1, unique[i].x_offset);
	int y5 = max(y1, unique[i].y_offset);
	int x6 = min(x2, unique[i].x_offset+ unique[i].width);
	int y6 = min(y2, unique[i].y_offset+ unique[i].height);
	
		if(x5 >= x6 || y5 >= y6){
			area=area;
		}
		else
		{ 
		area += (x6 - x5) * (y6 - y5);
		}	
	}
	return (area - ((x2-x1)*(y2-y1)));
}



int main()
{

//display cell is used to make a 2D linked list to store all the connections 

display_cell * head = NULL;
display_cell * v_pointer = NULL;
display_cell * h_pointer = NULL;

head =(display_cell*)malloc(sizeof(display_cell));
v_pointer =(display_cell*)malloc(sizeof(display_cell));
h_pointer =(display_cell*)malloc(sizeof(display_cell));

display_cell * start = NULL;
v_pointer=head;
h_pointer=head;
	
string line;
int i=0;
int display_flag=0;
int node_count=0;
int node_limit=0;




ifstream myfile2 ("ibm15.nets");
	if (myfile2.is_open())
	{
		while (getline (myfile2,line))
		{	i++;
			if(line.substr(0,4)=="NetD")
			{
			display_flag=1;
			node_count=0;
			node_limit=strtol(line.substr(line.find(":")+2,line.length()).c_str(),NULL,10);  //strtol(line2.c_str(),NULL,10);
			h_pointer=v_pointer;
			}
			else if(line.substr(0,1)!="N" && display_flag==1)
			{
			line=line.substr(0,10);
			node_count++;
				
				
			
				if(line.find("p")<10)
					{
					//cout<<line.substr(line.find("p")+1,line.length())<<"\n";
					line=line.substr(line.find("p")+1,line.length());
					
					//add condition to make the ap flag accoringly
					h_pointer->ap=0;	
					}
				else if(line.find("a")<10)
					{
					//cout<<line.substr(line.find("a")+1,line.length())<<"\n";
					line=line.substr(line.find("a")+1,line.length());

					//add condition to make the ap flag accordingly
					h_pointer->ap=1;
					}
				if(node_count==1)
				{
				h_pointer->cname=strtol(line.c_str(),NULL,10);
				h_pointer->node=node_count;
				v_pointer=h_pointer;// i think there something worng in this part, but let us test
				
				//incrememt v_counter
				display_cell * tempv = (display_cell*)malloc(sizeof(display_cell));
				tempv->down = NULL;
				v_pointer->down = tempv;
				v_pointer=v_pointer->down;
				


				//incrementing h_counter
				display_cell * temph = (display_cell*)malloc(sizeof(display_cell));
				temph->next = NULL;
				h_pointer->next = temph;
				h_pointer=h_pointer->next;				
				
				}
		
				if(node_count>1)
				{
				h_pointer->cname=strtol(line.c_str(),NULL,10);
				h_pointer->node=node_count;
				//condition where v_pointer remains the same and h_pointer increases
				//incrementing h_pointer		
				display_cell * temph = (display_cell*)malloc(sizeof(display_cell));
				temph->next = NULL;
				h_pointer->next = temph;
				h_pointer=h_pointer->next;					
					
				}
				
			}
			//cout<<node_limit<<"...    ..."<<node_count<<"\n";
		}	myfile2.close();
	}





/////////displaying function//////////////////////////


v_pointer=head;
h_pointer=head;
while(v_pointer->down!=NULL)
{
	h_pointer=v_pointer;
	v_pointer=v_pointer->down;
	while(h_pointer->next!=NULL)
		{
		//cout<<h_pointer->cname<<" , ";
		h_pointer=h_pointer->next;
		}//h_pointer loop ends
	//cout<<"\n";

}//v_pointer loop ends







///////////////////reading weights file and updating in 2D MATRIX//////////////////////////////


string line2,line2a,line2b;
float temp_weight;
int temp_ap;
int temp_name;
i=0;
ifstream myfile3 ("ibm15.wts");
	if (myfile3.is_open())
	{
		while (getline (myfile3,line2))
		{	i++;
			//cout<<line2<<"\n";
	
		if(i>5)	
			{		
			//cout<<line2<<"\n";		
			line2a=line2.substr(0,10);
			line2b=line2.substr(11,line2.length());
			if(line2a.find("p")<10)
					{
					line2a=line2a.substr(line2a.find("p")+1,line2a.length());
					temp_ap=0;
					}
			else if(line2a.find("a")<10)
					{
					line2a=line2a.substr(line2a.find("a")+1,line2a.length());
					temp_ap=1;
					}										

			
			//cout<<line2a;
			//cout<<line2b;
			temp_weight=strtol(line2b.c_str(),NULL,10);
			temp_name=strtol(line2a.c_str(),NULL,10);
			//cout<<temp_name<<"...."<<temp_weight<<"..."<<temp_ap;
						
			v_pointer=head;
			h_pointer=head;
			while(v_pointer->down!=NULL)
				{
				h_pointer=v_pointer;
				v_pointer=v_pointer->down;
				while(h_pointer->next!=NULL)
					{
					if(h_pointer->cname==temp_name && h_pointer->ap == temp_ap)
						{
						h_pointer->weight=temp_weight;	
						}
					h_pointer=h_pointer->next;
					}//h_pointer loop ends
				

				}//v_pointer loop ends
			
			}
		}myfile3.close();	
	}


///////////////////updating width and height///////////////////also set the initial orientation of cells to N and their position offset,placed as 0,0

string line3,line3a,line3b,line3c;
string temp_orientation;
int temp_offsetx;
int temp_offsety;
int temp_width;
int temp_height;
i=0;
int j;
j=0;
ifstream myfile4 ("ibm15.nodes");
	if (myfile4.is_open())
	{
		while (getline (myfile4,line3))
		{	i++;
		
	
		if(i>7)	
			{		
			//cout<<line2<<"\n";		
			line3a=line3.substr(0,11);
			line3b=line3.substr(11,11);
			line3c=line3.substr(line3.length()-5,line3.length());
			//cout<<line2.length();
			if(line3a.find("p")<10)
					{
					line3a=line3a.substr(line3a.find("p")+1,line3a.length());
					temp_name=strtol(line3a.c_str(),NULL,10);
					temp_offsetx=0;
					temp_offsety=0;
					temp_orientation="N";
					temp_ap=0;
					temp_width=1;
					temp_height=1;
					}
			else if(line3a.find("a")<10)
					{
					line3a=line3a.substr(line3a.find("a")+1,line3a.length());
					temp_ap=1;
					temp_offsetx=0;
					temp_offsety=0;
					temp_orientation="N";
					temp_width=strtol(line3b.c_str(),NULL,10);
					temp_height=strtol(line3c.c_str(),NULL,10);
					temp_name=strtol(line3a.c_str(),NULL,10);
					}										

						
			v_pointer=head;
			h_pointer=head;
			while(v_pointer->down!=NULL)
				{
				h_pointer=v_pointer;
				v_pointer=v_pointer->down;
				while(h_pointer->next!=NULL)
					{
					if(h_pointer->cname==temp_name && h_pointer->ap == temp_ap)
						{
						h_pointer->width=temp_width;
						h_pointer->height=temp_height;
						h_pointer->x_offset=temp_offsetx;
						h_pointer->y_offset=temp_offsety;
						h_pointer->orientation=temp_orientation;
                                                h_pointer->placed=0;

						}
					h_pointer=h_pointer->next;
					}//h_pointer loop ends
				

				}//v_pointer loop ends
						
			if(temp_ap==1)
			{
				
				unique[j].name=temp_name;
				unique[j].width=temp_width;
				unique[j].height=temp_height;
				unique[j].x_offset=temp_offsetx;
				unique[j].y_offset=temp_offsety;
				cout<<unique[j].name<<"...."<<unique[j].width<<"...."<<unique[j].height<<"...."<<unique[j].x_offset<<"...."<<unique[j].y_offset<<"...."<<temp_ap<<"....";
			j++;
			
			}
			


			//cout<<temp_name<<"...."<<temp_width<<"..."<<temp_height<<"..."<<temp_ap<<"..."<<temp_offsetx<<"..."<<temp_offsety<<"..."<<temp_orientation;
			cout<<"\n";
			}
			
		}	
	}










//////////////////////////////updating orientation and x,y offsets///////////// here only pads orientation is updated, not for cells

i=0;
string line4,line4a,line4b,line4c,line4d;


//int temp_offsetx;
//int temp_offsety;
//string temp_orientation;

ifstream myfile5 ("ibm15.pl");
	if (myfile5.is_open())
	{
		while (getline (myfile5,line4))
		{	i++;
		
	
		if(i>6 )	
			{		
						
			line4a=line4.substr(0,7);
			line4b=line4.substr(11,5);
			line4c=line4.substr(20,line4.find(":")-20-1);
			line4d=line4.substr(line4.find(":")+1,line4.length()-line4.find(":"));
			//	cout<<line4a<<" "<<line4b<<" "<<line4c<<" "<<line4d;
			//line4b=line4.substr(11,11);
			//line4c=line4.substr(line4.length()-5,line4.length());
			//cout<<line2.length();
			if(line4a.find("p")<10)
					{
					line4a=line4a.substr(line4a.find("p")+1,line4a.length());
					temp_name=strtol(line4a.c_str(),NULL,10);
					temp_offsetx=strtol(line4b.c_str(),NULL,10);
					temp_offsety=strtol(line4c.c_str(),NULL,10);
					temp_orientation=line4d;
					temp_ap=0;
					
					}
			else if(line4a.find("a")<10)
					{
					line4a=line4a.substr(line4a.find("a")+1,line4a.length());
					temp_ap=1;
					temp_offsetx=0;
					temp_offsety=0;
					temp_orientation="N";
					temp_name=strtol(line4a.c_str(),NULL,10);
					}										

			v_pointer=head;
			h_pointer=head;
			while(v_pointer->down!=NULL)
				{
				h_pointer=v_pointer;
				v_pointer=v_pointer->down;
				while(h_pointer->next!=NULL)
					{
					if(h_pointer->cname==temp_name && h_pointer->ap == temp_ap)
						{
						h_pointer->x_offset=temp_offsetx;
						h_pointer->y_offset=temp_offsety;
						h_pointer->orientation=temp_orientation;
						}
					h_pointer=h_pointer->next;
					}//h_pointer loop ends
				

				}//v_pointer loop ends
			
					


			//cout<<temp_name<<"...."<<temp_offsetx<<"..."<<temp_offsety<<"..."<<temp_orientation;
			//cout<<"\n";
			}
		}	
	}













//displying after initial positioning////////////////
int k=0;
int r1=0;
int r2=0;
while(k<161187)
	{
	r1=(r1+ rand() % 6764)%6764;
	r2=(r2+ rand() % 422)%422;
	if(unique[i].width + r1  < 6764 && unique[i].height + r2 < 422)
		{
		unique[k].x_offset = r2;
		unique[k].y_offset = r1;
		k++;
		}
	//cout<<" k "<<k <<"r1: "<< r1<<"r2: "<< r2<<endl;
	}
			

	

for(i=0;i<161187;i++)
		{

			v_pointer=head;
			h_pointer=head;
			while(v_pointer->down!=NULL)
				{
				h_pointer=v_pointer;
				v_pointer=v_pointer->down;
				while(h_pointer->next!=NULL)
					{
					if(h_pointer->cname==unique[i].name)
						{
						h_pointer->x_offset=unique[i].x_offset;
						h_pointer->y_offset=unique[i].y_offset;
						//h_pointer->orientation=temp_orientation;
						}
					h_pointer=h_pointer->next;
					}//h_pointer loop ends
				

				}//v_pointer loop ends
			

		} // for loop ends prev_wl;






float total_temp_wl=0;
float total_wl;
v_pointer=head;
h_pointer=head;

	while(v_pointer->down!=NULL)
	{	//i++;
		h_pointer=v_pointer;
	
		while(h_pointer->next!=NULL)
			{
	
			total_temp_wl=total_temp_wl+wire_length(v_pointer->x_offset,v_pointer->y_offset,h_pointer->x_offset, h_pointer->y_offset);
			
			//cout<<v_pointer->cname<<"."<<h_pointer->cname<<"\n";
			//cout<<total_temp_wl<<"\n";
			h_pointer=h_pointer->next;
			}//h_pointer loop ends
	
		v_pointer=v_pointer->down;
	}//v_pointer loop ends

total_wl=total_temp_wl;

//////////calculating total overlapp area///////////
float total_overlap;
total_overlap=0;
for (int i=0;i<161187;i++)
	{
	total_overlap=total_overlap+findOverlapArea(unique[i].x_offset,unique[i].y_offset,unique[i].x_offset+ unique[i].width, unique[i].y_offset + unique[i].height);
	}
	
float initial_overlap;
initial_overlap=total_overlap;




float prev_wl;
float new_wl;
int prev_area;
int new_area;
float temperature;
int prev_offsetx;
int prev_offsety;
int area_diff;
int wl_diff;
int selected;



temperature=4000000;
float alpha;
int iteration=0;
while(temperature>0.1)

{	
	if(temperature>3600000 || temperature <400000)
		alpha=0.8;
	else 
		alpha=0.95;
	iteration++;
	//cout<<temperature<<","<<iteration<<"\n";
	//if(selected==1)	
	temperature=schedule(temperature,alpha);
	//temperature--;
	for(int blah=0;blah<5000;blah++)
	{	
		i=rand()%161187;
		k=0;
		selected=1;	



			prev_area=findOverlapArea(unique[i].x_offset,unique[i].y_offset,unique[i].x_offset+ unique[i].width, unique[i].y_offset + unique[i].height);
			v_pointer=head;
			h_pointer=head;
			float temp_wl=0;
			//cout<<"debug 1\n";
			while(v_pointer->down!=NULL)
			{	//cout<<"ye ho rha hai";
				//if(v_pointer->down==NULL)
				//cout<<"first wala chal rha \n";
				h_pointer=v_pointer;
	
				while(h_pointer->next!=NULL)
					{
					if(v_pointer->cname==i) //checking only for a0
						{
						temp_wl=temp_wl+wire_length(v_pointer->x_offset,v_pointer->y_offset,h_pointer->x_offset,h_pointer->y_offset);
						//cout<<"ye ho rha hai";
						//cout<<v_pointer->cname<<"."<<h_pointer->cname<<"\n";
						//cout<<temp_wl<<"\n";
			
						}
					else if (h_pointer->node>1 && h_pointer->cname==i )
						{
						temp_wl=temp_wl+wire_length(v_pointer->x_offset,v_pointer->y_offset,h_pointer->x_offset,h_pointer->y_offset);
						//cout<<"ye bhi ho rha hai";
						//cout<<v_pointer->cname<<"."<<h_pointer->cname<<"\n";
			
						//cout<<temp_wl<<"\n";
						}
		
					h_pointer=h_pointer->next;
					}//h_pointer loop ends
	
				v_pointer=v_pointer->down;
			}//v_pointer loop ends
			//cout<<"debug 2\n";
			prev_wl=temp_wl;
			prev_offsetx=unique[i].x_offset;
			prev_offsety=unique[i].y_offset;
		
			k=0;
			while(k<1)
			{
			r1=(rand() % 6764)-unique[i].width;
			r2=( rand() %422) -unique[i].height;
			//cout<<"debug 2.1\n";
			if(unique[i].width + r1  < 6764 && unique[i].height + r2 < 422)
				{
				//cout<<"debug 2.2\n";5153
				unique[i].x_offset = r2;
				unique[i].y_offset = r1;
				k++;
				}


			}
			//cout<<"debug 3\n";

		

					v_pointer=head;
					h_pointer=head;
					while(v_pointer->down!=NULL)
						{
						h_pointer=v_pointer;
						v_pointer=v_pointer->down;
						while(h_pointer->next!=NULL)
							{
							if(h_pointer->cname==unique[i].name)
								{
								h_pointer->x_offset=unique[i].x_offset;
								h_pointer->y_offset=unique[i].y_offset;
								//h_pointer->orientation=temp_orientation;
								}
							h_pointer=h_pointer->next;
							}//h_pointer loop ends
			
						}//v_pointer loop ends
			

				
			//cout<<"debug 4\n";

			new_area=findOverlapArea(unique[i].x_offset,unique[i].y_offset,unique[i].x_offset+ unique[i].width, unique[i].y_offset + unique[i].height);
			//cout<<"debug 5\n";

			v_pointer=head;
			h_pointer=head;
			temp_wl=0;
			//cout<<"ye ho rha hai lol \n";
			while(v_pointer->down!=NULL)
			{	//i++;
				cout<<"ye ho rha hai lol";
				h_pointer=v_pointer;
	
				while(h_pointer->next!=NULL)
					{
					if(v_pointer->cname==i) //checking only for a0
						{
						temp_wl=temp_wl+wire_length(v_pointer->x_offset,v_pointer->y_offset,h_pointer->x_offset,h_pointer->y_offset);
						//cout<<"ye ho rha hai";
						//cout<<v_pointer->cname<<"."<<h_pointer->cname<<"\n";
						//cout<<temp_wl<<"\n";
			
						}
					else if (h_pointer->node>1 && h_pointer->cname==i )
						{
						temp_wl=temp_wl+wire_length(v_pointer->x_offset,v_pointer->y_offset,h_pointer->x_offset,h_pointer->y_offset);
						//cout<<"ye bhi ho rha hai";
						//cout<<v_pointer->cname<<"."<<h_pointer->cname<<"\n";
			
						//cout<<temp_wl<<"\n";
						}//else if ends
		
					h_pointer=h_pointer->next;
					}//h_pointer loop ends
	
				v_pointer=v_pointer->down;
			}//v_pointer loop ends
			//cout<<"ye ho rha hai\n";
			
			new_wl=temp_wl;
			area_diff=prev_area-new_area;
			wl_diff=prev_wl-new_wl;
			//cout<<"results for node";
			//cout<<i<<endl;
			//cout<<prev_area<<" ... "<<new_area<<"\n";
			//cout<<prev_wl<<" ... "<<new_wl<<"\n";
			//cout<<wl_diff<<"\n";
			//cout<<area_diff<<"\n";
			if(wl_diff+area_diff>0 || (rand()%2>exp((wl_diff+area_diff)/temperature) ))
				{
				selected=1;
				}
			else				// you can probably put a condition here for acceptance according to temperature
				{
				selected=0;
				}

			if(selected==1)
				{
				unique[i].x_offset=unique[i].x_offset;
				unique[i].y_offset=unique[i].y_offset;	
				total_wl=total_wl-wl_diff;
				total_overlap=total_overlap-area_diff;			
				//do something like exiting a while condition which should run a maximum of 10 times if the gain is still less that 0
				}
			else if(selected==0)
				{
				unique[i].x_offset=prev_offsetx;
				unique[i].y_offset=prev_offsety;
		
				
					v_pointer=head;
					h_pointer=head;
					while(v_pointer->down!=NULL)
						{
						h_pointer=v_pointer;
						v_pointer=v_pointer->down;
						while(h_pointer->next!=NULL)
							{
							if(h_pointer->cname==unique[i].name)
								{
								h_pointer->x_offset=unique[i].x_offset;
								h_pointer->y_offset=unique[i].y_offset;
								//h_pointer->orientation=temp_orientation;
								}
							h_pointer=h_pointer->next;
							}//h_pointer loop ends
			
						}//v_pointer loop ends
			

				// again designate the unique offsets to the previous one and update the 2d array as well
				}
		
	}
		cout<<"total wire length is "<<total_wl<<"\n";
			//cout<<"total overlapp area is "<<total_overlap<<"\n";
}
// temperature for ends
cout<<total_temp_wl<<"\n";
total_temp_wl=0;

v_pointer=head;
h_pointer=head;

	while(v_pointer->down!=NULL)
	{	//i++;
		h_pointer=v_pointer;
	
		while(h_pointer->next!=NULL)
			{
	
			total_temp_wl=total_temp_wl+wire_length(v_pointer->x_offset,v_pointer->y_offset,h_pointer->x_offset, h_pointer->y_offset);
			//cout<<"lol ye ho rha hai";
			//cout<<v_pointer->cname<<"."<<h_pointer->cname<<"\n";
			//cout<<total_temp_wl<<"\n";
			h_pointer=h_pointer->next;
			}//h_pointer loop ends
	
		v_pointer=v_pointer->down;
	}//v_pointer loop ends

total_wl=total_temp_wl;
cout<<total_wl<<"\n";
total_overlap=0;
for (int i=0;i<161187;i++)
	{
	total_overlap=total_overlap+findOverlapArea(unique[i].x_offset,unique[i].y_offset,unique[i].x_offset+ unique[i].width, unique[i].y_offset + unique[i].height);
	}
	
cout<<initial_overlap<<"\n";
cout<<total_overlap<<"\n";







}//int main ends




// need a function to calculate wire length







