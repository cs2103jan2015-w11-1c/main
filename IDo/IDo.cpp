#include "IDo.h"

Scheduler::Scheduler () {
	_numberOfItems=0;
}

Scheduler::~Scheduler () {
	_numberOfItems=0;
	_items.erase(_items.begin(),_items.end());
}

int Scheduler::getNumberOfItems () {
	return _numberOfItems;
}

string Scheduler::getFileName () {
	return fileName;
}

void Scheduler::modifyFileName (string newFileName) {
	fileName=newFileName;
	return;
}

void Scheduler::addEvent (EVENT temp) {
	_items.push_back(temp);
	_numberOfItems++;
	return;
}

void Scheduler::print () {
	cout << "Event: " << _items[0].name << endl;
	cout << "Description: " << _items[0].description << endl;
	cout << "Start time: " << _items[0].startTime << endl;
	cout << "Start date: " << _items[0].startDate << endl;
	cout << "End time: " << _items[0].endTime << endl;
	cout << "End date: " << _items[0].endDate << endl;
	return;
}