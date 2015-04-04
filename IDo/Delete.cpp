#include "Delete.h"

bool Delete::execute(vector<string> parsedInformation, vector<AllTasks> taskList){
	int size = parsedInformation.size();

	if(size == 2) {//delete TaskIndex
		getTaskIndexToBeDeleted(parsedInformation);
		findAndDeleteTask(taskList);
	} else { 
		return false;
	}
	return true;
}

void Delete::getTaskIndexToBeDeleted(vector<string> parsedInformation){
	_taskIndex = atoi(parsedInformation[1].c_str());
}

void Delete::findAndDeleteTask(vector<AllTasks> taskList){
	
	newList = taskList;
	newList.erase(newList.begin() + _taskIndex - 1);
}

vector<AllTasks> Delete::getNewList(){
	return newList;
}