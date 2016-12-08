#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include <ctime>
#include<iostream>
#include<string.h>
#include<time.h>
#include<windows.h>
#define pi 3.14159265

using namespace std;
using namespace Graph_lib;
//------------------------------------------------------------------------------


class Clock : public Shape
{
private:
	int curr_hour;
	int curr_minute;
	int curr_second;
	int lengths_hand[3];
	Circle dial1;
	Circle dial2;
	Graph_lib::Rectangle dial3;
	Point centerOfDial;
	Text texts_time_dial[12];
	Lines lines;

	friend Simple_window;
private:
	void number_scale();
	void lines_scale();
	void all_scale();
	void dial();
	void num_dial(); 
	void run();
public:
	Clock();
	~Clock() {}
	void display();

};