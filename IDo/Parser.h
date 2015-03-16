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
		 
		vector<string> inputs;
		string _taskName;
		string _deadline;
		string _duration;
		string _startTime;
		string _endTime;
		string _startDate;
		string _endDate;	
		Task tasks;
		
		string _taskInfo;
		string _editContent;
		int _editNumber;
	
	public:
		
		bool processAddContent(string userInput);
		Task getTask ();
		void processEditContent(string userInput);

		int getEditNumber ();
		string getTaskInfo ();
		string getEditContent ();

		bool dateTimeValid(string dateTime);
		string splitStartDateTime(string dateTime);
		string splitEndDateTime(string dateTime);
		bool isPossibleTime(string time);
		bool isDateValid(string date);
		void print();
		
		vector<string> split(string userInput);
		string removeFirstWord();		
	//	static string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
	//	static string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
	//	static string trim(const string &s, const string& delimiters = "\f\n\r\t\v");
		
		
};

#endif
