#ifndef DELETE_H
#define DELETE_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"

using namespace std;

class Delete{
private:

public:
	bool isValidInput(vector <string> parsedInformation, int taskListSize);
	void execute(vector<string> parsedInformation, vector<Task> &taskList);
};

#endif