#include "Mark.h"

//checks if input number falls within size of task list
bool Mark::isValidInput(int userinput, int taskListSize) {
		if (userinput <= taskListSize) {
		_indexToMark = userinput - 1;
		return true;
	} else {
		return false;
	}
}

void Mark::setContentToMark(string content) {
	_contentToMark = content;
}

vector<Task> Mark::execute(vector<string> parsedInfo, vector<Task> taskListFromLogic) {
	setContentToMark (parsedInfo[2]);
	
	Task taskToMark = taskListFromLogic[_indexToMark];
	Task marked;
	
	if (_contentToMark == "done" || "notdone") {
		marked = markStatus(taskToMark);
	} else if (_contentToMark == "high" || "medium" || "low" || "none") {
		marked = markPriority(taskToMark);
	} else if (_contentToMark == "studies" || "cca" || "friends" || "family" || "misc") {
		marked = markLabel(taskToMark);
	}
	
	taskListFromLogic[_indexToMark] = marked;
	return taskListFromLogic;
}


Task Mark::markStatus (Task taskToMark) {
	if (_contentToMark == "done") {
		taskToMark.setStatus(done);
	} else if (_contentToMark == "notdone") {
		taskToMark.setStatus(notdone);
	} 
	return taskToMark;
}

Task Mark::markPriority (Task taskToMark) {
	if (_contentToMark == "high") {
		taskToMark.setPriority(high);
	} else if (_contentToMark == "medium") {
		taskToMark.setPriority(medium);
	} else if (_contentToMark == "low") {
		taskToMark.setPriority(low);
	} else if (_contentToMark == "none") {
		taskToMark.setPriority(none);
	}
	return taskToMark;
}

Task Mark::markLabel (Task taskToMark) {
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
	return taskToMark;
}