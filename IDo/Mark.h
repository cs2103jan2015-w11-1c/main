#ifndef MARK_H
#define MARK_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"

using namespace std;

class Mark {
private:
	int _indexToMark;
	string _contentToMark;

public:
	bool isValidInput(int, int);
	vector<Task> execute (vector<string> parsedInformation, vector<Task> taskListFromLogic);
	Task markStatus (Task);
	Task markPriority (Task);
	Task markLabel (Task);
	void setTypeToMark(string);
	void setContentToMark(string);
};

#endif
