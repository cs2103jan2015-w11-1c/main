#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <iterator>
#include "boost/date_time/gregorian/gregorian.hpp" 

using namespace std;
using namespace boost::gregorian;


class Parser {
private:
	vector<string> splittedUserInputs;
	vector<string> parsedInputs;

	//Command Choices
	static const string CHOICE_ADD;
	static const string CHOICE_DELETE;
	static const string CHOICE_EDIT;
	static const string CHOICE_MARK;
	static const string CHOICE_CLEAR;
	static const string CHOICE_ERROR;
	static const string CHOICE_VIEW;
	static const string CHOICE_EXIT;

	//Error Messages
	static const string MESSAGE_INVALID_TIME;
	static const string MESSAGE_INVALID_DATE;

	string _userInputs;	
	string _userCommand;
	string _taskContent;
		
	enum CommandType{
		ADD, DEL, EDIT, CLEAR, VIEW, EXIT, INVALID, MARK
	};
	CommandType userCommand();

	//Functions to process inputs
	vector<string> split(string userInput);
	bool parseActions(vector<string> inputs);	
	bool processAddContent(vector<string> inputs);
	bool processEditContent(vector<string> inputs);
	bool processMarkContent(vector<string> inputs);
	bool processView(vector<string> inputs);
	vector<string> getParsedInputs();

	//Functions to check for validity
	bool dateTimeValid(string dateTime);
	bool splitStartDateTime(string dateTime);
	bool splitEndDateTime(string dateTime);
	bool isPossibleTime(string time);
	bool isDateValid(string date);
	
public:
	//Stores information that has been parsed
	vector<string> completeParsing(string);
};

#endif
