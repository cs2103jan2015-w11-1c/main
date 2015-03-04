#ifndef IDO_H
#define IDO_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct EVENT {                //change to class
	string name;
	int startTime;
	int startDate;
	int endTime;
	int endDate;
	string description;
};

class Scheduler {
private:
	vector<EVENT> _items;
	int _numberOfItems;
	string fileName;

public:
	Scheduler();
	~Scheduler();
	int getNumberOfItems();
	string getFileName();
	void modifyFileName (string newFileName);
	void addEvent (EVENT temp);
	void print ();
};

#endif