#include "Mark.h"
Mark::Mark() {
}

Mark::~Mark() {
}

//checks if input number falls within size of task list
bool Mark::isValidInput(int userinput, int taskListSize) {
	//cout << "taskListSize = " << taskListSize << endl;

	if (userinput <= taskListSize) {
		_indextomark = userinput - 1;
		
		return true;
	} else {
		return false;
	}
	
}

vector<Task> Mark::execute(vector<string> parsedInfo, vector<Task> taskListFromLogic) {
	_typetomark = parsedInfo[2];
	
	_contenttomark = parsedInfo[3];
	
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
	if (_contenttomark == "completed") {
		tasktomark.setStatus(COMPLETED);
	} else if (_contenttomark == "incomplete") {
		tasktomark.setStatus(INCOMPLETE);
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