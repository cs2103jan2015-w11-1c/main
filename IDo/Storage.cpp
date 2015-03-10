#include "Storage.h"

Task::Task () {
}

Task::Task (TaskType code, string name, string date1, string time1, string date2, string time2, string tempStatus, string elaboration) {
	taskType=code;
	taskName=name;
	startDate=date1;
	startTime=time1;
	endDate=date2;
	endTime=time2;
	status=tempStatus;
	description=elaboration;
}

TaskType Task::getTaskType () {
	return taskType;
}

string Task::getTaskName () {
	return taskName;
}

string Task::getStartDate () {
	return startDate;
}

string Task::getStartTime() {
	return startTime;
}

string Task::getEndDate() {
	return endDate;
}

string Task::getEndTime() {
	return endTime;
}

string Task::getStatus() {
	return status;
}

string Task::getDescription() {
	return description;
}

void Task::setTaskType (TaskType type) {
	taskType=type;
}

void Task::setTaskName (string name) {
	taskName=name;
}

void Task::setStartDate (string date) {
	startDate=date;
}

void Task::setStartTime (string time) {
	startTime=time;
}

void Task::setEndDate (string date) {
	endDate=date;
}

void Task::setEndTime (string time) {
	endTime=time;
}

void Task::setStatus (string tempStatus) {
	status=tempStatus;
}

void Task::setDescription (string elaboration) {
	description=elaboration;
}

Storage::Storage () {
	numberOfItems=0;
	storageFileName="IDo.txt";
}

int Storage::getNumberOfItems () {
	return numberOfItems;
}

string Storage::getStorageFileName () {
	return storageFileName;
}

void Storage::editStorageFileName (string name) {
	storageFileName=name;
}

void Storage::addTask (Task task) {
	_scheduler.push_back(task);
	numberOfItems++;
}

Task Storage::getTask () {
	return _scheduler[0];
}
	
void Storage::readFromFile () {
	ifstream readFile (storageFileName);
	Task hello;
	string name;
	string date1; 
	string time1;
	getline(readFile,name);
	while (name!="NULL") {
		getline(readFile,date1);
		getline(readFile,time1);
		hello.setTaskName(name);
		hello.setStartDate(date1);
		hello.setStartTime(time1);
		cout << hello.getTaskName() << endl;
		cout << hello.getStartDate() << endl;
		cout << hello.getStartTime() << endl;
		name="NULL";
		getline(readFile,name);
		readFile.close();
	}
}
