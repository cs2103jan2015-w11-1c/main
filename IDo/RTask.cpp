#include "RecurringTask.h"

RTask::RTask(){
	_status = notdone;
	_label = "misc";
	_priority = low;
}

RTask::~RTask(){
}

void RTask::setAbstrInfo(vector <string> parsedInfo) {
	//initialise abstract task attributes
	setTaskName(parsedInfo[1]);
	setInterval(1);	//parsedInfo[6]
	setLastDate("2015/12/12");	//parsedInfo[8]
	setPeriod("day");	//parsedInfo[7]
}

string RTask::getStartDate() {
	return _startDate;
}

string RTask::getStartTime() {
	return _startTime;
}

string RTask::getEndDate() {
	return _endDate;
}

string RTask::getEndTime() {
	return _endTime;
}

Status RTask::getStatus() {
	return _status;
}

Priority RTask::getPriority() {
	return _priority;
}

string RTask::getLabel() {
	return _label;
}

void RTask::setStartDate(string date) {
	_startDate = date;
}

void RTask::setStartTime(string time) {
	_startTime = time;
}

void RTask::setEndDate(string date) {
	_endDate = date;
}

void RTask::setEndTime(string time) {
	_endTime = time;
}

void RTask::setStatus(Status state) {
	_status = state;
}

void RTask::setPriority(Priority priority) {
	_priority = priority;
}

void RTask::setLabel(string label) {
	_label = label;
}

RTask RTask::getNextOccurrence() {
	return *(_nextOccurrence);
}

void RTask::setNextOccurrence(vector <string> parsedInfo) {
	if (_endDate != getLastDate())  {
		//create new occurrence 
		//

		RTask *nextR;
		nextR = new RTask;
		(*nextR).setAbstrInfo(parsedInfo);	//the same info as current occurrence

		if (getPeriod() == hour) {
			int taskDuration = stoi(_endTime) - stoi(_startTime);
			int endtime = stoi(_endTime);
			int starttime = stoi(_startTime);
			endtime += (taskDuration + getIntervalBtwPeriod());
			(*nextR).setEndTime(to_string(endtime));
			starttime += (taskDuration + getIntervalBtwPeriod());
			(*nextR).setStartTime(to_string(starttime));
			(*nextR).setStartDate(_startDate);
			(*nextR).setEndDate(_endDate);
		}
		else if (getPeriod() == day) {	//task duration must be in same month
			int i = _endDate.find_last_of("/");
			int enddate = stoi(_endDate.substr(i + 1));
			i = _startDate.find_last_of("/");
			int startdate = stoi(_startDate.substr(i + 1));
			int taskDuration = enddate - startdate;

			enddate += (taskDuration + getIntervalBtwPeriod());
			(*nextR).setEndDate(to_string(enddate));
			startdate += (taskDuration + getIntervalBtwPeriod());
			(*nextR).setStartDate(to_string(startdate));
			(*nextR).setStartTime(_startTime);
			(*nextR).setEndTime(_endTime);
		}
		_nextOccurrence = nextR;	//save in private

		delete nextR;
	}
	
}