#include "View.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

const string DISPLAYING = "[List of Tasks]";

void View::printMessage() {
	cout << endl <<  DISPLAYING <<  endl << endl;
}

void View::SetColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

// Display the header of the tasks added
void View::printHeader() {
	cout << " " 
		 << center("No.", 1) << "  "
		 << center("From", 12) << "  "
		 << center("To/by ", 18) << "  "
	     << center("Status", 12) << "  "
		 << center("Label", 7) << " "
		 << center("Task", 15) << endl;

	cout << string(80, '-') << endl;
}

string View::center(string heading, const int w) {
	stringstream ss, spaces;
	int padding = w - heading.size();	// count excess room to pad
	for (int i=0; i<padding/2; ++i) {
		spaces << " ";
	}
	ss << spaces.str() << heading << spaces.str(); // format with padding
	if(padding>0 && padding%2 != 0) {	// if odd #, add 1 space
		ss << " ";
	}
	return ss.str();
}

// Print out one event
void View::display(Task task) {

	cout << setw(5) << " ";
	if(!task.getStartDate().empty()){
		cout << setw(10) << task.getStartDate();
		cout << setw(5) << task.getStartTime();
		cout << setw(2) << " ";
		cout << setw(9) << task.getEndDate() ;
		cout << setw(5) << task.getEndTime() ;
	} else {
		cout << setw(16) << " ";
		cout << setw(10) << task.getEndDate() ;
		cout << setw(5) << task.getEndTime() ;
	}

	if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(3) << " ";
	} else {
		cout << setw(8) << "[DONE]" << setw(7) << " ";
	}

	if (task.getLabel() == misc) {
		cout << "[MISC]" << setw(6) << " ";
	} else if (task.getLabel() == studies) {
		cout << "[STUDIES]" << setw(3) << " ";
	} else if (task.getLabel() == cca) {
		cout << "[CCA]" << setw(7) << " ";
	} else if (task.getLabel() == friends) {
		cout << "[FRIENDS]" << setw(3) << " ";
	} else {
		cout << "[FAMILY]" << setw(4) << " ";
	}

	if (task.getPriority() == high) {
		SetColor(12); // red
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	} else if (task.getPriority() == medium) {
		SetColor(14); // bright yellow
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	} else if (task.getPriority() == low) {
		SetColor(10); // bright green
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	} else {
		SetColor(7); // default white
		cout << task.getTaskName() << endl;
	}
}

void View::viewAll(vector <Task> &list) {
	printMessage();
	printHeader();
	int size = list.size();
	for (int i = 0 ; i < size ; i++) {
		cout << setw(3) << i+1 << ".";
		display(list[i]);
	}
	cout <<  endl;
}

// Display the tasks that are done
void View::viewDoneTasks(vector <Task> &list) {
	printMessage();
	printHeader();
	int _size = list.size();
	for (int i = 0 ; i < _size ; i++) {
		if (list[i].getStatus() == done) {
			cout << setw(3) << i+1 << ".";
			display(list[i]);
		}
	}
	cout << endl;
}

// Display the tasks that are not done
void View::viewNotDoneTasks(vector <Task> &list) {
	printMessage();
	printHeader();
	int _size = list.size();
	for (int i = 0 ; i < _size ; i++) {
		if (list[i].getStatus() == notdone) {
			cout << setw(3) << i+1 << ".";
			display(list[i]);
		}
	}
	cout << endl;
}
/*
// Default view after every command
void View::viewDefault() {
	viewNotDoneTasks();
}
*/