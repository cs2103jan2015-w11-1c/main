#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Logic.h"
#include "Task.h"

using namespace std;

class View {
private:
	Task _task;
	void printMessage();
	void printHeader();
	string center(string heading, const int w);
	void display(Task task);
	void SetColor(int value);

public:
	void viewAll(vector <Task> list);
	void viewDoneTasks(vector <Task> list);
	void viewNotDoneTasks(vector <Task> list);
};

#endif