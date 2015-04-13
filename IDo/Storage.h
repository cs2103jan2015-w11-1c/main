//@author A0115465H
#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include "Log.h"
#include "Task.h"

using namespace std;

class Task;

// This class
class Storage {
private:
	Log _log;
	string _storageFileName;
	static const string BACKUP;

	string dateAndTime (Task , bool);
	string priorityDecider (Priority);
	string statusDecider (Status);
	void setTempStatus(Task &, string);
	void setTempPriority(Task &, string);

public:
	Storage();
	string getStorageFileName ();
	void editStorageFileName (string name);
	void updateFile (vector <Task> &temp, bool isUndoTrue);
	void readFile (vector <Task> &temp, bool isUndoTrue);
};

#endif