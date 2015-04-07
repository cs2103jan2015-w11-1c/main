#ifndef RTASK_H
#define RTASK_H

#include <string>
#include <iostream>
#include "Task.h"
#include "Dates.h"

enum Period {
	day, month, year
};

class RTask : public Task {
private:
	Task _abstract;	//task name, start time, end time
	Task _occur;	//start date, end date, label, prio, status
	double _noOfOccurrences;
	int _intervalBtwPeriod;
	int _limit;
	Period _period;
	Period _secPeriod;

	vector <Task> _listOfOccurrences;

public:
	RTask();
	~RTask();
	vector<Task> getListOfOccurrences();

	void setAbstrInfo(vector <string>);
	void setNoOfOccurrences(int);
	void setPeriod(string);
	void setPeriod2(string);
	void setInterval(int);
	void setLimit(string);

	void setFirstOccur(vector <string>);
	void stringToIntDate(string, int *day, int *month, int *yr);
	void generateOccurs();
	void generateOccursForTimedTask();

};

#endif