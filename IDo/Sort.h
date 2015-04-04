#ifndef SORT_H
#define SORT_H

#include <string>
#include <vector>
#include <iostream>
#include "Task.h"
#include "boost/date_time/gregorian/gregorian.hpp" 

using namespace std;
using namespace boost::gregorian;

class Sort {
private:
	Task _task;
	string _sortChoice;
	vector<Task> sortList;

	enum SortChoice{
		FROM, TO, BY, DEADLINE, DONE, NOTDONE, PRIORITY, TASKNAME, INVALID
	};

	SortChoice sortWhat();
	
	bool sortFrom();
	bool sortTaskName();
	bool sortStartTime();
	bool sortToBy();
	bool sortEndTime();
	bool sortDeadLine();

	bool swap(int current, int next);

public:
	bool execute(vector <string> parsedInformation, vector <Task> list);
	vector<Task> getSortedList();
};

#endif