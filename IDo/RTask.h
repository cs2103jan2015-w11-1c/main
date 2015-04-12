//@author A0115545J
#ifndef RTASK_H
#define RTASK_H

#include <string>
#include <iostream>
#include "Task.h"
#include "Dates.h"
#include "Log.h"

enum Period {
	day, month, year
};

class RTask : public Task {
private:

	Log _log;
	//Stores task name, start time, end time;
	Task _abstract;	
	//Stores start date, end date, label, priority, status
	Task _occur;	

	//Variables
	double _noOfOccurrences;
	int _intervalBtwPeriod;
	int _limit;
	int sizeType;

	Period _period;
	Period _limitingPeriod;
	vector <Task> _listOfOccurrences;

	date startDate;
	date endDate;
	date nextStartDate;
	date nextEndDate;

public:
	RTask();
	~RTask();

	//Setter Function
	bool setAbstrInfo(vector <string>);
	bool setInterval(int);
	bool setPeriod(string);
	bool setFirstOccur(vector <string>);
	bool setLimitingPeriod(string);
	bool setLimit(string);
	bool setNoOfOccurrences(int);

	//Process Function
	void generateOccursForDeadlineTask();
	void generateOccursForTimedTask();

	//Getter Functions
	vector<Task> getListOfOccurrences();
};

#endif