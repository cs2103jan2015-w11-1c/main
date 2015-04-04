#include "RecurringTask.h"

AbstractRTask::AbstractRTask(){
}

AbstractRTask::~AbstractRTask(){
}

string AbstractRTask::getTaskName() {
	return _taskName;
}

string AbstractRTask::getLastDate() {
	return _lastDate;
}

int AbstractRTask::getIntervalBtwPeriod() {
	return _intervalBtwPeriod;
}

Period AbstractRTask::getPeriod() {
	return _period;
}

void AbstractRTask::setTaskName(string name) {
	_taskName = name;
}

void AbstractRTask::setLastDate(string date) {
	_lastDate = date;
}

void AbstractRTask::setInterval(int number) {
	_intervalBtwPeriod = number;
}

void AbstractRTask::setPeriod(string period) {
	if (period == "hour") {
		_period = hour;
	} else if (period == "day") {
		_period = day;
	} else if (period == "week") {
		_period = week;
	} else if (period == "month") {
		_period = month;
	} else if (period == "year") {
		_period = year;
	}
}