#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "UserInterface.h"
#include "Logic.h"
#include "Parser.h"
#include "Task.h"

using namespace std;

class Task;

class Storage {
private:
	string storageFileName;
	int numberOfItems;

public:
	Storage();
	int getNumberOfItems();
	string getStorageFileName ();
	void editStorageFileName (string name);
	void updateFile (vector <Task> &temp);
//	void readFromFile ();
};

#endif