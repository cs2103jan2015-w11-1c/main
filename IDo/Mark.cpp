#include "Mark.h"

void Mark::markStatus (Task &taskToMark){
	if (_contentToMark == "done") {
		taskToMark.setStatus(done);
	} else if (_contentToMark == "notdone") {
		taskToMark.setStatus(notdone);
	}
}

void Mark::markPriority(Task &taskToMark) {
	if (_contentToMark == "high") {
		taskToMark.setPriority(high);
	} else if (_contentToMark == "medium") {
		taskToMark.setPriority(medium);
	} else if (_contentToMark == "low") {
		taskToMark.setPriority(low);
	}	
}

void Mark::markLabel (Task &taskToMark) {
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
		if (!(parsedInformation[size] == "done" || parsedInformation[size] == "notdone" ||
			parsedInformation[size] == "high" || parsedInformation[size] == "medium" ||
			parsedInformation[size] == "low")) {
			return false;
		}
	}
	return validNumber;
}

void Mark::execute(vector<string> parsedInformation, vector<Task> &taskListFromLogic) {
	int size = parsedInformation.size();
	_contentToMark = parsedInformation[size - 1];
	
	for (int i = 1; i < size - 1; i++) {
		_indexToMark = atoi(parsedInformation[i].c_str()) - 1;

		Task taskToMark;

		if (_contentToMark == "done" || _contentToMark == "notdone") {
			markStatus(taskToMark);
		} else if (_contentToMark == "high" || _contentToMark == "medium" || _contentToMark == "low") {
			markPriority(taskToMark);
		} else {
			markLabel(taskToMark);
		}
	}
}


