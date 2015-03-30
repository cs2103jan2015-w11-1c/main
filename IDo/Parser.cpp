#include "Parser.h"

const int FIRST_WORD = 0;
const int SECOND_WORD = 1;
const int THIRD_WORD = 2;

const string Parser::CHOICE_ADD = "add";
const string Parser::CHOICE_DELETE = "delete";
const string Parser::CHOICE_EDIT = "edit";
const string Parser::CHOICE_CLEAR = "clear";
const string Parser::CHOICE_SEARCH = "search";
const string Parser::CHOICE_MARK = "mark";
const string Parser::CHOICE_VIEW = "view";
const string Parser::CHOICE_ERROR = "details not parsed";
const string Parser::CHOICE_EXIT = "exit";
const string Parser::MESSAGE_INVALID_TIME = "Invalid Time Input";
const string Parser::MESSAGE_INVALID_DATE = "Invalid Date Input";

//This checks the choice of command 
Parser::CommandType Parser::userCommand(){

	//i.e. Returns "add" if user keys in "add do tutorial"
	_userCommand = splittedUserInputs[0];

	if (_userCommand == CHOICE_ADD) {
		return ADD;
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
	else if (_userCommand == CHOICE_SEARCH) {
		return SEARCH;
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
	
	//Removes the first word u.e. user command
	splittedUserInputs.erase(splittedUserInputs.begin());
	
	switch (commandChoice){
		case ADD:
			parsedInputs.push_back("add");
			processAddContent(splittedUserInputs);
			break;

		case DEL:
			parsedInputs.push_back("delete");
			parsedInputs.push_back(splittedUserInputs[0]);
			break;

		case EDIT:
			parsedInputs.push_back("edit");
			processEditContent(splittedUserInputs);
			break;

		case CLEAR:
			parsedInputs.push_back("clear");
			break;
		
		case SEARCH:
			parsedInputs.push_back("search");
			parsedInputs.push_back(splittedUserInputs[0]);
			break;

		case MARK:
			parsedInputs.push_back("mark");
			processMarkContent(splittedUserInputs);
			break;	
		
		case VIEW:
			parsedInputs.push_back("view");
			processView(splittedUserInputs);
			break;

		case EXIT:
			parsedInputs.push_back("exit");

		case INVALID:
			parsedInputs.push_back("invalid");
			break;
	}

	return 1;
}

//Post: Returns true if it's a timed-task i.e. add...from <date/time> to <date/time>
//		Returns false if it's not a timed-task
bool Parser::checkTimedTask(){
	Dates check;
	int size = splittedUserInputs.size();
	fromPosition = -1;
	int toPosition = -1;
	bool valid = true;

	for(int i = 0; i < size; i ++) {
		if(splittedUserInputs[i] == "from") {
			fromPosition = i;
		} 
		if(splittedUserInputs[i] == "to") {
			toPosition = i;
		}
	}

	if(fromPosition !=-1 && toPosition != -1) {
		for(int i = fromPosition+1; i < toPosition; i ++ ) {
			if(!check.isDateValid(splittedUserInputs[i]) && !isPossibleTime(splittedUserInputs[i])) {
				valid = false;
			}
		}
		for(int i = toPosition+1 ; i <size ; i++) {
			if(!check.isDateValid(splittedUserInputs[i]) && !isPossibleTime(splittedUserInputs[i])) {
				valid = false;
			}
		}
	} else {
		return false;
	}
	

	if(valid == true) {
		for(int i = fromPosition+1; i < toPosition; i ++ ) {
			if(check.isDateValid(splittedUserInputs[i])) {
				_startDate = check.getFormattedDates();
			}
			if(isPossibleTime(splittedUserInputs[i])) {
				_startTime = splittedUserInputs[i];
			}
		}

		for(int i = toPosition+1 ; i < size ; i++) {
			if(check.isDateValid(splittedUserInputs[i])) {
				_endDate = check.getFormattedDates();
			}
			if(isPossibleTime(splittedUserInputs[i])) {
				_endTime = splittedUserInputs[i];
			}
		}
	}

	if(!_startDate.empty() && !_endDate.empty()) { 
		if(compareDates(_startDate,_endDate)) {
			valid = false;
		}
	}

	return valid;
}

//Post: Returns true if it's a deadline task i.e. add...by <date/time>
//		Returns false if it's not a deadline task
bool Parser::checkDeadlineTask(){
	Dates check;
	int size = splittedUserInputs.size();
	byPosition = -1;
	bool valid = true;

	for(int i = 0; i < size; i ++) {
		if(splittedUserInputs[i] == "by") {
			byPosition = i;
		}
	}

	if(byPosition != -1) {
		for(int i = byPosition+1; i < size; i ++ ) {
			if(!check.isDateValid(splittedUserInputs[i]) && !isPossibleTime(splittedUserInputs[i])) {
				valid = false;
			}
		}
	}
	else if (byPosition == -1) {
		return false;
	}
	else {
		valid = true;
	}

	if(valid == true) {
		for(int i = byPosition+1 ; i < size ; i++) {
	
			if(check.isDateValid(splittedUserInputs[i])) {
				_endDate = check.getFormattedDates();
			}
			if(isPossibleTime(splittedUserInputs[i])) {
				_endTime = splittedUserInputs[i];
			}
		}
	}

	return valid;
}

//Post: Returns true if it's floating task
//		Returns false if it's not a floating task
bool Parser::checkFloating(){
	int size = splittedUserInputs.size();
	Dates check;
	bool valid = true;

	if(fromPosition!=size-1 && fromPosition!=-1) {
		if(check.checkDateFormat(splittedUserInputs[fromPosition+1])){
			valid = false;
		}
		if(isTimeFormat(splittedUserInputs[fromPosition+1])){
			valid = false;
		}
	}

	if(byPosition!=size-1 && byPosition!=-1) {
		if(check.checkDateFormat(splittedUserInputs[byPosition+1])){
			valid = false;
		}
		if(isTimeFormat(splittedUserInputs[byPosition+1])){
			valid = false;
		}
	}

	return valid;
}

//This sorts out the correct information for add function
//Pre: Takes in the content of userinputs less the command
//Post: Returns false if userinput is invalid
bool Parser::processAddContent(vector<string> inputs) {

	Dates check;

	bool addResultValid = true;
	int size = inputs.size();

	if(checkTimedTask()){
		cout<<"timetask"<<endl;
		for(int i = 0; i < fromPosition-1; i++){
		_taskContent += inputs[i] + " ";
		}
		parsedInputs.push_back(_taskContent);

		if(_startDate.empty() && _endDate.empty()) {
			_startDate = check.getTodayDate();
			_endDate = check.getTodayDate();
		}
		if(!_startDate.empty() && _endDate.empty()){
			_endDate = _startDate;
		}
		if(_startDate.empty() && !_endDate.empty()){
			_startDate = check.getTodayDate();
		}

		parsedInputs.push_back(_startDate);
		parsedInputs.push_back(_startTime);
		parsedInputs.push_back(_endDate);
		parsedInputs.push_back(_endTime);

	} else if (checkDeadlineTask()) {
		cout<<"deadlinetask"<<endl;
		for(int i = 0; i < byPosition-1; i++){
			_taskContent += inputs[i] + " ";
		}
		parsedInputs.push_back(_taskContent);

		if(_endTime.empty()) {
			_endTime = "2359";
		}
		
		if(_endDate.empty()) {
			_endDate = check.getTodayDate();
		}

		parsedInputs.push_back(_endDate);
		parsedInputs.push_back(_endTime);

	} else if(checkFloating()) {
		cout<<"floatingtask"<<endl;
		for(int i = 0; i < size; i++){
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

	if(inputSize >= 3){
		parsedInputs.push_back(inputs[FIRST_WORD]); //task index to be edited
		parsedInputs.push_back(inputs[SECOND_WORD]); //task type to be edited
	
		for(int i = 2; i < inputSize ; i++){
			_taskContent += inputs[i] + " "; //task details to be edited
		}
		parsedInputs.push_back(_taskContent);

	} else {
		return false;
	}

	return true;
} 

//This processes all words if mark function is called
bool Parser::processMarkContent(vector<string> inputs){

	int size = inputs.size();

	for(int i = 0; i < size ; i++) {
		parsedInputs.push_back(inputs[i]);
	}

	return true;
}

//This parses the information that a view function requires i.e. undone, done, commands
bool Parser::processView(vector<string> inputs) {

	int size = inputs.size();

	if(size == 1) {
		parsedInputs.push_back(inputs[FIRST_WORD]); //notdone, done, commands 
	} else {
		return false;
	}

	return true;
}

vector<string> Parser::getParsedInputs(){
	return parsedInputs;
}

//Post: Return true if date is a larger date than date2
bool Parser::compareDates(string date, string date2) {
	int size = date.size();
	int size2 = date2.size();

	for(int i = 0; i < size ; i++) {
		if(date[i] == '/') {
			date.erase(date.begin()+i);
			size = date.size();
		}
	}
	
	for(int i = 0; i < size2 ; i++) {
		if(date2[i] == '/') {
			date2.erase(date2.begin()+i);
			size2 = date2.size();
		}
	}

	if(atoi(date.c_str()) > atoi(date2.c_str())) {
		cout << endl << "[Error] End Date is before Start Date??" << endl <<endl;
		return true;
	} else {
		return false;
	}
}

//This checks if time is valid
//Post: Returns true if valid, Returns false if invalid
bool Parser::isPossibleTime(string time){
	
	size_t found = time.find_first_of(",");
	if(found != string::npos && found != 0){
		time = time.substr(found+1,time.size()-1);
	}

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
		cout << "Error: Outside time range 0000 to 2359" << endl;
		return false;
	}

	_time = time;
		
	return true;
}

//Return false if time is not 4 digit or time is digit
bool Parser::isTimeFormat(string time) {

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


//Pre: A string that takes in userinputs
//Post: Returns a vector of inputs which have been parsed
vector<string> Parser::completeParsing(string line){
	split(line);

	parseActions(splittedUserInputs);

	return parsedInputs;
}