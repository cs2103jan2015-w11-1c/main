//@author A0111624W
#include "Parser.h"

const int NOT_VALID = -1;
const int FIRST_WORD = 0;
const int SECOND_WORD = 1;
const int THIRD_WORD = 2;

const string Parser::CHOICE_ADD = "add";
const string Parser::CHOICE_DELETE = "delete";
const string Parser::CHOICE_EDIT = "edit";
const string Parser::CHOICE_CLEAR = "clear";
const string Parser::CHOICE_SEARCH = "search";
const string Parser::CHOICE_VIEW = "view";
const string Parser::CHOICE_MARK = "mark";
const string Parser::CHOICE_SORT = "sort";
const string Parser::CHOICE_UNDO = "undo";
const string Parser::CHOICE_STORE = "store";
const string Parser::CHOICE_EXIT = "exit";
const string Parser::CHOICE_ERROR = "error";
const string Parser::MESSAGE_INVALID_TIME = "Invalid Time Input";
const string Parser::MESSAGE_INVALID_DATE = "Invalid Date Input";
const char* Parser::ERROR_TIME_OUT_RANGE = "[ERROR] Outside time range 0000 to 2359";
const char* Parser:: ERROR_END_TIME_B4_STARTTIME = "[ERROR] End Time before Start Time";

//This checks the choice of command 
Parser::CommandType Parser::userCommand(){

	//i.e. Returns "add" if user keys in "add do tutorial"
	_userCommand = splittedUserInputs[0];

	if (_userCommand == CHOICE_ADD) {
		return ADD;
    } else if (_userCommand == CHOICE_DELETE) {
        return DEL;
    } else if (_userCommand == CHOICE_EDIT) {
        return EDIT;
    } else if (_userCommand == CHOICE_CLEAR) {
        return CLEAR;
    } else if (_userCommand == CHOICE_SEARCH) {
		return SEARCH;
	} else if (_userCommand == CHOICE_VIEW) {
        return VIEW;
    } else if (_userCommand == CHOICE_MARK) {
		return MARK;
	} else if (_userCommand == CHOICE_SORT) {
        return SORT;
    } else if (_userCommand == CHOICE_STORE) {
		return STORE;
	} else if (_userCommand == CHOICE_UNDO) {
		return UNDO;
	} else if (_userCommand == CHOICE_EXIT) {
		return EXIT;
	} else {
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
			parsedInputs.push_back(CHOICE_ADD);
			processAddContent(splittedUserInputs);
			break;

		case DEL:
			parsedInputs.push_back(CHOICE_DELETE);
			processDeleteContent(splittedUserInputs);
			break;

		case EDIT:
			parsedInputs.push_back(CHOICE_EDIT);
			processEditContent(splittedUserInputs);
			break;

		case CLEAR:
			parsedInputs.push_back(CHOICE_CLEAR);
			break;
		
		case SEARCH:
			parsedInputs.push_back(CHOICE_SEARCH);
			processSearchContent(splittedUserInputs);
			break;

		case VIEW:
			parsedInputs.push_back(CHOICE_VIEW);
			processView(splittedUserInputs);
			break;

		case MARK:
			parsedInputs.push_back(CHOICE_MARK);
			processMarkContent(splittedUserInputs);
			break;	
	
		case SORT:
			parsedInputs.push_back(CHOICE_SORT);
			processSortContent(splittedUserInputs);
			break;	

		case STORE:
			parsedInputs.push_back(CHOICE_STORE);
			parsedInputs.push_back(splittedUserInputs[FIRST_WORD]);
			break;

		case UNDO:
			parsedInputs.push_back(CHOICE_UNDO);
			break;

		case EXIT:
			parsedInputs.push_back(CHOICE_EXIT);

		case INVALID:
			parsedInputs.push_back(CHOICE_ERROR);
	}

	return 1;
}

//Post: Returns true if it's a timed-task i.e. add...from <date/time> to <date/time>
//		Returns false if it's not a timed-task
bool Parser::checkTimedTask(){

    splittedSize = splittedUserInputs.size();
	bool valid = true;

	fromPosition = keywordPos("from");
	toPosition = keywordPos("to");
	everyPosition = keywordPos("every");

	if(fromPosition != NOT_VALID && toPosition != NOT_VALID && everyPosition != NOT_VALID) {
		for(int i = fromPosition+1; i < toPosition; i++ ) {
			if(!validDateTime(i)) {
				valid = false;
			}
		}
		for(int i = toPosition+1 ; i < everyPosition ; i++) {
			if(!validDateTime(i)) {
				valid = false;
			}
		}
	} else if (fromPosition != NOT_VALID && toPosition != NOT_VALID && everyPosition == NOT_VALID) {
		for(int i = fromPosition+1; i < toPosition; i++ ) {
			if(!validDateTime(i)) {
				valid = false;
			}
		}
		for(int i = toPosition+1 ; i < splittedSize ; i++) {
			if(!validDateTime(i)) {
				valid = false;
			}
		}
	} else {
		return false;
	}
	
	if(valid == true) {

		//Stores startdate, starttime, enddate, endtime
		storeTimedTaskInfo();

		//Return false if start date is larger than end date
		if(compareDates(_startDate,_endDate)) {
			valid = false;
		}
	
		//Return false if start time is larger than end time
		if(_startDate == _endDate && compareTimes(_startTime,_endTime)) {
			valid = false;
		}
		//Return false if time is less than today's time
		if(!checkTimeIfDateIsToday(_startDate, _startTime)){
			cout << "[Error] You should start on your task NOW!" <<endl;
			valid = false;
		}
	}
	return valid;
}

