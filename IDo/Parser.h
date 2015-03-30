#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <iterator>
#include "Dates.h"

using namespace std;

class Parser {
private:
	vector<string> splittedUserInputs;
	vector<string> parsedInputs;

	//Command Choices
	static const string CHOICE_ADD;
	static const string CHOICE_DELETE;
	static const string CHOICE_EDIT;
	static const string CHOICE_CLEAR;
	static const string CHOICE_SEARCH;
	static const string CHOICE_MARK;
	static const string CHOICE_VIEW;
	static const string CHOICE_SORT;
	static const string CHOICE_ERROR;
	static const string CHOICE_EXIT;

	//Error Messages
	static const string MESSAGE_INVALID_TIME;
	static const string MESSAGE_INVALID_DATE;

	int fromPosition;
	int byPosition;

	string _userInputs;	
	string _userCommand;
	string _taskContent;
	string _time;
	string _startDate;
	string _endDate;
	string _startTime;
	string _endTime;
		
	enum CommandType{
		ADD, DEL, EDIT, CLEAR, SEARCH, VIEW, MARK, SORT, INVALID, EXIT, 
	};
	CommandType userCommand();

	//Functions to process inputs
	vector<string> split(string userInput);
	bool parseActions(vector<string> inputs);	
	bool processAddContent(vector<string> inputs);
	bool processEditContent(vector<string> inputs);
	bool processMarkContent(vector<string> inputs);
	bool processView(vector<string> inputs);
	bool processSortContent(vector<string> inputs);
	vector<string> getParsedInputs();

	bool checkTimedTask();
	bool checkDeadlineTask();
	bool checkFloating();

	//Functions to check for validity
	bool compareDates(string date, string date2);
	bool isPossibleTime(string time);
	bool isTimeFormat(string time);

	bool isDateValid(string date);
	bool timecheck(string input);
	
public:
	//Stores information that has been parsed
	vector<string> completeParsing(string);
};

#endif