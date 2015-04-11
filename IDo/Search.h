#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include <iostream>
#include "Dates.h"
#include "Task.h"

using namespace std;

class Search {
private:
	string _searchword;
	int _searchWordSize;
	vector <Task> _listOfFoundTasks;
	vector <int> _listOfFoundTaskNum;
	int _noOfFoundTasks;
	int searchForWord(vector<string>);

public:
	void setSearchWord(string);
	bool isSearchDate();
	bool foundDate(string);
	void execute(vector<Task>);
	vector<string> stringToTokens(string);
	bool foundWord(string);
	vector<Task> getListOfFoundTasks();
	vector <int> getListOfFoundTaskNum();
	int getNoOfFoundTasks();
};

#endif