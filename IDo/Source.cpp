#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "IDo.h"

using namespace std;

EVENT parser (string line);

int main () {
	ofstream outFile;
	string newFileName;
	string command;
	string line;
	string description;

	cout << "Input working directory: " << endl;
	getline(cin,newFileName);
	outFile.open(newFileName);
	Scheduler testClass;
	testClass.modifyFileName(newFileName);
	cout << "Successfully change working directory to: " << newFileName << endl;

	cout << "Input command: " << endl;
	cin >> command;
	if (command == "add") {
		getline(cin,line);
	}
	
	cout << "here" << endl;

	testClass.addEvent(parser(line));
	testClass.print(); 
	system("pause");
	return 0;
}

EVENT parser (string line) {
	EVENT newEvent;
	if (line.find("from")==string::npos) {
		newEvent.name=line;
	}
	newEvent.startTime=1200;
	newEvent.startDate=3032015;
	newEvent.endTime=1400;
	newEvent.endDate=3032015;
	newEvent.description="nothing";
	return newEvent;
}