#include "Mark.h"
Mark::Mark(int num) {
	_indextomark = num - 1;
}

Mark::~Mark() {
}

//checks if input number falls within size of task list
bool Mark::isValidInput(int taskListSize) {
	//cout << "taskListSize = " << taskListSize << endl;

	if (_indextomark <= taskListSize) {
		
		return true;
	} else {
		return false;
	}
	
}

void Mark::setTypeToMark (string type) {
	_typetomark = type;
}

void Mark::setContentToMark (string content) {
	_contenttomark = content;
}

vector<Task> Mark::execute (vector<string> parsedInfo, vector<Task> taskListFromLogic) {
	setTypeToMark (parsedInfo[2]);
	
	setContentToMark (parsedInfo[3]);
	
	Task tasktomark = taskListFromLogic[_indextomark];
	Task marked;
	
	if (_typetomark == "status") {
		marked = markStatus(tasktomark);
	} else if (_typetomark == "priority") {
		marked = markPriority(tasktomark);
	} else if (_typetomark == "label") {
		marked = markLabel(tasktomark);
	}
	
	taskListFromLogic[_indextomark] = marked;
	return taskListFromLogic;
}


Task Mark::markStatus (Task tasktomark) {
	if (_contenttomark == "done") {
		tasktomark.setStatus(DONE);
	} else if (_contenttomark == "notdone") {
		tasktomark.setStatus(NOTDONE);
	} 
	
	return tasktomark;
}

Task Mark::markPriority (Task tasktomark) {
	if (_contenttomark == "high") {
		tasktomark.setPriority(HIGH);
	} else if (_contenttomark == "medium") {
		tasktomark.setPriority(MEDIUM);
	} else if (_contenttomark == "low") {
		tasktomark.setPriority(LOW);
	} else if (_contenttomark == "none") {
		tasktomark.setPriority(NONE);
	}

	return tasktomark;
}

Task Mark::markLabel (Task tasktomark) {
	if (_contenttomark == "studies") {
		tasktomark.setLabel(STUDIES);
	} else if (_contenttomark == "CCA") {
		tasktomark.setLabel(CCA);
	} else if (_contenttomark == "family") {
		tasktomark.setLabel(FAMILY);
	} else if (_contenttomark == "friends") {
		tasktomark.setLabel(FRIENDS);
	} else if (_contenttomark == "misc") {
		tasktomark.setLabel(MISC);
	}

	return tasktomark;
}