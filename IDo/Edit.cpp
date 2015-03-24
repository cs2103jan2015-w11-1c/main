#include "Edit.h"

bool Edit::execute(vector<string> parsedInfo, vector<Task> taskListFromLogic){

	parsedInformation = parsedInfo;
	taskList = taskListFromLogic;

	parsedInfoSize = parsedInformation.size();
	numberOfTasks = taskList.size();
	cout<<"Size:"<<parsedInfoSize;

	if(parsedInfoSize == 4){
		editNumber = atoi(parsedInformation[1].c_str());
		editType = parsedInformation[2];
		editContent = parsedInformation[3];
		if(checkAndProcess()){
			cout<<"Edit Successfully"<<endl;
		} else{
			cout<<"Edit Unsucessful!"<<endl;
		}
	} else{
		return false;
	}

	return true;
}

bool Edit::checkAndProcess(){
	
	//check if task number is available
	if(editNumber > numberOfTasks){
		return false;
	}

	//edit task type
	if(editType == "taskname"){
		taskList[editNumber-1].setTaskName(editContent);
	} else if(editType == "startdate"){
		taskList[editNumber-1].setStartDate(editContent);
	} else if(editType == "starttime"){
		taskList[editNumber-1].setStartTime(editContent);
	} else if(editType == "enddate"){
		taskList[editNumber-1].setEndDate(editContent);
	} else if(editType == "endtime"){
		taskList[editNumber-1].setEndTime(editContent);
	} else if(editType == "deadline"){
		taskList[editNumber-1].setDeadline(editContent);
	} else {
		return false;
	}

	return true;
}

vector<Task> Edit::getNewList(){
	return taskList;
}
