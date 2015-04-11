#include "Search.h"

//takes in a single word to be search
void Search::setSearchWord(string userInput) {
	_searchword = userInput;
	_searchWordSize = _searchword.size();
}

bool Search::isSearchDate() {
	Dates d;

	if (d.checkDateFormat(_searchword)) {
		if(d.isDateValid(_searchword)) {
			_searchword = d.getFormattedDates();
		} else {
			cout<<"searching task instead...."<<endl;
			return false;
		}
	} else {
		return false;
	}

	return true;

}

bool Search::foundDate(string date) {
	if (_searchword == date) {
		return true;
	} else {
		return false;
	}
}

//Pre-condition: takes in a vector of task objects from logic
//looks through the tasks according to task name
void Search::execute(vector <Task> taskListFromLogic) {

	int i;
	if (!isSearchDate()) {
		for (i = 0; i < taskListFromLogic.size(); i++) {
			//cout << "searching in " << taskListFromLogic[i].getTaskName() << endl;
			if (foundWord(taskListFromLogic[i].getTaskName())) {
				_listOfFoundTasks.push_back(taskListFromLogic[i]);
				_listOfFoundTaskNum.push_back(i + 1);
			}
		}
		_noOfFoundTasks = _listOfFoundTasks.size();
	} else {
		for (i = 0; i < taskListFromLogic.size(); i++) {
			//cout << "searching date " << taskListFromLogic[i].getEndDate() << endl;
			if (foundDate(taskListFromLogic[i].getEndDate()) || foundDate(taskListFromLogic[i].getStartDate())) {
				_listOfFoundTasks.push_back(taskListFromLogic[i]);
				_listOfFoundTaskNum.push_back(i + 1);
			}
		}
		_noOfFoundTasks = _listOfFoundTasks.size();
	}
	
}

vector <string> Search::stringToTokens(string taskname) {
	vector<string> tokenisedTaskName;
	char* ptr = (char*)taskname.c_str();
	char *tokens;
	tokens = strtok(ptr, " ,-");
	while (tokens != NULL) {
		//cout << "tokens: " << tokens << endl;
		tokenisedTaskName.push_back(tokens);
		tokens = strtok(NULL, " ,-");
	}
	return tokenisedTaskName;
}

int Search::searchForWord(vector<string> tokenisedTaskName) {
	vector <string>::iterator iter = tokenisedTaskName.begin();
	int foundIndex = 0;
	while (iter != tokenisedTaskName.end()) {
		int size = (*iter).size();	//length of 1 word
		int i = 0;
		
		while (i < size) {
			foundIndex = ((*iter).substr(i)).find(_searchword);
			//cout << "foundIndex : " << foundIndex << endl;
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

//Pre condition: takes in the task name of task in list
//conducts the matching of task name with the word to be searched
//returns true if word is found, false otherwise
bool Search::foundWord(string taskname) {

	int whiteSpaceIndex;
	//cout << _searchword << "search word size: " << _searchword.size() << endl;
	if (_searchword.size() == 1) {	//single first character search
		if (taskname[0] == _searchword[0]) {
			return true;
		} else {
			return false;
		}
	} else if (_searchword.size() > 1) {

		vector <string> tokenisedTaskName;;
		tokenisedTaskName = stringToTokens(taskname);

		whiteSpaceIndex = _searchword.find_first_of(" ");

		//cout << "whitespace index" << whiteSpaceIndex << endl;

		if (whiteSpaceIndex == -1) {	//search word is 1 word
			int i = searchForWord(tokenisedTaskName);
			if (i != -1) {
				return true;
			} else {
				return false;
			}

		} else {	//search more than 1 word
			int i = 0;
			vector<string> tokenisedSearchWord = stringToTokens(_searchword);
			int size = tokenisedSearchWord.size();
			int size2 = tokenisedTaskName.size();

			//cout << "i " << i << endl;
			bool foundfirst = false;
			while (!foundfirst && i < size2) {
				if (tokenisedSearchWord[0] == tokenisedTaskName[i]) {
					foundfirst = true;
				} else {
					i++;
				}
			}
			//cout << "i " << i << endl;
			if (foundfirst && i < size2 - 1) {
				bool running = true;
				for (int j = 0; j < size && running && i < size2; j++) {
					if (tokenisedSearchWord[j] == tokenisedTaskName[i]) {
						i++;
					} else {
						running = false;
					}
				}
				return running;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}

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