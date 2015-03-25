#include "Add.h"

bool Add::execute(vector<string> parsedInformation){
	int size = parsedInformation.size();
	
	if (size == 2) {
		_task.setTaskName(parsedInformation[1]);
	} else if(size == 4){ //task with deadlines only i.e. add tutorials by 12/12/2015,2323
		_task.setTaskName(parsedInformation[1]);
		_task.setEndDate(parsedInformation[2]);
		_task.setEndTime(parsedInformation[3]);
	} else if (size == 6) { //timed-task i.e. add tutorials from 2015/12/12,2323 to 2015/12/12,2323
		_task.setTaskName(parsedInformation[1]);
		_task.setStartDate(parsedInformation[2]);
		_task.setStartTime(parsedInformation[3]);
		_task.setEndDate(parsedInformation[4]);
		_task.setEndTime(parsedInformation[5]);
	} else {
		return false;
	}
	return true;
}

Task Add::getTask(){
	return _task;
}

