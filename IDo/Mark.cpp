//@author A0115465H
#include "Mark.h"

const string DONE = "done";
const string NOTDONE = "notdone";
const string HIGH = "high";
const string MEDIUM = "medium";
const string LOW = "low";

//This function set the task statuc to done or not done
void Mark::markStatus (Task &taskToMark){
	_log.log("Marking status");
	if (_contentToMark == DONE) {
		taskToMark.setStatus(done);
	} else if (_contentToMark == NOTDONE) {
		taskToMark.setStatus(notdone);
	}
}

//This function set the task priority to low,medium,high
void Mark::markPriority(Task &taskToMark) {
	_log.log("Marking priority");
	if (_contentToMark == HIGH) {
		taskToMark.setPriority(high);
	} else if (_contentToMark == MEDIUM) {
		taskToMark.setPriority(medium);
	} else if (_contentToMark == LOW) {
		taskToMark.setPriority(low);
	}	
}

//This function set the task label to what the user wants
void Mark::markLabel (Task &taskToMark) {
	_log.log("Marking label");
	taskToMark.setLabel(_contentToMark);
}

//checks if input number falls within size of task list
bool Mark::isValidInput(vector <string> parsedInformation, int taskListSize) {
	bool validNumber = true;
	int size = parsedInformation.size() - 1; 
	for (int i = 1 ; i < size ; i++) {
		if (atoi(parsedInformation[i].c_str()) > taskListSize || atoi(parsedInformation[i].c_str()) < 0) {
			return false;
		}
	}
	return validNumber;
}

//This function processes if mark function is called
void Mark::execute(vector<string> parsedInformation, vector<Task> &taskListFromLogic) {
	int size = parsedInformation.size();

	_contentToMark = parsedInformation[size - 1];
	
	for (int i = 1; i < size - 1; i++) {
		_indexToMark = atoi(parsedInformation[i].c_str()) - 1;

		if (_contentToMark == DONE || _contentToMark == NOTDONE) {
			markStatus(taskListFromLogic[_indexToMark]);
		} else if (_contentToMark == HIGH || _contentToMark == MEDIUM || _contentToMark == LOW) {
			markPriority(taskListFromLogic[_indexToMark]);
		} else {
			markLabel(taskListFromLogic[_indexToMark]);
		}
		_markedTask.push_back(taskListFromLogic[_indexToMark]);
		_markedTaskIndex.push_back(_indexToMark + 1);
	}
}

vector<Task> Mark::getMarkedTasks(){
	return _markedTask;
}

vector<int> Mark::getMarkedTaskIndex(){
	return _markedTaskIndex;
}


