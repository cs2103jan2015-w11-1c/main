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

bool Parser::processAddContent(string userInput){

	bool addResultValid = true;

	split(userInput);
	
	for(int i=0;i<inputs.size();i++) {
		if(inputs[i] == "from" && inputs[i+2] == "to"){	
			if(dateTimeValid(inputs[i+1]) && dateTimeValid(inputs[i+3])){
				splitStartDateTime(inputs[i+1]);
				splitEndDateTime(inputs[i+3]);
			}
			else{
				addResultValid = false;
			}
			break;
		}
		else if(inputs[i] == "by") {
			if(isDateValid(inputs[i+1])){
				_deadline = inputs[i+1];
			}
			else{
				addResultValid = false;
			} 
			break;
		}
		else {
			if(!_taskName.empty()){
				_taskName = _taskName + " " + inputs[i];
			}
			else{
				_taskName = inputs[i];
			}
		}
	}

	if(_startTime>_endTime){
		addResultValid = false;
	}

	return addResultValid;
}

Task Parser::getTask () {

	tasks.setTaskName(_taskName);
	tasks.setStartDate(_startDate);
	tasks.setStartTime(_startTime);
	tasks.setEndDate(_endDate);
	tasks.setEndTime(_endTime); 
	tasks.setDeadline(_deadline);

	return tasks;
}

void Parser::processEditContent(string userInput){
		
	split(userInput);
	_editNumber = atoi(inputs[0].c_str());
	_taskInfo = inputs[1];

	for(int i=2;i<inputs.size();i++){
		if(!_editContent.empty()){
			_editContent = _editContent + " " + inputs[i];
		}
		else{
			_editContent = inputs[i];
		}
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

bool Parser::dateTimeValid(string dateTime){
	
	bool valid = true;
	size_t found = dateTime.find_first_of(",");;
	
	if(found!=string::npos){
		if(!isDateValid(dateTime.substr(0, found))){
			valid = false; 	
		}
		if(!isPossibleTime(dateTime.substr(found+1, dateTime.size()))){
			valid = false;
		}
	}	
	
	return valid;
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
	
	int minute = atoi(time.c_str());
	
	if(time.size()>4 || minute > 2359) {
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

	if(month>12 || year > 9999 ) {
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


vector<string> Parser::split(string userInput){
	vector<string> tokens;
	istringstream iss(userInput);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
	inputs = tokens;

	return tokens;
}

void Parser::print(){

	cout<<"Task: "<<_taskName<<endl;
	cout<<"Start: "<<_startDate << " " << _startTime <<endl;
	cout<<"End: "<<_endDate << " " << _endTime <<endl;
	cout<<"Deadline: "<<_deadline<<endl;	
	
}

