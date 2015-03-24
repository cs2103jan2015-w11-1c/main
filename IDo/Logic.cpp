#include "Logic.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <string>

const string SUCCESSFULLY_MARKED = "[Marked Successfully]";
const string SUCCESSFULLY_ADDED = "[Added Successfully]";
const string DISPLAYING = "[List of Tasks]";
const string ERROR_WRONG_INPUT = "Error: Wrong Input!";

void Logic::updateStorage () {
	Storage saveToDisk;
	saveToDisk.updateFile (_listOfTasks);
}

void Logic::getParsedInformation(string line){

	Parser parser;
	userInput = line;
	//pass to parser and process
	parsedInformation = parser.completeParsing(userInput);

}

void Logic::printMessage(string message){
	cout << endl <<  message <<  endl << endl;
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


// Print out the tasks added
void Logic::printMessage2(){

	
	cout << center("No.", 3) << " | "
		 << center("Frm date:", 10) << " | "
		 << center("Frm time:", 6) << " | "
		 << center("To date:", 10) << " | "
		 << center("To time:", 6) << " | "
	     << center("Status:", 10) << " | "
		 << center("Task:", 15) << endl;

	cout << string(80, '-') << endl;

	int size = _listOfTasks.size();
	for (int i = 0 ; i < size ; i++) {
		cout << i+1 << "." << setw(4) << " | ";
		display(_listOfTasks[i]);
	}
}

string Logic::fillTable(const string content, const int width) {
		stringstream ss;
		ss << fixed << right;
		ss.fill(' ');        // fill space around displayed text
		ss.width(width);     // set width around displayed text
		ss << content;
		return ss.str();
	}

// Returns the string of a particular Task class
void Logic::display(Task task) {

	// output start, end date, time or deadline
	if(!task.getStartDate().empty()){
		cout << fillTable(task.getStartDate(), 10) << " | "
			 << fillTable(task.getStartTime(), 9) << " | " 
			 << fillTable(task.getEndDate(), 10) << " | "  
			 << fillTable(task.getEndTime(), 8) << " | ";
	} else if(!task.getDeadline().empty()) {
		cout << fillTable(task.getDeadline(), 10) << " | ";
	}

	// output completion status
	if(task.getStatus() == NOTDONE) {
		cout << fillTable("(NOT DONE)", 10) << " | ";
	} else {
		cout << fillTable("(DONE)", 10) << " | ";
	}
	
	// output task name
	cout << left << setw(15) << task.getTaskName() << endl;
	
}

// Processes the command and inputs passed from UI
bool Logic::process(string line){

	getParsedInformation(line);
	commandChoice = parsedInformation[0];

	if(commandChoice == "add"){
		Add add;
		if(add.execute(parsedInformation)){
			_listOfTasks.push_back(add.getTask());
			printMessage(SUCCESSFULLY_ADDED);
			updateStorage();
		}

	} else if(commandChoice == "delete"){
		Delete remove;
		if(remove.execute(parsedInformation, getListofTasks())){
			_listOfTasks = remove.getNewList();
			updateStorage();
		} else {
			cout<<"Task List is empty/Wrong task input!"<<endl;
		}

	} else if(commandChoice == "edit"){
		Edit edit;
		if(edit.execute(parsedInformation, getListofTasks())){
			setListOfTasks(edit.getNewList());
			updateStorage();
		} else {
			cout<<"Task NOT edited"<<endl;
		}

	} else if(commandChoice == "display"){
		printMessage(DISPLAYING);
		printMessage2();

	} else if(commandChoice == "mark"){
		//markStatus();
		Mark mark(atoi(parsedInformation[1].c_str()));
		
		if (mark.isValidInput(_listOfTasks.size())) {
			_listOfTasks = mark.execute(parsedInformation, getListofTasks());
			printMessage(SUCCESSFULLY_MARKED);
			updateStorage();
		} else {
			printMessage(ERROR_WRONG_INPUT);
		}

	} else if(commandChoice == "exit"){
		updateStorage();
		return false;
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
