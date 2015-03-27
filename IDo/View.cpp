#include "View.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

const string DISPLAYING = "[List of Tasks]";

void View::printMessage() {
	cout << endl <<  DISPLAYING <<  endl << endl;
}

// Display the header of the tasks added
void View::printHeader() {
	cout << center("No.", 3) << "  "
		 << center("From", 14) << "  "
		 << center("To/by ", 16) << "  "
	     << center("Status", 15) << "  "
		 << center("Priority", 1) << " "
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

	if(!task.getStartDate().empty()){
		cout << setw(10) << task.getStartDate();
		cout << setw(6) << task.getStartTime();
		cout << setw(13) << task.getEndDate() ;
		cout << setw(6) << task.getEndTime() ;
	} else {
		cout << setw(16) << " ";
		cout << setw(13) << task.getEndDate() ;
		cout << setw(6) << task.getEndTime() ;
	}

	if (task.getStatus() == notdone) {
		cout << setw(13) << "[NOT DONE]" ;
	} else {
		cout << setw(9) << "[DONE]" << setw(4) << " ";
	}

	if (task.getPriority() == high) {
		cout << setw(9) << "[HIGH]" << setw(8) << " ";
	} else if (task.getPriority() == medium) {
		cout << setw(11) << "[MEDIUM]" << setw(6) << " ";
	} else if (task.getPriority() == low) {
		cout << setw(8) << "[LOW]" << setw(9) << " ";
	} else {
		cout << setw(9) << "[NONE]" << setw(8) << " ";
	} 

	
	// output task name
	cout << task.getTaskName() << endl;
}

void View::viewAll(vector <Task> list) {
	printMessage();
	printHeader();
	int size = list.size();
	for (int i = 0 ; i < size ; i++) {
		cout << i+1 << "." << setw(3) << "   ";
		display(list[i]);
	}
	cout <<  endl;
}

// Display the tasks that are done
void View::viewDoneTasks(vector <Task> list) {
	printMessage();
	printHeader();
	int _size = list.size();
	for (int i = 0 ; i < _size ; i++) {
		if (list[i].getStatus() == done) {
			cout << i+1 << "." << setw(3) << "   ";
			display(list[i]);
		}
	}
	cout << endl;
}

// Display the tasks that are completed
void View::viewNotDoneTasks(vector <Task> list) {
	printMessage();
	printHeader();
	int _size = list.size();
	for (int i = 0 ; i < _size ; i++) {
		if (list[i].getStatus() == notdone) {
			cout << i+1 << "." << setw(3) << "   ";
			display(list[i]);
		}
	}
	cout << endl;
}