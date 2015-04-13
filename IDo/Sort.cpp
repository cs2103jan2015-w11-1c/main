//@author A0114010L
#include "Sort.h"

// convert the sort choices from string to enumerated sortChoice
Sort::SortChoice Sort::sortWhat(){
	if (_sortChoice == "taskname") {
		return TASKNAME;
	}
	else if (_sortChoice == "from") {
		return FROM;
	}
	else if (_sortChoice == "to") {
		return TO;
	}
	else if (_sortChoice == "by") {
		return BY;
	}
	else if (_sortChoice == "deadline") {
		return DEADLINE;
	}
	else {
		return INVALID;
	}
}

// sort by start date & time
bool Sort::sortFrom() {

	int listSize = _sortList.size();

	//Ascending Sort
	for (int i = 0; i < listSize - 1; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			if (!_sortList[j].getStartDate().empty() && !_sortList[j + 1].getStartDate().empty()) {

				date startDate(from_simple_string(_sortList[j].getStartDate()));
				date startDate2(from_simple_string(_sortList[j + 1].getStartDate()));

				if (startDate > startDate2) {
					swap(j, j + 1);
				}
				else if (startDate == startDate2) {
					if (_sortList[j].getStartTime() > _sortList[j + 1].getStartTime()) {
						swap(j, j + 1);
					}
				}
			}
			else if (_sortList[j].getStartDate().empty()) {
				swap(j, j + 1);
			}
		}
	}
	_log.log("Sort by start date and time");
	return true;
}

// sort task name alphabetically
bool Sort::sortTaskName(){

	vector <Task> swap;
	int listSize = _sortList.size();

	//sort a to z
	for (int i = 0; i < listSize - 1; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			if (_sortList[j].getTaskName() > _sortList[j + 1].getTaskName()) {
				swap.push_back(_sortList[j]);
				_sortList[j] = _sortList[j + 1];
				_sortList[j + 1] = swap[0];
				swap.clear();
			}
		}
	}
	_log.log("Sort taskname alphabetically");
	return true;
}

// sort by start time
bool Sort::sortStartTime() {
	vector <Task> swap;
	int listSize = _sortList.size();

	//Ascending Sort
	for (int i = 0; i < listSize - 1; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			if (_sortList[j].getStartDate() == _sortList[j + 1].getStartDate() 
				&& _sortList[j].getStartTime() > _sortList[j + 1].getStartTime()) {
				swap.push_back(_sortList[j]);
				_sortList[j] = _sortList[j + 1];
				_sortList[j + 1] = swap[0];
				swap.clear();
			}
		}
	}
	_log.log("Sort by start time");
	return true;
}

// sort by end date & time
bool Sort::sortToBy() {

	int listSize = _sortList.size();

	//Ascending Sort
	for (int i = 0; i < listSize - 1; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			if (!_sortList[j].getEndDate().empty() && !_sortList[j + 1].getEndDate().empty()) {
			
				date endDate(from_simple_string(_sortList[j].getEndDate()));
				date endDate2(from_simple_string(_sortList[j + 1].getEndDate()));

				if (endDate > endDate2) {
					swap(j, j + 1);
				} else if (endDate == endDate2) {
					if (_sortList[j].getEndTime() > _sortList[j + 1].getEndTime()) {
						swap(j, j + 1);
					}
				} else if (_sortList[j].getEndDate().empty()) {
					swap(j, j + 1);
				}
			} else if (_sortList[j].getEndDate().empty()) {
				swap(j, j + 1);
			}
		}
	}
	_log.log("Sort by end date and time");
	return true;
}

// sort by end time
bool Sort::sortEndTime() {
	vector <Task> swap;
	int listSize = _sortList.size();

	//Ascending Sort
	for (int i = 0; i < listSize - 1; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			if (_sortList[j].getEndDate() == _sortList[j + 1].getEndDate() 
				&& _sortList[j].getEndTime() > _sortList[j + 1].getEndTime()) {
				swap.push_back(_sortList[j]);
				_sortList[j] = _sortList[j + 1];
				_sortList[j + 1] = swap[0];
				swap.clear();
			}
		}
	}
	_log.log("Sort by end time");
	return true;
}

// sort by deadline, using start date & time of timed tasks and end date & time
// of deadline tasks
bool Sort::sortDeadLine() {

	int listSize = _sortList.size();

	for (int i = 0; i < listSize - 1; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {

			if (!_sortList[j].getStartDate().empty() && !_sortList[j + 1].getStartDate().empty()) {

				date startDate(from_simple_string(_sortList[j].getStartDate()));
				date startDate2(from_simple_string(_sortList[j + 1].getStartDate()));

				if (startDate > startDate2) {
					swap(j, j + 1);
				} else if (startDate == startDate2) {
					if (_sortList[j].getStartTime() > _sortList[j + 1].getStartTime()) {
						swap(j, j + 1);
					}
				}

			} else if (!_sortList[j].getStartDate().empty() && _sortList[j + 1].getStartDate().empty()) {

				date startDate(from_simple_string(_sortList[j].getStartDate()));
				date endDate(from_simple_string(_sortList[j + 1].getEndDate()));

				if (startDate > endDate) {
					swap(j, j + 1);
				} else if (startDate == endDate) {
					if (_sortList[j].getStartTime() > _sortList[j + 1].getEndTime()) {
						swap(j, j + 1);
					}
				}

			} else if (_sortList[j].getStartDate().empty() && _sortList[j + 1].getStartDate().empty()) {

				date endDate(from_simple_string(_sortList[j].getEndDate()));
				date endDate2(from_simple_string(_sortList[j + 1].getEndDate()));

				if (endDate > endDate2) {
					swap(j, j + 1);
				} else if (endDate == endDate2) {
					if (_sortList[j].getEndTime() > _sortList[j + 1].getEndTime()) {
						swap(j, j + 1);
					}
				}
			} else if (_sortList[j].getStartDate().empty() && !_sortList[j + 1].getStartDate().empty()) {

				date endDate(from_simple_string(_sortList[j].getEndDate()));
				date startDate(from_simple_string(_sortList[j + 1].getStartDate()));

				if (endDate > startDate) {
					swap(j, j + 1);
				} else if (endDate == startDate) {
					if (_sortList[j].getEndTime() > _sortList[j + 1].getStartTime()) {
						swap(j, j + 1);
					}
				}
			} else {
				return false;
			}
		}
	}
	_log.log("Sort by deadline");
	return true;
}

bool Sort::swap(int current, int next) {
	vector <Task> swap;

	swap.push_back(_sortList[current]);
	_sortList[current] = _sortList[next];
	_sortList[next] = swap[0];
	swap.clear();

	return true;
}

// main function that processes the command and executes them
bool Sort::execute(vector <string> parsedInformation, vector <Task> list) {
	int size = parsedInformation.size();

	if (size == 2) {
		_sortChoice = parsedInformation[1];
		_sortList = list;
	}
	else {
		cout << "[Error] No such sorting!" << endl;
		return false;
	}

	SortChoice sortType = sortWhat();

	switch (sortType) {
		case TASKNAME:
			sortTaskName();
			break;
		case FROM:
			sortFrom();
			break;
		case TO:
			sortToBy();
			break;
		case BY:
			sortToBy();
			break;
		case DEADLINE:
			sortDeadLine();
			break;
		case INVALID:
			return false;
	}

	return true;
}

vector<Task> Sort::getSortedList() {
	return _sortList;
}