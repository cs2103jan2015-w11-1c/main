#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include <iostream>
#include "Dates.h"
#include "Task.h"
#include "Log.h"
#include "Assert.h"

using namespace std;

class Search {
private:
	Log _log;
	string _searchWord;
	int _searchWordSize;
	string _taskName;
	string _endDate;
	string _startDate;
	vector <Task> _listOfFoundTasks;
	vector <int> _listOfFoundTaskNum;
	int _noOfFoundTasks;
	int searchForWord(vector<string>);
	bool canFindFirst(int &, vector<string>, vector<string>);
	bool findSec(int &, vector<string>, vector<string>);
	bool foundWord(string);

public:
	Search();
	~Search();
	void setSearchWord(string);
	bool isSearchDate();
	bool foundDate(string);
	void execute(vector<Task>);
	vector<string> stringToTokens(string);
	vector<Task> getListOfFoundTasks();
	vector <int> getListOfFoundTaskNum();
	int getNoOfFoundTasks();
	string getSearchWord();
};

#endif