bool Parser::storeTimedTaskInfo() {

		assert (fromPosition != NOT_VALID || byPosition != NOT_VALID);

		for (int i = fromPosition+1; i < toPosition; i++ ) {
			if (check.isDateValid(splittedUserInputs[i])) {
				_startDate = check.getFormattedDates();
			}
			if (isPossibleTime(splittedUserInputs[i])) {
				_startTime = splittedUserInputs[i];
			}
		}

		for (int i = toPosition + 1; i < splittedSize; i++) {
			if(check.isDateValid(splittedUserInputs[i])) {
				_endDate = check.getFormattedDates();
			}
			if(isPossibleTime(splittedUserInputs[i])) {
				_endTime = splittedUserInputs[i];
			}
		}

		setMissingDateTime();

		return true;
}

bool Parser::setMissingDateTime() {

	if(_startTime.empty() && _startDate == check.getTodayDate()) {
		_startTime = getTodayTime();
	} else if(_startTime.empty()){
		_startTime = "0000";
	}

	if(_endTime.empty()) {
		_endTime = "2359";
	}

	if(_startDate.empty()){
		_startDate = check.getTodayDate();
	}

	if(_endDate.empty()) {
		_endDate = _startDate;
	}
	return true;
}



//Post: Returns true if it's a deadline task i.e. add...by <date/time>
//		Returns false if it's not a deadline task
bool Parser::checkDeadlineTask(){

	int size = splittedUserInputs.size();
	byPosition = -1;
	int everyPosition = -1;
	bool valid = true;

	everyPosition = keywordPos("every");
	byPosition = keywordPos("by");

	if(byPosition != -1 && everyPosition != -1) {
		for(int i = byPosition+1; i < everyPosition; i ++ ) {
			if(!check.isDateValid(splittedUserInputs[i]) && !isPossibleTime(splittedUserInputs[i])) {
				valid = false;
			}
		}
	} else if (byPosition != -1 && everyPosition == -1) {
		for(int i = byPosition+1; i < size; i ++ ) {
			if(!check.isDateValid(splittedUserInputs[i]) && !isPossibleTime(splittedUserInputs[i])) {
				valid = false;
			}
		}
	} else if (byPosition == -1) {
		return false;
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

		if(_endDate.empty()) {
			_endDate = check.getTodayDate();
		}

		if(_endTime.empty()) {
			_endTime = "2359";
		}

		if(!checkTimeIfDateIsToday(_endDate, _endTime)){
			cout << "You Missed Your DEADLINE!" <<endl;
			valid = false;
		}
	}
	return valid;
}

//Post: Returns true if it's floating task
//		Returns false if it's not a floating task
bool Parser::checkFloating(){
	int size = splittedUserInputs.size();
	bool valid = true;

	if(fromPosition != size-1 && fromPosition != -1) {
		if(check.checkDateFormat(splittedUserInputs[fromPosition+1])){
			valid = false;
		}
		if(isTimeFormat(splittedUserInputs[fromPosition+1])){
			valid = false;
		}
	}

	if(byPosition != size-1 && byPosition != -1) {
		if(check.checkDateFormat(splittedUserInputs[byPosition+1])){
			valid = false;
		}
		if(isTimeFormat(splittedUserInputs[byPosition+1])){
			valid = false;
		}
	}

	return valid;
}

//Post: Returns true if it's recurring task
//		Returns false if it's not a recurring task
bool Parser::checkRecurring() {
	
	bool validRecurring = false;

	string firstKeyword = "every";
	string secondKeyword;
	string thirdKeyword;

	int size = splittedUserInputs.size();

	for (int i = 0; i < size; i++) {
		if(splittedUserInputs[i] == firstKeyword && i != size - 1) {
			if(checkSecondWord (i + 1) && checkThirdWord (i+2)) {
				secondKeyword = splittedUserInputs[i+1];
				thirdKeyword = splittedUserInputs[i+2];
				validRecurring = true;
			} else if (checkSecondWord(i+1) &&  !checkThirdWord(i+2)) {
				secondKeyword = splittedUserInputs[i+1];
				validRecurring = true;
			} 
		} 
	}

	if(validRecurring == true) {
		parsedInputs.push_back(firstKeyword);
		parsedInputs.push_back(secondKeyword);
		if(!thirdKeyword.empty())
			parsedInputs.push_back(thirdKeyword);
	}

	return validRecurring;
}

