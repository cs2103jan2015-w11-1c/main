//@author A0115465H
#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum Status {
	done, notdone
};

enum Priority {
	high, medium, low, none
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
	string _label;
	int _recurringIndex;

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
	string getLabel();
	int getRecurringIndex();
	void setTaskName(string name);
	void setStartDate(string date);
	void setStartTime(string time);
	void setEndDate(string date);
	void setEndTime(string time);
	void setDeadline(string date);
	void setStatus(Status state);
	void setPriority(Priority priority);
	void setLabel(string label);
	void setRecurringIndex(int index);
};

#endif