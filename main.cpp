#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include "graphics.h"
#include <time.h>
#pragma comment(lib,"graphics.lib")
using namespace std;
#define Round(a)(int)(a + 0.5) // Lam tron so
int color = 15;
//nhap ten
char ch;
//do dai ten
int leng = 0;
//point nguoi dang choi
int point =0;
//dan
int ammo = 3;
//so sanh diem
int dc =0;
//ten nguoi choi
char _a[30] = {""};
struct Point { int x,y ;};
// point nguoi choi ten va point
struct GuyPoint{
	char name[30];
	int point;
};
GuyPoint p[100]; // khai bao tam 100 nguoi choi
Point d;
void bg();
void loading();
void lineDDA(int x1, int y1, int x2, int y2);
void button_level();
void button_Play_Quit();
void Go();
void button_Go();
void input_name();
void plot(Point p,int x,int y,int color,int type);
void draw_elip(Point d, int a, int b, int type,int color);
void drawLipDuck_Left(Point d);
void drawLipDuck_Right(Point d);
void drawRearDuck_Left(Point d);
void drawRearDuck_Right(Point d);
void drawHeadDuck(Point d);
void drawHandDuckTop(Point d);
void drawHandDuckDown(Point d);
void drawDuck_Left(Point d,int color);
void drawDuck_Right(Point d,int color);
void drawDuck_RightB(Point d,int color);
void animationDuck(Point d);
void buttonCheckDie(int &a, int &b);
void draw8point(int x0,int y0,int x, int y, int color);
void MidPoint(int x0,int y0,int r,int color);
void draw_Sun();
void draw_Bamboo();
bool checkDuckDie();
bool checkHighScore();
bool getMouseClickEvent(int &a, int &b);
bool checkPlay();
bool checkInputName();
bool checkName();
bool checkBack();
void run();

