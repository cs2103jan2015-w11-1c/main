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

using namespace std;

class Logic {
private:
	Storage _storage;
	Dates _dates;

	string _commandChoice;
	vector<string> _parsedInformation;
	string _userInput;
	vector<Task> _listOfTasks;
	
	void updateStorage();
	void undo();
	void backup();
	void getParsedInformation(string);
	void printMessage(string message);
	void addTask();
	int searchNextRecurringIndex();
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
	vector<Task> getListofTasks();
};

#endif