//@author A0115545J
#include "RTask.h"

const static string KEYWORD_EVERY = "every";
const static string PERIOD_DAY = "day";
const static string PERIOD_MONTH = "month";
const static string PERIOD_YEAR = "year";
static const int RECURRING_DEADLINE_NO_LIMIT = 7;
static const int RECURRING_DEADLINE_WITH_LIMIT = 10;
static const int RECURRING_TIMED_NO_LIMIT = 9;
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

	_log.log(RTASK_TO_TASK);
	assert (!parsedInfo.empty());

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

	assert (!period.empty());

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

	_log.log(RTASK_TO_TASK);
	assert (!parsedInfo.empty());

    int type = parsedInfo.size();
	_occur.setTaskName(_abstract.getTaskName());

	if (type == RECURRING_DEADLINE_NO_LIMIT || type == RECURRING_DEADLINE_WITH_LIMIT) {	

		_occur.setEndTime(_abstract.getEndTime());
		_occur.setEndDate(parsedInfo[2]);

	} else if (type == RECURRING_TIMED_NO_LIMIT || type == RECURRING_TIMED_WITH_LIMIT ) {

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

	assert (!period.empty());

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

//This function sets the last date limit given by the user
//Pre: Takes in userinput as a string
//Post: Returns true if the recurring lastDateLimit is set
bool RTask::setLimit(string limit) {

	assert (!limit.empty());

	_limit = atoi(limit.c_str());

	days difference;
	date now;
	if (!_occur.getStartDate().empty()){
		now = from_simple_string(_occur.getStartDate());
	} else {
		now = from_simple_string(_occur.getEndDate());
	}

	if (_limitingPeriod == month) {
		months interval(_limit);
		_lastDateLimit = now + interval;
	} else if (_limitingPeriod == year) {
		years interval(_limit);
		_lastDateLimit = now + interval;
	} else if (_limitingPeriod == day) {
		days interval(_limit);
		_lastDateLimit = now + interval;
	} else {
		return false;
	}

	return true;
}

//This function stores the datelimit for a recurring function
//Pre: Takes in a default limit 
//Post: Return true if date limit and number of occurrences is set
bool RTask::setNoOfOccurrences(int noOfOccurrences) {

	date now;

	if(!_occur.getStartDate().empty()){
		now = from_simple_string(_occur.getStartDate());
	} else {
		now = from_simple_string(_occur.getEndDate());
	}

	noOfOccurrences = (noOfOccurrences - 1) * _intervalBtwPeriod;

	if(_period == day) {
		days interval(noOfOccurrences);
		_lastDateLimit = now + interval;
	} else if(_period == month) {
		months interval(noOfOccurrences);
		_lastDateLimit = now + interval;
	} else if(_period == year) {
		years interval(noOfOccurrences);
		_lastDateLimit = now + interval;
	}

	_noOfOccurrences = noOfOccurrences;

	return true;
}

//This functions calculates the number of occurences for deadline tasks. 
//It also stores every recurring tasks information in a vector
void RTask::generateOccursForDeadlineTask() {

	//Push in the first occurence
	_listOfOccurrences.push_back(_occur);
	Task next = _occur;

	_nextEndDate = from_simple_string(next.getEndDate());

	
	while (_nextEndDate <= _lastDateLimit) {
		_endDate = from_simple_string(_occur.getEndDate());
		
		if (_period == day) {	
			date_duration interval(_intervalBtwPeriod);
			_nextEndDate = _endDate + interval;	
		} else if (_period == month) {	
			months interval(_intervalBtwPeriod);
			_nextEndDate = _endDate + interval;
		} else if (_period == year) {		
			years interval(_intervalBtwPeriod);
			_nextEndDate = _endDate + interval;			
		} 

		_log.log(RTASK_TO_TASK);

		if(_nextEndDate <= _lastDateLimit) {
			next.setEndDate(to_simple_string(_nextEndDate));
			_listOfOccurrences.push_back(next);
			_occur = next;
		}
	} 
}

//This functions calculates the number of occurences for tiemd tasks. 
//It also stores every recurring tasks information in a vector
void RTask::generateOccursForTimedTask() {

	//Push in the first occurrence
	_listOfOccurrences.push_back(_occur);
	days diff;
	Task next = _occur;
	_nextEndDate = from_simple_string(next.getEndDate());

	while (_nextEndDate <= _lastDateLimit) {
		_startDate = from_simple_string(_occur.getStartDate());
		_endDate = from_simple_string(_occur.getEndDate());
		diff = _endDate - _startDate;

		if (_period == day) {		
			date_duration interval(_intervalBtwPeriod);
			_nextStartDate = _endDate + interval;
			_nextEndDate = _nextStartDate + diff;

		} else if (_period == month) {
			months interval(_intervalBtwPeriod);
			_nextStartDate = _endDate + interval;
			_nextEndDate = _nextStartDate + diff;

		} else if (_period == year) {
			years interval(_intervalBtwPeriod);
			_nextStartDate = _endDate + interval;
			_nextEndDate = _nextStartDate + diff;
		}

		_log.log(RTASK_TO_TASK);

		if (_nextEndDate <= _lastDateLimit) {
			next.setStartDate(to_simple_string(_nextStartDate));
			next.setEndDate(to_simple_string(_nextEndDate));
			_listOfOccurrences.push_back(next);
			_occur = next;
		}
	}
}


vector <Task> RTask::getListOfOccurrences() {
	return _listOfOccurrences;
}