//Post: Returns true if after the word "for", the second word is a digit and the 
//		third word is a day/month/year	
bool Parser::checkRecurringLimit() {

	string keyWord = "for";
	string duration;
	string dayMthYear;

	bool valid = false;

	int position = keywordPos(keyWord);

	if(position != - 1) {
		if(checkNumberOfRepeats(position+1) && checkThirdWord(position+2)) { 
			duration = splittedUserInputs[position+1];
			dayMthYear = splittedUserInputs[position+2];
			valid = true;
		}
	}
                                                                                	      
	if(valid == true) {
		parsedInputs.push_back(keyWord);
		parsedInputs.push_back(duration);
		parsedInputs.push_back(dayMthYear);
	}

	return valid;
}

bool Parser::checkSecondWord(int index) {
	string secondKeyword[6] = {"day", "month" , "year", "days", "months", "years"};
	int size = splittedUserInputs.size();
	cout<<index<<endl;
	//check vector boundary
	if(index >= size) {
		return false;
	}

	bool valid = false;
	   
	for(int i = 0; i < 6; i++) {
		if(splittedUserInputs[index] == secondKeyword[i]) {
			return true;
		} else if(checkNumberOfRepeats(index)) {
			return true;
		}
	}
	return valid;
}

bool Parser::checkNumberOfRepeats(int index) {
	int size1 = splittedUserInputs.size();

	//check vector boundary
	if(index >= size1) {
		return false;
	}

	int size = splittedUserInputs[index].size();
	
	for (int j = 0; j < size; j++) {
		if(!isdigit(splittedUserInputs[index][j]))
			return false;
	}
	return true;
}

bool Parser::checkThirdWord(int index) {
	string thirdKeyword[6] = {"day", "month" , "year", "days", "months", "years"};
	int size = splittedUserInputs.size();

	//check vector boundary
	if(index >= size) {
		return false;
	}

	for(int i = 0; i < 6; i++) {
		if(splittedUserInputs[index] == thirdKeyword[i]) {
			return true;
		} 
	}
	return false;
}

bool Parser::storeTaskContent(int start, int end, vector<string> inputs) {
	for(int i = start; i < end; i++) {
		if(i == end-1){
			_taskContent += inputs[i];
		} else {
			_taskContent += inputs[i] + " ";
		}
	}
	return true;
}

//This sorts out the correct information for add function
//Pre: Takes in the content of userinputs less the command
//Post: Returns false if userinput is invalid
bool Parser::processAddContent(vector<string> inputs) {
	bool addResultValid = true;
	int size = inputs.size();

	_log.log("Parser processing input for adding");
	if(checkTimedTask()) {
		storeTaskContent(0, fromPosition-1, inputs);
		parsedInputs.push_back(_taskContent);
		parsedInputs.push_back(_startDate);
		parsedInputs.push_back(_startTime);
		parsedInputs.push_back(_endDate);
		parsedInputs.push_back(_endTime);

		if(checkRecurring()) {
			checkRecurringLimit();
		}

	} else if (checkDeadlineTask()) {
		storeTaskContent(0, byPosition-1, inputs);
		parsedInputs.push_back(_taskContent);
		parsedInputs.push_back(_endDate);
		parsedInputs.push_back(_endTime);

		if(checkRecurring()) {
			checkRecurringLimit();
		}

	} else if(checkFloating()) {
		storeTaskContent(0, size, inputs);
		parsedInputs.push_back(_taskContent);

	} else {
		addResultValid = false;
	}
	
	return addResultValid;
}

//This sorts out the information that an edit function requires i.e. task index, type and details
bool Parser::processEditContent(vector<string> inputs) {
	int inputSize = inputs.size();

	_log.log("Parser processing input for edit");
	if(inputSize >= 3){
		parsedInputs.push_back(inputs[FIRST_WORD]); //task index to be edited
		parsedInputs.push_back(inputs[SECOND_WORD]); //task type to be edited
	
		storeTaskContent(2, inputSize, inputs);
		parsedInputs.push_back(_taskContent);

	} else {
		return false;
	}

	return true;
} 

//This processes all words if delete function is called
bool Parser::processDeleteContent(vector<string> inputs){
	int size = inputs.size();

	_log.log("Parser processing input for delete");
	for(int i = 0; i < size ; i++) {
		parsedInputs.push_back(inputs[i]);
	}
	return true;
}

