#include "Storage.h"
#include "UserInterface.h"
#include "Logic.h"
#include "Parser.h"
#include "Task.h"


Storage::Storage () {
	numberOfItems=0;
	storageFileName="output.txt";
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

void Storage::updateFile (vector <Task> &temp) {
	ofstream writeFile (storageFileName);
	writeFile << temp[0].getTaskName() << endl;
	writeFile.close();
}

/*
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