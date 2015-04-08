#ifndef EDIT_H
#define EDIT_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"

using namespace std;

class Edit {
private:
	vector<Task> _taskList;
	vector<string> _parsedInformation;
	int _editNumber;
	string _editType;
	string _editContent;
	int _numberOfTasks;
	int _parsedInfoSize;

public:
	bool execute(vector<string> parsedInformation, vector<Task> taskList);
	bool checkAndProcess();
	vector<Task> getList();
};

#endif