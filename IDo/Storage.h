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
	string _storageFileName;
	static const string BACKUP;

public:
	Storage();
	string getStorageFileName ();
	void editStorageFileName (string name);
	void updateFile (vector <Task> &temp, bool isUndoTrue);
	void readFile (vector <Task> &temp, bool isUndoTrue);
};

#endif