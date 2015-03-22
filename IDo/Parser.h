#ifndef PARSER_H
#define PARSER_H

//#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "UserInterface.h"
#include "Logic.h"
#include "Task.h"
#include "Storage.h"

using namespace std;

class Parser {
	
	private:
		vector<string> splittedUserInputs;
		vector<string> parsedInputs;

		Task tasks;

		static const string MESSAGE_ADD;
		static const string MESSAGE_DISPLAY;
		static const string MESSAGE_DELETE;
		static const string MESSAGE_EDIT;
		static const string MESSAGE_CLEAR;
		static const string MESSAGE_ERROR;
		static const string MESSAGE_EXIT;

		string _userInputs;	
		string _userCommand;
		
		enum CommandType{
			ADD, DISPLAY, DELETE, EDIT, CLEAR, EXIT, ERROR, MARK
		};
		CommandType userCommand();

		vector<string> split(string userInput);
		bool parseActions(vector<string> inputs);	
		bool processAddContent(vector<string> inputs);
		bool processEditContent(vector<string> inputs);
		bool processMarkContent(vector<string> inputs);
		vector<string> getParsedInputs();
		bool dateTimeValid(string dateTime);
		bool splitStartDateTime(string dateTime);
		bool splitEndDateTime(string dateTime);
		bool isPossibleTime(string time);
		bool isDateValid(string date);
	
	public:
		vector<string> completeParsing(string);
};

#endif
