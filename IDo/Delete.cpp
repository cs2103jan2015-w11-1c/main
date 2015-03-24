#include "Delete.h"

bool Delete::execute(vector<string> parsedInformation, vector<Task> taskList){
	int size = parsedInformation.size();

	if(size == 1) {//delete TaskIndex
		getTaskIndexToBeDeleted(parsedInformation);
		findAndDeleteTask(taskList);
	} else{ 
		return false;
	}
	return true;
}

void Delete::getTaskIndexToBeDeleted(vector<string> parsedInformation){
	_taskIndex = atoi(parsedInformation[0].c_str());
}


void Delete::findAndDeleteTask(vector<Task> taskList){
	
	newList = taskList;
	newList.erase(newList.begin() + _taskIndex);
}

vector<Task> Delete::getNewList(){
	return newList;
}