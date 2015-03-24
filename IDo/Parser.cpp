#include "Parser.h"
#include <iostream>

const int FIRST_WORD = 0;
const int SECOND_WORD = 1;
const int THIRD_WORD = 2;

const string Parser::CHOICE_ADD = "add";
const string Parser::CHOICE_DISPLAY = "display";
const string Parser::CHOICE_DELETE = "delete";
const string Parser::CHOICE_EDIT = "edit";
const string Parser::CHOICE_MARK = "mark";
const string Parser::CHOICE_CLEAR = "clear";
const string Parser::CHOICE_ERROR = "details not parsed";
const string Parser::CHOICE_VIEW = "view";
const string Parser::CHOICE_EXIT = "exit";
const string Parser::MESSAGE_INVALID_TIME = "Invalid Time Input";
const string Parser::MESSAGE_INVALID_DATE = "Invalid Date Input";

//This checks the choice of command 
Parser::CommandType Parser::userCommand(){
	_userCommand = splittedUserInputs[0];

	if (_userCommand == CHOICE_ADD) {
		return ADD;
    }
	else if (_userCommand == CHOICE_DISPLAY) {
        return DISPLAY;
    }
	else if (_userCommand == CHOICE_DELETE) {
        return DEL;
    }
	else if (_userCommand == CHOICE_EDIT) {
        return EDIT;
    }
	else if (_userCommand == CHOICE_CLEAR) {
        return CLEAR;
    }
	else if (_userCommand == CHOICE_MARK) {
		return MARK;
	}
	else if (_userCommand == CHOICE_VIEW) {
        return VIEW;
    }
	else if (_userCommand == CHOICE_EXIT) {
		return EXIT;
	}
	else {
		return INVALID;
	}
}

//This splits a string into words and stores them in a vector. Spacing is removed.
vector<string> Parser::split(string userInput){
	vector<string> tokens;
	istringstream iss(userInput);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
	splittedUserInputs = tokens;

	return tokens;
}

//This processes the different commands.
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

		case DEL:
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
		
		case VIEW:
			parsedInputs.push_back("view");
			processView(splittedUserInputs);
			break;

		case EXIT:
			parsedInputs.push_back("exit");

		case INVALID:
			break;
	}

	return 1;
}

//This sorts out the correct information for add function
//Returns false if userinput is invalid
bool Parser::processAddContent(vector<string> inputs){

	bool addResultValid = true;
	int size = inputs.size();

	if(size>4){
		if(inputs[size-4] == "from" && inputs[size-2] == "to"){	
			if(dateTimeValid(inputs[size-3]) && dateTimeValid(inputs[size-1])){
				for(int i=0;i<size-4;i++){
					_taskContent += inputs[i] + " ";
				}
				parsedInputs.push_back(_taskContent);
				splitStartDateTime(inputs[size-3]);
				splitEndDateTime(inputs[size-1]);
			}
		} /*else if(inputs[size-2] == "by"){
			if(isDateValid(inputs[size-1])){
				parsedInputs.push_back(inputs[size-1]);
			}
		} else {
			for(int i=0;i<size;i++){
				_taskContent += inputs[i] + " ";
			}
			parsedInputs.push_back(_taskContent);
		}*/
	} else if(size > 2){
		if(inputs[size-2] == "by"){
			if(isDateValid(inputs[size-1])){
				for(int i=0;i<size-2;i++){
					_taskContent += inputs[i] + " ";
				}
				parsedInputs.push_back(_taskContent);
				parsedInputs.push_back(inputs[size-1]);
				parsedInputs.push_back("2359");
			}
			if(dateTimeValid(inputs[size-1])) {
				for(int i=0;i<size-4;i++){
					_taskContent += inputs[i] + " ";
				}
				parsedInputs.push_back(_taskContent);
				splitEndDateTime(inputs[size-1]);
			}

		}/* else {
			for(int i=0;i<size;i++){
				_taskContent += inputs[i] + " ";
			}
			parsedInputs.push_back(_taskContent);
		}*/
	} else if (size!=0){
		for(int i=0;i<size;i++){
				_taskContent += inputs[i] + " ";
			}
		parsedInputs.push_back(_taskContent);
	} else {
		return false;
	}

	
	return addResultValid;
}

