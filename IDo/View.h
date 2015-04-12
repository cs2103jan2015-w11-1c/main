//@author A0115465H
#ifndef VIEW_H
#define VIEW_H

const int blue = 1;
const int green = 2;
const int cyan = 3;
const int red = 4;
const int purple = 5;
const int darkYellow = 6;
const int defaultWhite = 7;
const int grey = 8;
const int brightBlue = 9;
const int brightGreen = 10;
const int brightCyan = 11;
const int brightRed = 12;
const int pink = 13;
const int yellow = 14;
const int brightWhite = 15;


#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <Windows.h>
#include "Dates.h"
#include "Sort.h"
#include "Parser.h"
#include "Task.h"
#include "Log.h"

using namespace std;

class View {
private:
	Task _task;
	Dates _date;
	string _todayDate;
	Log _log;

	void printMessage(string);
	void displayToday(vector <Task> &, int, string);
	void printTimedTaskHeader();
	void displayTimedTask(int, Task);
	void displayDeadline(vector <Task> &, int, string);
	void printDeadlineTaskHeader();
	void displayDeadlineTask(int, Task);
	void displayFloating(vector <Task> &, int);
	void printFloatingTaskHeader();
	void displayFloatingTask(int, Task);
	void SetColor(int value);
	void printIndex(int);
	void printStart(Task);
	void printDeadline(Task);
	void printStatus(Task, bool);
	void printLabel(Task);
	void printPriority(Task);

	void printHeader();
	void display(Task task);

public:
	View();
	void viewSelectedFew(vector<Task>, vector<int>);
	void viewSelectedOne(vector<Task>, int);
	void viewDefault(vector<Task> &list, string);
	
	void viewAll(vector <Task> &list);
	void viewDoneTasks(vector <Task> &list);
	void viewNotDoneTasks(vector <Task> &list);
	void viewPriority(vector <Task> &list, string priority);
};

#endif
