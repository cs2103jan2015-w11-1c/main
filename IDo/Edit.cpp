//@author A0111624W
#include "Edit.h"

const char* ERROR_STARTTIME = "[ERROR] Start Time is Over";
const char* ERROR_ENDTIME = "[ERROR] End Time is Over";
const char* ERROR_END_BEFORE_START = "[ERROR] End-Time cannot be earlier than Start-Time";
const char* ERROR_STARTDATE_LATER_THAN_ENDDATE = "[ERROR] Start-Date will be later than End-Date";
const char* ERROR_TIMEFORMAT = "[Error] Time format should be HHMM";
const char* ERROR_TIME_NOT_DIGIT = "[Error] Time format should be numbers withing 0000 to 2359";
const char* ERROR_TIME_RANGE = "[Error] Outside Time Range 0000 to 2359";
const char* ERROR_TASK_INDEX = "[Error] Invalid Task Index";
const char* ERROR_TASK_TYPE = "[Error] Invalid Task Type";
const string ERROR_INVALIDINPUT = "[ERROR] Invalid Inputs";

const string TASK_NAME = "taskname";
const string START_DATE = "startdate";
const string END_DATE = "enddate";
const string START_TIME = "starttime";
const string END_TIME = "endtime";

//This function processes parsed information from parser and also tasklist from logic
//Post: Return true if the execution of information is successful
//		Return false if the execution of information is not successful
bool Edit::execute(vector<string> parsedInfo, vector<Task> taskListFromLogic){

	_parsedInformation = parsedInfo;
	_taskList = taskListFromLogic;

	_parsedInfoSize = _parsedInformation.size();
	_numberOfTasks = _taskList.size();

	if(_parsedInfoSize == 4) {
		_editNumber = atoi(_parsedInformation[1].c_str()) - 1;
		_editType = _parsedInformation[2];
		_editContent = _parsedInformation[3];

		try {
			checkAndProcess();
		} catch (const char* msg) {
			cerr << msg << endl;
			return false;
		}
	} else {
		printMessage(ERROR_INVALIDINPUT);
		return false;
	}

	return true;
}

//Post: Return the edited tasklist 
vector<Task> Edit::getList(){
	return _taskList;
}

//This function checks and processese the content user wants to edit 
//Post: Return true if tasktype, tasknumber and task content to be edited is valid;
//		Return false if otherwise;
bool Edit::checkAndProcess(){

	//Return false if task number is unavailable
	if(_editNumber > _numberOfTasks){
		throw ERROR_TASK_INDEX;
	}

	//Match the type of task to be edited
	if(_editType == TASK_NAME){
		_log.log("Editing Taskname");
		_taskList[_editNumber].setTaskName(_editContent);

	} else if(_editType == START_DATE){
		_log.log("Editing Startdate");
		if(!setStartDate(_editContent, _editNumber)){
			return false;
		}
	} else if(_editType == START_TIME){
		_log.log("Editing Starttime");
		if(!setStartTime(_editContent, _editNumber)) {
			return false;
		} 
	} else if(_editType == END_DATE){
		_log.log("Editing Enddates");
		if(!setEndDate(_editContent, _editNumber)){
			return false;
		}
	} else if(_editType == END_TIME){
		_log.log("Editing Endtime");
		if(!setEndTime(_editContent, _editNumber)) {
			return false;
		} 
	} else {
		throw ERROR_TASK_TYPE;
	}

	return true;
}

//Pre: Takes in intended start date contnet and tasklist number to be edited
//Post: Return true if content is valid date
//		Return false if content is not valid date and thus throwing the specific error 
bool Edit::setStartDate(string startDate, int index) {

	getSelectedTaskInfo(index);

	if(check.isDateValid(startDate)) {
		startDate = check.getFormattedDates();
		try {
			compareDates(startDate, _endDate);
			cout<<"hihihi"<<endl;
			compareTime(startDate, _endDate, _startTime, _endTime);
			cout<<"asdasd"<<endl;
			_taskList[index].setStartDate(startDate);
		} catch (const char* msg) {
			cerr << msg << endl;
			return false;
		}
	} else {
		return false;
	}

	return true;
}

