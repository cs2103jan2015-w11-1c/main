#include "Edit.h"

bool Edit::execute(vector<string> parsedInfo, vector<Task> taskListFromLogic){

	_parsedInformation = parsedInfo;
	_taskList = taskListFromLogic;

	_parsedInfoSize = _parsedInformation.size();
	_numberOfTasks = _taskList.size();

	if(_parsedInfoSize == 4){
		_editNumber = atoi(_parsedInformation[1].c_str());
		_editType = _parsedInformation[2];
		_editContent = _parsedInformation[3];
		if(checkAndProcess()){
			cout<< endl << "Edited Successfully"<<endl;
		} else {
			cout<< endl << "Edit Unsuccessful!"<<endl;
		}
		cout << endl;
	} else {
		return false;
	}

	return true;
}

bool Edit::checkAndProcess(){
	
	//check if task number is available
	if(_editNumber > _numberOfTasks){
		return false;
	}

	//edit task type
	if(_editType == "taskname"){
		_taskList[_editNumber-1].setTaskName(_editContent);
	} else if(_editType == "startdate"){
		_taskList[_editNumber-1].setStartDate(_editContent);
	} else if(_editType == "starttime"){
		_taskList[_editNumber-1].setStartTime(_editContent);
	} else if(_editType == "enddate"){
		_taskList[_editNumber-1].setEndDate(_editContent);
	} else if(_editType == "endtime"){
		_taskList[_editNumber-1].setEndTime(_editContent);
	} else if(_editType == "deadline"){
		_taskList[_editNumber-1].setDeadline(_editContent);
	} else {
		return false;
	}

	return true;
}

vector<Task> Edit::getNewList(){
	return _taskList;
}
