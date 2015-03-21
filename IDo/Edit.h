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
		vector<Task> taskList;
		vector<string> parsedInformation;
		int editNumber;
		string editType;
		string editContent;

		int numberOfTasks;
		int parsedInfoSize;

	public:
		
		Edit();
		~Edit();
		Task _task;
		Task getTask();
		bool execute(vector<string> parsedInformation, vector<Task> taskList);
		bool checkAndProcess();
		vector<Task> getNewList();
};

#endif