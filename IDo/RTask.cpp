#include "RTask.h"

RTask::RTask(){
}

RTask::~RTask(){
}

vector <Task> RTask::getListOfOccurrences() {
	return _listOfOccurrences;
}

void RTask::setAbstrInfo(vector <string> parsedInfo) {
	//initialise abstract task attributes
	_abstract.setTaskName(parsedInfo[1]);
	
	if (parsedInfo[4] == "every"){	//deadline recurring task
		_abstract.setEndTime(parsedInfo[3]);
	}
	else if (parsedInfo[6] == "every") {	//timed task recurring task
		_abstract.setEndTime(parsedInfo[5]);
		_abstract.setStartTime(parsedInfo[3]);
	}
}

void RTask::setNoOfOccurrences(int noOfOccurrences) {
	_noOfOccurrences = noOfOccurrences;
}

void RTask::setPeriod(string period) {

	if (period == "day") {
		_period = day;
	}
	else if (period == "month") {
		_period = month;
	}
	else if (period == "year") {
		_period = year;
	}
}

void RTask::setPeriod2(string period) {
	if (period == "day") {
		_secPeriod = day;
	}
	else if (period == "month") {
		_secPeriod = month;
	}
	else if (period == "year") {
		_secPeriod = year;
	}
}


void RTask::setInterval(int interval) {
	_intervalBtwPeriod = interval;
}

void RTask::setLimit(string limit) {

	_limit = atoi(limit.c_str());
	if (_period == 0 && _secPeriod == 1) {
		_noOfOccurrences = _limit*30/_intervalBtwPeriod;
	} else if (_period == 0 && _secPeriod == 2) {
		_noOfOccurrences = _limit*365/_intervalBtwPeriod;
	} else if (_period == 1 && _secPeriod == 2) {
		_noOfOccurrences = _limit*12/_intervalBtwPeriod;
	} else if (_period == _secPeriod) {
		_noOfOccurrences = _limit/_intervalBtwPeriod;
	} 
}

void RTask::setFirstOccur(vector<string> parsedInfo){
	_occur.setTaskName(_abstract.getTaskName());
	if (parsedInfo.size() == 7) {	//deadline recurring task without limit
		_occur.setEndTime(_abstract.getEndTime());
		cout << "parsedinformation two : " << parsedInfo[2] << endl;
		_occur.setEndDate(parsedInfo[2]);
	} else if(parsedInfo.size() == 9) { //timed task recurring without limit
		_occur.setStartTime(_abstract.getStartTime());
		_occur.setEndTime(_abstract.getEndTime());
		_occur.setStartDate(parsedInfo[2]);
		_occur.setEndDate(parsedInfo[4]);
	} else if (parsedInfo.size() == 10) { //deadline recurring task with limit
	//	_occur.setStartTime(_abstract.getStartTime());
		_occur.setEndTime(_abstract.getEndTime());
	//	_occur.setStartDate(parsedInfo[3]);
		_occur.setEndDate(parsedInfo[2]);
	} else if(parsedInfo.size() == 12) { //timed task recurring with limit
		_occur.setStartTime(_abstract.getStartTime());
		_occur.setEndTime(_abstract.getEndTime());
		_occur.setStartDate(parsedInfo[2]);
		_occur.setEndDate(parsedInfo[4]);
	}
}
/*
void RTask::stringToIntDate(string date, int *day, int *month, int *yr) {
	int pos = date.find_first_of("/");
	int pos2 = date.find_last_of("/");
	*day = stoi(date.substr(pos2 + 1));
	*month = stoi(date.substr(pos + 1, pos2 - pos));	//eg 2 or 10
	*yr = stoi(date.substr(0, 4));	//eg 2014

}*/

void RTask::generateOccurs() {

	_listOfOccurrences.push_back(_occur);
	int count = 1;
	cout << "_noOfOccurrences: " << _noOfOccurrences << endl;

	Task next = _occur;

	while (count < _noOfOccurrences) {
		if (_period == day) {	//for deadline task
			date endDate(from_simple_string(_occur.getEndDate()));
			date_duration interval(_intervalBtwPeriod);
			date nextEndDate = endDate + interval;
			next.setEndDate(to_simple_string(nextEndDate));

			_listOfOccurrences.push_back(next);
			_occur = next;
		}
		else if (_period == month) {
			
			date endDate(from_simple_string(_occur.getEndDate()));
			months interval(_intervalBtwPeriod);
			date nextEndDate = endDate + interval;
			next.setEndDate(to_simple_string(nextEndDate));

			_listOfOccurrences.push_back(next);
			_occur = next;
		}
		else if (_period == year) {
			
			date endDate(from_simple_string(_occur.getEndDate()));
			years interval(_intervalBtwPeriod);
			date nextEndDate = endDate + interval;
			next.setEndDate(to_simple_string(nextEndDate));

			_listOfOccurrences.push_back(next);
			_occur = next;
		}
		count++;
	}
}

void RTask::generateOccursForTimedTask() {

	_listOfOccurrences.push_back(_occur);
	int count = 1;

	Task next = _occur;

	while (count < _noOfOccurrences) {
		if (_period == day) {	//for deadline task
			date startDate(from_simple_string(_occur.getStartDate()));
			date endDate(from_simple_string(_occur.getEndDate()));
			date_duration interval(_intervalBtwPeriod);
			date nextStartDate = startDate + interval;
			date nextEndDate = endDate + interval;
			next.setStartDate(to_simple_string(nextStartDate));
			next.setEndDate(to_simple_string(nextEndDate));

			_listOfOccurrences.push_back(next);
			_occur = next;
		}
		else if (_period == month) {
			date startDate(from_simple_string(_occur.getStartDate()));
			date endDate(from_simple_string(_occur.getEndDate()));
			months interval(_intervalBtwPeriod);
			date nextStartDate = startDate + interval;
			date nextEndDate = endDate + interval;
			next.setStartDate(to_simple_string(nextStartDate));
			next.setEndDate(to_simple_string(nextEndDate));

			_listOfOccurrences.push_back(next);
			_occur = next;
		}
		else if (_period == year) {
			date startDate(from_simple_string(_occur.getStartDate()));
			date endDate(from_simple_string(_occur.getEndDate()));
			years interval(_intervalBtwPeriod);
			date nextStartDate = startDate + interval;
			date nextEndDate = endDate + interval;
			next.setStartDate(to_simple_string(nextStartDate));
			next.setEndDate(to_simple_string(nextEndDate));

			_listOfOccurrences.push_back(next);
			_occur = next;
		}
		count++;
	}
}