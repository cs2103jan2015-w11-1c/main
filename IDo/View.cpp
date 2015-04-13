//@author A0115465H
#include "View.h"

const string DISPLAYING = "[List of Tasks]";
const string CHANGES = "**Last Change Made**";

View::View() {
	_todayDate = _date.getTodayDate();
}

void View::printMessage(string message) {
	cout << endl << message << endl << endl;
}

void View::displayToday(vector <Task> &list, int size, string date) {
	SetColor(brightWhite);
	cout << "Today's Date [" << _todayDate << "]" << endl << endl;
	SetColor(pink);
	cout << "** " << date << " Timed-Tasks **" << endl << endl;
	SetColor(defaultWhite);
	printTimedTaskHeader();
	for(int i = 0; i < size; i++) {
		if(list[i].getStartDate() == date) {
			displayTimedTask(i+1,list[i]);
		}
	}
	cout << endl;
}

void View::printTimedTaskHeader() {
	cout << " "
		<< setw(3) << "No." << setw(4) << " "
		<< "Period" << setw(8) << " "
		<< "Status" << setw(5) << " "
		<< "Label" << setw(12) << " "
		<< "Task" << endl;

	SetColor(cyan);
	cout << string(80, '-') << endl;
	SetColor(defaultWhite);
}

// Print out timed tasks 
void View::displayTimedTask(int index, Task task) {
	printIndex(index);
	printStart(task);
	printStatus(task,0);
	printLabel(task);
	printPriority(task);
}

void View::displayDeadline(vector <Task> &list, int size, string date) {
	SetColor(pink);
	cout << "** Upcoming Deadline Tasks from " << date << " onwards **" << endl << endl; 
	SetColor(defaultWhite);

	printDeadlineTaskHeader();

	Sort sort;
	vector <string> parsedInformation;
	vector <Task> deadlineList;
	vector <int> indexList;
	parsedInformation.push_back("sort");
	parsedInformation.push_back("deadline");
	
	for (int i = 0; i < size; i++) {
		if((list[i].getStartDate().empty()) && !list[i].getEndDate().empty() && list[i].getStatus() == notdone) {
			deadlineList.push_back(list[i]);
			indexList.push_back(i+1);
		}
	}

	if (sort.execute(parsedInformation, deadlineList)) {
		deadlineList = sort.getSortedList();
	}

	int displaySize = deadlineList.size();
	int j = 0; 
	for (int i = 0 ; i < displaySize && j < 5; i++) {
		if (deadlineList[i].getEndDate() >= date) {
			displayDeadlineTask(indexList[i], deadlineList[i]);	
			j++;
		}
	}
	cout << endl;
}

void View::printDeadlineTaskHeader() {
	cout << " " 
		 << setw(3) << "No." << setw(4) << " "
		 << "Due Date" << setw(10) << " "
	     << "Status"<< setw(5) << " "
		 << "Label" << setw(12) << " "
		 << "Task" << endl;

	SetColor(cyan);
	cout << string(80, '-') << endl;
	SetColor(defaultWhite);
}

// Print out deadline tasks
void View::displayDeadlineTask(int index, Task task) {
	printIndex(index);
	printDeadline(task);
	printStatus(task,0);
	printLabel(task);
	printPriority(task);
}

void View::displayFloating(vector <Task> &list, int size) {
	SetColor(pink);
	cout << "** Floating Tasks **" << endl << endl;
	SetColor(defaultWhite);

	printFloatingTaskHeader();
	for (int i = 0; i < size; i++) {
		if((list[i].getStartDate().empty()) && list[i].getEndDate().empty()) {
		
			displayFloatingTask(i+1,list[i]);
		}
	}
	cout << endl;
}

void View::printFloatingTaskHeader() {
	cout << " " 
		 << setw(3) << "No." << setw(4) << " "
	     << "Status"<< setw(5) << " "
		 << "Label" << setw(12) << " "
		 << "Task" << endl;

	SetColor(cyan);
	cout << string(80, '-') << endl;
	SetColor(defaultWhite);
}

// Print out floating tasks
void View::displayFloatingTask(int index, Task task) {
	printIndex(index);
	printStatus(task,1);
	printLabel(task);
	printPriority(task);
}

