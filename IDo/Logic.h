#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Parser.h"
#include "Add.h"
#include "Delete.h"
#include "Task.h"
#include "Parser.h"
#include "Edit.h"

using namespace std;

class Logic {
private:

	string commandChoice;
	vector<string> parsedInformation;
	string userInput;
	vector<Task> _listOfTasks;

public:

	bool process(string);
	void getParsedInformation(string);
	void updateStorage ();
	void printMessage(string message);
	void printMessage2(string message);
	string display();
	void markStatus();
	vector<Task> getListofTasks();
	vector<Task> setListOfTasks(vector<Task> newList);
};

#endif