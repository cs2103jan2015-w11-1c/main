#include "Add.h"

bool Add::execute(vector<string> parsedInformation){
	int size = parsedInformation.size();

	if (size == 2){//floating task i.e. add do tutorials
		_task.setTaskName(parsedInformation[1]);

	} else if (size == 4){ //task with deadlines only i.e. add tutorials by 12/12/2015
			_task.setTaskName(parsedInformation[1]);
			_task.setEndDate(parsedInformation[2]);
			_task.setEndTime(parsedInformation[3]);
	} else if(size == 6){ //timed-task
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

