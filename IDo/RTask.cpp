#include "RTask.h"

const static string KEYWORD_EVERY = "every";
const static string PERIOD_DAY = "day";
const static string PERIOD_MONTH = "month";
const static string PERIOD_YEAR = "year";
static const int RECURRING_DEADLINE_NO_LIMIT = 7;
static const int RECURRING_DEADLINE_WITH_LIMIT = 9;
static const int RECURRING_TIMED_NO_LIMIT = 10;
static const int RECURRING_TIMED_WITH_LIMIT = 12;
static const string RTASK_TO_TASK = "RTASK to Task";

RTask::RTask(){
}

RTask::~RTask(){
}

//This function initializes abstract task attributes such as taskname, starttime, endtime
//Post: Return true if the attribute are set
//		Return false if the attributes are not set
bool RTask::setAbstrInfo(vector <string> parsedInfo) {

	log.log(RTASK_TO_TASK);
	//initialise abstract task attributes
	_abstract.setTaskName(parsedInfo[1]);
	
	if (parsedInfo[4] == KEYWORD_EVERY){	//deadline recurring task
		_abstract.setEndTime(parsedInfo[3]);
	} else if (parsedInfo[6] == KEYWORD_EVERY) {	//timed task recurring task
		_abstract.setEndTime(parsedInfo[5]);
		_abstract.setStartTime(parsedInfo[3]);
	} else {
		return false;
	}

	return true;
}

//Pre: Takes in a number
//Post: Return true if the interval between periods i.e. every 5 day, 5 is stored
bool RTask::setInterval(int interval) {
	_intervalBtwPeriod = interval;
	return true;
}

//Pre:Takes in a string 
//Post: Return true if the string is day, month, year
//		Return false if the string does not
bool RTask::setPeriod(string period) {

	if (period == PERIOD_DAY) {
		_period = day;
	}
	else if (period == PERIOD_MONTH) {
		_period = month;
	}
	else if (period == PERIOD_YEAR) {
		_period = year;
	} else {
		return false;
	}
	return true;
}

//This function stores starttime,startdate,endtime,enddate depending
//on the type of recurring task
//Pre: Takes in parsed information from parser in vector
//Post: Return true if it is identified as one of the recurring type
//		Reuturn false if it is not
bool RTask::setFirstOccur(vector<string> parsedInfo){

	log.log(RTASK_TO_TASK);

	sizeType = parsedInfo.size();
	_occur.setTaskName(_abstract.getTaskName());

	if (sizeType == RECURRING_DEADLINE_NO_LIMIT || sizeType ==RECURRING_TIMED_NO_LIMIT) {	
		_occur.setEndTime(_abstract.getEndTime());
		_occur.setEndDate(parsedInfo[2]);
	} else if(sizeType == RECURRING_DEADLINE_WITH_LIMIT || sizeType == RECURRING_TIMED_WITH_LIMIT ) {
		_occur.setStartTime(_abstract.getStartTime());
		_occur.setEndTime(_abstract.getEndTime());
		_occur.setStartDate(parsedInfo[2]);
		_occur.setEndDate(parsedInfo[4]);
	} else {
		return false;
	}
	return true;
}

//Pre: Takes in a string
//Post: Returns true if it is a day, month, year
//		Returns false if it is not
bool RTask::setLimitingPeriod(string period) {
	if (period == PERIOD_DAY) {
		_limitingPeriod = day;
	}
	else if (period == PERIOD_MONTH) {
		_limitingPeriod = month;
	}
	else if (period == PERIOD_YEAR) {
		_limitingPeriod = year;
	} else {
		return false;
	}
	return true;
}

bool RTask::setLimit(string limit) {

	_limit = atoi(limit.c_str());

	if (_period == day && _limitingPeriod == month) {
		_noOfOccurrences = _limit*30/_intervalBtwPeriod;
	} else if (_period == day && _limitingPeriod == year) {
		_noOfOccurrences = _limit*365/_intervalBtwPeriod;
	} else if (_period == month && _limitingPeriod == year) {
		_noOfOccurrences = _limit*12/_intervalBtwPeriod;
	} else if (_period == _limitingPeriod) {
		_noOfOccurrences = _limit/_intervalBtwPeriod;
	} else {
		return false;
	}
	return true;
}

//Pre: Takes in an integer
//Post: Return true if number of occurrences is set
bool RTask::setNoOfOccurrences(int noOfOccurrences) {
	_noOfOccurrences = noOfOccurrences;

	return true;
}

//This functions calculates the number of occurences for deadline tasks. 
//It also stores every recurring tasks information in a vector
void RTask::generateOccursForDeadlineTask() {

	//Push in the first occurence
	_listOfOccurrences.push_back(_occur);
	int count = 1;
	Task next = _occur;

	while (count < _noOfOccurrences) {
		endDate = from_simple_string(_occur.getEndDate());
		if (_period == day) {	
			date_duration interval(_intervalBtwPeriod);
			nextEndDate = endDate + interval;	
		}
		else if (_period == month) {	
			months interval(_intervalBtwPeriod);
			date nextEndDate = endDate + interval;
		}
		else if (_period == year) {		
			years interval(_intervalBtwPeriod);
			date nextEndDate = endDate + interval;			
		}

		log.log(RTASK_TO_TASK);

		next.setEndDate(to_simple_string(nextEndDate));
		_listOfOccurrences.push_back(next);
		_occur = next;
		count++;
	}
}

//This functions calculates the number of occurences for tiemd tasks. 
//It also stores every recurring tasks information in a vector
void RTask::generateOccursForTimedTask() {

	//Push in the first occurrence
	_listOfOccurrences.push_back(_occur);
	int count = 1;

	Task next = _occur;

	while (count < _noOfOccurrences) {
		startDate = from_simple_string(_occur.getStartDate());
		endDate = from_simple_string(_occur.getEndDate());

		if (_period == day) {		
			date_duration interval(_intervalBtwPeriod);
			nextStartDate = startDate + interval;
			nextEndDate = endDate + interval;

		}
		else if (_period == month) {
			months interval(_intervalBtwPeriod);
			nextStartDate = startDate + interval;
			nextEndDate = endDate + interval;
		}
		else if (_period == year) {
			years interval(_intervalBtwPeriod);
			nextStartDate = startDate + interval;
			nextEndDate = endDate + interval;
		}

		log.log(RTASK_TO_TASK);
		next.setStartDate(to_simple_string(nextStartDate));
		next.setEndDate(to_simple_string(nextEndDate));
		_listOfOccurrences.push_back(next);
		_occur = next;
		count++;
	}
}


vector <Task> RTask::getListOfOccurrences() {
	return _listOfOccurrences;
}
