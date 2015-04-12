//@author A0115465H
#include "Delete.h"

void Delete::deleteRecurring (vector <Task> taskList) {
	getRecurringIndexToDelete (taskList);
	checkRecurringToDelete (taskList);
}

void Delete::getRecurringIndexToDelete (vector <Task> taskList) {
	int recurringIndex;
	int size = parsedInfo.size();
	for (int i = 2 ; i < size ; i++) {
		recurringIndex = taskList[atoi(parsedInfo[i].c_str())-1].getRecurringIndex();
		if (recurringIndex != 0) {
			recurringToDelete.push_back(recurringIndex);
		}
	}
}

void Delete::checkRecurringToDelete (vector <Task> taskList) {
	if (recurringToDelete.size() == 0) {  // if user wants to batch delete a non-recurring task
			taskIndexToDelete.push_back(atoi(parsedInfo[2].c_str())-1);
	} else {
		getRecurringToDelete(taskList);
	}
}

void Delete::getRecurringToDelete (vector <Task> taskList) {
	int sizeTaskList = taskList.size();
	int sizeRecurring = recurringToDelete.size();
	for (int i = 0 ; i < sizeTaskList ; i++) {
		for (int j = 0 ; j < sizeRecurring ; j++) {	
			if (taskList[i].getRecurringIndex() == recurringToDelete[j]) {
				taskIndexToDelete.push_back(i);
			}
		}
	}
	sort(taskIndexToDelete.begin(),taskIndexToDelete.end());
}

bool Delete::isValidInput(vector <string> parsedInformation, int taskListSize) {
	parsedInfo = parsedInformation;
	bool validNumber = true;
	int size = parsedInformation.size(); 
	
	if (size < 2) {
		return false;
	}

	if (parsedInformation[1] == "all") {
		for (int i = 2 ; i < size ; i++) {
			if (atoi(parsedInformation[i].c_str()) > taskListSize ||
			atoi(parsedInformation[i].c_str()) <= 0) {
				return false;
			}
		}
	} else {
		for (int i = 1 ; i < size ; i++) {
			if (atoi(parsedInformation[i].c_str()) > taskListSize ||
			atoi(parsedInformation[i].c_str()) <= 0) {
				return false;
			}
		}
	}
	return validNumber;
}

void Delete::execute(vector<Task> &taskList) {
	int size = parsedInfo.size();
	
	if (parsedInfo[1] != "all") {   // deleting non-recurring task
		_log.log("Deleting non-recurring tasks");
		for (int i = 1 ; i < size ; i++) {
			taskIndexToDelete.push_back((atoi(parsedInfo[i].c_str()))-1);
		}
	} else {    //deleting recurring tasks
		_log.log("Batch deleting recurring tasks");
		deleteRecurring(taskList);	
	}
	
	size = taskIndexToDelete.size();
	for (int i = size - 1; i >= 0; i--) {
		 taskList.erase(taskList.begin() + taskIndexToDelete[i]);
	}
}