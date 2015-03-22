#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iterator>
#include "Parser.h"

const int FIRST_WORD = 0;
const string Parser::MESSAGE_ADD = "add";
const string Parser::MESSAGE_DISPLAY = "display";
const string Parser::MESSAGE_DELETE = "delete";
const string Parser::MESSAGE_EDIT = "edit";
const string Parser::MESSAGE_CLEAR = "clear";
const string Parser::MESSAGE_ERROR = "details not parsed";
const string Parser::MESSAGE_EXIT = "exit";

Parser::CommandType Parser::userCommand(){
	_userCommand = splittedUserInputs[0];

	if (_userCommand == "add") {
		return ADD;
    }
    else if (_userCommand == "display") {
        return DISPLAY;
    }
	else if (_userCommand == "delete") {
        return DELETE;
    }
	else if (_userCommand == "edit") {
        return EDIT;
    }
	else if (_userCommand == "clear") {
        return CLEAR;
    }
	else if (_userCommand == "mark") {
		return MARK;
	}
	else if (_userCommand == "exit") {
		return EXIT;
	}
	else {
		return ERROR;
	}
}

vector<string> Parser::split(string userInput){
	vector<string> tokens;
	istringstream iss(userInput);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
	splittedUserInputs = tokens;

	return tokens;
}

bool Parser::parseActions(vector<string> splittedUserInputs){
	CommandType commandChoice = userCommand();
	splittedUserInputs.erase(splittedUserInputs.begin());
	
	switch (commandChoice){
		case ADD:
			parsedInputs.push_back("add");
			processAddContent(splittedUserInputs);
			break;

		case DISPLAY:
			parsedInputs.push_back("display");
			break;

		case DELETE:
			parsedInputs.push_back("delete");
			break;

		case EDIT:
			parsedInputs.push_back("edit");
			processEditContent(splittedUserInputs);
			break;
		
		case MARK:
			parsedInputs.push_back("mark");
			processMarkContent(splittedUserInputs);
			break;

		case CLEAR:
			parsedInputs.push_back("clear");
			break;

		case EXIT:
			parsedInputs.push_back("exit");

	}

	return 1;
}

bool Parser::processAddContent(vector<string> inputs){

	bool addResultValid = true;
	int size = inputs.size();
	string task;

	if(size>4){
		if(inputs[size-4] == "from" && inputs[size-2] == "to"){	
			if(dateTimeValid(inputs[size-3]) && dateTimeValid(inputs[size-1])){
				for(int i=0;i<size-4;i++){
					task += inputs[i] + " ";
				}
				parsedInputs.push_back(task);
				splitStartDateTime(inputs[size-3]);
				splitEndDateTime(inputs[size-1]);
			}
		} else if(inputs[size-2] == "by"){
			if(isDateValid(inputs[size-1])){
				parsedInputs.push_back(inputs[size-1]);
			}
		} else {
			for(int i=0;i<size;i++){
				task += inputs[i] + " ";
			}
			parsedInputs.push_back(task);
		}
	} else if(size==3 || size==4){
		if(inputs[size-2] == "by"){
			if(isDateValid(inputs[size-1])){
				for(int i=0;i<size-2;i++){
					task += inputs[i] + " ";
				}
				parsedInputs.push_back(task);
				parsedInputs.push_back(inputs[size-1]);
			}
		} else {
			for(int i=0;i<size;i++){
				task += inputs[i] + " ";
			}
			parsedInputs.push_back(task);
		}
	} else if (size!=0){
		for(int i=0;i<size;i++){
				task += inputs[i] + " ";
			}
		parsedInputs.push_back(task);
	} else {
		return false;
	}

	
	return addResultValid;
}


bool Parser::processEditContent(vector<string> inputs){
	
	int size = inputs.size();
	string task;

	if(size == 3){
		parsedInputs.push_back(inputs[0]); //task index to be edited
		parsedInputs.push_back(inputs[1]); //task type to be edited
	
		for(int i=2;i<size;i++){
			task += inputs[i] + " ";; //task details to be edited
		}
		parsedInputs.push_back(inputs[2]);
	} else {
		return false;
	}

	return true;
} 

bool Parser::processMarkContent(vector<string> inputs){

	int size = inputs.size();
	string task;

	if(size == 2){
		parsedInputs.push_back(inputs[0]); //task index to be edited
		parsedInputs.push_back(inputs[1]); //task type to be edited
	} else {
		return false;
	}

	return true;
}

vector<string> Parser::getParsedInputs(){
	return parsedInputs;
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

bool Parser::splitStartDateTime(string dateTime){
	
	size_t found = dateTime.find_first_of(",");;
	
	if(found!=string::npos){
		parsedInputs.push_back(dateTime.substr(0, found));		
		parsedInputs.push_back(dateTime.substr(found+1,dateTime.size()));
	} else{
		return false;
	}
	
	return true;
}

bool Parser::splitEndDateTime(string dateTime){
	
	size_t found = dateTime.find_first_of(",");;
	
	if(found!=string::npos){
		parsedInputs.push_back(dateTime.substr(0, found));		
		parsedInputs.push_back(dateTime.substr(found+1,dateTime.size()));
	} else{
		return 0;
	}	
	
	return 1;
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

vector<string> Parser::completeParsing(string line){
	split(line);

	parseActions(splittedUserInputs);

	return parsedInputs;
}