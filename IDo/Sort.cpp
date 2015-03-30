#include "Sort.h"

bool Sort::execute(vector <string> parsedInformation, vector <Task> list) {
	int size = parsedInformation.size();

	if(size == 2) {
		_sortChoice = parsedInformation[1]; 
		sortList = list;
	} else {
		cout << "[Error] No such Sorting!" << endl;
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

Sort::SortChoice Sort::sortWhat(){
	if (_sortChoice == "taskname") { 
		return TASKNAME;
	} else if (_sortChoice == "from") {
		return FROM;
	} else if (_sortChoice == "to") {
		return TO;
	} else if (_sortChoice == "by") {
		return BY;
	} else if (_sortChoice == "deadline") {
		return DEADLINE;
	} else {
		return INVALID;
	}
}

bool Sort::sortTaskName(){
		
	vector <Task> swap;
	int listSize = sortList.size();

	//sort a to z
	for (int i = 0; i < listSize - 1; i++ ) {
		for(int j = 0; j < listSize - i - 1; j++) {
			if(sortList[j].getTaskName() > sortList[j+1].getTaskName()) {
				swap.push_back(sortList[j]);
				sortList[j]= sortList[j+1];
				sortList[j+1] = swap[0];
				swap.clear();
			}
		}
	}

	return true;
}


bool Sort::sortFrom() {
	vector <Task> swap;
	int listSize = sortList.size();

	//Ascending Sort
	for (int i = 0; i < listSize - 1; i++ ) {
		for(int j = 0; j < listSize - i - 1; j++) {
			if(sortList[j].getStartDate() > sortList[j+1].getStartDate()) {
				swap.push_back(sortList[j]);
				sortList[j]= sortList[j+1];
				sortList[j+1] = swap[0];
				swap.clear();
			}
		}
	}

	sortStartTime();

	for (int i = 0; i < listSize - 1; i++ ) {
		for(int j = 0; j < listSize - i - 1; j++) {
			if(sortList[j].getStartDate().empty()) {
				swap.push_back(sortList[j]);
				sortList[j]= sortList[j+1];
				sortList[j+1] = swap[0];
				swap.clear();
			}
		}
	}

	return true;
}

bool Sort::sortStartTime() {
	vector <Task> swap;
	int listSize = sortList.size();

	//Ascending Sort
	for (int i = 0; i < listSize - 1; i++ ) {
		for(int j = 0; j < listSize - i - 1; j++) {
			if(sortList[j].getStartDate() == sortList[j+1].getStartDate() && sortList[j].getStartTime() > sortList[j+1].getStartTime()) {
				swap.push_back(sortList[j]);
				sortList[j]= sortList[j+1];
				sortList[j+1] = swap[0];
				swap.clear();
			}
		}
	}

	return true;
}

bool Sort::sortToBy() {
	vector <Task> swap;
	int listSize = sortList.size();

	//Ascending Sort
	for (int i = 0; i < listSize - 1; i++ ) {
		for(int j = 0; j < listSize - i - 1; j++) {
			if(sortList[j].getEndDate() > sortList[j+1].getEndDate()) {
				swap.push_back(sortList[j]);
				sortList[j]= sortList[j+1];
				sortList[j+1] = swap[0];
				swap.clear();
			}
		}
	}

	sortEndTime();

	return true;
}

bool Sort::sortEndTime() {
	vector <Task> swap;
	int listSize = sortList.size();

	//Ascending Sort
	for (int i = 0; i < listSize - 1; i++ ) {
		for(int j = 0; j < listSize - i - 1; j++) {
			if(sortList[j].getEndDate() == sortList[j+1].getEndDate() && sortList[j].getEndTime() > sortList[j+1].getEndTime()) {
				swap.push_back(sortList[j]);
				sortList[j]= sortList[j+1];
				sortList[j+1] = swap[0];
				swap.clear();
			}
		}
	}

	return true;
}

bool Sort::sortDeadLine() {

	vector <Task> swap;
	int listSize = sortList.size();

	for (int i = 0; i < listSize - 1; i++ ) {
		for(int j = 0; j < listSize - i - 1; j++) {
			if(!sortList[j].getStartDate().empty() && !sortList[j+1].getStartDate().empty()) {
				if (sortList[j].getStartDate() > sortList[j+1].getStartDate()) {
					swap.push_back(sortList[j]);
					sortList[j]= sortList[j+1];
					sortList[j+1] = swap[0];
					swap.clear();
				} else if (sortList[j].getStartDate() == sortList[j+1].getStartDate()) {
					if (sortList[j].getStartTime() > sortList[j+1].getStartTime()) {
					swap.push_back(sortList[j]);
					sortList[j]= sortList[j+1];
					sortList[j+1] = swap[0];
					swap.clear();
					}
				}
			} else if (!sortList[j].getStartDate().empty() && sortList[j+1].getStartDate().empty()) {
				if(sortList[j].getStartDate() > sortList[j+1].getEndDate()) {
					swap.push_back(sortList[j]);
					sortList[j]= sortList[j+1];
					sortList[j+1] = swap[0];
					swap.clear();
				} else if (sortList[j].getStartDate() == sortList[j+1].getEndDate()) {
					if (sortList[j].getStartTime() > sortList[j+1].getEndTime()) {
						swap.push_back(sortList[j]);
						sortList[j]= sortList[j+1];
						sortList[j+1] = swap[0];
						swap.clear();
					}
				}
			} else if (sortList[j].getStartDate().empty() && sortList[j+1].getStartDate().empty()) {
				if(sortList[j].getEndDate() > sortList[j+1].getEndDate()) {
					swap.push_back(sortList[j]);
					sortList[j]= sortList[j+1];
					sortList[j+1] = swap[0];
					swap.clear();
				} else if (sortList[j].getEndDate() == sortList[j+1].getEndDate()) {
					if (sortList[j].getEndTime() > sortList[j+1].getEndTime()) {
						swap.push_back(sortList[j]);
						sortList[j]= sortList[j+1];
						sortList[j+1] = swap[0];
						swap.clear();
					}
				}
			} else if (sortList[j].getStartDate().empty() && !sortList[j+1].getStartDate().empty()) {
				if(sortList[j].getEndDate() > sortList[j+1].getStartDate()) {
					swap.push_back(sortList[j]);
					sortList[j]= sortList[j+1];
					sortList[j+1] = swap[0];
					swap.clear();
				} else if (sortList[j].getEndDate() == sortList[j+1].getStartDate()) {
					if (sortList[j].getEndTime() > sortList[j+1].getStartTime()) {
						swap.push_back(sortList[j]);
						sortList[j]= sortList[j+1];
						sortList[j+1] = swap[0];
						swap.clear();
					}
				}
			} else {
				return false;
			}
		}
	}


	return true;
}


vector<Task> Sort::getSortedList() {
	return sortList;
}