//Post: Return true if content is a valid date
//		Return false if content is not valid date and thus sthrowing the specific error 
bool Edit::setEndDate(string endDate, int index) {

	getSelectedTaskInfo(index);

	if(check.isDateValid(endDate)) {
		endDate = check.getFormattedDates();
		try {
			compareDates(_startDate, endDate);
			compareTime(_startDate, endDate, _startTime, _endTime);
			_taskList[index].setEndDate(endDate);
		} catch (const char* msg) {
			cerr << msg << endl;
			return false;
		}
	} else {
		return false;
	}

	return true;
}

//Post: Return true if content is a valid Time
//		Return false if content is not valid date and thus sthrowing the specific error 
bool Edit::setStartTime(string startTime, int index) {

	try {
		getSelectedTaskInfo(index);
		isPossibleTimeFormat(startTime);
		compareTime( _startDate, _endDate, startTime,  _endTime);
		compareDates( _startDate, _endDate);
		_taskList[index].setStartTime(startTime);
		_taskList[index].setStartDate(_startDate);
	} catch (const char* msg) {
		cerr << msg << endl;
		return false;
	}

	if(_startDate.empty()) {
		_taskList[index].setStartDate(check.getTodayDate());
	}

	return true;
}

//Post: Return true if content is a valid Time
//		Return false if content is not valid date and thus sthrowing the specific error 
bool Edit::setEndTime(string endTime, int index) {

	try {
		getSelectedTaskInfo(index);
		isPossibleTimeFormat(endTime);
		compareTime(_startDate, _endDate, _startTime,  endTime);
		compareDates( _startDate, _endDate);
		_taskList[index].setEndTime(endTime);
		_taskList[index].setEndDate(_endDate);
	} catch (const char* msg) {
		cerr << msg << endl;
		return false;
	}
	return true;
}

//This checks if timeformat i.e. HHMM and time value is valid
//Post: Returns true if valid, Returns false if invalid
bool Edit::isPossibleTimeFormat(string time){
	
	if(time.size()>4) {
		throw ERROR_TIMEFORMAT;
		return false;
	}

	for(int i = 0; i < 4; i++) { 
		if(!isdigit(time[i])){
			throw ERROR_TIME_NOT_DIGIT;
			return false;
		}
	}

	int minute = atoi(time.c_str());
	
	if(minute > 2359) {
		throw ERROR_TIME_RANGE;
		return false;
	}

	_time = time;
		
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

	date startDate(from_simple_string(date1));
	date endDate(from_simple_string(date2));

	if(startDate > endDate) {
		throw ERROR_STARTDATE_LATER_THAN_ENDDATE;
	}

	return true;
}

//Pre: Takes in 2 string dates and 2 string time
//Post: Return true if starttime is smaller than endtime given same date
//		Return false if otherwise;
bool Edit::compareTime(string date1, string date2, string startTime, string endTime) {

	if(date1.empty() || date2.empty() || startTime.empty() || endTime.empty()) {
		return false;
	}

	date startDate(from_simple_string(_startDate));
	date endDate(from_simple_string(_endDate));
	date todayDate(from_simple_string(check.getTodayDate()));

	if(startDate == endDate) {
		if(startTime > endTime) 
			throw ERROR_END_BEFORE_START;
	} else if(startDate == todayDate) {
		if(startTime < getTodayTime()) {
			throw ERROR_STARTTIME;
		}
	} else if(endDate == todayDate) {
		if(endTime < getTodayTime()) {
			throw ERROR_ENDTIME;
		}
	}

	return true;
}

//This function stores information of a selected task from the list of tasks
void Edit::getSelectedTaskInfo(int index) {
	_startDate =  _taskList[index].getStartDate();
	_endDate =  _taskList[index].getEndDate();
	_startTime =  _taskList[index].getStartTime();
	_endTime =  _taskList[index].getEndTime();
}

//Pre: Takes in a string 
//Post: Print out the intended message
void Edit::printMessage(string message) {
	cout << endl << message << endl;
}