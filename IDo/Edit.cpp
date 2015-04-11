#include "Edit.h"

const string ERROR_STARTTIME = "[ERROR] Start Time is Over";
const string ERROR_ENDTIME = "[ERROR] End Time is Over";
const string ERROR_ENDLESSTHANSTART = "[ERROR] End-Time cannot be earlier than Start-Time";
const string ERROR_INVALIDINPUT = "[ERROR] Invalid Inputs";
const string ERROR_STARTDATE_LATER_THAN_ENDDATE = "[ERROR] Start-Date cannot be later than End-Date";
const string ERROR_ENDDATE_EARLIER_THAN_STARTDATE = "[ERROR] End-Date cannot be earlier than Start-Date";
const string ERROR_ENDDATETIME_EARLIER_THAN_STARTDATETIME = "[ERROR] End-Date-Time cannot be earlier than Start-Date-Time";
const string ERROR_STARTDATETIME_LATER_THAN_STARTDATETIME = "[ERROR] Start-Date-Time cannot be later than End-Date-Time";
const string TASK_NAME = "taskname";
const string START_DATE = "startdate";
const string END_DATE = "enddate";
const string START_TIME = "starttime";
const string END_TIME = "endtime";

bool Edit::execute(vector<string> parsedInfo, vector<Task> taskListFromLogic){

	_parsedInformation = parsedInfo;
	_taskList = taskListFromLogic;

	_parsedInfoSize = _parsedInformation.size();
	_numberOfTasks = _taskList.size();

	if(_parsedInfoSize == 4) {
		_editNumber = atoi(_parsedInformation[1].c_str()) - 1;
		_editType = _parsedInformation[2];
		_editContent = _parsedInformation[3];

		if(checkAndProcess()){
			return true;
		} else {
			return false;
		}
	} else {
		printMessage(ERROR_INVALIDINPUT);
		return false;
	}
}

bool Edit::checkAndProcess(){
	
	//Returns false if task number is unavailable
	if(_editNumber > _numberOfTasks){
		return false;
	}

	//Match the type of task to be edited
	if(_editType == TASK_NAME){
		_taskList[_editNumber].setTaskName(_editContent);
	} else if(_editType == START_DATE){
		if(check.isDateValid(_editContent)) {
			if(compareDates(check.getFormattedDates(), _taskList[_editNumber].getEndDate())) {
				printMessage(ERROR_STARTDATE_LATER_THAN_ENDDATE);
				return false;
			} else if(compareSameDates(check.getFormattedDates(), _taskList[_editNumber].getEndDate())){
				if(_taskList[_editNumber].getStartTime()>_taskList[_editNumber].getEndTime()) {
					printMessage(ERROR_STARTDATETIME_LATER_THAN_STARTDATETIME);
					return false;
				} else {
					_taskList[_editNumber].setStartDate(check.getFormattedDates());
				}
			} else {
				_taskList[_editNumber].setStartDate(check.getFormattedDates());
			}
		} else {
			return false;
		}
	} else if(_editType == START_TIME){

		if(isPossibleTime(_editContent)) {
			if(_taskList[_editNumber].getStartDate() == check.getTodayDate()) {
				if(_editContent < getTodayTime()){
					printMessage(ERROR_STARTTIME);
					return false;
				} 
			}
			_taskList[_editNumber].setStartTime(_editContent);
		} else {
			return false;
		}

	} else if(_editType == END_DATE){
		if(check.isDateValid(_editContent)) {
			if(!compareDates(check.getFormattedDates(), _taskList[_editNumber].getStartDate())) {
				printMessage(ERROR_ENDDATE_EARLIER_THAN_STARTDATE);
				return false;
			} else if(compareSameDates(check.getFormattedDates(), _taskList[_editNumber].getStartDate())){
				if(_taskList[_editNumber].getStartTime()>_taskList[_editNumber].getEndTime()) {
					printMessage(ERROR_ENDDATETIME_EARLIER_THAN_STARTDATETIME);
					return false;
				} else {
					_taskList[_editNumber].setEndDate(check.getFormattedDates());
				}
			} else {
				_taskList[_editNumber].setEndDate(check.getFormattedDates());
			}
		} else {
			return false;
		}
	} else if(_editType == END_TIME){
		if(isPossibleTime(_editContent)) {
			if(_taskList[_editNumber].getEndDate() == check.getTodayDate()) {

				if(_editContent < getTodayTime()){
					printMessage(ERROR_ENDTIME);
					return false;
				} 

				if(_taskList[_editNumber].getStartDate() == _taskList[_editNumber].getEndDate() && 
					_editContent < _taskList[_editNumber].getStartDate()) {
					printMessage(ERROR_ENDLESSTHANSTART);
				}
			}
			_taskList[_editNumber].setEndTime(_editContent);
		} else {
			return false;
		}
	}  else {
		return false;
	}

	return true;
}

vector<Task> Edit::getList(){
	return _taskList;
}

//Pre: Takes in a string
//Post: Return true if string is a valid time
//		Return false if string is not a valid time
bool Edit::isPossibleTime(string time) {
	if(isPossibleTimeFormat(time) && isTimeFormat(time)) {
		return true;
	} else {
		return false;
	}
	return true;
}

//This checks if timeformat i.e. HHMM and time value is valid
//Post: Returns true if valid, Returns false if invalid
bool Edit::isPossibleTimeFormat(string time){
	
	if(time.size()>4) {
		return false;
	}

	for(int i = 0; i < 4; i++) { 
		if(!isdigit(time[i])){
			return false;
		}
	}

	int minute = atoi(time.c_str());
	
	if(minute > 2359) {
		cout << "[Error] Outside time range 0000 to 2359" << endl;
		return false;
	}

	_time = time;
		
	return true;
}

//Post: Takes in a string
//Post: Return false if time is not 4 digit number
//		Return true if time is 4 digit number
bool Edit::isTimeFormat(string time) {

	if(time.size()>4) {
		return false;
	}

	for(int i = 0; i < 4; i++) { 
		if(!isdigit(time[i])){
			return false;
		}
	}

	return true;
}


//Post: Returns today's time as string
string Edit::getTodayTime() {

	string todayTime;
	time_t currentTime;
	struct tm localTime;

	time( &currentTime );					  // Get the current time
	localtime_s( &localTime , &currentTime );  // Convert the current time to the local time

	int hour = localTime.tm_hour;
	int min  = localTime.tm_min;

	if(hour < 10) {
		todayTime = '0' + to_string(hour * 100 + min);
	} else {
		todayTime = to_string(hour * 100 + min);
	}

	return todayTime;
}

//Pre: Takes in two different dates
//Post: Return true if date1 is later than or equal to date2
//		Return false if date1 is earlier than date2
bool Edit::compareDates(string date1, string date2) {

	//Return false if function takes in 1 or 0 parmeters
	if(date1.empty() || date2.empty()) {
		return false;
	} 

	date d1(from_simple_string(date1));
	date d2(from_simple_string(date2));

	if(d1 > d2) {
		return true;
	} else {
		return false;
	}
}

//Pre: Takes in 2 dates string
//Post: Return true if date1 equals to date2
//		Return false if both not equal
bool Edit::compareSameDates(string date1, string date2) {

	
	//Return false if function takes in 1 or 0 parmeters
	if(date1.empty() || date2.empty()) {
		return false;
	} 

	date d1(from_simple_string(date1));
	date d2(from_simple_string(date2));

	if(d1 == d2) {
		return true;
	} else {
		return false;
	}
}

//Pre: Takes in a string 
//Post: Print out the intended message
void Edit::printMessage(string message) {
	cout << endl << message << endl;
}