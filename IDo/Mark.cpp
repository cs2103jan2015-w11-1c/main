#include "Mark.h"

void Mark::markStatus (AllTasks &taskToMark){
	if (taskToMark.type == 1) {
		if (_contentToMark == "done") {
			(taskToMark.rtask).setStatus(done);
		} else if (_contentToMark == "notdone") {
			(taskToMark.rtask).setStatus(notdone);
		}
	} else if (taskToMark.type == 2) {
		if (_contentToMark == "done") {
			(taskToMark.task).setStatus(done);
		} else if (_contentToMark == "notdone") {
			(taskToMark.task).setStatus(notdone);
		}
	}
}

void Mark::markPriority(AllTasks &taskToMark) {
	if (taskToMark.type == 1) {
		if (_contentToMark == "high") {
			(taskToMark.rtask).setPriority(high);
		} else if (_contentToMark == "medium") {
			(taskToMark.rtask).setPriority(medium);
		} else if (_contentToMark == "low") {
			(taskToMark.rtask).setPriority(low);
		}
	} else if (taskToMark.type == 2) {
		if (_contentToMark == "high") {
			(taskToMark.task).setPriority(high);
		} else if (_contentToMark == "medium") {
			(taskToMark.task).setPriority(medium);
		} else if (_contentToMark == "low") {
			(taskToMark.task).setPriority(low);
		}
	}
	 
}

void Mark::markLabel (AllTasks &taskToMark) {
	if (taskToMark.type == 1) {
		(taskToMark.rtask).setLabel(_contentToMark);
	} else if (taskToMark.type == 2) {
		(taskToMark.task).setLabel(_contentToMark);
	}
	
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

void Mark::execute(vector<string> parsedInformation, vector<AllTasks> &taskListFromLogic) {
	int size = parsedInformation.size();
	_contentToMark = parsedInformation[size - 1];
	
	for (int i = 1; i < size - 1; i++) {
		_indexToMark = atoi(parsedInformation[i].c_str()) - 1;

		AllTasks taskToMark;

		if (taskListFromLogic[_indexToMark].type == 1) {	//rtask
			taskToMark.rtask = taskListFromLogic[_indexToMark];
		} else if (taskListFromLogic[_indexToMark].type == 2) {	//nrtask
			taskToMark.task = taskListFromLogic[_indexToMark];
		}

		if (_contentToMark == "done" || _contentToMark == "notdone") {
			markStatus(taskToMark);
		} else if (_contentToMark == "high" || _contentToMark == "medium" || _contentToMark == "low") {
			markPriority(taskToMark);
		} else {
			markLabel(taskToMark);
		}
	}
}


