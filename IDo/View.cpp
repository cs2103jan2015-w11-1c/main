#include "View.h"

const string DISPLAYING = "[List of Tasks]";
const string CHANGES = "[Last Change Made]";

View::View() {
	_todayDate = _date.getTodayDate();
}

void View::printMessage(string message) {
	cout << endl << message << endl << endl;
}

void View::displayToday(vector <Task> &list, int size) {
	SetColor(15);
	cout << "[" << _todayDate << "]" << endl;
	SetColor(13);
	cout << "** Today's Timed-Tasks **" << endl << endl;
	SetColor(7);
	printTimedTaskHeader();
	for(int i = 0; i < size; i++) {
		if(list[i].getStartDate() == _todayDate) {
			cout << setw(3) << i+1 << "." << setw(4) << " ";
			displayTimedTask(list[i]);
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

	SetColor(3);
	cout << string(80, '-') << endl;
	SetColor(7);
}

// Print out timed tasks 
void View::displayTimedTask(Task task) {
	int spacing;

	if (!task.getStartTime().empty() && !task.getEndTime().empty()){
		cout << setw(4) << task.getStartTime() << " " << setw(2) << "to"
		     << " " << setw(4) << task.getEndTime();
	}

	if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(1) << " ";
	}
	else {
		cout << setw(8) << "[DONE]" << setw(5) << " ";
	}

	cout << "[" << task.getLabel() << "]";
	spacing = 15 - task.getLabel().size();
	cout << setw(spacing) << " ";

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

void View::displayDeadline(vector <Task> &list, int size) {
	SetColor(13);
	cout << "** Upcoming Deadline Tasks **" << endl << endl; 
	SetColor(7);

	printDeadlineTaskHeader();

	Sort sort;
	vector <string> parsedInformation;
	vector <Task> deadlineList;
	vector <int> indexList;
	parsedInformation.push_back("sort");
	parsedInformation.push_back("deadline");
	
	for (int i = 0; i < size; i++) {
		if((list[i].getStartDate().empty()) && !list[i].getEndDate().empty()) {
			deadlineList.push_back(list[i]);
			indexList.push_back(i+1);
		}
	}

	if(sort.execute(parsedInformation, deadlineList)) {
		deadlineList = sort.getSortedList();
	}

	int displaySize = deadlineList.size();
	if (displaySize > 5) {   // only the next 5 deadline tasks will be displayed
		displaySize = 5; 
	}
	for (int i = 0 ; i < displaySize ; i++) {
		cout << setw(3) << indexList[i] << "." << setw(4) << " ";
		displayDeadlineTask(deadlineList[i]);	
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

	SetColor(3);
	cout << string(80, '-') << endl;
	SetColor(7);
}

// Print out deadline tasks
void View::displayDeadlineTask(Task task) {
	int spacing;

	if(task.getStartTime().empty() && !task.getEndTime().empty()){
		cout << task.getEndDate() << " " << task.getEndTime();
	} 

	if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(1) << " ";
	} else {
		cout << setw(8) << "[DONE]" << setw(5) << " ";
	}

	cout << "[" << task.getLabel() << "]";
	spacing = 15 - task.getLabel().size();
	cout << setw(spacing) << " ";

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

void View::displayFloating(vector <Task> &list, int size) {
	SetColor(13);
	cout << "** Floating Tasks **" << endl << endl;
	SetColor(7);

	printFloatingTaskHeader();
	for (int i = 0; i < size; i++) {
		if((list[i].getStartDate().empty()) && list[i].getEndDate().empty()) {
			cout << setw(3) << i+1 << "." << setw(4) << " ";
			displayFloatingTask(list[i]);
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

	SetColor(3);
	cout << string(80, '-') << endl;
	SetColor(7);
}

// Print out floating tasks
void View::displayFloatingTask(Task task) {
	int spacing;

	if (task.getStatus() == notdone) {
		cout << setw(7) << "[NOT DONE]" << setw(1) << " ";
	} else {
		cout << setw(3) << "[DONE]" << setw(5) << " ";
	}

	cout << "[" << task.getLabel() << "]";
	spacing = 15 - task.getLabel().size();
	cout << setw(spacing) << " ";

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

void View::SetColor(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

// Display the header of the tasks added
void View::printHeader() {
	cout << " "
		 << setw(3) << "No." << setw(3) << " "
		 << "From" << setw(14) << " "
		 << "To" << setw(16) << " "
		 << "Status" << setw(7) << " "
		 << "Label" << setw(12) << " "
		 << "Task" << endl;

	SetColor(3);
	cout << string(80, '-') << endl;
	SetColor(7);
}

// Print out one event
void View::display(Task task) {
	int spacing;

	cout << setw(3) << " ";
	if (!task.getStartDate().empty()){
		cout << setw(10) << task.getStartDate();
		cout << setw(5) << task.getStartTime();
		cout << setw(2) << " ";
		cout << setw(9) << task.getEndDate();
		cout << setw(5) << task.getEndTime();
	} else if (task.getStartDate().empty() && !task.getEndDate().empty()) {
		cout << setw(18) << " ";
		cout << setw(10) << task.getEndDate();
		cout << setw(5) << task.getEndTime();
	} else {
		cout << setw(34) << " ";
	}

	if (task.getStatus() == notdone) {
		cout << setw(12) << "[NOT DONE]" << setw(3) << " ";
	}
	else {
		cout << setw(8) << "[DONE]" << setw(7) << " ";
	}

	cout << "[" << task.getLabel() << "]";
	spacing = 15 - task.getLabel().size();
	cout << setw(spacing) << " ";

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

void View::viewSelectedFew(vector<Task> list, vector<int> taskNum) {
	printMessage(DISPLAYING);
	printHeader();
	int size = list.size();
	for (int i = 0; i < size; i++) {
		cout << taskNum[i] << "." << setw(3) << "   ";
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
void View::viewDefault(vector<Task> &list) {
	displayToday(list,list.size());
	displayDeadline(list,list.size());
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