#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <iostream>
#include "UserInterface.h"
#include "Parser.h"
#include "Logic.h"

using namespace std;

class Task {
private:
	string _taskName;
	string _startDate;
	string _startTime;
	string _endDate;
	string _endTime;
	string _deadline;

public:
	string getTaskName();
	string getStartDate();
	string getStartTime();
	string getEndDate();
	string getEndTime();
	string getDeadline();
	void setTaskName (string name);
	void setStartDate (string date);
	void setStartTime (string time);
	void setEndDate (string date);
	void setEndTime (string time);
	void setDeadline (string date);
};

#endif