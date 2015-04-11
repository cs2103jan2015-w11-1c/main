#include "Add.h"

bool Add::isRecurring(vector <string> parsedInfo) {
	int size = parsedInfo.size();

	if (size > 4 && parsedInfo[4] == "every") {
		return true;
	} else if (size > 6 &&  parsedInfo[6] == "every") {
		return true;
	} else {
		return false;
	}

	return true;
}

bool Add::execute(vector<string> parsedInformation){
	int size = parsedInformation.size();

	if(size == 1) {
		return false;
	}

	if (isRecurring(parsedInformation)) {	//check if it's command for recurring
		if (size == 7) {	//recurring deadline without "for"
			RTask rtask;
			
			int interval = stoi(parsedInformation[5]);
			rtask.setAbstrInfo(parsedInformation);
			rtask.setInterval(interval);
			rtask.setPeriod(parsedInformation[6]);
			rtask.setNoOfOccurrences(5);
			rtask.setFirstOccur(parsedInformation);
			rtask.generateOccursForDeadlineTask();

			_listOfOccurrences = rtask.getListOfOccurrences();

		} else if(size == 9) { //recurring timed task without "for"
			RTask rtask;

			rtask.setAbstrInfo(parsedInformation);
			rtask.setInterval(stoi(parsedInformation[7]));
			rtask.setPeriod(parsedInformation[8]);
			rtask.setNoOfOccurrences(5);
			rtask.setFirstOccur(parsedInformation);
			rtask.generateOccursForTimedTask();

			_listOfOccurrences = rtask.getListOfOccurrences();

		} else if(size == 10) { //recurring deadline with number of times
			RTask rtask;

			rtask.setAbstrInfo(parsedInformation);
			rtask.setInterval(stoi(parsedInformation[5]));
			rtask.setPeriod(parsedInformation[6]);
			rtask.setPeriod2(parsedInformation[9]);
			rtask.setLimit(parsedInformation[8]);
			rtask.setFirstOccur(parsedInformation);
			rtask.generateOccursForDeadlineTask();

			_listOfOccurrences = rtask.getListOfOccurrences();

		} else if(size == 12) { //recurring timed task with number of times
			RTask rtask;

			rtask.setAbstrInfo(parsedInformation);
			rtask.setInterval(stoi(parsedInformation[7]));
			rtask.setPeriod(parsedInformation[8]);
			rtask.setPeriod2(parsedInformation[11]);
			rtask.setLimit(parsedInformation[10]);
			rtask.setFirstOccur(parsedInformation);
			rtask.generateOccursForTimedTask();

			_listOfOccurrences = rtask.getListOfOccurrences();
		} 

	} else { // check if it's a valid command
		_task.setTaskName(parsedInformation[1]);
		if (size == 4) { //deadline tasks
			_task.setEndDate(parsedInformation[2]);
			_task.setEndTime(parsedInformation[3]);

		} else if (size == 6) { //timed-tasks
			_task.setStartDate(parsedInformation[2]);
			_task.setStartTime(parsedInformation[3]);
			_task.setEndDate(parsedInformation[4]);
			_task.setEndTime(parsedInformation[5]);
		} 
	} 
	return true;
}

vector <Task> Add::getOccurrences () {
	return _listOfOccurrences;
}

Task Add::getTask(){
	return _task;
}
