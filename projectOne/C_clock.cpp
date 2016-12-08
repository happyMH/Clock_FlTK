#include "C_clock.h"

void Clock::number_scale()
{
	int x, y;
	for (int i = 0; i < 12; ++i)
	{
		x = 80 * sin((i / 12.0) * 2 * pi) + 144;                  // 设立texts[i] 的位置
		y = -80 * cos((i / 12.0) * 2 * pi) + 206;
		Point p(x, y);
		texts_time_dial[i].set_place(p);

		string s = "";                                 // 生成texts[i]的内容
		if (i == 0)
		{
			s.push_back('1');
			s.push_back('2');
		}

		if (i < 10 && i > 0)
			s.push_back(i + '0');

		if (i >= 10)
		{
			s.push_back('1');
			s.push_back(i - 10 + '0');
		}
		texts_time_dial[i].set_label(s);
	}

}

void Clock::lines_scale()
{
	int x, y, length;
	Point end_point;
	Point start_point;
	for (int i = 0; i < 60; ++i)
	{
		x = 100 * sin((i / 60.0) * 2 * pi) + 150;
		y = -100 * cos((i / 60.0) * 2 * pi) + 200;
		end_point.x = x;
		end_point.y = y;

		if (i % 5 == 0)
			length = 85;
		else
			length = 95;

		x = length * sin((i / 60.0) * 2 * pi) + 150;
		y = -length * cos((i / 60.0) * 2 * pi) + 200;
		start_point.x = x;
		start_point.y = y;

		lines.add(start_point, end_point);
	}
}

void Clock::all_scale()
{
	number_scale();
	lines_scale();
}

void Clock::dial()
{
	dial1.set_radius(110);
	dial1.set_center(centerOfDial);

	dial2.set_radius(100);
	dial2.set_center(centerOfDial);
}

void Clock::num_dial()
{
	dial3.set_rec(Point(380, 150), Point(620, 220));
	dial3.set_color(Color::blue);
}

void Clock::run()
{	
	Simple_window win(Point(100, 100), 900, 600, "Clock");
	win.attach(dial1);
	win.attach(dial2);
	win.attach(dial3);
	win.attach(lines);
	for (int i = 0; i < 12; ++i)
		win.attach(texts_time_dial[i]);


	Point tmp;
	int x,y,last_second;

	Text texts_time_numClock[3];	
	for (int i = 0; i < 3; ++i)
	{
		texts_time_numClock[i].set_place(Point(400 + 80 * i, 200));
		texts_time_numClock[i].set_font_size(36);
		win.attach(texts_time_numClock[i]);
	}

	while (1)
	{
		Line lines_hand[3];
		for (int i = 0; i < 3; ++i)
		{
			if (i < 2)
			{
				lines_hand[i].set_style(Line_style(Line_style::solid, 4 - i * 2));
				lines_hand[i].set_color(Color::black);
			}
			else
			{
				lines_hand[i].set_style(Line_style(Line_style::solid, 1));
				lines_hand[i].set_color(Color::red);
			}
			win.attach(lines_hand[i]);
		}

		// 表针的移动
		x = lengths_hand[0] * sin(((((curr_hour - 12) * 3600 + curr_minute * 60 + curr_second) / (12 * 3600.0)) * 2 * pi)) + 150;
		y = -lengths_hand[0] * cos((((curr_hour * 3600 + curr_minute * 60 + curr_second) / (12 * 3600.0)) * 2 * pi)) + 200;
		tmp.x = x; tmp.y = y;
		lines_hand[0].set_place(centerOfDial, tmp);

		x = lengths_hand[1] * sin(((curr_minute * 60 + curr_second) / 3600.0)* pi * 2) + 150;
		y = -lengths_hand[1] * cos(((curr_minute * 60 + curr_second) / 3600.0) * pi * 2) + 200;
		tmp.x = x; tmp.y = y;
		lines_hand[1].set_place(centerOfDial, tmp);

		x = lengths_hand[2] * sin(curr_second / 60.0 * 2 * pi) + 150;
		y = -lengths_hand[2] * cos(curr_second / 60.0 * 2 * pi) + 200;
		tmp.x = x; tmp.y = y;
		lines_hand[2].set_place(centerOfDial, tmp);

		string h = "    :";
		h[0] = (curr_hour / 10) + '0';
		h[1] = (curr_hour % 10) + '0';
		texts_time_numClock[0].set_label(h);

		string m = "    :";
		m[0] = (curr_minute / 10) + '0';
		m[1] = (curr_minute % 10) + '0';
		texts_time_numClock[1].set_label(m);

		string s = "  ";
		s[0] = (curr_second / 10) + '0';
		s[1] = (curr_second % 10) + '0';
		texts_time_numClock[2].set_label(s);

		Fl::wait();
		Fl::redraw();

		last_second = curr_second;                       // 直到下一秒再开始移动
		while (1)
		{
			SYSTEMTIME t;
			GetLocalTime(&t);
			curr_second = t.wSecond;
			curr_minute = t.wMinute;
			curr_hour = t.wHour;
			if (last_second != curr_second)
				break;
		}
	}
}

Clock::Clock()
{
	SYSTEMTIME t;  
	GetLocalTime(&t);
	curr_second = t.wSecond;
	curr_minute = t.wMinute;
	curr_hour = t.wHour;

	centerOfDial.x = 150;
	centerOfDial.y = 200;

	lengths_hand[0] = 45;
	lengths_hand[1] = 65;
	lengths_hand[2] = 80;
}

void Clock::display()
{
	dial();
	num_dial();
	all_scale();
	run();
}
