#include "Logic.h"

const string SUCCESSFULLY_MARKED = "[Marked Successfully]";
const string SUCCESSFULLY_ADDED = "[Added Successfully]";
const string SUCCESSFULLY_EDITED = "[Edited Successfully]";
const string NOT_EDITED = "[Editing NOT Successful]";
const string SUCCESSFULLY_DELETED = "[Deleted Successfully]";
const string SUCCESSFULLY_CLEARED = "[Cleared Successfully]";
const string SUCCESSFULLY_SORTED = "[Sorted Successfully]";
const string TASK_NOT_FOUND = "[Task Not Found]";
const string ERROR_WRONG_INPUT = "Error: Wrong Input!";

void Logic::updateStorage() {
	_storage.updateFile(_listOfTasks,0);
}

void Logic::undo() {
	View view;
	_listOfTasks.clear();
	_storage.readFile(_listOfTasks,1);
	view.viewDefault(_listOfTasks,_dates.getTodayDate());
}

void Logic::backup() {
	_storage.updateFile(_listOfTasks,1);
}

void Logic::getParsedInformation(string line) {
	Parser parser;
	_userInput = line;
	//pass to parser and process
	_parsedInformation = parser.completeParsing(_userInput);
}

void Logic::printMessage(string message) {
	cout << endl << message << endl << endl;
}

void Logic::addTask() {
	Add add;
	View view;
	backup();
	if (add.execute(_parsedInformation)) {

		if(!add.isRecurring(_parsedInformation)){
			_listOfTasks.push_back(add.getTask());
		} else {
			vector <Task> temp = add.getOccurrences();
			int size = temp.size();
			int index = searchNextRecurringIndex();
			for(int i = 0; i < size; i++) {
				temp[i].setRecurringIndex(index);
				_listOfTasks.push_back(temp[i]);
			}
		}

		view.viewDefault(_listOfTasks,_dates.getTodayDate());
		view.viewSelectedOne(_listOfTasks, _listOfTasks.size());
		printMessage(SUCCESSFULLY_ADDED);
		updateStorage();

	} else {
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
	View view;
	backup();
	if (remove.isValidInput(_parsedInformation, _listOfTasks.size())) {
		remove.execute(_listOfTasks);
		view.viewDefault(_listOfTasks,_dates.getTodayDate());
		printMessage(SUCCESSFULLY_DELETED);
		updateStorage();
	}
	else {
		cout << "Task List is empty/Wrong task input!" << endl;
	}
}

void Logic::editTask() {
	Edit edit;
	View view;
	backup();

	view.viewDefault(_listOfTasks,_dates.getTodayDate());
	int editedTaskNumber;
	if (edit.execute(_parsedInformation, _listOfTasks)) {
		_listOfTasks=edit.getList();
		editedTaskNumber = atoi(_parsedInformation[1].c_str());
		view.viewSelectedOne(_listOfTasks, editedTaskNumber);
		printMessage(SUCCESSFULLY_EDITED);
		updateStorage();
	} else {
		printMessage(NOT_EDITED);
	}
}

void Logic::markTask() {
	Mark mark;
	View view;
	backup();

	if (mark.isValidInput(_parsedInformation, _listOfTasks.size())) {
		mark.execute(_parsedInformation, _listOfTasks);
		view.viewDefault(_listOfTasks,_dates.getTodayDate());
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
	View view;

	if (_parsedInformation.size() == 1) {
		return false;
	}

	system("CLS");

	if (_parsedInformation[1] == "all") {
		view.viewAll(_listOfTasks);
		return true;
	} else if (_parsedInformation[1] == "done") {
		view.viewDoneTasks(_listOfTasks);
		return true;
	} else if (_parsedInformation[1] == "notdone") {
		view.viewNotDoneTasks(_listOfTasks);
		return true;
	} else if (_parsedInformation[1] == "commands") {
		viewCommands();
		return true;
	//} else if (_parsedInformation[1] == "high" || _parsedInformation[1] == "medium" || _parsedInformation[1] == "low") {
		//view.viewPriority(_listOfTasks,_parsedInformation[1]);
		//return true;
	} else {
		view.viewDefault(_listOfTasks,_parsedInformation[1]);
		return true;
	}
}

void Logic::storeChange() {
	_storage.editStorageFileName(_parsedInformation[1]);
}

void Logic::sortTask() {
	Sort sort;
	backup();

	if (sort.execute(_parsedInformation, _listOfTasks)) {
		_listOfTasks = sort.getSortedList();
		cout << endl << SUCCESSFULLY_SORTED << endl;
	} else {
		printMessage(ERROR_WRONG_INPUT);
	}
}

void Logic::searchWord() {
	Search search;
	system("CLS");
	search.setSearchWord(_parsedInformation[1]);
	search.execute(_listOfTasks);
	View printFoundTasks;

	if (search.getNoOfFoundTasks() != 0) {
		vector <Task> listOfFoundTasks;
		vector <int> listOfFoundTaskNum;
		listOfFoundTasks = search.getListOfFoundTasks();
		listOfFoundTaskNum = search.getListOfFoundTaskNum();
		printFoundTasks.viewSelectedFew(listOfFoundTasks, listOfFoundTaskNum);

	} else {
		printFoundTasks.viewDefault(_listOfTasks, _dates.getTodayDate());
		printMessage(TASK_NOT_FOUND);
	}
}

void Logic::readFromFile() {
	_storage.readFile(_listOfTasks,0);
}

// Processes the command and inputs passed from UI
bool Logic::process(string line) {

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
		printMessage(SUCCESSFULLY_CLEARED);
		updateStorage();
	} else if (_commandChoice == "mark") {
		markTask();
	} else if (_commandChoice == "view") {
		if (!viewDecider()) {
			cout << ERROR_WRONG_INPUT << endl;
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
	} else if (_commandChoice == "invalid") {
		cout << ERROR_WRONG_INPUT << endl;
	} else {
		cout << ERROR_WRONG_INPUT << endl;
	}

	return true;
}

vector<Task> Logic::getListOfTasks(){
	return _listOfTasks;
}