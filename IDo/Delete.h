#ifndef DELETE_H
#define DELETE_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Task.h"

using namespace std;

class Delete{
private:
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