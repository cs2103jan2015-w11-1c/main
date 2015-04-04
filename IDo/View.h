#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <Windows.h>
#include "Logic.h"
#include "Task.h"
#include "Dates.h"

using namespace std;

class View {
private:
	Task _task;
	Dates date;
	void printMessage(string);
	void printHeader();
	void printTimedTaskHeader();
	string center(string heading, const int w);
	void display(Task task);
	void displayWithoutDates(Task task);
	void SetColor(int value);

public:
	void viewAll(vector <Task> &list);
	void viewDoneTasks(vector <Task> &list);
	void viewNotDoneTasks(vector <Task> &list);
	void viewSelected(vector<Task>, vector<int>);
	void viewSelected2(vector<Task>, int);
	void viewDefault(vector<Task> &list);
};

#endif