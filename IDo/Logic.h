#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>
#include <iostream>
#include "UserInterface.h"
#include "Parser.h"
#include "Add.h"
#include "Delete.h"
#include "Task.h"
#include "UserInterface.h"
#include "Parser.h"
#include "Edit.h"
#include <iomanip>

using namespace std;

class Logic {
private:

	Task task;
	vector<Task> _listOfTasks;
	vector<string> parsedInformation;
	string userInput;
	string commandChoice;

public:

	void getParsedInformation(string);
	bool process(string);
	string display();	

	void printMessage(string message);
	void printMessage2(string message);
	void updateStorage ();

	Task getTask();
	vector<Task> getListofTasks();
	vector<Task> setListOfTasks(vector<Task> newList);
};

#endif