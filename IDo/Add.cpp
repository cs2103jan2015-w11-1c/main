//@author A0115545J
#include "Add.h"

static const int INVALID = 1;
static const int DEADLINE_TASK = 4;
static const int TIMED_TASK = 6;
static const int RECURRING_DEADLINE_WITHOUT_LIMIT = 7;
static const int RECURRING_DEADLINE_GOT_LIMIT = 10;
static const int RECURRING_TIMED_WITHOUT_LIMIT = 9;
static const int RECURRING_TIMED_GOT_LIMIT = 12;
static const int DEFAULT_OCCURRENCE = 5;
static const string WORD_EVERY = "every";
static const string ADD_TO_RTASK = "Add to Rtask";
static const string ADD_TO_TASK = "Add to Task";

//Pre: Takes in parsed information from the parser
//Post: Return true if it contains keyword "every"
//		Return false if it does not contain keyword "every"
bool Add::isRecurring(vector <string> parsedInfo) {
	int size = parsedInfo.size();

	if (size > 4 && parsedInfo[4] == WORD_EVERY) {
		return true;
	} else if (size > 6 &&  parsedInfo[6] == WORD_EVERY) {
		return true;
	} else {
		return false;
	}

	return true;
}

bool Add::execute(vector<string> parsedInformation){
	int sizeType = parsedInformation.size();

	if(sizeType == INVALID) {
		return false;
	}

	if (isRecurring(parsedInformation)) {

		_log.log(ADD_TO_RTASK);

		rtask.setAbstrInfo(parsedInformation);
		rtask.setFirstOccur(parsedInformation);
	
		if (sizeType == RECURRING_DEADLINE_WITHOUT_LIMIT) {	
			
			rtask.setNoOfOccurrences(DEFAULT_OCCURRENCE);
			rtask.setInterval(stoi(parsedInformation[5]));
			rtask.setPeriod(parsedInformation[6]);

			rtask.generateOccursForDeadlineTask();
			_listOfOccurrences = rtask.getListOfOccurrences();

		} else if(sizeType == RECURRING_TIMED_WITHOUT_LIMIT) { 

			rtask.setNoOfOccurrences(DEFAULT_OCCURRENCE);
			rtask.setInterval(stoi(parsedInformation[7]));
			rtask.setPeriod(parsedInformation[8]);

			rtask.generateOccursForTimedTask();
			_listOfOccurrences = rtask.getListOfOccurrences();

		} else if(sizeType == RECURRING_DEADLINE_GOT_LIMIT) {

			rtask.setInterval(stoi(parsedInformation[5])); 
			rtask.setPeriod(parsedInformation[6]); 			
			rtask.setLimitingPeriod(parsedInformation[9]); 
			rtask.setLimit(parsedInformation[8]);

			rtask.generateOccursForDeadlineTask();
			_listOfOccurrences = rtask.getListOfOccurrences();

		} else if(sizeType == RECURRING_TIMED_GOT_LIMIT) { 

			rtask.setInterval(stoi(parsedInformation[7]));
			rtask.setPeriod(parsedInformation[8]);
			rtask.setLimitingPeriod(parsedInformation[11]);
			rtask.setLimit(parsedInformation[10]);

			rtask.generateOccursForTimedTask();
			_listOfOccurrences = rtask.getListOfOccurrences();

		} else {
			return false;
		}

	} else { 
		_log.log(ADD_TO_TASK);

		_task.setTaskName(parsedInformation[1]);

		if (sizeType == DEADLINE_TASK) { 
			_task.setEndDate(parsedInformation[2]);
			_task.setEndTime(parsedInformation[3]);

		} else if (sizeType == TIMED_TASK) { 
			_task.setStartDate(parsedInformation[2]);
			_task.setStartTime(parsedInformation[3]);
			_task.setEndDate(parsedInformation[4]);
			_task.setEndTime(parsedInformation[5]);

		} 
	} 
	return true;
}

//This function is for storing recurring tasks
//Post: Return a list of recurring tasks in vector
vector <Task> Add::getOccurrences () {
	return _listOfOccurrences;
}


//Post: Return information of the task stored
Task Add::getTask(){
	return _task;
}
