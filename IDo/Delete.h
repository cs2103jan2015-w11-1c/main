//@author A0115465H
#ifndef DELETE_H
#define DELETE_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Log.h"
#include "Task.h"

using namespace std;

class Delete{
private:
	Log _log;
	vector <string> parsedInfo;
	vector <int> taskIndexToDelete;
	vector <int> recurringToDelete;

	void deleteRecurring (vector <Task> taskList);
	void getRecurringIndexToDelete (vector <Task> taskList);
	void checkRecurringToDelete (vector <Task> taskList);
	void getRecurringToDelete (vector <Task> taskList);

public:
	bool isValidInput(vector <string> parsedInformation, int taskListSize);
	void execute(vector<Task> &taskList);
};

#endif