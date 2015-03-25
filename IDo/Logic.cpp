#include "Logic.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <string>

const string SUCCESSFULLY_MARKED = "[Marked Successfully]";
const string SUCCESSFULLY_ADDED = "[Added Successfully]";
const string SUCCESSFULLY_DELETED = "[Deleted Successfully]";
const string DISPLAYING = "[List of Tasks]";
const string ERROR_WRONG_INPUT = "Error: Wrong Input!";

void Logic::updateStorage () {
	Storage saveToDisk;
	saveToDisk.updateFile (_listOfTasks);
}

void Logic::getParsedInformation(string line) {
	Parser parser;
	userInput = line;
	//pass to parser and process
	parsedInformation = parser.completeParsing(userInput);

}

void Logic::printMessage(string message) {
	cout << endl <<  message <<  endl << endl;
}

// Display the header of the tasks added
void Logic::printMessage2() {
	cout << center("No.", 3) << "  "
		 << center("From", 14) << "  "
		 << center("To/by ", 16) << "  "
	     << center("Status", 15) << "  "
		 << center("Priority", 1) << " "
		 << center("Task", 15) << endl;

	cout << string(80, '-') << endl;
}

// Display all tasks
void Logic::printMessage3() {
	int size = _listOfTasks.size();
	for (int i = 0 ; i < size ; i++) {
		cout << i+1 << "." << setw(3) << "   ";
		display(_listOfTasks[i]);
	}
	cout <<  endl;
}

string Logic::center(string heading, const int w) {
	stringstream ss, spaces;
	int padding = w - heading.size();	// count excess room to pad
	for (int i=0; i<padding/2; ++i)
		spaces << " ";
	ss << spaces.str() << heading << spaces.str(); // format with padding
	if(padding>0 && padding%2 != 0)	// if odd #, add 1 space
		ss << " ";
		return ss.str();
	}

// Returns the string of a particular Task class
void Logic::display(Task task) {

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

string Logic::fillTable(const string content, const int width) {
		stringstream ss;
		ss << fixed << right;
		ss.fill(' ');        // fill space around displayed text
		ss.width(width);     // set width around displayed text
		ss << content;
		return ss.str();
}

// Display the tasks that are done
void Logic::viewDoneTasks() {
	int _size = _listOfTasks.size();
	int j = 1; 
	for (int i = 0 ; i < _size ; i++) {
		if (_listOfTasks[i].getStatus() == done) {
			cout << j << "." << setw(3) << "   ";
			display(_listOfTasks[i]);
			j++;
		}
	}
	cout << endl;
}

// Display the tasks that are completed
void Logic::viewNotDoneTasks() {
	int _size = _listOfTasks.size();
	int j = 1; 
	for (int i = 0 ; i < _size ; i++) {
		if (_listOfTasks[i].getStatus() == notdone) {
			cout << j << "." << setw(3) << "   ";
			display(_listOfTasks[i]);
			j++;
		}
	}
	cout << endl;
}

// List the commands available
void Logic::viewCommands() {
	cout << "Add a floating task: " << setw(30) << "add <task>" << endl;
	cout << "Add a time task: add <task> from yyyy/mm/dd,hhmm to yyyy/mm/dd,hhmm" << endl;
	cout << "Add a deadline: add <task> by yyyy/mm/dd,hhmm" << endl;
	cout << "Editing details: edit <task number> <info to edit> <new content>" << endl;
	cout << "Displaying all tasks: display" << endl;
	cout << "Deleting a task: delete <task number> " << endl;
	cout << "View completed task: view done" << endl;
	cout << "View task to be completed: view notdone" << endl;
	cout << "To change status: mark <task number> <done/notdone> " << endl;
	cout << "To change priority: mark <task number> <high/medium/low/none> " << endl;
	cout << "To change label: mark <task number> <friends/family/misc etc> " << endl;
}


// Processes the command and inputs passed from UI
bool Logic::process(string line) {

	getParsedInformation(line);
	commandChoice = parsedInformation[0];
	
	if(commandChoice == "add") {
		Add add;
		if (add.execute(parsedInformation)) {
			_listOfTasks.push_back(add.getTask());
			printMessage(SUCCESSFULLY_ADDED);
			updateStorage();
		}

	} else if (commandChoice == "delete") {
		Delete remove;
		if (remove.execute(parsedInformation, getListofTasks())) {
			_listOfTasks = remove.getNewList();
			printMessage(SUCCESSFULLY_DELETED);
			updateStorage();
		} else {
			cout<<"Task List is empty/Wrong task input!"<<endl;
		}

	} else if (commandChoice == "edit") {
		Edit edit;
		if (edit.execute(parsedInformation, getListofTasks())) {
			setListOfTasks(edit.getNewList());
			updateStorage();
		} else {
			cout<<"Task NOT edited"<<endl;
		}

	} else if (commandChoice == "display") {
		printMessage(DISPLAYING);
		printMessage2();
		printMessage3();

	} else if (commandChoice == "mark") {
		Mark mark;
		if (mark.isValidInput(atoi(parsedInformation[1].c_str()), _listOfTasks.size())) {
			_listOfTasks = mark.execute(parsedInformation, _listOfTasks);
			printMessage(SUCCESSFULLY_MARKED);
			updateStorage();
		} else {
			printMessage(ERROR_WRONG_INPUT);
		}
		updateStorage();

	} else if (commandChoice == "view") {
		printMessage(DISPLAYING);
		if (parsedInformation[1] == "done") {
			printMessage2();
			viewDoneTasks();
		} else if (parsedInformation[1] == "notdone") {
			printMessage2();
			viewNotDoneTasks();
		} else if (parsedInformation[1] == "commands") {
			viewCommands();
		}

	} else if (commandChoice == "exit") {
		updateStorage();
		return false;

	} else if (commandChoice == "invalid") {
		cout << ERROR_WRONG_INPUT << endl;
	} else {
		cout << ERROR_WRONG_INPUT << endl;
	}
	return true;
}

vector<Task> Logic::getListofTasks(){
	return _listOfTasks;
}

vector<Task> Logic::setListOfTasks(vector<Task> newList){
	_listOfTasks = newList;
	return _listOfTasks;
}