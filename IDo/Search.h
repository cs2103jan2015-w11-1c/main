#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"

using namespace std;

class Search {
private:
	string _searchword;
	vector <Task> _listOfFoundTasks;
	vector <int> _listOfFoundTaskNum;
	int _noOfFoundTasks;

public:
	void setSearchWord(string);
	void execute(vector<Task>);
	bool foundWord(string);
	vector<Task> getListOfFoundTasks();
	vector <int> getListOfFoundTaskNum();
	int getNoOfFoundTasks();
};

#endif