// Nhap ten ng??i ch?i
void InputPoin_Name(char name[20])
{
	ofstream out("kq.txt", std::ofstream::app);	
	out<< name << endl;
	out.close();
}
//// Nhâp ?i?m ng??i ch?i
void InputPoin_Point(int point)
{
	
	ofstream out("kq.txt", std::ofstream::app); 
	out << point << endl ;
	out.close();
}
// dem so dong trong file
int lineCount()
{
   ifstream f1;
   char c;
   int numchars, numlines;
   f1.open("kq.txt");
   numchars = 0;
   numlines = 0;
   f1.get(c);
   while (f1) {
     while (f1 && c != '\n') {
       numchars = numchars + 1;
       f1.get(c);
     }
     numlines = numlines + 1;
     f1.get(c);
   }
   return numlines;
}
// doc point file
void readPoint()
{
	int i = 0;
	ofstream output;
	ifstream input;
	input.open("kq.txt",ios::in);
	int lineNumber = lineCount()/2; 
	if(input.is_open())
	{
		while (i < lineNumber){
			string a;
			int b;
			input >> a;
			input.ignore();
			input >> b;
			input.ignore();
			std::string str = a;
			std::copy(str.begin(), str.end(), p[i].name);
			p[i].point = b;
			i++;
		}
	}
	else
		cout << "Open file error! ";
	input.close();
	//xep hang point
}
// xep hang nguoi choi
void xepHang()
{
	int lineNumber = lineCount()/2;
	for(int m = 0; m < lineNumber -1 ; m++)
	{
		for(int n = m + 1; n < lineNumber;n++)
		{
			if(p[m].point < p[n].point){
                // Hoan vi 2 so a[i] va a[j]
                GuyPoint p1 = p[m];
                p[m] = p[n];
                p[n] = p1; 
			}
		}
	}
	/*for(int m = 0; m < lineNumber ; m++)
	{
		cout <<p[m].name <<"	" << p[m].point << endl;
	}*/
}
void Go()
{
	int x = getmaxx();
	int	y = getmaxy();
	//Go
	lineDDA(x - 100,y -455,x -25, y -455);
	lineDDA(x -25,y - 455,x - 25, y -430);
	lineDDA(x -25,y - 430,x - 100, y -430);
	lineDDA(x - 100,y -430,x - 100, y -455);
	outtextxy(x - 80,y - 450,"Go");
}
void high_Score()
{
	Go();
	int lineNumber = lineCount()/2;
	settextstyle(2,0,10);
	outtextxy(getmaxx()/2- 180,getmaxy()/2-230,"HIGH SCORE");
	settextstyle(0,0,2);
	outtextxy(getmaxx()/2- 260,getmaxy()/2-190,"STT          Name            Point");
	int a = 20;
	for(int m = 0; m < lineNumber ; m++)
	{
		//STT
		int number= m +1 ;
		stringstream strs;
		strs << number;
		string temp_str = strs.str();
		char* char_type = (char*) temp_str.c_str();
		int x,y;
		x = getmaxx()/2- 260;
		y =	getmaxy()/2-180 + a;
		outtextxy(x,y,char_type);
		///NAME
		outtextxy(x + 180,y,p[m].name);
		//POINT
		int number_1= p[m].point ;
		stringstream strs_1;
		strs_1 << number_1;
		string temp_str_1 = strs_1.str();
		char* char_Point = (char*) temp_str_1.c_str();
		outtextxy(x + 180+250,y,char_Point);
		a+=20;
		}
}
//// Hi?n ?i?m ng??i cao nh?t và ng??i ?ang ch?i
void Point_Player()
{
	
	int x,y;
	x =getmaxx();
	y = getmaxy() ;
	settextstyle(1,0,1);
	outtextxy(x- 400, 10,"HIGHSCORE:");
	//settextstyle(0,0,2);
	//outtextxy(x-80,y+80,"Name                   Point");
	setcolor(WHITE);

	// NGUOi Choi Cao point Nhat
	///NAME
	outtextxy(x-200,10,p[0].name);
	//POINT
	int number_2= p[0].point;
	stringstream strs_2;
	strs_2 << number_2;
	string temp_str_2 = strs_2.str();
	char* char_Point2 = (char*) temp_str_2.c_str();
	outtextxy(x - 100,10,char_Point2);

	// Hien point Nguoi Dang Choi
	//setcolor(15);
	//settextstyle(2,0,9);
	outtextxy(x / 2 + 100,y - 30,"Ammo: ");
	//settextstyle(0,0,2);
	outtextxy(x / 2 - 200,y - 30,"Your Score: ");
	//setcolor(RED);
	///NAME
	//outtextxy(x ,y+260,_a);
	//POINT
	int number_3 = point;
	stringstream strs_3;
	strs_3 << number_3;
	string temp_str_3 = strs_3.str();
	char* char_Point3 = (char*) temp_str_3.c_str(); 
	outtextxy(x / 2 - 50,y - 30,char_Point3);
	
	//amo
	int number_4 = ammo;
	stringstream strs_4;
	strs_4 << number_4;
	string temp_str_4 = strs_4.str();
	char* char_Point4 = (char*) temp_str_4.c_str();
	outtextxy(x / 2 + 200,y - 30,char_Point4);

	if(number_2 < number_3)
		dc = 1;
	else 
		dc = 0;
}
// tuy tron ve elip , 0 tròn elip, 1 n?a elip trên, 2 n?a elip d??i
void plot(Point p,int x,int y,int color,int type)
{
	if (type == 0) //full
	{
		putpixel(p.x+x, p.y+y, color);
		putpixel(p.x-x, p.y+y, color);
		putpixel(p.x+x, p.y-y, color);
		putpixel(p.x-x, p.y-y, color);
	}
	if (type == 1) //down
	{
		putpixel(p.x+x, p.y-y, color);
		putpixel(p.x-x, p.y-y, color);
	}
	if (type == 2) //up
	{
		putpixel(p.x+x, p.y+y, color);
		putpixel(p.x-x, p.y+y, color);
	}
}
void draw_elip(Point d, int a, int b, int type,int color) //a khoang cach ngang, b khoang cach doc
{
    int x, y, fx, fy, a2, b2, p;
    x = 0;
    y = b;
    a2 = a*a;
    b2 = b*b;
    fx = 0;
    fy = 2 * a2 * y;
    plot(d,x, y,color,type);
    p = Round(b2 -(a2*b) + (0.25*a2));
    while(fx<fy)
    {
        x++;
        fx += 2*b2;
       // delay(10);
        if(p<0)
        {
            p += b2*(2*x + 3);
        }
        else
        {
            y--;
            p += b2*(2*x +3) + a2*(2- 2*y);
            fy -= 2*a2;
        }
        plot(d, x, y, color, type);
    }
    p = Round(b2*(x +0.5)*(x +0.5) + a2*(y-1)*(y-1) - a2*b2);
    while(y>0)
    {
        y--;
        fy -= 2*a2;
        //delay(10);
        if(p >=0)
        {
            p += a2*(3-2*y); 
        }
        else
        {
            x++;
            fx += 2*b2;
            p += b2*(2*x +2) +a2*(3- 2*y);
        }
        plot(d, x, y, color, type);
    }
}
// m? v?t bay trái
void drawLipDuck_Left(Point d)
{
	Point p[3];
	p[0] = d;
	p[1].x = p[0].x -5;
	p[1].y = p[0].y +5;
	p[2].x = p[0].x;
	p[2].y = p[1].y+5;
	lineDDA(p[0].x,p[0].y,p[1].x,p[1].y);
	lineDDA(p[1].x,p[1].y,p[2].x,p[2].y);
	lineDDA(p[2].x,p[2].y,p[0].x,p[0].y);
}
// m? v?t bay ph?i
void drawLipDuck_Right(Point d)
{
	Point p[3];
	p[0] = d;
	p[1].x = p[0].x + 5;
	p[1].y = p[0].y + 5;
	p[2].x = p[0].x;
	p[2].y = p[1].y+5;
	lineDDA(p[0].x,p[0].y,p[1].x,p[1].y);
	lineDDA(p[1].x,p[1].y,p[2].x,p[2].y);
	lineDDA(p[2].x,p[2].y,p[0].x,p[0].y);
}
// duoi vit bay trái
void drawRearDuck_Left(Point d)
{
	Point p[3];
	p[0] = d;
	p[1].x = p[0].x - 10;
	p[1].y = p[0].y +10;
	p[2].x = p[0].x;
	p[2].y = p[1].y+10;
	lineDDA(p[0].x,p[0].y,p[1].x,p[1].y);
	lineDDA(p[1].x,p[1].y,p[2].x,p[2].y);
	lineDDA(p[2].x,p[2].y,p[0].x,p[0].y);
}
// ?uôi v?t bay ph?i
void drawRearDuck_Right(Point d)
{
	Point p[3];
	p[0] = d;
	p[1].x = p[0].x + 10;
	p[1].y = p[0].y +10;
	p[2].x = p[0].x;
	p[2].y = p[1].y+10;
	lineDDA(p[0].x,p[0].y,p[1].x,p[1].y);
	lineDDA(p[1].x,p[1].y,p[2].x,p[2].y);
	lineDDA(p[2].x,p[2].y,p[0].x,p[0].y);

}
// m? v?t
void drawHeadDuck(Point d)
{
	Point p[3];
	p[0] = d;
	p[1].x = p[0].x - 8;
	p[1].y = p[0].y +8;
	p[2].x = p[0].x+8;
	p[2].y = p[1].y;
	lineDDA(p[0].x,p[0].y,p[1].x,p[1].y);
	lineDDA(p[1].x,p[1].y,p[2].x,p[2].y);
	lineDDA(p[2].x,p[2].y,p[0].x,p[0].y);
}
// cánh v?t trên
void drawHandDuckTop(Point d)
{
	Point p[3];
	p[0] = d;
	p[1].x = p[0].x - 15;
	p[1].y = p[0].y - 30;
	p[2].x = p[0].x+30;
	p[2].y = p[1].y;
	lineDDA(p[0].x,p[0].y,p[1].x,p[1].y);
	lineDDA(p[1].x,p[1].y,p[2].x,p[2].y);
	lineDDA(p[2].x,p[2].y,p[0].x,p[0].y);
}
// cánh v?t d??i
void drawHandDuckDown(Point d){
	Point p[3];
	p[0] = d;
	p[1].x = p[0].x -15;
	p[1].y = p[0].y + 30;
	p[2].x = p[0].x+30;
	p[2].y = p[1].y;
	lineDDA(p[0].x,p[0].y,p[1].x,p[1].y);
	lineDDA(p[1].x,p[1].y,p[2].x,p[2].y);
	lineDDA(p[2].x,p[2].y,p[0].x,p[0].y);
}
// v?t bay sang trái
void drawDuck_Left(Point d,int color)
{
	Point p[7];
	p[0] = d;
	// than vit
	draw_elip(p[0],22,18, 0,color);
	// dau vit
	p[1].x = p[0].x - 32;
	p[1].y = p[0].y;
	draw_elip(p[1],13,13, 0,color);
	//canh vit
	p[2].x = p[0].x;
	p[2].y = p[0].y - 5 ;
	drawHandDuckTop(p[2]);
	//draw_elip(p[0],18,5,1,color);
	//draw_elip(p[0],18,8,2,color);
	 //mieng vit
	p[4].x = p[0].x - 20 - 13*2;
	p[4].y = p[0].y - 5;
	drawLipDuck_Left(p[4]);
	//mat vit
	draw_elip(p[1],8,7,1,15);
	draw_elip(p[1],3,3,0,RED);
	// duoi vit
	p[5].x = p[0].x + 32;
	p[5].y = p[0].y - 15;
	drawRearDuck_Left(p[5]);
	p[5].x = p[0].x + 32;
	p[5].y = p[0].y - 12;
	drawRearDuck_Left(p[5]);
	p[5].x = p[0].x + 32;
	p[5].y = p[0].y - 10;
	drawRearDuck_Left(p[5]);
	// mu vit
	p[6].y = p[1].y - 13 -10 + 1;
	p[6].x = p[1].x;
	drawHeadDuck(p[6]);
}
// v?t bay sang ph?i
void drawDuck_Right(Point d,int color)
{
	Point p[7];
	p[0] = d;
	// than vit
	draw_elip(p[0],22,18, 0,color);
	//canh vit
	p[2].x = p[0].x;
	p[2].y = p[0].y- 5;
	//draw_elip(p[0],18,5,1,color);
	drawHandDuckTop(p[2]);
	// dau vit
	p[1].x = p[0].x + 32 ;
	p[1].y = p[0].y;
	draw_elip(p[1],13,13, 0,color);
	//mat vit
	draw_elip(p[1],8,7,1,15);
	draw_elip(p[1],3,3,0,RED);
	 //mieng vit
	p[4].x = p[0].x + 20 + 13*2;
	p[4].y = p[0].y - 5;
	drawLipDuck_Right(p[4]);
	//draw_elip(p[0],18,8,2,color);
	// duoi vit
	p[5].x = p[1].x - 32 - 30;
	p[5].y = p[0].y - 15;
	drawRearDuck_Right(p[5]);
	p[5].x = p[1].x - 32 - 30; // x - 60 
	p[5].y = p[0].y - 12;
	drawRearDuck_Right(p[5]);
	p[5].x =p[1].x - 32 - 30;
	p[5].y = p[0].y - 10;
	drawRearDuck_Right(p[5]);
	// mu vit
	p[6].y = p[1].y - 13 -10 + 1;
	p[6].x = p[0].x + 32;
	drawHeadDuck(p[6]);
}
void drawDuck_RightB(Point d,int color)
{
	
	Point p[7];
	p[0] = d;
	// than vit
	draw_elip(p[0],22,18, 0,color);
	//canh vit
	p[2].x = p[0].x;
	p[2].y = p[0].y- 5;
	//draw_elip(p[0],18,5,1,color);
	drawHandDuckDown(p[2]);
	// dau vit
	p[1].x = p[0].x + 32 ;
	p[1].y = p[0].y;
	draw_elip(p[1],13,13, 0,color);
	//mat vit
	draw_elip(p[1],8,7,1,15);
	draw_elip(p[1],3,3,0,RED);
	 //mieng vit
	p[4].x = p[0].x + 20 + 13*2;
	p[4].y = p[0].y - 5;
	drawLipDuck_Right(p[4]);
	//draw_elip(p[0],18,8,2,color);
	// duoi vit
	p[5].x = p[1].x - 32 - 30;
	p[5].y = p[0].y - 15;
	drawRearDuck_Right(p[5]);
	p[5].x = p[1].x - 32 - 30;
	p[5].y = p[0].y - 12;
	drawRearDuck_Right(p[5]);
	p[5].x =p[1].x - 32 - 30;
	p[5].y = p[0].y - 10;
	drawRearDuck_Right(p[5]);
	// mu vit
	p[6].y = p[1].y - 13 -10 + 1;
	p[6].x = p[0].x + 32;
	drawHeadDuck(p[6]);
	
}
void bg()
{
	int x = getmaxx()/4;
	setcolor(LIGHTBLUE);
	settextstyle(3,0,5);
	outtextxy(x-70,20,"DUCK SHOOTING");

}
void animationDuck()
{
	int i = 0;
	int maxX = getmaxx();
	int a,b;
	d.x = -60;
	d.y = 100;
	if(ammo != 0){
	//Round 1
	while (point < 100 && ammo != 0){
	for(i = 0;i <= maxX ;i++)
	{
		Point_Player();
		d.x += i;
		if(ammo > 0 && ammo <= 3){
		if(i % 2 == 0)
		{
			d.y += 50;
			draw_Bamboo();
			drawDuck_Right(d,7);
			
			if(ismouseclick(WM_LBUTTONDOWN))
			{

				if(checkDuckDie() == true)
				{
					cout << "Die" << endl;
					point += 50;
					if(ammo < 3 && ammo > 0)
					{
						ammo++;
					}
					cleardevice();
					delay(300);
					animationDuck();
					
				}	
				else
				{
					ammo--;
					cleardevice();
					delay(100);
					animationDuck();
				}
			}
		
			
		}else
		{
			d.y -= 50;
			drawDuck_RightB(d,7);	
			if(ismouseclick(WM_LBUTTONDOWN))
			{
				if(checkDuckDie() == true)
				{
					
					cout << "Die" << endl;
					point += 50;
					if(ammo < 3 && ammo > 0)
					{
						ammo++;
					}
					cleardevice();
					delay(300);
					
					animationDuck();
				}	
				else
				{
					ammo--;
					cleardevice();
					delay(100);
					animationDuck();
					
				}
			}
		}
				
		delay(100);
		cleardevice();
		if(i == 40){
			d.x = 0;
			d.y = 100;
			animationDuck();
		}
		cout <<"point: " << point << endl;
		cout <<"ammo " << ammo << endl;
		cout <<"x : " << d.x << endl;
		cout <<"y : " << d.y << endl;
		cout <<"i = " << i  << endl;
	}
	}
	}
	// Round 2
	while (point >= 100 && ammo != 0 && point < 300){
	for(i = 0;i <= maxX ;i++)
	{
		Point_Player();
		d.x += i;
		if(ammo > 0 && ammo <= 3){
		if(i % 2 == 0)
		{
			d.y += 50;
			draw_Sun();
			drawDuck_Right(d,7);
			
			
			if(ismouseclick(WM_LBUTTONDOWN))
			{
				
				if(checkDuckDie() == true)
				{
					cout << "Die" << endl;
					point += 50;
					if(ammo < 3 && ammo > 0)
					{
						ammo++;
					}
					cleardevice();
					delay(100);
					animationDuck();
					
				}	
				else
				{
					ammo--;
					cleardevice();
					delay(100);
					animationDuck();
				}
			}
		
			
		}else
		{
			d.y -= 50;
			drawDuck_RightB(d,7);	
			if(ismouseclick(WM_LBUTTONDOWN))
			{
				if(checkDuckDie() == true)
				{
					
					cout << "Die" << endl;
					point += 50;
					if(ammo < 3 && ammo > 0)
					{
						ammo++;
					}
					cleardevice();
					delay(100);
					
					animationDuck();
				}	
				else
				{
					ammo--;
					cleardevice();
					delay(100);
					animationDuck();
					
				}
			}
		}
				
		delay(100);
		cleardevice();
		if(i == 40){
			d.x = 0;
			d.y = 100;
			animationDuck();
		}
		cout <<"point: " << point << endl;
		cout <<"ammo " << ammo << endl;
		cout <<"x : " << d.x << endl;
		cout <<"y : " << d.y << endl;
		cout <<"i = " << i  << endl;
	}	
	}
	}
	//Round 3
	while (point >= 300 && ammo != 0){
	for(i = 0;i <= maxX ;i++)
	{
		Point_Player();
		d.x += i;
		if(ammo > 0 && ammo <= 3){
		if(i % 2 == 0)
		{
			d.y += 50;
			drawDuck_Right(d,7);
			
			
			if(ismouseclick(WM_LBUTTONDOWN))
			{
				
				if(checkDuckDie() == true)
				{
					cout << "Die" << endl;
					point += 50;
					if(ammo < 3 && ammo > 0)
					{
						ammo++;
					}
					cleardevice();
					delay(100);
					animationDuck();
					
				}	
				else
				{
					ammo--;
					cleardevice();
					delay(100);
					animationDuck();
				}
			}
		
			
		}else
		{
			d.y -= 50;
			drawDuck_RightB(d,7);	
			if(ismouseclick(WM_LBUTTONDOWN))
			{
				
				if(checkDuckDie() == true)
				{
					
					cout << "Die" << endl;
					point += 50;
					if(ammo < 3 && ammo > 0)
					{
						ammo++;
					}
					cleardevice();
					delay(100);
					
					animationDuck();
				}	
				else
				{
					ammo--;
					cleardevice();
					delay(100);
					animationDuck();
					
				}
			}
		}
				
		delay(100);
		cleardevice();
		if(i == 40){
			d.x = 0;
			d.y = 100;
			animationDuck();
		}
		cout <<"point: " << point << endl;
		cout <<"ammo " << ammo << endl;
		cout <<"x : " << d.x << endl;
		cout <<"y : " << d.y << endl;
		cout <<"i = " << i  << endl;
	}	
	}
	}
	//
	}else
		{
		
		InputPoin_Point(point);
		readPoint();
		xepHang();
		
		if(dc == 1){
			outtextxy(maxX/2 - 250,240,"Congratulations!! You get new highscore!!!");
			Point_Player();
		}
		else 
		{
			cleardevice();
			outtextxy(maxX/2 - 200,240,"You lose !! Try to play next time !!");
			Point_Player();
		}
		system("pause");
		}
}
void lineDDA(int x1, int y1, int x2, int y2)
{
	int Dx = x2 - x1, Dy = y2 - y1;
	float x_inc, y_inc;
	float step = max(abs(Dx),abs(Dy));
	x_inc = Dx / step;
	y_inc = Dy / step;
	float x = x1, y = y1;
	putpixel(x,y,color);
	int k = 1;
	while(k <= step){
		k++;
	
		x += x_inc;
		y += y_inc;
		putpixel(Round(x),Round(y),color);
	}

}
void button_Play_Quit()
{
	int x = getmaxx()/2;
	int	y = getmaxy()/2;
	
	//Play
	lineDDA(x - 75,y - 150,x + 75, y - 150);
	lineDDA(x + 75,y- 150,x + 75, y - 90);
	lineDDA(x + 75,y - 90,x - 75, y - 90);
	lineDDA(x - 75,y - 90,x - 75, y - 150);
	outtextxy(x - 25,y - 130,"Play");
	//Quit
	lineDDA(x - 75,y + 90,x + 75, y + 90);
	lineDDA(x + 75,y+ 90,x + 75, y + 150);
	lineDDA(x + 75,y + 150,x - 75, y + 150);
	lineDDA(x - 75,y + 150,x - 75, y + 90);
	outtextxy(x - 25,y + 110,"Quit");
	

}
void button_Go()
{
	int x = getmaxx()/2;
	int	y = getmaxy()/2;
	//Go
	lineDDA(x - 75,y + 90,x + 75, y + 90);
	lineDDA(x + 75,y+ 90,x + 75, y + 150);
	lineDDA(x + 75,y + 150,x - 75, y + 150);
	lineDDA(x - 75,y + 150,x - 75, y + 90);
	outtextxy(x - 15,y + 110,"Go");
	//Highscore
	lineDDA(x - 75,y - 30,x + 75, y - 30);
	lineDDA(x + 75,y- 30,x + 75, y + 30);
	lineDDA(x + 75,y + 30,x - 75, y + 30);
	lineDDA(x - 75,y + 30,x - 75, y - 30);
	outtextxy(x - 65,y - 10,"High Score");
}
void buttonCheckDie(int &a, int &b)
{

	while(true){
	if(getMouseClickEvent(a,b) == true)
	{
		//HV
		rectangle(a-40,b-40,a+40,b+40);
		delay(100);
		
	}
	}
}
void draw8point(int x0,int y0,int x, int y, int color)
{
  putpixel( x0 + x , y0 + y ,color);
  putpixel( x0 - x , y0 + y ,color);
  putpixel( x0 + x , y0 - y ,color);
  putpixel( x0 - x , y0 - y ,color);
  putpixel( x0 + y , y0 + x ,color);
  putpixel( x0 - y , y0 + x ,color);
  putpixel( x0 + y , y0 - x ,color);
  putpixel( x0 - y , y0 - x ,color);
}
void MidPoint(int x0,int y0,int r,int color)
{
	int x=0;
	int y=r;
	int p=5/4-r;
	draw8point(x0,y0,x,y,color);
	while(x < y)
	{
		if(p < 0)
			p = p+2*x+3;
		else
		{
			p = p+2*(x-y)+5;
			y = y-1;
		}
		x = x+1;
		draw8point
			(x0,y0,x,y,color);
	}
	
}
void draw_Sun()
{
	cleardevice ();

	int red = 4, yellow = 14;
	//MidPoint(150,60,50,12);
	//ban kinh ban dau la 50
	for(int i = 50; i >= 0; i--)
	{
		int color = 0;
		if(i % 2 == 0)
			color = 14;
		else
			color = 12;
		MidPoint(150,60,i,color);
	}
}
void draw_Bamboo()
{
	//cleardevice ();
	/*setbkcolor (10);*/
	draw_Sun();
	
	//cay thu nhat
	lineDDA(32,478,32,433);32,478,32,433,
	lineDDA(32,433,44,432);44,432,
	lineDDA(44,432,46,436);46,436,
	lineDDA(46,436,44,440);44,440,
	lineDDA(44,440,42,478);42,478;

	lineDDA(33,428,45,427);33,428,45,427,
	lineDDA(45,427,51,396);51,396,
	lineDDA(51,396,54,391);54,391,
	lineDDA(54,391,52,378);52,378,
	lineDDA(52,378,44,374);44,374,
	lineDDA(44,374,41,379);41,379,
	lineDDA(41,379,41,389);41,389,
	lineDDA(41,389,40,406);40,406,
	lineDDA(40,406,36,419);36,419,
	lineDDA(36,419,33,428);33,428,

	lineDDA(32,433,24,432);32,433,24,432,
	lineDDA(24,432,18,427);18,427,
	lineDDA(18,427,32,432);32,432,

	lineDDA(33,428,31,430);
	lineDDA(27,428,23,420);
	lineDDA(23,420,22,392);
	lineDDA(22,392,29,420);
	lineDDA(29,420,32,430);

	
	lineDDA(44,371,61,316);
	lineDDA(61,316,68,316);
	lineDDA(68,316,73,320);
	lineDDA(73,320,54,373);
	lineDDA(44,371,48,374);
	lineDDA(48,374,54,373);

	lineDDA(41,389,34,377);
	lineDDA(34,377,28,367);
	lineDDA(28,367,25,338);
	lineDDA(25,338,27,331);
	lineDDA(27,331,34,362);
	lineDDA(34,362,41,374);
	lineDDA(41,374,41,380);
	
	lineDDA(46,353,47,326);
	lineDDA(47,326,49,316);
	lineDDA(49,316,53,329);
	lineDDA(53,329,53,340);
	lineDDA(53,340,46,353);

	lineDDA(48,298,47,294);
	lineDDA(47,294,47,270);
	lineDDA(47,270,50,269);
	lineDDA(50,269,51,293);
	lineDDA(51,293,49,298);

	lineDDA(47,270,36,276);
	lineDDA(36,276,18,277);
	lineDDA(18,277,35,271);
	lineDDA(35,271,43,269);
	lineDDA(43,269,27,253);
	lineDDA(27,253,21,238);
	lineDDA(21,238,39,262);
	lineDDA(50,269,47,270);
	
	lineDDA(50,191,49,204);
	lineDDA(51, 204,50,191);
	lineDDA(48,213,47,243);
	lineDDA(47,243,50,247);
	lineDDA(50,247,51,243);
	lineDDA(51,243,50,214);

	lineDDA(44,243,40,243);
	lineDDA(40,243,23,231);
	lineDDA(23,231,35,234);
	lineDDA(35,234,44,243);

	lineDDA(11,235,15,235);
	lineDDA(15,235,19,231);
	lineDDA(19,231,21,229);
	lineDDA(21,229,28,230);
	lineDDA(28,230,34,231);
	lineDDA(34,231,39,230);
	lineDDA(39,230,47,240);
	lineDDA(47,240,46,229);
	lineDDA(47,240,44,228);
	lineDDA(44,228,32,203);
	lineDDA(32,203,20,180);
	lineDDA(20,180,27,205);
	lineDDA(27,205,32,217);
	lineDDA(32,217,34,255);
	lineDDA(34,255,33,227);
	lineDDA(33,227,28,222);
	lineDDA(28,222,21,222);
	lineDDA(21,222,17,225);
	lineDDA(17,225,14,230);
	lineDDA(14,230,11,235);

	lineDDA(75,314,71,311);
	lineDDA(71,311,68,314);
	lineDDA(68,314,59,309);
	lineDDA(59,309,54,312);
	lineDDA(54,312,45,310);
	lineDDA(45,310,36,308);
	lineDDA(36,308,23,308);
	lineDDA(23,308,18,306);
	lineDDA(18,306,31,302);
	lineDDA(31,302,41,301);
	lineDDA(41,301,51,300);
	lineDDA(51,300,57,299);
	lineDDA(57,299,62,303);
	lineDDA(62,303,65,302);
	lineDDA(65,302,61,298);
	lineDDA(61,298,56,288);
	lineDDA(56,288,52,275);
	lineDDA(52,275,50,269);
	lineDDA(50,269,48,258);
	lineDDA(48,258,47,249);
	lineDDA(47,249,52,257);
	lineDDA(52,257,55,268);
	lineDDA(55,268,59,278);
	lineDDA(59,278,67,294);
	lineDDA(67,294,75,310);
	lineDDA(75,310,54,261);
	lineDDA(54,261,59,260);
	lineDDA(59,260,62,259);
	lineDDA(62,259,66,253);
	lineDDA(66,253,68,241);
	lineDDA(68,241,60,251);
	lineDDA(60,251,54,260);

	lineDDA(51,201,52,194);
	lineDDA(52,194,56,185);
	lineDDA(56,185,61,175);
	lineDDA(61,175,67,167);
	lineDDA(67,167,76,159);
	lineDDA(76,159,71,167);
	lineDDA(71,167,67,174);
	lineDDA(67,174,63,184);
	lineDDA(63,184,60,196);
	lineDDA(60,196,56,202);
	lineDDA(56,202,51,201);
	
	lineDDA(49,189,50,187);
	lineDDA(50,187,45,181);
	lineDDA(45,181,40,180);
	lineDDA(40,180,7,173);
	lineDDA(7,173,37,182);
	lineDDA(37,182,45,185);
	lineDDA(45,185,49,189);

	
	lineDDA(50,180,50,178);
	lineDDA(50,178,52,171);
	lineDDA(52,171,55,166);
	lineDDA(55,166,78,147);
	lineDDA(78,147,74,153);
	lineDDA(74,153,67,161);
	lineDDA(67,161,56,172);
	lineDDA(56,172,50,180);
	lineDDA(49,167,51,162);

	lineDDA(51,162,49,136);
	lineDDA(49,136,49,167);
	lineDDA(41,131,42,130);
	lineDDA(42,130,34,124);
	lineDDA(34,124,24,120);
	lineDDA(24,120,14,119);
	lineDDA(14,119,22,122);
	lineDDA(22,122,29,125);
	lineDDA(29,125,41,131);
	lineDDA(46,129,50,128);
	lineDDA(50,128,50,124);
	lineDDA(50,124,44,116);
	lineDDA(44,116,32,96);
	lineDDA(32,96,26,87);
	lineDDA(26,87,18,78);
	lineDDA(18,78,29,95);
	lineDDA(29,95,41,119);
	lineDDA(41,119,43,127);
	lineDDA(43,127,46,129);
	// cay thu hai
	
	lineDDA(47,478,49,452);
	lineDDA(49,452,50,441);
	lineDDA(50,441,48,431);
	lineDDA(48,431,49,409);
	lineDDA(49,409,51,404);
	lineDDA(51,404,52,405);
	lineDDA(52,405,53,427);
	lineDDA(53,427,53,432);
	lineDDA(53,432,54,444);
	lineDDA(54,444,53,460);
	lineDDA(53,460,52,469);
	lineDDA(52,469,52,478);
	lineDDA(72,478,72,466);
	lineDDA(72,466,74,458);
	lineDDA(74,458,74,449);
	lineDDA(74,449,74,433);
	lineDDA(74,433,69,432);
	lineDDA(69,432,66,432);
	lineDDA(66,432,57,430);
	lineDDA(57,430,53,432);

	lineDDA(79,478,78,456);
	lineDDA(78,456,80,442);
	lineDDA(80,442,81,442);
	lineDDA(81,442,82,467);
	lineDDA(82,467,83,478);

	
	lineDDA(57,427,58,408);
	lineDDA(58,408,61,390);
	lineDDA(61,390,64,361);
	lineDDA(64,361,73,364);
	lineDDA(73,364,82,367);
	lineDDA(82,367,78,384);
	lineDDA(78,384,72,411);
	lineDDA(72,411,72,424);
	lineDDA(72,424,69,429);
	lineDDA(63,429,57,427);
	lineDDA(74,429,78,434);
	lineDDA(78,434,82,439);
	lineDDA(82,439,86,441);
	lineDDA(86,441,88,438);
	lineDDA(88,438,91,438);
	lineDDA(91,438,98,440);
	lineDDA(98,440,103,441);
	lineDDA(103,441,93,434);
	lineDDA(93,434,84,431);
	lineDDA(84,431,78,430);
	lineDDA(78,430,80,428);
	lineDDA(80,428,87,427);
	lineDDA(87,427,94,423);
	lineDDA(94,423,102,414);
	lineDDA(102,414,104,410);
	lineDDA(104,410,90,418);
	lineDDA(90,418,86,420);
	lineDDA(86,420,82,419);
	lineDDA(82,419,78,425);
	lineDDA(72,424,74,429);

	lineDDA(57,365,65,353);
	lineDDA(65,354,57,364);

	lineDDA(65,357,71,361);
	lineDDA(71,361,81,362);
	lineDDA(81,362,82,354);
	lineDDA(82,354,80,337);
	lineDDA(80,337,84,331);
	lineDDA(84,331,92,317);
	lineDDA(92,317,92,311);
	lineDDA(92,311,89,306);
	lineDDA(89,306,83,304);
	lineDDA(83,304,77,304);
	lineDDA(77,304,75,323);
	lineDDA(75,323,70,341);
	lineDDA(70,341,65,357);
	lineDDA(82,334,81,335);
	lineDDA(81,335,99,317);
	lineDDA(99,317,99,316);
	lineDDA(99,316,82,334);
	lineDDA(81,350,81,352);
	lineDDA(81,352,91,349);
	lineDDA(91,349,97,345);
	lineDDA(97,345,96,340);
	lineDDA(96,340,108,327);
	lineDDA(108,327,91,339);
	lineDDA(91,339,81,350);
	lineDDA(79,300,84,302);
	lineDDA(84,302,89,303);
	lineDDA(89,303,88,297);
	lineDDA(88,297,92,285);
	lineDDA(92,285,98,271);
	lineDDA(98,271,103,263);
	lineDDA(103,263,99,260);
	lineDDA(99,260,94,258);
	lineDDA(94,258,90,257);
	lineDDA(90,257,86,272);
	lineDDA(86,272,83,282);
	lineDDA(83,282,81,293);
	lineDDA(81,293,79,301);
	lineDDA(90,252,99,256);
	lineDDA(99,256,107,257);
	lineDDA(107,257,107,251);
	lineDDA(107,251,107,238);
	lineDDA(107,238,108,232);
	lineDDA(108,232,115,216);
	lineDDA(115,216,118,212);
	lineDDA(118,212,112,208);
	lineDDA(112,208,107,204);
	lineDDA(107,204,102,204);
	lineDDA(102,204,101,217);
	lineDDA(101,217,99,232);
	lineDDA(99,232,94,246);
	lineDDA(94,246,90,252);
	
	lineDDA(105,200,111,204);
	lineDDA(111,204,117,205);
	lineDDA(117,205,120,202);
	lineDDA(120,202,120,193);
	lineDDA(120,193,124,184);
	lineDDA(124,184,129,168);
	lineDDA(129,168,131,157);
	lineDDA(131,157,136,146);
	lineDDA(136,146,143,137);
	lineDDA(143,137,139,132);
	lineDDA(139,132,132,129);
	lineDDA(132,129,124,129);
	lineDDA(124,129,121,150);
	lineDDA(121,150,117,168);
	lineDDA(117,168,112,182);
	lineDDA(112,182,108,192);
	lineDDA(108,192,105,200);

	lineDDA(88,363,94,369);
	lineDDA(94,369,97,376);
	lineDDA(97,376,96,381);
	lineDDA(96,381,99,388);
	lineDDA(99,388,94,398);
	lineDDA(94,398,90,397);
	lineDDA(90,397,88,409);
	lineDDA(88,409,86,417);
	lineDDA(86,417,82,419);
	lineDDA(82,419,83,407);
	lineDDA(83,407,84,400);
	lineDDA(84,400,85,388);
	lineDDA(85,388,87,377);
	lineDDA(87,377,89,384);
	lineDDA(89,384,89,389);
	lineDDA(89,389,91,390);
	lineDDA(91,390,93,385);

	lineDDA(93,385,90,377);
	lineDDA(90,377,88,371);
	lineDDA(88,371,88,364);

	lineDDA(86,362,96,362);
	lineDDA(96,362,101,375);
	lineDDA(101,375,106,380);
	lineDDA(101,375,104,398);
	lineDDA(104,398,106,406);
	lineDDA(106,406,107,419);
	lineDDA(107,419,109,412);
	lineDDA(109,412,111,405);
	lineDDA(111,405,114,398);
	lineDDA(114,398,114,386);
	lineDDA(114,386,113,379);
	lineDDA(113,379,110,371);
	lineDDA(110,371,113,370);
	lineDDA(113,370,119,373);
	lineDDA(119,373,129,374);
	lineDDA(129,374,143,372);
	lineDDA(143,372,162,370);
	lineDDA(162,370,177,363);
	lineDDA(177,363,159,365);
	lineDDA(159,365,131,366);
	lineDDA(131,366,120,366);
	lineDDA(120,366,112,363);
	lineDDA(112,363,116,360);
	lineDDA(116,360,122,358);
	lineDDA(122,358,137,356);
	lineDDA(137,356,143,353);
	lineDDA(143,353,149,350);
	lineDDA(149,350,136,352);
	lineDDA(136,352,124,353);
	lineDDA(124,353,107,354);
	lineDDA(107,354,113,348);
	lineDDA(113,348,120,343);
	lineDDA(120,343,126,340);
	lineDDA(126,340,133,333);
	lineDDA(126,328,118,334);
	lineDDA(118,334,109,341);
	lineDDA(109,341,102,346);
	lineDDA(102,346,93,354);
	lineDDA(93,354,84,359);
	lineDDA(84,359,86,362);	
	lineDDA(117,378,120,388);
	lineDDA(120,388,126,395);
	lineDDA(126,395,135,402);
	lineDDA(135,402,144,408);
	lineDDA(144,408,141,401);
	lineDDA(141,401,134,393);
	lineDDA(134,393,126,383);
	lineDDA(126,383,117,378);
	
	lineDDA(104,341,113,323);
	lineDDA(113,323,104,342);
	lineDDA(104,342,114,323);
	lineDDA(114,323,105,341);
	lineDDA(105,341,114,324);
	
	lineDDA(107,308,137,278);
	lineDDA(137,278,107,308);
	lineDDA(107,308,138,279);
	lineDDA(138,279,108,307);
	lineDDA(108,307,139,279);
	lineDDA(139,279,107,309);
	
	lineDDA(156,266,178,248);
	lineDDA(178,248,157,266);
	lineDDA(157,266,179,249);
	lineDDA(179,249,158,266);
	lineDDA(158,266,180,250);
	lineDDA(96,301,100,283);
	lineDDA(100,283,104,263);
	lineDDA(104,263,101,283);
	lineDDA(101,283,96,301);
	lineDDA(96,301,102,283);
	lineDDA(102,283,105,263);
	lineDDA(106,263,102,283);
	lineDDA(102,283,96,301);

	lineDDA(127,269,133,250);
	lineDDA(133,250,134,254);
	lineDDA(134,254,128,268);
	
	lineDDA(135,241,138,234);
	lineDDA(138,234,136,241);
	lineDDA(136,241,139,234);
	lineDDA(140,221,143,210);
	lineDDA(143,210,141,220);

	lineDDA(112,238,118,230);
	lineDDA(118,230,125,251);
	lineDDA(125,251,133,210);
	lineDDA(133,210,140,192);
	lineDDA(140,192,144,185);
	lineDDA(144,185,144,186);
	lineDDA(144,186,134,209);
	lineDDA(134,209,126,221);
	lineDDA(126,221,119,230);
	lineDDA(119,230,113,238);
	lineDDA(89,236,90,228);
	lineDDA(90,228,92,219);
	lineDDA(92,219,96,205);
	lineDDA(96,205,93,218);
	lineDDA(93,218,91,227);
	lineDDA(91,227,90,236);
	
	lineDDA(104,178,106,170);
	lineDDA(106,170,110,160);
	lineDDA(110,160,116,148);
	lineDDA(116,148,119,143);
	lineDDA(119,143,119,146);
	lineDDA(119,146,116,150);
	lineDDA(116,150,111,160);
	lineDDA(111,160,108,170);
	lineDDA(108,170,105,178);

	lineDDA(115,170,112,160);
	lineDDA(112,160,112,145);
	lineDDA(112,145,113,151);
	lineDDA(113,151,113,160);
	lineDDA(113,160,116,171);
	lineDDA(122,110,126,101);
	lineDDA(126,101,130,95);
	lineDDA(130,95,136,87);
	lineDDA(136,87,137,88);
	lineDDA(137,88,131,95);
	lineDDA(131,95,127,102);
	lineDDA(127,102,123,109);
	
	lineDDA(122,134,117,138);
	lineDDA(117,138,111,142);
	lineDDA(111,142,102,139);
	lineDDA(102,139,96,134);
	lineDDA(96,134,89,131);
	lineDDA(89,131,101,134);
	lineDDA(101,134,110,134);
	lineDDA(110,134,118,131);
	lineDDA(118,131,111,127);
	lineDDA(111,127,111,115);
	lineDDA(111,115,112,115);
	lineDDA(112,115,112,108);
	lineDDA(112,108,115,100);
	lineDDA(115,100,117,108);
	lineDDA(117,108,119,113);
	lineDDA(119,113,118,121);
	lineDDA(118,121,117,124);
	lineDDA(117,124,120,128);
	lineDDA(120,128,123,131);
	lineDDA(123,131,122,134);

	lineDDA(108,129,107,125);
	lineDDA(107,125,105,124);
	lineDDA(105,124,102,120);
	lineDDA(102,120,97,113);
	lineDDA(97,113,91,110);
	lineDDA(91,110,85,109);
	lineDDA(85,109,56,102);
	lineDDA(56,102,88,119);
	lineDDA(88,119,97,120);
	lineDDA(97,120,105,124);

	lineDDA(108,124,101,111);
	lineDDA(101,111,97,105);
	lineDDA(97,105,95,100);
	lineDDA(95,100,91,87);
	lineDDA(91,87,90,60);
	lineDDA(90,60,95,78);
	lineDDA(95,78,99,86);
	lineDDA(99,86,100,93);
	lineDDA(100,93,103,108);
	lineDDA(103,108,108,123);
	lineDDA(106,106,111,101);
	lineDDA(111,101,113,96);
	lineDDA(113,96,113,88);
	lineDDA(113,88,111,86);
	lineDDA(111,86,107,94);
	lineDDA(107,94,106,106);
	lineDDA(114,78,118,67);
	lineDDA(118,67,115,82);

	lineDDA(94,53,100,69);
	lineDDA(100,69,106,76);
	lineDDA(106,76,111,86);
	lineDDA(111,86,116,90);
	lineDDA(116,90,126,99);
	lineDDA(126,99,129,89);
	lineDDA(129,89,132,80);
	lineDDA(132,80,132,57);
	lineDDA(132,57,128,37);
	lineDDA(128,37,125,52);
	lineDDA(125,52,124,67);
	lineDDA(124,67,126,84);
	lineDDA(126,84,124,97);
	lineDDA(124,97,122,91);
	lineDDA(122,91,113,79);
	lineDDA(113,79,94,53);

	
	lineDDA(102,198,98,195);
	lineDDA(98,195,92,193);
	lineDDA(92,193,86,194);
	lineDDA(86,194,91,191);
	lineDDA(91,191,74,191);
	lineDDA(74,191,66,194);
	lineDDA(66,194,73,186);
	lineDDA(73,186,79,183);
	lineDDA(79,183,86,185);
	lineDDA(86,185,94,189);
	lineDDA(94,189,95,193);
	lineDDA(101,198,99,191);
	lineDDA(99,191,95,179);
	lineDDA(95,179,94,165);
	lineDDA(94,165,92,141);
	lineDDA(92,141,98,157);
	lineDDA(98,157,101,168);
	lineDDA(101,168,103,180);
	lineDDA(103,180,105,189);
	lineDDA(105,189,101,198);
	
	lineDDA(107,251,109,252);
	lineDDA(109,252,112,248);
	lineDDA(112,248,116,245);
	lineDDA(116,245,122,242);
	lineDDA(122,242,149,243);
	lineDDA(149,243,138,247);
	lineDDA(138,247,127,249);
	lineDDA(127,249,112,258);
	lineDDA(112,258,119,261);
	lineDDA(119,261,124,267);
	lineDDA(124,267,129,285);
	lineDDA(129,285,116,270);
	lineDDA(116,270,106,258);
	
	lineDDA(141,275,145,263);
	lineDDA(145,263,151,249);
	lineDDA(151,249,159,239);
	lineDDA(159,239,172,227);
	lineDDA(172,227,162,242);
	lineDDA(162,242,158,255);
	lineDDA(158,255,155,266);
	lineDDA(155,266,153,270);
	lineDDA(153,270,147,273);
	lineDDA(147,273,148,277);
	lineDDA(148,277,156,277);
	lineDDA(156,277,171,279);
	lineDDA(171,279,189,286);
	lineDDA(189,286,168,286);
	lineDDA(168,286,151,284);
	lineDDA(151,284,143,278);
	lineDDA(178,248,184,239);
	lineDDA(184,239,190,229);
	lineDDA(190,229,199,220);
	lineDDA(199,220,218,193);
	lineDDA(218,193,211,212);
	lineDDA(211,212,199,237);
	lineDDA(199,237,195,240);
	lineDDA(195,240,202,240);
	lineDDA(202,240,211,242);
	lineDDA(211,242,220,245);
	lineDDA(220,245,228,254);
	lineDDA(228,254,244,268);
	lineDDA(244,268,220,254);
	lineDDA(220,254,209,247);
	lineDDA(209,247,198,246);
	lineDDA(198,246,206,250);
	lineDDA(206,250,217,258);
	lineDDA(217,258,236,275);
	lineDDA(236,275,244,284);
	lineDDA(244,284,228,274);
	lineDDA(228,274,209,264);
	lineDDA(209,264,194,254);
	lineDDA(194,254,187,249);
	lineDDA(187,249,180,250);
	
	lineDDA(120,231,129,233);
	lineDDA(129,233,136,232);
	lineDDA(136,232,147,229);
	lineDDA(147,229,156,225);
	lineDDA(156,225,162,217);
	lineDDA(162,217,172,203);
	lineDDA(172,203,160,213);
	lineDDA(160,213,150,218);
	lineDDA(150,218,140,222);
	lineDDA(140,222,129,227);
	lineDDA(129,227,120,231);
	
	lineDDA(123,220,121,214);
	lineDDA(121,214,126,197);
	lineDDA(126,197,130,188);
	lineDDA(130,188,136,176);
	lineDDA(136,176,142,164);
	lineDDA(142,164,150,159);
	lineDDA(150,159,140,170);
	lineDDA(140,170,137,180);
	lineDDA(137,180,135,193);
	lineDDA(135,193,133,203);
	lineDDA(133,203,129,212);
	lineDDA(129,212,123,220);
	
	lineDDA(144,185,149,184);
	lineDDA(149,184,154,181);
	lineDDA(154,181,158,186);
	lineDDA(158,186,162,191);
	lineDDA(162,191,170,195);
	lineDDA(170,195,177,198);
	lineDDA(177,198,187,201);
	lineDDA(187,201,198,204);
	lineDDA(198,204,189,196);
	lineDDA(189,196,177,189);
	lineDDA(177,189,168,184);
	lineDDA(168,184,160,178);
	lineDDA(160,178,156,178);
	lineDDA(156,178,150,181);
	lineDDA(150,181,147,183);
	lineDDA(147,183,144,185);	
}
bool  getMouseClickEvent(int &a, int &b)
{
	do{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, a, b);
			return true;
		}
	}while(true);
	return false;
}
bool checkPlay()
{
	int a,b;
	int xmax = getmaxx()/2;
	int ymax = getmaxy()/2;
	while(true){
	if(getMouseClickEvent(a,b) == true){
		for (int i = xmax - 75; i <= xmax + 75; i++)
			for(int j = ymax - 150; j <= ymax - 90; j++)
			{
				if(a == i && b == j)
					return true;
			}
		for (int i = xmax - 75; i <= xmax + 75; i++)
			for(int j = ymax + 90; j <= ymax + 150; j++)
			{
				if(a == i && b == j)
					return false;
			}
	}
	}
}
bool checkInputName()
{
	int a,b;
	int xmax = getmaxx()/2;
	int ymax = getmaxy()/2;
	while(true){
	if(getMouseClickEvent(a,b) == true){
		for (int i = xmax - 75; i <= xmax + 75; i++)
			for(int j = ymax + 90; j <= ymax + 150; j++)
			{
				if(a == i && b == j)
					return true;
			}
			for (int i = xmax - 75; i <= xmax + 75; i++)
			for(int j = ymax -30; j <= ymax +30; j++)
			{
				if(a == i && b == j)
					return false;
			}
	}
	}
}
void nameBG()
{
	setcolor(WHITE);
	button_Go();
	int x = getmaxx()/2;
	int	y = getmaxy()/2;
	outtextxy(x - 275,y-90,"Your Name: ");
	lineDDA(x - 95,y - 100,x + 95, y - 100);
	lineDDA(x + 95,y- 100,x + 95, y - 70);
	lineDDA(x + 95,y - 70,x - 95, y - 70);
	lineDDA(x - 95,y - 70,x - 95, y - 100);

}
void input_name()
{ 
	
	nameBG();
	int x = getmaxx()/2;
	int	y = getmaxy()/2;
	char str[2];
	int dem = 0;
	str[1] = 0;
	setcolor(4);
	delay(100);
	while(ch!=13 && dem < 10){
		do{
			ch = getch();
		}while(ch < 65 && ch > 90 || ch < 97 && ch > 132);
			str[0] = ch;
			strcat(_a,str);
			leng++;
			setcolor(WHITE);
			outtextxy(x - 90, y - 90,_a);
			if(leng == 15 || ch == 8 || ch > 7 && ch < 13 || ch > 13 && ch < 48 || ch > 57 && ch < 65 || ch > 90 && ch < 97 || ch > 122 &&  ch < 127)
			{
				outtextxy(x - 270, y - 50, "Only 15 charaters(a - z, A - Z, 0 - 9) please!");
				delay(300);
				_a[0] = 0;
				cleardevice();
				setcolor(WHITE);
				nameBG();
				leng = 0;
			}
			if(ch == 13 && leng < 15)
			{
				InputPoin_Name(_a);
				outtextxy(x-70, y- 50,"Succesful");
			}
	}
	
}
void loading()
{
	int x = 0;
	char *s = new char[5];
	while (x <= 100){
		cleardevice();
		setcolor (10);settextstyle(4,0,5);outtextxy (20,200,"Game Loading");
		sprintf (s,"%d",x);
		setcolor (4);
		outtextxy (470,200,strcat(s,"%"));
		if (x == 100)
			delay (500);
		delay (20);
		x++;
	}
}
bool checkDuckDie()
{
	int a,b;
	
		if(getMouseClickEvent(a,b) == true){
		for (int i = d.x - 60 ; i <= d.x + 90; i++)
			for(int j = d.y - 45 ; j <= d.y + 45; j++)
			{
				if(a == i && b == j)
				{
					
					return true;
				}
			}
		}
	
	return false;	
}
bool checkBack(){
	int a,b;
	int xmax = getmaxx();
	int ymax = getmaxy();
	while(true){
	if(getMouseClickEvent(a,b) == true){
		for (int i = xmax - 100; i <= xmax -25; i++)
			for(int j = ymax - 455; j <= ymax - 430; j++)
			{
				if(a == i && b == j)
					return true;
			}
	}
	}
	return false;
}
void run()
{
	initwindow(640,480);
	int a ,b;
	loading();
	cleardevice();
	//setcolor(15);
	bg();
	setcolor(15);
	settextstyle(1,0,1);
	button_Play_Quit();
	while(true){
	
	if(checkPlay() == true)
		{	
			cleardevice();
			input_name();

			if(checkInputName() == true)
			{
				cleardevice();
				animationDuck();
			}
			else
			{
				cleardevice();
				readPoint();
				xepHang();
				high_Score();
				if(checkBack() == true){
					cleardevice();
					animationDuck();
				}
			}
			
		}
	else
	{
		cleardevice();
		//closegraph();
	}
	}
}
int main()
{
	//initwindow(640,480);
	//Point_Player();
	run();
	getch();
	closegraph();
	return 0;
}
