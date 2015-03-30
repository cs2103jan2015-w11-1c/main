#include "Logic.h"


const string SUCCESSFULLY_MARKED = "[Marked Successfully]";
const string SUCCESSFULLY_ADDED = "[Added Successfully]";
const string SUCCESSFULLY_DELETED = "[Deleted Successfully]";
const string SUCCESSFULLY_CLEARED = "[Cleared Successfully]";
const string ERROR_WRONG_INPUT = "Error: Wrong Input!";

void Logic::updateStorage () {
	storage.updateFile (_listOfTasks);
}

void Logic::getParsedInformation(string line) {
	Parser parser;
	userInput = line;
	//pass to parser and process
	parsedInformation = parser.completeParsing(userInput);
}

void Logic::printMessage(string message) {
	cout << endl <<  message <<  endl << endl;
}

void Logic::addTask() {
	Add add;
	if (add.execute(parsedInformation)) {
		_listOfTasks.push_back(add.getTask());
		printMessage(SUCCESSFULLY_ADDED);
		updateStorage();
	}
}

void Logic::deleteTask() {
	Delete remove;
	if (remove.execute(parsedInformation, getListofTasks())) {
		_listOfTasks = remove.getNewList();
		printMessage(SUCCESSFULLY_DELETED);
		updateStorage();
	} else {
		cout<<"Task List is empty/Wrong task input!"<<endl;
	}
}

void Logic::editTask() {
	Edit edit;
	if (edit.execute(parsedInformation, getListofTasks())) {
		setListOfTasks(edit.getNewList());
		updateStorage();
	} else {
		cout<<"Task NOT edited"<<endl;
	}
}

void Logic::markTask() {
	Mark mark;
	if (mark.isValidInput(parsedInformation, _listOfTasks.size())) {
		mark.execute(parsedInformation, _listOfTasks);
		printMessage(SUCCESSFULLY_MARKED);
		updateStorage();
	} else {	
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

void Logic::viewDecider() {
	View view;
	system("CLS");
	if (parsedInformation[1] == "all") {
		view.viewAll(_listOfTasks);
	} else if (parsedInformation[1] == "done") {
		view.viewDoneTasks(_listOfTasks);
	} else if (parsedInformation[1] == "notdone") {
		view.viewNotDoneTasks(_listOfTasks);
	} else if (parsedInformation[1] == "commands") {
		viewCommands();
	}
}

void Logic::storeChange(string directory) {
	storage.editStorageFileName(parsedInformation[1]);
}

void Logic::exitProgram() {
	ofstream writeFile ("filename.txt");
	writeFile << storage.getStorageFileName();
	writeFile.close();
}

// Processes the command and inputs passed from UI
bool Logic::process(string line) {

	getParsedInformation(line);
	commandChoice = parsedInformation[0];
	
	if(commandChoice == "add") {
		addTask();
	} else if (commandChoice == "delete") {
		deleteTask();
	} else if (commandChoice == "edit") {
		editTask();
	} else if (commandChoice == "clear") {
		_listOfTasks.clear();
		printMessage(SUCCESSFULLY_CLEARED);
		updateStorage();
	} else if (commandChoice == "mark") {
		markTask();
	} else if (commandChoice == "view") {
		viewDecider();
	} else if (commandChoice == "store") {
		storeChange(parsedInformation[1]);
		updateStorage();
	} else if (commandChoice == "exit") {
		updateStorage();
		exitProgram();
		return false;
	} else if (commandChoice == "invalid") {
		cout << ERROR_WRONG_INPUT << endl;
	} else {
		cout << ERROR_WRONG_INPUT << endl;
	}
	return true;
}

vector<Task> Logic::getListofTasks(){
	return _listOfTasks;
}

vector<Task> Logic::setListOfTasks(vector<Task> newList) {
	_listOfTasks = newList;
	return _listOfTasks;
}