#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <Windows.h>
#include "Task.h"
#include "Dates.h"
#include "Sort.h"

using namespace std;

class View {
private:
	Task _task;
	Dates _date;
	string _todayDate;

	void printMessage(string);
	void displayToday(vector <Task> &, int, string);
	void printTimedTaskHeader();
	void displayTimedTask(Task task);
	void displayDeadline(vector <Task> &, int, string);
	void printDeadlineTaskHeader();
	void displayDeadlineTask(Task task);
	void displayFloating (vector <Task> &, int);
	void printFloatingTaskHeader();
	void displayFloatingTask(Task task);
	void SetColor(int value);

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
