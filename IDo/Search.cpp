//@author A0115545J
#include "Search.h"

Search::Search(){
	_noOfFoundTasks = 0;
}

Search::~Search(){
}

//Pre: Takes in a single word to be search
void Search::setSearchWord(string userInput) {
	_searchWord = userInput;
	_searchWordSize = _searchWord.size();
	
}

//Post: Return true if search word is a date
//		Return false if otherwise
bool Search::isSearchDate() {
	Dates d;

	if (d.checkDateFormat(_searchWord)) {
		if(d.isDateValid(_searchWord)) {
			_searchWord = d.getFormattedDates();
		} else {
			return false;
		}
	} else {
		return false;
	}

	return true;

}

//Pre: Takes in a date as a string
//Post: Return true if search word is the same as date
bool Search::foundDate(string date) {
	assert(date.size() > 0);

	if (_searchWord == date) {
		_log.log("Search word matches a date");
		return true;
	} else {
		return false;
	}
}

//Pre-condition: takes in a vector of task objects from logic
//looks through the tasks according to task name
void Search::execute(vector <Task> taskListFromLogic) {

	_log.log("Executing Search");

	int i;
	if (!isSearchDate()) {
		_log.log("Searching not a date");
		for (i = 0; i < taskListFromLogic.size(); i++) {
			_taskName = taskListFromLogic[i].getTaskName();
			if (foundWord(_taskName)) {
				_listOfFoundTasks.push_back(taskListFromLogic[i]);
				_listOfFoundTaskNum.push_back(i + 1);
			}
		}
	} else {
		_log.log("Searching for a date");
		for (i = 0; i < taskListFromLogic.size(); i++) {
			_endDate = taskListFromLogic[i].getEndDate();
			_startDate = taskListFromLogic[i].getStartDate();
			if (foundDate(_endDate) || foundDate(_startDate)) {
				_listOfFoundTasks.push_back(taskListFromLogic[i]);
				_listOfFoundTaskNum.push_back(i + 1);
			}
		}
		
	}
	_noOfFoundTasks = _listOfFoundTasks.size();
	_log.log("End of Search");
}

vector <string> Search::stringToTokens(string taskname) {
	vector<string> tokenisedTaskName;
	char* ptr = (char*)taskname.c_str();
	char *tokens;
	tokens = strtok(ptr, " ,-");
	while (tokens != NULL) {
		tokenisedTaskName.push_back(tokens);
		tokens = strtok(NULL, " ,-");
	}
	return tokenisedTaskName;
}

int Search::searchForWord(vector<string> tokenisedTaskName) {
	assert(tokenisedTaskName.size() > 0);

	_log.log("searching for 1 word\n");

	vector <string>::iterator iter = tokenisedTaskName.begin();
	int foundIndex = 0;
	while (iter != tokenisedTaskName.end()) {
		int size = (*iter).size();	//length of 1 word
		int i = 0;
		

		while (i < size) {
			foundIndex = ((*iter).substr(i)).find(_searchWord);
			if (foundIndex != -1) {
				 return foundIndex;
			} else {
				i++;
			}
		}

		iter++;
	}
	return foundIndex;
}

bool Search::canFindFirst(int &i, vector<string> tokenisedSearchWord, vector<string> tokenisedTaskName) {
	_log.log("searching for more than 1 word, finding first word\n");

	bool foundfirst = false;
	
	int size = tokenisedTaskName.size();

	while (!foundfirst && i < size) {
		if (tokenisedSearchWord[0] == tokenisedTaskName[i]) {
			foundfirst = true;
		}
		else {
			i++;
		}
	}
	return foundfirst;
}

bool Search::findSec(int &i, vector<string> tokenisedSearchWord, vector<string> tokenisedTaskName) {
	_log.log("searching for remaining words\n");

	bool running = true;
	int size = tokenisedSearchWord.size();
	int size2 = tokenisedTaskName.size();

	for (int j = 0; j < size && running && i < size2; j++) {
		if (tokenisedSearchWord[j] == tokenisedTaskName[i]) {
			i++;
		} else {
			running = false;
		}
	}
	return running;
}

//Pre condition: takes in the task name of task in list
//conducts the matching of task name with the word to be searched
//returns true if word is found, false otherwise
bool Search::foundWord(string taskname) {

	int whiteSpaceIndex;
	//cout << _searchword << "search word size: " << _searchword.size() << endl;
	if (_searchWord.size() == 1) {	//single first character search
		if (taskname[0] == _searchWord[0]) {
			_log.log("Search matches a word");
			return true;
		} else {
			return false;
		}
	}
	else if (_searchWord.size() > 1) {

		vector <string> tokenisedTaskName;;
		tokenisedTaskName = stringToTokens(taskname);

		whiteSpaceIndex = _searchWord.find_first_of(" ");

		//cout << "whitespace index" << whiteSpaceIndex << endl;
		try {
			if (whiteSpaceIndex == -1) {	//search word is 1 word
				int i = searchForWord(tokenisedTaskName);
				if (i != -1) {
					return true;
				}
				else {
					return false;
				}

			} else {	//search more than 1 word

				int i = 0;
				vector<string> tokenisedSearchWord = stringToTokens(_searchWord);
				int size2 = tokenisedTaskName.size();

				//cout << "i " << i << endl;
				bool foundfirst = false;
				foundfirst = canFindFirst(i, tokenisedSearchWord, tokenisedTaskName);

				if (foundfirst && i < size2 - 1) {
					if (findSec(i, tokenisedSearchWord, tokenisedTaskName)) {
						_log.log("found second word\n");
						return true;
					}
					else {
						if (i == size2 - 1) {
							throw ("exceed possible range");
						}
						return false;
					}
				} else {
					return false;
				}
			} 

		} 
		catch (char* strg){
			cout << "Exception raised: " << strg << endl;
		}
	} else {
		return false;
	}

	return true;
}


vector <Task> Search::getListOfFoundTasks() {
	return _listOfFoundTasks;
}

vector <int> Search::getListOfFoundTaskNum() {
	return _listOfFoundTaskNum;
}

int Search::getNoOfFoundTasks() {
	return _noOfFoundTasks;
}

string Search::getSearchWord(){
	return _searchWord;
}