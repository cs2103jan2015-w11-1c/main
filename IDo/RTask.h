#ifndef RECURRINGTASK_H
#define RECURRINGTASK_H

#include <string>
#include <iostream>
#include "Task.h"

enum Period {
	day, month, year
};

class RTask : public Task {
private:
	Task _abstract;	//task name, start time, end time
	Task _occur;	//start date, end date, label, prio, status
	int _noOfOccurrences;
	Period _period;
	int _intervalBtwPeriod;
	Period _totPeriod;

	vector <Task> _listOfOccurrences;

public:
	RTask();
	~RTask();
	void setAbstrInfo(vector <string>);
	void setNoOfOccurrences(int);
	void setPeriod(Period);
	void setTotPeriod(Period);
	void setInterval(int);
	void setFirstOccur(vector <string>);
	void stringToIntDate(string, int *day, int *month, int *yr);
	void generateOccurs();
};

#endif