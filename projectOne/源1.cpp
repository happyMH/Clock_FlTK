//#define WIN32 1
//#include "Simple_window.h"    // get access to our window library
//#include "Graph.h"            // get access to our graphics library facilities
//#include <ctime>
//#include<cstdio>
//#include<iostream>
//#include<string.h>
//#include<stdlib.h>
//#include<time.h>
//#include<windows.h>
//#define pi 3.14159265
//
//using namespace std;
//using namespace Graph_lib;
////------------------------------------------------------------------------------
//
//void kedu(Lines &l);
//
//class clock
//{
//private:
//	int curr_hour;
//	int curr_minute;
//	int curr_second;
//	int lengths_hand[3];
//	Circle dial1;
//	Circle dial2;
//	Line lines_hand[3];
//	Point centerOfDial;
//	Text texts_time_numClock[3];
//	Text texts_time_dial[12];
//	Lines lines;
//private:
//	void number_scale(Simple_window & win);
//	void lines_scale(Simple_window & win);
//	void all_scale(Simple_window & win);
//	void dial(Simple_window & win);
//	void run(Simple_window & win);
//public:
//	clock();
//	~clock() {}
//	void display();
//};
//
//int main()
//{
//	SYSTEMTIME t;
//
//	Point tl(100, 100);   //边界
//	Simple_window win(tl, 1000, 600, "Clock");    //界面
//
//	Point center(150, 200);
//	Circle c(center, 100);//圆形钟表界面
//	Circle d(center, 110);
//	d.set_color(Color::black);
//	c.set_color(Color::black);
//	win.attach(c);
//	win.attach(d);
//
//	Lines l;                                    //刻度线
//	kedu(l);
//	l.set_color(Color::black);
//	win.attach(l);
//
//	Text texts[12];                        // 刻度数
//	int x, y;
//	for (int i = 0; i < 12; ++i)
//	{
//		x = 80 * sin((i / 12.0) * 2 * pi) + 144;                  // 设立texts[i] 的位置
//		y = -80 * cos((i / 12.0) * 2 * pi) + 206;
//		Point p(x, y);
//		texts[i].set_place(p);
//
//		string s = "";                                 // 生成texts[i]的内容
//		if (i == 0)
//		{
//			s.push_back('1');
//			s.push_back('2');
//		}
//
//		if (i < 10 && i > 0)
//			s.push_back(i + '0');
//
//		if (i >= 10)
//		{
//			s.push_back('1');
//			s.push_back(i - 10 + '0');
//		}
//
//		texts[i].set_label(s);            // 设置font_size和label
//		texts[i].set_font_size(16);
//		win.attach(texts[i]);
//	}
//
//	Point tmp;
//	GetLocalTime(&t);
//	int curr_second = t.wSecond;
//	int curr_minute = t.wMinute;
//	int curr_hour = t.wHour;
//	int last_second = curr_second;
//
//	Text texts_time[3];                      // texts_time[0] -> 小时    texts_time[1]-> 分钟    texts_time[2]->秒
//	for (int i = 0; i < 3; ++i)
//	{
//		texts_time[i].set_place(Point(400 + 80 * i, 200));
//		texts_time[i].set_font_size(36);
//		win.attach(texts_time[i]);
//	}
//
//	int lengths_hand[3] = { 45,65,80 };     // 时针，分针，秒针 的长度
//
//	while (1)
//	{
//
//		GetLocalTime(&t);
//		curr_second = t.wSecond;
//		curr_minute = t.wMinute;
//		curr_hour = t.wHour;
//
//		Line lines_hand[3];                                // 时针、分针、秒针 的设定
//		for (int i = 0; i < 3; ++i)
//		{
//			if (i < 2)
//			{
//				lines_hand[i].set_style(Line_style(Line_style::solid, 4 - i * 2));
//				lines_hand[i].set_color(Color::black);
//			}
//			else
//			{
//				lines_hand[i].set_style(Line_style(Line_style::solid, 1));
//				lines_hand[i].set_color(Color::red);
//			}
//			win.attach(lines_hand[i]);
//		}
//
//		// 表针的移动
//		x = lengths_hand[0] * sin(((((curr_hour - 12) * 3600 + curr_minute * 60 + curr_second) / (12 * 3600.0)) * 2 * pi)) + 150;
//		y = -lengths_hand[0] * cos((((curr_hour * 3600 + curr_minute * 60 + curr_second) / (12 * 3600.0)) * 2 * pi)) + 200;
//		tmp.x = x; tmp.y = y;
//		lines_hand[0].set_place(center, tmp);
//
//
//		x = lengths_hand[1] * sin(((curr_minute * 60 + curr_second) / 3600.0)* pi * 2) + 150;
//		y = -lengths_hand[1] * cos(((curr_minute * 60 + curr_second) / 3600.0) * pi * 2) + 200;
//		tmp.x = x; tmp.y = y;
//		lines_hand[1].set_place(center, tmp);
//
//
//		x = lengths_hand[2] * sin(curr_second / 60.0 * 2 * pi) + 150;
//		y = -lengths_hand[2] * cos(curr_second / 60.0 * 2 * pi) + 200;
//		tmp.x = x; tmp.y = y;
//		lines_hand[2].set_place(center, tmp);
//
//
//		string h = "    :";
//		h[0] = (curr_hour / 10) + '0';
//		h[1] = (curr_hour % 10) + '0';
//		texts_time[0].set_label(h);
//
//
//		string m = "    :";
//		m[0] = (curr_minute / 10) + '0';
//		m[1] = (curr_minute % 10) + '0';
//		texts_time[1].set_label(m);
//
//
//		string s = "  ";
//		s[0] = (curr_second / 10) + '0';
//		s[1] = (curr_second % 10) + '0';
//		texts_time[2].set_label(s);
//
//
//		Fl::wait();
//		Fl::redraw();
//
//		last_second = curr_second;                       // 直到下一秒再开始移动
//		while (1)
//		{
//			GetLocalTime(&t);
//			curr_second = t.wSecond;
//			curr_minute = t.wMinute;
//			curr_hour = t.wHour;
//			if (last_second != curr_second)
//				break;
//		}
//	}
//}
