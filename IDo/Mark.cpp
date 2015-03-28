#include "Mark.h"

void Mark::markStatus (Task &taskToMark){
	if (_contentToMark == "done") {
		taskToMark.setStatus(done);
	} else if (_contentToMark == "notdone") {
		taskToMark.setStatus(notdone);
	} 
}

void Mark::markPriority (Task &taskToMark) {
	if (_contentToMark == "high") {
		taskToMark.setPriority(high);
	} else if (_contentToMark == "medium") {
		taskToMark.setPriority(medium);
	} else if (_contentToMark == "low") {
		taskToMark.setPriority(low);
	} else if (_contentToMark == "none") {
		taskToMark.setPriority(none);
	}
}

void Mark::markLabel (Task &taskToMark) {
	if (_contentToMark == "studies") {
		taskToMark.setLabel(studies);
	} else if (_contentToMark == "CCA") {
		taskToMark.setLabel(cca);
	} else if (_contentToMark == "family") {
		taskToMark.setLabel(family);
	} else if (_contentToMark == "friends") {
		taskToMark.setLabel(friends);
	} else if (_contentToMark == "misc") {
		taskToMark.setLabel(misc);
	}
}

//checks if input number falls within size of task list
bool Mark::isValidInput(vector <string> parsedInformation, int taskListSize) {
	bool validNumber;
	int size = parsedInformation.size() - 1; 
	for (int i = 1 ; i < size ; i++) {
		if (atoi(parsedInformation[i].c_str()) <= taskListSize && atoi(parsedInformation[i].c_str()) > 0) {
			validNumber = true;
		} else {
			return false;
		}
	}
	return validNumber;
}

void Mark::execute(vector<string> parsedInformation, vector<Task> &taskListFromLogic) {
	int size = parsedInformation.size();
	_contentToMark = parsedInformation[size - 1];
	
	for (int i = 1 ; i < size - 1 ; i++) {
		_indexToMark = atoi(parsedInformation[1].c_str()) - 1;

		if (_contentToMark == "done" || _contentToMark == "notdone") {
			markStatus(taskListFromLogic[_indexToMark]);
		} else if (_contentToMark == "high" || _contentToMark == "medium" || _contentToMark == "low" || _contentToMark == "none") {
			markPriority(taskListFromLogic[_indexToMark]);
		} else if (_contentToMark == "studies" || _contentToMark == "cca" || _contentToMark == "friends" || _contentToMark == "family" || _contentToMark == "misc") {
			markLabel(taskListFromLogic[_indexToMark]);
		}
	}
}