//This sorts out the information that an edit function requires i.e. task index, type and details
bool Parser::processEditContent(vector<string> inputs){
	
	int inputSize = inputs.size();

	if(inputSize == 3){
		parsedInputs.push_back(inputs[FIRST_WORD]); //task index to be edited
		parsedInputs.push_back(inputs[SECOND_WORD]); //task type to be edited
	
		for(int i = 2; i < inputSize ; i++){
			_taskContent += inputs[i] + " "; //task details to be edited
		}
		parsedInputs.push_back(inputs[THIRD_WORD]);

	} else {
		return false;
	}

	return true;
} 

//This sorts out the information that a mark function requires i.e. task index, task status
bool Parser::processMarkContent(vector<string> inputs){

	int size = inputs.size();

	if(size == 2){
		parsedInputs.push_back(inputs[FIRST_WORD]); //task index 
		parsedInputs.push_back(inputs[SECOND_WORD]); //task status
	} else if(size ==3){
		parsedInputs.push_back(inputs[FIRST_WORD]); //task index 
		parsedInputs.push_back(inputs[SECOND_WORD]); //task status
		parsedInputs.push_back(inputs[THIRD_WORD]); //task content
	} else {
		return false;
	}

	return true;
}

//This parses the information that a view function requires i.e. undone, done, commands
bool Parser::processView(vector<string> inputs) {

	int size = inputs.size();

	if(size == 1) {
		parsedInputs.push_back(inputs[FIRST_WORD]); //undone, done, commands 
	} else {
		return false;
	}

	return true;
}

vector<string> Parser::getParsedInputs(){
	return parsedInputs;
}

//check if date and time is in correct format and valid
//Post: Returns false if invalid, Returns true is valid
bool Parser::dateTimeValid(string dateTime){
	
	bool valid = true;
	size_t found = dateTime.find_first_of(",");

	if(found!=string::npos){
		if(!isDateValid(dateTime.substr(0, found))){
			valid = false; 	
		}
		if(!isPossibleTime(dateTime.substr(found+1, dateTime.size()))){
			valid = false;
		}
	} else {
		cout << endl << "[Error] Check that datetime is YYYY/MM/DD,HHMM" << endl << endl;
		valid = false;
	}
	
	return valid;
}

//This splits a string into start date and time
bool Parser::splitStartDateTime(string dateTime) {
	
	size_t found = dateTime.find_first_of(",");
	
	if (found != string::npos) {
		parsedInputs.push_back(dateTime.substr(0, found));		
		parsedInputs.push_back(dateTime.substr(found+1,dateTime.size()));
	} else {
		return false;
	}
	
	return true;
}

//This splits a string into end date and time
//Post: Returns true if success, Returns false if no
bool Parser::splitEndDateTime(string dateTime) {
	
	size_t found = dateTime.find_first_of(",");;
	
	if(found!=string::npos){
		parsedInputs.push_back(dateTime.substr(0, found));		
		parsedInputs.push_back(dateTime.substr(found+1,dateTime.size()));
	} else{
		return 0;
	}	
	
	return 1;
}

//This checks if time is valid
//Post: Returns true if valid, Returns false if invalid
bool Parser::isPossibleTime(string time){
	
	int minute = atoi(time.c_str());
	
	if(time.size()>4 || minute > 2359) {
		return false;
	}
		
	return true;
}

//This checks if date is valid
//Post: Returns true if valid, Returns false if invalid
bool Parser::isDateValid(string dateinput){

	date today = day_clock::local_day();

	if (dateinput[4]!='/' && dateinput[7]!= '/' || dateinput[4]!='/' && dateinput[6]!= '/') {
		cout << endl << "[ERROR] Check that Date Format is YYYY/MM/DD" << endl << endl;
		return false;
	}
	
	try{
		date dateToCheck(from_simple_string(dateinput));
		days difference = dateToCheck - today;

		if (difference < days(0)) {
			cout << "[ERROR] Check that the date is not before today" << today << endl << endl;
			return false;
		}
	} catch (exception& e) {
		cout<< "[ERROR] " << e.what() << endl << endl;
		return false;
	}

	 

/*	string checkDate;
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
	}*/	
	return true;
}

//Post: Returns a vector of inputs which have been parsed
vector<string> Parser::completeParsing(string line){
	split(line);

	parseActions(splittedUserInputs);

	return parsedInputs;
}