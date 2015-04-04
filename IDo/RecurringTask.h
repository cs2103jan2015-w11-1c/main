#ifndef RECURRINGTASK_H
#define RECURRINGTASK_H

#include <string>
#include <iostream>
#include "Task.h"

enum Period {
	hour, day, week, month, year
};

//Abstraction class contains all the info that is common to all members of
//a set of occurrences
class AbstractRTask {
private:
	string _taskName;
	int _intervalBtwPeriod;
	Period _period;
	string _lastDate;

public:
	AbstractRTask();
	~AbstractRTask();
	
	string getTaskName();
	string getLastDate();
	int getIntervalBtwPeriod();
	Period getPeriod();

	void setLastDate(string date);
	void setTaskName(string name);
	void setInterval(int number);
	void setPeriod(string period);
};

class RTask : public AbstractRTask {
private:
	string _startDate;
	string _startTime;
	string _endDate;
	string _endTime;
	Status _status;
	Priority _priority;
	string _label;
	RTask *_nextOccurrence;

public:
	RTask();
	~RTask();
	string getStartDate();
	string getStartTime();
	string getEndDate();
	string getEndTime();
	Status getStatus();
	Priority getPriority();
	string getLabel();
	RTask getNextOccurrence();

	void setAbstrInfo(vector <string>);
	void setStartDate(string date);
	void setStartTime(string time);
	void setEndDate(string date);
	void setEndTime(string time);
	void setStatus(Status status);
	void setLabel(string label);
	void setPriority(Priority priority);
	void setNextOccurrence(vector <string>);
};

#endif