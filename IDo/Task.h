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

enum Status{
	DONE, NOTDONE
};

enum Priority{
	HIGH, MEDIUM, LOW, NONE
};

enum Label {
	STUDIES, CCA, FRIENDS, FAMILY, MISC
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
	void setTaskName (string name);
	void setStartDate (string date);
	void setStartTime (string time);
	void setEndDate (string date);
	void setEndTime (string time);
	void setDeadline (string date);
	void setStatus (Status state);
	void setPriority(Priority priority);
	void setLabel (Label label);
};

#endif