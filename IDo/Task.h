#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <iostream>
#include "UserInterface.h"
#include "Parser.h"
#include "Logic.h"
#include "Storage.h"

using namespace std;

enum Status {
	done, notdone
};

enum Priority {
	high, medium, low, none
};

enum Label {
	studies, cca, friends, family, misc
};

class Task {
private:
	string _taskName;
	string _startDate;
	string _startTime;
	string _endDate;
	string _endTime;
	string _deadline;
	Status _status;
	Priority _priority;
	Label _label;
	string _extra;

public:
	Task();
	~Task();
	string getTaskName();
	string getStartDate();
	string getStartTime();
	string getEndDate();
	string getEndTime();
	string getDeadline();
	Status getStatus();
	Priority getPriority();
	Label getLabel();
	string getExtra();
	void setTaskName(string name);
	void setStartDate(string date);
	void setStartTime(string time);
	void setEndDate(string date);
	void setEndTime(string time);
	void setDeadline(string date);
	void setStatus(Status state);
	void setPriority(Priority priority);
	void setLabel(Label label);
	void setExtra(string extra);
};

#endif