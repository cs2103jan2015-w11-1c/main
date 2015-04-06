#include "Delete.h"

bool Delete::execute(vector<string> parsedInformation, vector<Task> taskList){
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

void Delete::findAndDeleteTask(vector<Task> taskList){
	
	_newList = taskList;
	_newList.erase(_newList.begin() + _taskIndex - 1);
}

vector<Task> Delete::getNewList(){
	return _newList;
}