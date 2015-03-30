#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class Task;

class Storage {
private:
	string storageFileName;

public:
	Storage();
	string getStorageFileName ();
	void editStorageFileName (string name);
	void updateFile (vector <Task> &temp);
	void readFile (vector <Task> &temp);
};

#endif