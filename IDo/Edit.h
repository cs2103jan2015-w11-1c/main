#ifndef EDIT_H
#define EDIT_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"
#include "Log.h"

using namespace std;

class Edit {
private:
	//Declaration of Objects
	Dates check;
	Log log;

	//Declaration of Variables
	vector<Task> _taskList;
	vector<string> _parsedInformation;

	string _editType;
	string _editContent;
	string _time;

	int _editNumber;
	int _numberOfTasks;
	int _parsedInfoSize;

	string _startDate;
	string _endDate;
	string _startTime;
	string _endTime;

	//Functions to set the change
	bool checkAndProcess();
	bool setStartDate(string, int);
	bool setEndDate(string, int);
	bool setStartTime(string, int);
	bool setEndTime(string, int);

	//Functions to check time and dates
	bool isPossibleTimeFormat(string);
	string getTodayTime();
	bool compareDates(string, string);
	bool compareTime(string, string, string, string);

	void getSelectedTaskInfo(int index);
	void printMessage(string);

public:
	bool execute(vector<string> parsedInformation, vector<Task> taskList);
	vector<Task> getList();
};

#endif