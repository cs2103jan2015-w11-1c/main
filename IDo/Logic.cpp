#include "Logic.h"

const string LAST_CHANGE = "** Last Change Made **";
const string SUCCESSFULLY_MARKED = "[Marked Successfully]";
const string SUCCESSFULLY_ADDED = "[Added Successfully]";
const string SUCCESSFULLY_EDITED = "[Edited Successfully]";
const string NOT_EDITED = "[Editing NOT Successful]";
const string SUCCESSFULLY_DELETED = "[Deleted Successfully]";
const string SUCCESSFULLY_CLEARED = "[Cleared Successfully]";
const string SUCCESSFULLY_SORTED = "[Sorted Successfully]";
const string SUCCESSFULLY_CHANGE_FILE= "[Successfully Changed File Location]";
const string TASK_NOT_FOUND = "[Task Not Found]";
const string ERROR_WRONG_INPUT = "[Error] Wrong Input!";
const string ERROR_COMMAND_INPUT = "[Error] Wrong Command Input!";
const string ENTER_TO_DEFAULT_VIEW = "Press the ENTER key to go back to default view";

void Logic::updateStorage() {
	_storage.updateFile(_listOfTasks,0);
}

void Logic::undo() {
	_log.log("Undo done");
	_listOfTasks.clear();
	_storage.readFile(_listOfTasks,1);
	_view.viewDefault(_listOfTasks,_dates.getTodayDate());
}

void Logic::backup() {
	_log.log("Back up files");
	_storage.updateFile(_listOfTasks,1);
}

void Logic::getParsedInformation(string line) {
	_log.log("Logic passes input to parser");
	Parser parser;
	_userInput = line;
	//pass to parser and process
	_parsedInformation = parser.completeParsing(_userInput);
}

void Logic::printMessage(string message) {
	cout << endl << message << endl << endl;
}

void Logic::printHeader(string message) {
	cout << endl << message << endl;
}

void Logic::addTask() {
	Add add;
	backup();
	if (add.execute(_parsedInformation)) {

		if(!add.isRecurring(_parsedInformation)){
			_log.log("Logic pass to add to add recurring tasks");
			_listOfTasks.push_back(add.getTask());
		} else {
			_log.log("Logic pass to add to add tasks");
			vector <Task> temp = add.getOccurrences();
			int size = temp.size();
			int index = searchNextRecurringIndex();
			for(int i = 0; i < size; i++) {
				temp[i].setRecurringIndex(index);
				_listOfTasks.push_back(temp[i]);
			}
		}

		_view.viewDefault(_listOfTasks,_dates.getTodayDate());
		_view.viewSelectedOne(_listOfTasks, _listOfTasks.size());
		printMessage(SUCCESSFULLY_ADDED);
		updateStorage();

	} else {
		_view.viewDefault(_listOfTasks,_dates.getTodayDate());
		printMessage(ERROR_WRONG_INPUT);
	}
}

int Logic::searchNextRecurringIndex() {
	int size = _listOfTasks.size();
	int max = 0; 
	int index; 
	for (int i = 0 ; i < size; i++) {
		index = _listOfTasks[i].getRecurringIndex();
		if (index > max) {
			max = index;
		}
	}

	return max + 1;
}

void Logic::deleteTask() {
	Delete remove;
	backup();

	_view.viewDefault(_listOfTasks, _dates.getTodayDate());
	if (remove.isValidInput(_parsedInformation, _listOfTasks.size())) {
		_log.log("Logic pass to delete");
		remove.execute(_listOfTasks);
		printMessage(SUCCESSFULLY_DELETED);
		updateStorage();
	}
	else {
		cout << "Task List is empty/Wrong task input!" << endl;
	}
}

void Logic::editTask() {
	Edit edit;
	backup();

	_view.viewDefault(_listOfTasks,_dates.getTodayDate());
	int editedTaskNumber;
	if (edit.execute(_parsedInformation, _listOfTasks)) {
		_log.log("Logic pass to edit");
		_listOfTasks=edit.getList();
		editedTaskNumber = atoi(_parsedInformation[1].c_str());
		_view.viewSelectedOne(_listOfTasks, editedTaskNumber);
		printMessage(SUCCESSFULLY_EDITED);
		updateStorage();
	} else {
		printMessage(NOT_EDITED);
	}
}

void Logic::markTask() {
	Mark mark;
	backup();

	_view.viewDefault(_listOfTasks, _dates.getTodayDate());
	if (mark.isValidInput(_parsedInformation, _listOfTasks.size())) {
		_log.log("Logic pass to mark");
		mark.execute(_parsedInformation, _listOfTasks);
		printHeader(LAST_CHANGE);
		_view.viewSelectedFew(mark.getMarkedTasks(), mark.getMarkedTaskIndex());
		printMessage(SUCCESSFULLY_MARKED);
		updateStorage();
	}
	else {
		printMessage(ERROR_WRONG_INPUT);
	}
	updateStorage();
}

