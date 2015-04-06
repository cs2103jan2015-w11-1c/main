#include "RTask.h"

RTask::RTask(){
}

RTask::~RTask(){
}

void RTask::setAbstrInfo(vector <string> parsedInfo) {
	//initialise abstract task attributes
	_abstract.setTaskName(parsedInfo[1]);
	if (parsedInfo[4] == "every"){	//deadline recurring task
		_abstract.setEndTime(parsedInfo[3]);
	}
	else if (parsedInfo[6] == "every") {	
		_abstract.setEndTime(parsedInfo[5]);
		_abstract.setStartTime(parsedInfo[3]);
	}
}

void RTask::setNoOfOccurrences(int noOfOccurrences) {
	_noOfOccurrences = noOfOccurrences;
}

void RTask::setPeriod(Period period) {
	_period = period;
}

void RTask::setInterval(int interval) {
	_intervalBtwPeriod = interval;
}

void RTask::setFirstOccur(vector<string> parsedInfo){
	_occur.setTaskName(_abstract.getTaskName());
	if (parsedInfo.size() == 7) {	//deadline recurring task
		_occur.setEndTime(_abstract.getStartTime());
		_occur.setEndDate(parsedInfo[3]);
	} else if (parsedInfo.size() == 9) {
		_occur.setStartTime(_abstract.getStartTime());
		_occur.setEndTime(_abstract.getEndTime());
		_occur.setStartDate(parsedInfo[3]);
		_occur.setEndDate(parsedInfo[5]);
	}
}

void RTask::stringToIntDate(string date, int *day, int *month, int *yr) {
	int pos = date.find_first_of("/");
	int pos2 = date.find_last_of("/");
	*day = stoi(date.substr(pos2 + 1));
	*month = stoi(date.substr(pos + 1, pos2 - pos));	//eg 2 or 10
	*yr = stoi(date.substr(0, 4));	//eg 2014

}

void RTask::generateOccurs() {

	_listOfOccurrences.push_back(_occur);
	int count = 1;
	int currEndDay, currEndMonth, currEndYr;
	int currStartDay, currStartMonth, currStartYr;

	stringToIntDate(_occur.getEndDate(), &currEndDay, &currEndMonth, &currEndYr);
	stringToIntDate(_occur.getStartDate(), &currStartDay, &currStartMonth, &currStartYr);

	Task next = _occur;

	while (count < _noOfOccurrences) {
		if (_period == day) {	//for deadline task

			currEndDay = currEndDay + _intervalBtwPeriod;
			string newEndDate = to_string(currEndYr) + "/"
				+ to_string(currEndMonth) + "/" + to_string(currEndDay);
			next.setEndDate(newEndDate);


			_listOfOccurrences.push_back(next);
		}
		else if (_period == month) {
			currEndMonth = currEndMonth + _intervalBtwPeriod;
			string newEndDate = to_string(currEndYr) + "/"
				+ to_string(currEndMonth) + "/" + to_string(currEndDay);
			next.setEndDate(newEndDate);

			next.setEndDate(newEndDate);

			_listOfOccurrences.push_back(next);
		}
		else if (_period == year) {
			currEndYr = currEndYr + _intervalBtwPeriod;
			string newEndDate = to_string(currEndYr) + "/"
				+ to_string(currEndMonth) + "/" + to_string(currEndDay);
			next.setEndDate(newEndDate);

			next.setEndDate(newEndDate);

			_listOfOccurrences.push_back(next);
		}
		count++;
	}
}