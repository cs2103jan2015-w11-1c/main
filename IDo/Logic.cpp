#include "Logic.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <string>

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

// Print out the tasks added
void Logic::printMessage2(){

	string center(string heading, const int w) {
		stringstream ss, spaces;
		int padding = w - heading.size();	// count excess room to pad
		for (int i=0; i<padding/2; ++i)
			spaces << " ";
		ss << spaces.str() << heading << spaces.str(); // format with padding
		if(padding>0 && padding%2 != 0)	// if odd #, add 1 space
			ss << " ";
		return ss.str();
	}

	cout << center("No.", 4) << " | "
		 << center("From:", 8) << " | "
		 << center("To:", 8) << " | "
	     << center("Status:", 10) << " | "
		 << center("Task name:", 15) << endl;

	cout << string(45, '-') << endl;

	int size = _listOfTasks.size();
	for (int i = 0 ; i < size ; i++) {
		cout << i+1 << display(_listOfTasks[i]) <<  endl;
	}
}

// Returns the string of a particular Task class
string Logic::display(Task task){

	string fillTable(const string content, const int width) {
		stringstream ss;
		ss << fixed << right;
		ss.fill(' ');        // fill space around displayed text
		ss.width(width);     // set width around displayed text
		ss << content;
		return ss.str();
	}

	// output start, end date, time or deadline
	if(!task.getStartDate().empty()){
		cout << fillTable(task.getStartDate(), 8) << " | " << endl 
			 << fillTable(task.getStartTime(), 8) << " | " 
			 << fillTable(task.getEndDate(), 8) << endl << task.getEndTime() << endl;
	} else if(!task.getDeadline().empty()){
		cout << fillTable(task.getDeadline(), 8) << endl;
	}
	// output completion status
	
	if(task.getStatus() == UNCOMPLETED) {
	 cout << fillTable("(UNCOMPLETED)", 10); 
	} else {
		cout << fillTable("(COMPLETED)", 10);
	}
	
	// output task name
	fillTable(task.getTaskName(), 15);
	
}

// Marks status as COMPLETED or UNCOMPLETED
void Logic::markStatus(){
	int numberToMark=atoi(parsedInformation[1].c_str());
	string status=parsedInformation[2];
	
	if(status == "yes"){
		_listOfTasks[numberToMark-1].setStatus(COMPLETED);
	} else if(status == "no"){
		_listOfTasks[numberToMark-1].setStatus(UNCOMPLETED);
	}
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
		markStatus();

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
