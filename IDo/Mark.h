#ifndef MARK_H
#define MARK_H

#include <string>
#include <vector>
#include <iostream>
#include "Task.h"

using namespace std;

class Mark {
private:
	string _contentToMark;
	
	void markStatus (Task &taskToMark);
	void markPriority (Task &taskToMark);
	void markLabel (Task &taskToMark);

public:
	bool isValidInput(vector <string>, int);
	void execute (vector<string> parsedInformation, vector<Task> &taskListFromLogic);
};

#endif