//This processes all words if mark function is called
bool Parser::processMarkContent(vector<string> inputs){
	int size = inputs.size();

	_log.log("Parser processing input for mark");
	for(int i = 0; i < size ; i++) {
		parsedInputs.push_back(inputs[i]);
	}
	return true;
}

//This parses the information that a view function requires i.e. undone, done, commands
bool Parser::processView(vector<string> inputs) {
	int size = inputs.size();

	_log.log("Parser processing input for viewing");
	if(size == 1 && inputs[FIRST_WORD] == "tmr") {
		parsedInputs.push_back(check.datesFromToday(1));
	} else if (size == 1 && check.checkDay(inputs[FIRST_WORD]) == 8) {
		parsedInputs.push_back(inputs[FIRST_WORD]); //notdone, done, commands 
	} else if(size == 1 && check.checkDay(inputs[FIRST_WORD]) < 8) {
		parsedInputs.push_back(check.datesGivenDays(check.getTodayDate(),inputs[FIRST_WORD]));
	} else if (size == 2 && check.checkDay(inputs[SECOND_WORD]) != 0 && inputs[FIRST_WORD] == "next") {
		parsedInputs.push_back(check.datesGivenDays(check.getTodayDate(),inputs[SECOND_WORD]));
	} else if (size == 3) {
		if(inputs[FIRST_WORD] < ":" && inputs[FIRST_WORD] > "/") {
			if(inputs[SECOND_WORD] == "day" &&  inputs[THIRD_WORD] == "after") {
				int index = atoi(inputs[FIRST_WORD].c_str());
				parsedInputs.push_back(check.datesFromToday(index));
			}
		}
	} else {
		return false;
	}
	return true;
}

//This parses the information that a sort function requires i.e. sort date/time/undone/priority
bool Parser::processSortContent(vector<string> inputs) {
	int size = inputs.size();

	if(size == 1) {
		parsedInputs.push_back(inputs[FIRST_WORD]); //date/time/undone/priority
	} else {
		return false;
	}
	return true;
}

bool Parser::processSearchContent(vector<string> inputs) {
	int size = inputs.size();
	string content;

	_log.log("Parser processing input for search");
	if(size == 1) {
		content = inputs[FIRST_WORD];
		parsedInputs.push_back(content);
	} else if(size > 1) {
		for(int i = 0;  i < size; i++){
			if(i != size -1) { 
				content += inputs[i] + " ";
			} else {
				content += inputs[i];
			}
		}
		parsedInputs.push_back(content);
	} 

	return true;
}

vector<string> Parser::getParsedInputs(){
	return parsedInputs;
}

//Post: Return true if date1 is a larger date than date2
bool Parser::compareDates(string date1, string date2) {

	if(date1.empty() || date2.empty()) {
		return false;
	} 

	date d1(from_simple_string(date1));
	date d2(from_simple_string(date2));

	if(d1 > d2) {
		cout << endl << "[Error] End Date is before Start Date??" << endl <<endl;
		return true;
	} else {
		return false;
	}
}

//Post: Return true if time1 is a larger time than time2
bool Parser::compareTimes(string time1, string time2) {

	if(time1.empty() || time2.empty()) {
		return false;
	}

	if(time1 > time2) {
//		throw ERROR_END_TIME_B4_STARTTIME;
		return true;
	} else {
		return false;
	}
}

//This checks if timeformat i.e. HHMM and time value is valid
//Post: Returns true if valid, Returns false if invalid
bool Parser::isPossibleTime(string time){
	
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
//		throw ERROR_TIME_OUT_RANGE;
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


//Return false if time is before today's time
bool Parser::checkTimeIfDateIsToday(string date, string time) {
	
	if(date.empty() || time.empty()) {
		return false;
	}

	if(date == check.getTodayDate()) {
		if(time < getTodayTime()) {
			throw "[ERROR] Time is OVER!!!";
		}
	}
	return true;
}

bool Parser::validDateTime(int index) {
	
	if(!check.isDateValid(splittedUserInputs[index])) {
		if(!isPossibleTime(splittedUserInputs[index])) {
			return false;
		}
	} 

	return true;
}
//Return today'sTime as a string
string Parser::getTodayTime() {

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

//Return the position of keyword in splittedUserInputs
int Parser::keywordPos(string keyword) {
	int position = NOT_VALID;

	int size = splittedUserInputs.size();

	for(int i = 0; i < size; i++) {
		if(keyword == splittedUserInputs[i]) {
			position = i;
		}
	}

	return position;
}


//Pre: A string that takes in userinputs
//Post: Returns a vector of inputs which have been parsed
vector<string> Parser::completeParsing(string line){

	//removes spacing between words
	split(line);
	_log.log("Parser removes spacing between words");
	//Process Parsing 
	parseActions(splittedUserInputs);
	_log.log("Parser parses the user input and stores in vector");

	return parsedInputs;
}