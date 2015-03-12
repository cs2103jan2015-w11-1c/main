#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>
#include <iostream>
#include "UserInterface.h"
#include "Parser.h"
#include "Task.h"
#include "Storage.h"

using namespace std;

class Logic {
private:
	vector<Task> _listOfTasks;

public:
	void add (string inputLine);
	string display();
	string del (int numberToDelete);
	string edit (string inputLine);
	void updateStorage ();
};

#endif