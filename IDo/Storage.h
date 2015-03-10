#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum TaskType {
	Timed, Deadline, Floating
};

class Task {
private:
	TaskType taskType;
	string taskName;
	string startDate;
	string startTime;
	string endDate;
	string endTime;
	string status;
	string description;

public:
	Task ();
	Task (TaskType code, string name, string date1, string time1, string date2, string time2, string tempStatus, string elaboration);
	TaskType getTaskType ();
	string getTaskName();
	string getStartDate();
	string getStartTime();
	string getEndDate();
	string getEndTime();
	string getStatus();
	string getDescription();
	void setTaskType (TaskType type);
	void setTaskName (string name);
	void setStartDate (string date);
	void setStartTime (string time);
	void setEndDate (string date);
	void setEndTime (string time);
	void setStatus (string tempStatus);
	void setDescription (string elaboration);
};


class Storage {
private:
	string storageFileName;
	vector<Task> _scheduler;
	int numberOfItems;

public:
	Storage();
	int getNumberOfItems();
	string getStorageFileName ();
	void editStorageFileName (string name);
	void addTask (Task task);
	Task getTask ();
	void readFromFile ();
};

#endif