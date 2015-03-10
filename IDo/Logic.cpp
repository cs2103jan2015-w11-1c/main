#include "Logic.h"
#include "UserInterface.h"
#include "Parser.h"
#include "Task.h"
#include <sstream>

//Pre-condition: takes in a task object
//adds the task to the private vector list of tasks
//passes the updated vector to storage 
//Post-condition: none
void Logic::add(string inputLine) {
	Parser data;
	cout << endl << data.processAddContent(inputLine) << endl;
	_listOfTasks.push_back(data.getTask());
//	updateStorage(_listOfTasks);
}



//Pre-condition:none
//strings all the tasks in the vector 
//Post: returns the string
string Logic::display() {

	if (_listOfTasks.empty()) {
		return "NO TASKS RECORDED\n";
	} 

	ostringstream oss;

	for (int i = 0; i < _listOfTasks.size(); i++) {
		if (!_listOfTasks[i].getStartDate().empty()) {
			oss << i+1 << ". " << "Task Name:" << _listOfTasks[i].getTaskName() << endl <<
			"Start: " << _listOfTasks[i].getStartDate() << "," << _listOfTasks[i].getStartTime() << endl <<
			"End: " << _listOfTasks[i].getEndDate() << "," << _listOfTasks[i].getEndTime() << endl << endl;
		}
		else if (!_listOfTasks[i].getDeadline().empty()) {
			oss << i+1 << ". " << "Task Name:" << _listOfTasks[i].getTaskName() << endl <<
			"Deadline: " << _listOfTasks[i].getDeadline() << endl << endl;
		}
		else {
			oss << i+1 << ". " << "Task Name:" << _listOfTasks[i].getTaskName() << endl << endl;
		}
	}

	return oss.str();

}

//Pre: takes in the number to be deleted
//Post: returns the deleted string
string Logic::del(int numberToDelete) {
	if (_listOfTasks.empty()) {
		return "NO TASKS ADDED\n";
	}
	else {
		_listOfTasks.erase(_listOfTasks.begin()+numberToDelete);
		ostringstream oss;
		oss << "SUCCESSFULLY DELETED TASK " << numberToDelete+1 << endl;
		return oss.str();
	}
}

string Logic::edit(string inputLine){
	Parser data;
	data.processEditContent(inputLine);

	if (data.getTaskInfo()=="taskname") {
		int numberToEdit=data.getEditNumber()-1;
		string newContent=data.getEditContent();
		_listOfTasks[numberToEdit].setTaskName(newContent);
	}
	else if (data.getTaskInfo()=="starttime") {
		int numberToEdit=data.getEditNumber()-1;
		string newContent=data.getEditContent();
		_listOfTasks[numberToEdit].setStartTime(newContent);
	}
	else if (data.getTaskInfo()=="startdate") {
		int numberToEdit=data.getEditNumber()-1;
		string newContent=data.getEditContent();
		_listOfTasks[numberToEdit].setStartDate(newContent);
	}
	else if (data.getTaskInfo()=="endtime") {
		int numberToEdit=data.getEditNumber()-1;
		string newContent=data.getEditContent();
		_listOfTasks[numberToEdit].setEndTime(newContent);
	}
	else if (data.getTaskInfo()=="enddate") {
		int numberToEdit=data.getEditNumber()-1;
		string newContent=data.getEditContent();
		_listOfTasks[numberToEdit].setEndDate(newContent);
	}
	else if (data.getTaskInfo()=="deadline") {
		int numberToEdit=data.getEditNumber()-1;
		string newContent=data.getEditContent();
		_listOfTasks[numberToEdit].setDeadline(newContent);
	}

	ostringstream oss;
	oss << endl << "SUCCESSFULLY EDITED TASK " << data.getEditNumber() << endl;
	return oss.str();
}
