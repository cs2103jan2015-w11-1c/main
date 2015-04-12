//@author A0111624W
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
#include "Log.h"

using namespace std;

class Parser {
private:
	Dates check;
	Log _log;

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
	static const string CHOICE_STORE;
	static const string CHOICE_UNDO;
	static const string CHOICE_ERROR;
	static const string CHOICE_EXIT;

	//Error Messages
	static const string MESSAGE_INVALID_TIME;
	static const string MESSAGE_INVALID_DATE;
	static const char* ERROR_TIME_OUT_RANGE;
	static const char* ERROR_END_TIME_B4_STARTTIME;

	int fromPosition;
	int byPosition;
	int toPosition;
	int everyPosition;

	string _userInputs;	
	string _userCommand;
	string _taskContent;
	string _time;
	string _startDate;
	string _endDate;
	string _startTime;
	string _endTime;
		
	enum CommandType{
		ADD, DEL, EDIT, CLEAR, SEARCH, VIEW, MARK, SORT, INVALID, STORE, UNDO, EXIT
	};
	CommandType userCommand();

	//Functions to process inputs
	vector<string> split(string userInput);
	bool parseActions(vector<string> inputs);	
	bool processAddContent(vector<string> inputs);
	bool processDeleteContent(vector<string> inputs);
	bool processEditContent(vector<string> inputs);
	bool processMarkContent(vector<string> inputs);
	bool processView(vector<string> inputs);
	bool processSortContent(vector<string> inputs);
	bool processSearchContent(vector<string> inputs);
	vector<string> getParsedInputs();

	bool checkTimedTask();
	bool checkDeadlineTask();
	bool checkFloating();
	bool checkRecurring();
	bool checkRecurringLimit();

	//Functions for Recurring Feature
	bool checkSecondWord(int);
	bool checkNumberOfRepeats(int);
	bool checkThirdWord(int);
	
	//Functions to check for validity
	//bool compareDates(string date1, string date2);
	bool compareTimes(string time1, string time2); 
	bool isPossibleTime(string time);
	bool isTimeFormat(string time);
	bool checkTimeIfDateIsToday(string date, string time);
	bool validDateTime(int index);


	string getTodayTime();
	int keywordPos(string keyword);

	bool setMissingDateTime();
	bool storeTaskContent(int, int, vector<string>);

public:
	//Stores information that has been parsed
	vector<string> completeParsing(string);
	bool compareDates(string date1, string date2);
};

#endif