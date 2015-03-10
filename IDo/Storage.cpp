#include "Storage.h"
#include "UserInterface.h"
#include "Logic.h"
#include "Parser.h"

/*Task::Task (TaskType code, string name, string date1, string time1, string date2, string time2) {
	taskType=code;
	taskName=name;
	startDate=date1;
	startTime=time1;
	endDate=date2;
	endTime=time2;
} */

/*
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
*/