#ifndef ADD_H
#define ADD_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"
#include "RTask.h"

using namespace std;

class Add {
private:
	Task _task;

public:
	Task getTask();
	bool isRecurring(vector <string>);
	bool execute(vector<string> parsedInformation);	//for adding nrtask
};
#endif