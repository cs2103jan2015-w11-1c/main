#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <assert.h>

#include "Parser.h"
#include "Add.h"
#include "Delete.h"
#include "Task.h"
#include "Edit.h"
#include "Mark.h"
#include "View.h"
#include "Storage.h"
#include "Sort.h"
#include "Search.h"
#include "RecurringTask.h"

using namespace std;

union AllTasks {
	int type;	//1 = rtask. 2 = nrtask
	RTask rtask;
	Task task;
};

class Logic {
private:
	Storage storage;

	string commandChoice;
	vector<string> parsedInformation;
	string userInput;
	vector<AllTasks> _listOfTasks;
	void updateStorage ();
	void getParsedInformation(string);
	void printMessage(string message);
	void addTask();
	void deleteTask();
	void editTask();
	void markTask();
	void viewCommands();
	void viewDecider();
	void storeChange();
	void sortTask();
	void searchWord();

public:
	void readFromFile();
	bool process(string);
	vector<AllTasks> getListofTasks();
	vector<AllTasks> setListOfTasks(vector<AllTasks> newList);
};

#endif