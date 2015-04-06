#include "View.h"

const string DISPLAYING = "[List of Tasks]";
const string CHANGES = "[Last Change Made]";

void View::printMessage(string message) {
	cout << endl << message << endl << endl;
}

void View::SetColor(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
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

	SetColor(3);
	cout << string(80, '-') << endl;
	SetColor(7);
}

string View::center(string heading, const int w) {
	stringstream ss, spaces;
	int padding = w - heading.size();	// count excess room to pad
	for (int i = 0; i<padding / 2; ++i) {
		spaces << " ";
	}
	ss << spaces.str() << heading << spaces.str(); // format with padding
	if (padding>0 && padding % 2 != 0) {	// if odd #, add 1 space
		ss << " ";
	}
	return ss.str();
}

// Print out one event
void View::display(Task task) {

	cout << setw(5) << " ";
	if (!task.getStartDate().empty()){
		cout << setw(10) << task.getStartDate();
		cout << setw(5) << task.getStartTime();
		cout << setw(2) << " ";
		cout << setw(9) << task.getEndDate();
		cout << setw(5) << task.getEndTime();
	}
	else {
		cout << setw(16) << " ";
		cout << setw(10) << task.getEndDate();
		cout << setw(5) << task.getEndTime();
	}

	if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(3) << " ";
	}
	else {
		cout << setw(8) << "[DONE]" << setw(7) << " ";
	}
/*
	if (task.getLabel() == misc) {
		cout << "[MISC]" << setw(6) << " ";
	}
	else if (task.getLabel() == studies) {
		cout << "[STUDIES]" << setw(3) << " ";
	}
	else if (task.getLabel() == cca) {
		cout << "[CCA]" << setw(7) << " ";
	}
	else if (task.getLabel() == friends) {
		cout << "[FRIENDS]" << setw(3) << " ";
	}
	else {
		cout << "[FAMILY]" << setw(4) << " ";
	}
*/
	if (task.getPriority() == high) {
		SetColor(12); // red
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	}
	else if (task.getPriority() == medium) {
		SetColor(14); // bright yellow
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	}
	else if (task.getPriority() == low) {
		SetColor(10); // bright green
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	}
	else {
		SetColor(7); // default white
		cout << task.getTaskName() << endl;
	}
}

void View::viewAll(vector <Task> &list) {
	printMessage(DISPLAYING);
	printHeader();
	int size = list.size();
	for (int i = 0; i < size; i++) {
		cout << setw(3) << i + 1 << ".";
		display(list[i]);
	}
	cout << endl;
}

// Display the tasks that are done
void View::viewDoneTasks(vector <Task> &list) {
	printMessage(DISPLAYING);
	printHeader();
	int _size = list.size();
	for (int i = 0; i < _size; i++) {
		if (list[i].getStatus() == done) {
			cout << setw(3) << i + 1 << ".";
			display(list[i]);
		}
	}
	cout << endl;
}

// Display the tasks that are not done
void View::viewNotDoneTasks(vector <Task> &list) {
	printMessage(DISPLAYING);
	printHeader();
	int _size = list.size();
	for (int i = 0; i < _size; i++) {
		if (list[i].getStatus() == notdone) {
			cout << setw(3) << i + 1 << ".";
			display(list[i]);
		}
	}
	cout << endl;
}

void View::viewSelected(vector<Task> list, vector<int> taskNum) {
	printMessage(DISPLAYING);
	printHeader();
	int size = list.size();
	for (int i = 0; i < size; i++) {
		cout << taskNum[i] << "." << setw(3) << "   ";
		display(list[i]);
	}
	cout << endl;
}

void View::viewSelected2(vector<Task> list, int taskNumber) {
	printMessage(CHANGES);
	printHeader();

	cout << setw(3) << taskNumber << ".";
	display(list[taskNumber - 1]);

	cout << endl;
}


