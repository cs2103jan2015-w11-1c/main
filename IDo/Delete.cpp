#include "Delete.h"

bool Delete::isValidInput(vector <string> parsedInformation, int taskListSize) {
	bool validNumber = true;
	int size = parsedInformation.size(); 
	if (size < 3) {
		return false;
	}
	if (parsedInformation[1] == "all") {
		for (int i = 2 ; i < size ; i++) {
			if (atoi(parsedInformation[i].c_str()) > taskListSize || atoi(parsedInformation[i].c_str()) <= 0) {
				return false;
			}
		}
	} else {
		for (int i = 1 ; i < size ; i++) {
			if (atoi(parsedInformation[i].c_str()) > taskListSize || atoi(parsedInformation[i].c_str()) <= 0) {
				return false;
			}
		}
	}
	return validNumber;
}

void Delete::execute(vector<string> parsedInformation, vector<Task> &taskList){
	int size = parsedInformation.size();
	int sizeVector = taskList.size();
	int recurringIndex;
	vector <int> listToDelete;
	vector <int> recurringToDelete;
	if (parsedInformation[1] != "all") {
		for (int i = 1 ; i < size ; i++) {
			listToDelete.push_back((atoi(parsedInformation[i].c_str()))-1);
		}
	} else {
		for (int i = 2 ; i < size ; i++) {
			recurringIndex = taskList[atoi(parsedInformation[i].c_str())-1].getRecurringIndex();
			recurringToDelete.push_back(recurringIndex);
		}
	}

	int sizeRecurring = recurringToDelete.size();
	for (int i = 0 ; i < sizeVector ; i++) {
		for (int j = 0 ; j < sizeRecurring ; j++) {
			if (taskList[i].getRecurringIndex() == recurringToDelete[j]) {
				listToDelete.push_back(i);
			}
		}
	}

	sort(listToDelete.begin(),listToDelete.end());
	
	size = listToDelete.size();
	for (int i = size - 1; i >= 0; i--) {
		 taskList.erase(taskList.begin() + listToDelete[i]);
	}
}