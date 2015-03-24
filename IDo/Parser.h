#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Parser {
private:
	vector<string> splittedUserInputs;
	vector<string> parsedInputs;

	//Command Choices
	static const string CHOICE_ADD;
	static const string CHOICE_DISPLAY;
	static const string CHOICE_DELETE;
	static const string CHOICE_EDIT;
	static const string CHOICE_MARK;
	static const string CHOICE_CLEAR;
	static const string CHOICE_ERROR;
	static const string CHOICE_EXIT;

	//Error Messages
	static const string MESSAGE_INVALID_TIME;
	static const string MESSAGE_INVALID_DATE;

	string _userInputs;	
	string _userCommand;
	string _taskContent;
		
	enum CommandType{
		ADD, DISPLAY, DEL, EDIT, CLEAR, EXIT, INVALID, MARK
	};
	CommandType userCommand();

	//Functions to process inputs
	vector<string> split(string userInput);
	bool parseActions(vector<string> inputs);	
	bool processAddContent(vector<string> inputs);
	bool processEditContent(vector<string> inputs);
	bool processMarkContent(vector<string> inputs);
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