// List the commands available
void Logic::viewCommands() {
	cout << "Add a floating task: " << "add <task>" << endl;
	cout << "Add a time task: add <task> from yyyy/mm/dd,hhmm to yyyy/mm/dd,hhmm" << endl;
	cout << "Add a deadline: add <task> by yyyy/mm/dd,hhmm" << endl;
	cout << "Editing details: edit <task number> <info to edit> <new content>" << endl;
	cout << "Displaying all tasks: display" << endl;
	cout << "Deleting a task: delete <task number> " << endl;
	cout << "View completed task: view done" << endl;
	cout << "View task to be completed: view notdone" << endl;
	cout << "To change status: mark <task number> <done/notdone> " << endl;
	cout << "To change priority: mark <task number> <high/medium/low/none> " << endl;
	cout << "To change label: mark <task number> <friends/family/misc etc> " << endl;
}

bool Logic::viewDecider() {

	if (_parsedInformation.size() == 1) {
		return false;
	}

	system("CLS");

	if (_parsedInformation[1] == "all") {
		_view.viewAll(_listOfTasks);
		enterToGoDefaultView();
		return true;
	} else if (_parsedInformation[1] == "done") {
		_view.viewDoneTasks(_listOfTasks);
		enterToGoDefaultView();
		return true;
	} else if (_parsedInformation[1] == "notdone") {
		_view.viewNotDoneTasks(_listOfTasks);
		enterToGoDefaultView();
		return true;
	} else if (_parsedInformation[1] == "commands") {
		viewCommands();
		enterToGoDefaultView();
		return true;
	} else {
		_view.viewDefault(_listOfTasks,_parsedInformation[1]);
		return true;
	}
}

void Logic::storeChange() {
	string filename;
	_log.log("Logic call storage to change storage file name");
	_view.viewDefault(_listOfTasks,_dates.getTodayDate());
	filename = _parsedInformation[1] + ".txt";
	_storage.editStorageFileName(filename);
	cout << "New File Storage: " << filename << endl; 
	printMessage(SUCCESSFULLY_CHANGE_FILE);
}

void Logic::sortTask() {
	Sort sort;
	backup();

	if (sort.execute(_parsedInformation, _listOfTasks)) {
		_log.log("Logic pass to sort");
		_listOfTasks = sort.getSortedList();
		_view.viewDefault(_listOfTasks,_dates.getTodayDate());
		printMessage(SUCCESSFULLY_SORTED);
	} else {
		_view.viewDefault(_listOfTasks,_dates.getTodayDate());
		printMessage(ERROR_WRONG_INPUT);
	}
}

void Logic::searchWord() {
	Search search;
	search.setSearchWord(_parsedInformation[1]);
	search.execute(_listOfTasks);
	View printFoundTasks;

	system("CLS");
	if (search.getNoOfFoundTasks() != 0) {
		_log.log("Logic pass to search");
		vector <Task> listOfFoundTasks;
		vector <int> listOfFoundTaskNum;
		listOfFoundTasks = search.getListOfFoundTasks();
		listOfFoundTaskNum = search.getListOfFoundTaskNum();
		printFoundTasks.viewSelectedFew(listOfFoundTasks, listOfFoundTaskNum);
		enterToGoDefaultView();
	} else {
		printFoundTasks.viewDefault(_listOfTasks, _dates.getTodayDate());
		printMessage(TASK_NOT_FOUND);
	 }
}

void Logic::enterToGoDefaultView() {
	string userInput;
	printMessage(ENTER_TO_DEFAULT_VIEW);

	char one;
	cin.get(one);
	if (one == '\n') {
		_view.viewDefault(_listOfTasks,_dates.getTodayDate());
	} else {
		getline(cin, userInput);
		userInput = one + userInput;
		process(userInput);
	}
}

void Logic::readFromFile() {
	_log.log("Read data from storage file");
	_storage.readFile(_listOfTasks,0);
}

// Processes the command and inputs passed from UI
bool Logic::process(string line) {

	if(line.empty()){
		cout << "[ERROR] No Input" << endl;
		enterToGoDefaultView();
		return true;
	}
	
	getParsedInformation(line);
	_commandChoice = _parsedInformation[0];

	if (_commandChoice == "undo") {
		undo();
	} else if (_commandChoice == "add") {
		addTask();
	} else if (_commandChoice == "delete") {
		deleteTask();
	} else if (_commandChoice == "edit") {
		editTask();
	} else if (_commandChoice == "clear") {
		_listOfTasks.clear();
		_view.viewDefault(_listOfTasks,_dates.getTodayDate());
		printMessage(SUCCESSFULLY_CLEARED);
		updateStorage();
	} else if (_commandChoice == "mark") {
		markTask();
	} else if (_commandChoice == "view") {
		if (!viewDecider()) {
			printMessage(ERROR_WRONG_INPUT);
		}
	} else if (_commandChoice == "store") {
		storeChange();
		updateStorage();
	} else if (_commandChoice == "sort") {
		sortTask();
		updateStorage();
	} else if (_commandChoice == "search") {
		searchWord();
	} else if (_commandChoice == "exit") {
		updateStorage();
		return false;
	} else if (_commandChoice == "error") {
		_view.viewDefault(_listOfTasks, _dates.getTodayDate());	
		printMessage(ERROR_COMMAND_INPUT);
	} else {
		_view.viewDefault(_listOfTasks, _dates.getTodayDate());
		printMessage(ERROR_WRONG_INPUT);
	}

	return true;
}

vector<Task> Logic::getListOfTasks(){
	return _listOfTasks;
}