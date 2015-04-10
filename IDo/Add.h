#ifndef ADD_H
#define ADD_H

#include <string>
#include <vector>
#include <iostream>
#include "Task.h"
#include "RTask.h"

using namespace std;

class Add {
private:
	Task _task;
	vector <Task> _listOfOccurrences;

public:
	Task getTask();
	vector<Task> getOccurrences();
	bool isRecurring(vector <string>);
	bool execute(vector<string> parsedInformation);	//for adding nrtask
};
#endif