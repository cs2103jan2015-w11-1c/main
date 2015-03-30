#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <assert.h>

#include "Parser.h"
#include "Add.h"
#include "Delete.h"
#include "Task.h"
#include "Edit.h"
#include "Mark.h"
#include "View.h"
#include "Storage.h"

using namespace std;

class Logic {
private:
	Storage storage;

	string commandChoice;
	vector<string> parsedInformation;
	string userInput;
	vector<Task> _listOfTasks;
	void updateStorage ();
	void getParsedInformation(string);
	void printMessage(string message);
	void addTask();
	void deleteTask();
	void editTask();
	void markTask();
	void viewCommands();
	void viewDecider();
	void storeChange(string directory);
	void exitProgram();

public:
	bool process(string);
	vector<Task> getListofTasks();
	vector<Task> setListOfTasks(vector<Task> newList);
};

#endif