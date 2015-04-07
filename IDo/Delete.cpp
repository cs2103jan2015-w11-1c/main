#include "Delete.h"

bool Delete::isValidInput(vector <string> parsedInformation, int taskListSize) {
	bool validNumber = true;
	int size = parsedInformation.size(); 
	for (int i = 1 ; i < size ; i++) {
		if (atoi(parsedInformation[i].c_str()) > taskListSize || atoi(parsedInformation[i].c_str()) <= 0) {
			return false;
		}
	}
	return validNumber;
}

void Delete::execute(vector<string> parsedInformation, vector<Task> &taskList){
	int size = parsedInformation.size();
	vector <int> listToDelete;
	for (int i = 1 ; i < size ; i++) {
		listToDelete.push_back((atoi(parsedInformation[i].c_str()))-1);
	}

	sort(listToDelete.begin(),listToDelete.end());
	
	size = listToDelete.size();
	for (int i = size - 1; i >= 0; i--) {
		 taskList.erase(taskList.begin() + listToDelete[i]);
	}
}