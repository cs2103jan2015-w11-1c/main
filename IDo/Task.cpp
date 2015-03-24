#include "Logic.h"
#include "UserInterface.h"
#include "Parser.h"
#include "Task.h"
#include <sstream>

Task::Task(){
	_status=INCOMPLETE;
	_priority=LOW;
}

Task::~Task(){
}

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

Status Task::getStatus() {
	return _status;
}

Priority Task::getPriority() {
	return _priority;
}

Label Task::getLabel() {
	return _label;
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

void Task::setStatus (Status state) {
	_status=state;
}

void Task::setPriority (Priority priority) {
	_priority=priority;
} 

void Task::setLabel (Label label) {
	_label = label;
}