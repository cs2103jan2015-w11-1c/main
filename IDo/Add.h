//@author A0115545J
#ifndef ADD_H
#define ADD_H

#include <string>
#include <vector>
#include <iostream>
#include "Task.h"
#include "RTask.h"
#include "Log.h"

using namespace std;

class Add {
private:

	//Declaration of objects
	Task _task;
	Log _log;
	RTask rtask;

	//Declaration of variables
	vector <Task> _listOfOccurrences;

public:

	//Process Functions
	bool isRecurring(vector <string>);
	bool execute(vector<string> parsedInformation);	

	//Getter Functions
	vector<Task> getOccurrences();
	Task getTask();
};
#endif