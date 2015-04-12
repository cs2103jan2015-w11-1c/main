//@author A0115465H
#ifndef MARK_H
#define MARK_H

#include <string>
#include <vector>
#include <iostream>
#include "Log.h"
#include "Task.h"

using namespace std;

class Mark {
private:
	string _contentToMark;
	Log _log;
	
	void markStatus (Task &taskToMark);
	void markPriority (Task &taskToMark);
	void markLabel (Task &taskToMark);

public:
	bool isValidInput(vector <string>, int);
	void execute (vector<string> parsedInformation, vector<Task> &taskListFromLogic);
};

#endif
