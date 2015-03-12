#include "Logic.h"
#include "UserInterface.h"
#include "Parser.h"
#include "Task.h"
#include "Storage.h"
#include <sstream>

string Task::getTaskName () {
	return _taskName;
}

string Task::getStartDate () {
	return _startDate;
}

string Task::getStartTime() {
	return _startTime;
}

string Task::getEndDate() {
	return _endDate;
}

string Task::getEndTime() {
	return _endTime;
}

string Task::getDeadline() {
	return _deadline;
}

void Task::setTaskName (string name) {
	_taskName=name;
}

void Task::setStartDate (string date) {
	_startDate=date;
}

void Task::setStartTime (string time) {
	_startTime=time;
}

void Task::setEndDate (string date) {
	_endDate=date;
}

void Task::setEndTime (string time) {
	_endTime=time;
}

void Task::setDeadline (string date) {
	_deadline=date;
}