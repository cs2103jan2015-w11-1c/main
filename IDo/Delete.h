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
		int _taskIndex;
		vector<Task> newList;

	public:
		
		Delete();
		~Delete();
		bool execute(vector<string> parsedInformation, vector<Task> taskList);
		void getTaskIndexToBeDeleted(vector<string> parsedInformation);
		void findAndDeleteTask(vector<Task> listOfTasks);

		vector<Task> getNewList();
};

#endif