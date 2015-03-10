#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Storage.h"

using namespace std;

int main () {
	Storage testStorage;
	string newFileName;
	string eventName;
	Event getter;

	cout << "Input working directory: " << endl;
	getline(cin,newFileName);	
	testStorage.editStorageFileName(newFileName);
	cout << "Successfully change working directory to: " << newFileName << endl;
	getter.setEventName("do CS tutorial");
	getter.setStartDate("10032015");
	getter.setStartTime("1040");
	getter.setEndDate("11032015");
	getter.setEndTime("1030");
	getter.setStatus("not completed");
	getter.setDescription("test 1!");
	testStorage.addEvent(getter);
	Event setter;
	setter=testStorage.getEvent();
	cout << "test output: " << endl;
	cout << "event name: " << setter.getEventName() << endl;
	cout << "start date: " << setter.getStartDate() << endl;
	cout << "start time: " << setter.getStartTime() << endl;
	cout << "end date: " << setter.getEndDate() << endl;
	cout << "end time: " << setter.getEndTime() << endl;
	cout << "status: " << setter.getStatus() << endl;
	cout << "description: " << setter.getDescription() << endl;
	cout << endl << endl;
	testStorage.readFromFile();
	cout << endl;
	system("pause");
	return 0;
}

