#ifndef EDIT_H
#define EDIT_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"

using namespace std;

class Edit {
private:
	//Declaration of Objects
	Dates check;

	//Declaration of Variables
	vector<Task> _taskList;
	vector<string> _parsedInformation;

	string _editType;
	string _editContent;
	string _time;

	int _editNumber;
	int _numberOfTasks;
	int _parsedInfoSize;

	//Functions
	bool checkAndProcess();
	bool isPossibleTime(string time);
	bool isPossibleTimeFormat(string time);
	bool isTimeFormat(string time);
	string getTodayTime();
	bool compareDates(string date1, string date2);
	bool compareSameDates(string date1, string date2);
	void printMessage(string message);

public:
	bool execute(vector<string> parsedInformation, vector<Task> taskList);
	vector<Task> getList();
};

#endif