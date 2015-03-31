#ifndef SORT_H
#define SORT_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"

using namespace std;

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

public:
	bool execute(vector <string> parsedInformation, vector <Task> list);
	vector<Task> getSortedList();
};

#endif