void View::SetColor(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

void View::printIndex(int index) {
	cout << setw(3) << index << "." << setw(4) << " ";
}

void View::printStart(Task task) {
	if (!task.getStartTime().empty() && !task.getEndTime().empty()){
		cout << setw(4) << task.getStartTime() << " " << setw(2) << "to"
		     << " " << setw(4) << task.getEndTime();
	}
}

void View::printDeadline(Task task) {
	Parser parser;
	string _todayDate;
	bool valid = false;
	parser.compareDates(_todayDate, task.getDeadline());

	if(task.getStartTime().empty() && !task.getEndTime().empty()){
		if(valid) {
		SetColor(brightRed);
		cout << task.getEndDate() << " " << task.getEndTime();
		SetColor(defaultWhite);
		} else {
			cout << task.getEndDate() << " " << task.getEndTime();
		}
	} 
}

void View::printStatus (Task task, bool isFloatingTask) {
	if (!isFloatingTask) {
		if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(1) << " ";
		} else {
		cout << setw(8) << "[DONE]" << setw(5) << " ";
		}
	} else {
		if (task.getStatus() == notdone) {
			cout << setw(7) << "[NOT DONE]" << setw(1) << " ";
		} else {
			cout << setw(3) << "[DONE]" << setw(5) << " ";
		}
	}
}

void View::printLabel (Task task) {
	int spacing;
	cout << "[" << task.getLabel() << "]";
	spacing = 15 - task.getLabel().size();
	cout << setw(spacing) << " ";
}

void View::printPriority (Task task) {
	if (task.getPriority() == high) {
		SetColor(brightRed); // red
		cout << task.getTaskName() << endl;
		SetColor(defaultWhite); // default white
	} else if (task.getPriority() == medium) {
		SetColor(yellow); // bright yellow
		cout << task.getTaskName() << endl;
		SetColor(defaultWhite); // default white
	} else if (task.getPriority() == low) {
		SetColor(brightGreen); // bright green
		cout << task.getTaskName() << endl;
		SetColor(defaultWhite); // default white
	} else {
		SetColor(defaultWhite); // default white
		cout << task.getTaskName() << endl;
	}
}

// Display the header of the tasks added
void View::printHeader () {
	cout << " "
		 << setw(3) << "No." << setw(3) << " "
		 << "From" << setw(14) << " "
		 << "To" << setw(16) << " "
		 << "Status" << setw(7) << " "
		 << "Label" << setw(12) << " "
		 << "Task" << endl;

	SetColor(cyan);
	cout << string(80, '-') << endl;
	SetColor(defaultWhite);
}

// Print out one event
void View::display(Task task) {
	cout << setw(3) << " ";
	if (!task.getStartDate().empty()){    // timed tasks
		cout << setw(10) << task.getStartDate();
		cout << setw(5) << task.getStartTime();
		cout << setw(2) << " ";
		cout << setw(9) << task.getEndDate();
		cout << setw(5) << task.getEndTime();
	} else if (task.getStartDate().empty() && !task.getEndDate().empty()) { // deadline tasks
		cout << setw(18) << " ";
		cout << setw(10) << task.getEndDate();
		cout << setw(5) << task.getEndTime();
	} else {  // floating tasks
		cout << setw(34) << " ";
	}

	if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(3) << " ";
	}
	else {
		cout << setw(8) << "[DONE]" << setw(7) << " ";
	}

	printLabel(task);
	printPriority(task);
}

void View::viewSelectedFew(vector<Task> list, vector<int> taskNum) {
	printMessage(DISPLAYING);
	printHeader();
	int size = list.size();
	for (int i = 0; i < size; i++) {
		cout << setw(3) << taskNum[i] << ".";
		display(list[i]);
	}
	cout << endl;
}

void View::viewSelectedOne(vector<Task> list, int taskNumber) {
	printMessage(CHANGES);
	printHeader();

	cout << setw(3) << taskNumber << ".";
	display(list[taskNumber - 1]);
}

// Default view after every command
void View::viewDefault(vector<Task> &list, string date) {
	system("CLS");
	_log.log("Called display to view timed tasks");
	displayToday(list,list.size(),date);
	_log.log("Called display to view deadline tasks");
	displayDeadline(list,list.size(),date);
	_log.log("Called display to view floating tasks");
	displayFloating(list,list.size());
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

void View::viewPriority(vector <Task> &list, string priority) {
	printMessage(DISPLAYING);
	printHeader();
	int _size = list.size();
	Priority enumPriority;

	if (priority == "high") {
		enumPriority = high;
	} else if (priority == "medium") {
		enumPriority = medium;
	} else {
		enumPriority = low;
	}

	for (int i = 0; i < _size; i++) {
		if (list[i].getPriority() == enumPriority) {
			cout << setw(3) << i + 1 << ".";
			display(list[i]);
		}
	}
	cout << endl;
}