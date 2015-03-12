#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iterator>
#include "Parser.h"
#include "UserInterface.h"
#include "Logic.h"
#include "Task.h"
#include "Storage.h"

const int FIRST_WORD = 0;

string Parser::processAddContent(string userInput){

	string addResult="Successfully added '" + userInput + "'";
	split(userInput);
	
	for(int i=0;i<inputs.size();i++) {
		if(inputs[i]=="from" && inputs[i+2]=="to"){	
			splitStartDateTime(inputs[i+1]);
			splitEndDateTime(inputs[i+3]);
			break;
		}
		else if(inputs[i]=="by") {
			_deadline = inputs[i+1];
			break;
		}
		else {
			_taskName = _taskName + " " + inputs[i];
		}
	}

	if (!_startTime.empty() && !_endTime.empty()) {
		if(!isPossibleTime(_startTime) || !isPossibleTime(_endTime)){
			addResult = "Error: Wrong Input";
			return addResult;
		}
	} 
	if (!_startDate.empty() && !_endDate.empty()) {
		if(!isDateValid(_startDate)|| !isDateValid(_endDate)){
			addResult = "Error: Wrong Input";
			return addResult;
		}
	}  
	cout << "parser task name:" << _taskName << endl;
	tasks.setTaskName(_taskName);
	tasks.setStartDate(_startDate);
	tasks.setStartTime(_startTime);
	tasks.setEndDate(_endDate);
	tasks.setEndTime(_endTime); 
	if (!_deadline.empty()) {
		tasks.setDeadline(_deadline);
	}
	return addResult;
}

Task Parser::getTask () {
	return tasks;
}

void Parser::processEditContent(string userInput){
		
	split(userInput);
	
	_editNumber = atoi(inputs[0].c_str());
	
	_taskInfo = inputs[1];
	
	for(int i=2;i<inputs.size();i++){
		_editContent = _editContent + " " + inputs[i];
	} 
}

int Parser::getEditNumber () {
	return _editNumber;
}

string Parser::getTaskInfo () {
	return _taskInfo;
}

string Parser::getEditContent () {
	return _editContent;
}

string Parser::splitEndDateTime(string dateTime){
	
	string endDateTime;
	size_t found = dateTime.find_first_of(",");;
	
	if(found!=string::npos){
		_endDate = dateTime.substr(0, found);
		_endTime = dateTime.substr(found+1,dateTime.size());
	}		
	
	endDateTime = _endDate + _endTime;
	
	return endDateTime;
}

string Parser::splitStartDateTime(string dateTime){
	
	string startDateTime;
	size_t found = dateTime.find_first_of(",");;
	
	if(found!=string::npos){
		_startDate = dateTime.substr(0, found);		
		_startTime = dateTime.substr(found+1,dateTime.size());
	}		
	
	startDateTime = _startDate + _startTime;
	
	return startDateTime;
}


bool Parser::isPossibleTime(string time){
	
	int minute;
	if(time.size()>4) {
		return false;
	}
		
	minute = atoi(time.c_str());

	if(minute>2359) {
		return false;
	}
		
	return true;
}

bool Parser::isDateValid(string date){
	
	string checkDate;
	bool valid=true;
	if(date[3]!='/' && date[5]!= '/') {
		valid = false;
	}
			
	size_t found = date.find_first_of("/");
	
	int days = atoi(date.substr(0,found).c_str());
	checkDate = date.substr(found+1,date.size());
		
	int month = atoi(checkDate.substr(0,found).c_str());
	found = checkDate.find_first_of("/");	

	checkDate = checkDate.substr(found+1,checkDate.size());
	int year = atoi(checkDate.substr(0,checkDate.size()).c_str());

	if(month>12 || year > 9999) {
		valid = false;
	}
		
	if(month%2==0 && days>30) {
		valid=false;
	}
	else if(month%2!=0 && days>31) {
		valid=false;			
	}
	else {
		if(month==2 && days>29) {
			valid = false;
		}
	}	
	return valid;
}


vector<string> Parser::splitParameters(string commandParametersString){
	vector<string> tokens;
	istringstream iss(commandParametersString);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
		
	return tokens;
}

void Parser::split(string userInput){
	inputs = splitParameters(userInput);
}


void Parser::print(){
	
	cout<<"Task: "<<_taskName<<endl;
	cout<<"Start: "<<_startDate << " " << _startTime <<endl;
	cout<<"End: "<<_endDate << " " << _endTime <<endl;
	cout<<"Deadline: "<<_deadline<<endl;	
	
}

