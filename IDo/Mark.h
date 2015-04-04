#ifndef MARK_H
#define MARK_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"
#include "RecurringTask.h"

using namespace std;

class Mark {
private:
	int _indexToMark;
	string _contentToMark;
	void markStatus (AllTasks &taskToMark);
	void markPriority (AllTasks &taskToMark);
	void markLabel (AllTasks &taskToMark);

public:
	bool isValidInput(vector <string>, int);
	void execute (vector<string> parsedInformation, vector<AllTasks> &taskListFromLogic);
};

#endif
