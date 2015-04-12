//@author A0115465H
#include "Mark.h"

void Mark::markStatus (Task &taskToMark){
	_log.log("Marking status");
	if (_contentToMark == "done") {
		taskToMark.setStatus(done);
	} else if (_contentToMark == "notdone") {
		taskToMark.setStatus(notdone);
	}
}

void Mark::markPriority(Task &taskToMark) {
	_log.log("Marking priority");
	if (_contentToMark == "high") {
		taskToMark.setPriority(high);
	} else if (_contentToMark == "medium") {
		taskToMark.setPriority(medium);
	} else if (_contentToMark == "low") {
		taskToMark.setPriority(low);
	}	
}

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

void Mark::execute(vector<string> parsedInformation, vector<Task> &taskListFromLogic) {
	int size = parsedInformation.size();
	int _indexToMark;
	_contentToMark = parsedInformation[size - 1];
	
	for (int i = 1; i < size - 1; i++) {
		_indexToMark = atoi(parsedInformation[i].c_str()) - 1;

		if (_contentToMark == "done" || _contentToMark == "notdone") {
			markStatus(taskListFromLogic[_indexToMark]);
		} else if (_contentToMark == "high" || _contentToMark == "medium" || _contentToMark == "low") {
			markPriority(taskListFromLogic[_indexToMark]);
		} else {
			markLabel(taskListFromLogic[_indexToMark]);
		}
	}
}


