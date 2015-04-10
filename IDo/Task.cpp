#include "Task.h"

Task::Task(){
	_status = notdone;
	_priority = low;
	_label = "none";
	_recurringIndex = 0;
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

string Task::getLabel() {
	return _label;
}

int Task::getRecurringIndex() {
	return _recurringIndex;
}

void Task::setTaskName(string name) {
	_taskName = name;
}

void Task::setStartDate(string date) {
	_startDate = date;
}

void Task::setStartTime(string time) {
	_startTime = time;
}

void Task::setEndDate(string date) {
	_endDate = date;
}

void Task::setEndTime(string time) {
	_endTime = time;
}

void Task::setDeadline(string date) {
	_deadline = date;
}

void Task::setStatus(Status state) {
	_status = state;
}

void Task::setPriority(Priority priority) {
	_priority = priority;
} 

void Task::setLabel(string label) {
	_label = label;
}

void Task::setRecurringIndex(int index) {
	_recurringIndex = index;
}