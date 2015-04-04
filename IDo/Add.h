#ifndef ADD_H
#define ADD_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"
#include "RecurringTask.h"

using namespace std;

template <class T>
class Add {
private:
	T _task;

public:
	T getTask();
	bool execute(vector<string> parsedInformation);	//for adding nrtask
	bool executeR(vector<string>);
};
#endif