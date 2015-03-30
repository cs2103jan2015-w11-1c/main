#include "Search.h"

//takes in a single word to be search
void Search::setSearchWord(string userInput) {
	_searchword = userInput;
}

//Pre-condition: takes in a vector of task objects from logic
//looks through the tasks according to task name
void Search::execute(vector <Task> taskListFromLogic) {
	vector <Task>::iterator iter;
	for (iter = taskListFromLogic.begin(); iter != taskListFromLogic.end(); iter++)
	{
		if (foundWord((*iter).getTaskName()))
		{
			_listOfFoundTasks.push_back((*iter));
		}
	}
	_noOfFoundTasks = _listOfFoundTasks.size();
}

//Pre condition: takes in the task name of task in list
//conducts the matching of task name with the word to be searched
//returns true if word is found, false otherwise
bool Search::foundWord(string taskname) {
	int i;
	bool found = false;

	vector <string> tokenisedTaskName;

	char* ptr = (char*)taskname.c_str();
	char *tokens;
	tokens = strtok(ptr, " ,.-");
	while (tokens != NULL) {
		//cout << "tokens: " << tokens << endl;
		tokenisedTaskName.push_back(tokens);
		tokens = strtok(NULL, " ,.-");
	}
	
	vector <string>::iterator iter = tokenisedTaskName.begin();
	while (iter != tokenisedTaskName.end() && !found) {
		if (*(iter) == _searchword) {
			found = true;
		}
		iter++;
	}
	return found;
}

vector <Task> Search::getListOfFoundTasks() {
	return _listOfFoundTasks;
}

int Search::getNoOfFoundTasks() {
	return _noOfFoundTasks;
}