// Default view after every command
void View::viewDefault(vector<Task> &list) {
	
	string todayDate = date.getTodayDate();
	SetColor(15);
	cout << "[" << todayDate << "]" << endl;
	SetColor(13);
	cout << "** Today's Timed-Tasks **" << endl << endl;
	SetColor(7);

	printTimedTaskHeader();

	int size = list.size();

	for(int i = 0; i < size; i++) {
		if(list[i].getStartDate() == todayDate) {
			cout << setw(3) << i+1 << ".";
			displayWithoutDates(list[i]);
			cout << endl << endl;
		}
	}

	SetColor(13);
	cout << "** Upcoming Deadline Tasks **" << endl << endl; 
	SetColor(7);

	printDeadlineTaskHeader();

	for (int i = 0; i < size; i++) {
		if((list[i].getStartDate().empty()) && !list[i].getEndDate().empty()) {
			cout << setw(3) << i+1 << ".   ";
			displayWithoutDates2(list[i]);
	    	cout << endl << endl;
	}	

}	SetColor(13);
	cout << "** Floating Tasks **" << endl << endl;
	SetColor(7);

	printTimedTaskHeader();
	for (int i = 0; i< size; i++) {
		if((list[i].getStartDate().empty()) && list[i].getEndDate().empty()) {
			cout << setw(3) << i+1 << ".              ";
			displayWithoutDates(list[i]);
	    	cout << endl << endl;
	}	

	}
}

void View::printTimedTaskHeader() {
	cout << " "
		<< setw(3) << "No." << setw(7) << " "
		<< "Period" << setw(8) << " "
		<< "Status" << setw(5) << " "
		<< "Label" << setw(6) << " "
		<< "Task" << endl;

	SetColor(3);
	cout << string(80, '-') << endl;
	SetColor(7);
}

void View::printDeadlineTaskHeader() {
	cout << " " 
		 << setw(3) << "No." << setw(7) << " "
		 << "Due Date" << setw(8) << " "
	     << "Status"<< setw(5) << " "
		 << "Label" << setw(6) << " "
		 << "Task" << endl;

	SetColor(3);
	cout << string(80, '-') << endl;
	SetColor(7);
}


// Print out one event without dates 
void View::displayWithoutDates(Task task) {

	cout << setw(2) << " ";
	if (!task.getStartTime().empty() && !task.getEndTime().empty()){
		cout << setw(5) << task.getStartTime();
		cout << setw(2) << " ";
		cout << setw(2) << "to";
		cout << setw(2) << " ";
		cout << setw(4) << task.getEndTime();
	}

	if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(3) << " ";
	}
	else {
		cout << setw(8) << "[DONE]" << setw(7) << " ";
	}
/*
	if (task.getLabel() == misc) {
		cout << "[MISC]" << setw(5) << " ";
	}
	else if (task.getLabel() == studies) {
		cout << "[STUDIES]" << setw(2) << " ";
	}
	else if (task.getLabel() == cca) {
		cout << "[CCA]" << setw(6) << " ";
	}
	else if (task.getLabel() == friends) {
		cout << "[FRIENDS]" << setw(2) << " ";
	}
	else {
		cout << "[FAMILY]" << setw(3) << " ";
	}
*/
	if (task.getPriority() == high) {
		SetColor(12); // red
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	}
	else if (task.getPriority() == medium) {
		SetColor(14); // bright yellow
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	}
	else if (task.getPriority() == low) {
		SetColor(10); // bright green
		cout << task.getTaskName() << endl;
		SetColor(7); // default white
	}
	else {
		SetColor(7); // default white
		cout << task.getTaskName() << endl;
	}
}

// Print out event with deadline
void View::displayWithoutDates2(Task task) {

	cout << " ";
	if(task.getStartTime().empty() && !task.getEndTime().empty()){
		cout << task.getEndDate() << " " << task.getEndTime();
	} 

	if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(3) << " ";
	} else {
		cout << setw(8) << "[DONE]" << setw(7) << " ";
	}

	if (task.getLabel() == misc) {
		cout << "[MISC]" << setw(5) << " ";
	} else if (task.getLabel() == studies) {
		cout << "[STUDIES]" << setw(2) << " ";
	} else if (task.getLabel() == cca) {
		cout << "[CCA]" << setw(6) << " ";
	} else if (task.getLabel() == friends) {
		cout << "[FRIENDS]" << setw(2) << " ";
	} else {
		cout << "[FAMILY]" << setw(3) << " ";
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