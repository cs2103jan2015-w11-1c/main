#include "Logic.h"
#include <sstream>
#include <assert.h>

const string SUCCESSFULLY_MARKED = "[Marked Successfully]";
const string SUCCESSFULLY_ADDED = "[Added Successfully]";
const string DISPLAYING = "[List of Tasks]";
const string ERROR_WRONG_INPUT = "Error: Wrong Input!";

void Logic::updateStorage () {
	Storage saveToDisk;
	saveToDisk.updateFile (_listOfTasks);
}

void Logic::getParsedInformation(string line){

	Parser parser;
	userInput = line;
	//pass to parser and process
	parsedInformation = parser.completeParsing(userInput);

}

void Logic::printMessage(string message){
	cout << endl <<  message <<  endl << endl;
}

// Print out the tasks added
void Logic::printMessage2(){
	int size = _listOfTasks.size();
	for (int i = 0 ; i < size ; i++) {
		cout << i+1 << display(_listOfTasks[i]) <<  endl;
	}
}

// Returns the string of a particular Task class
string Logic::display(Task task){
	ostringstream oss;
	
	oss << ". "  << task.getTaskName();
	// output completion status
	if(task.getStatus() == UNCOMPLETED) {
		oss << "(UNCOMPLETED)"; 
	} else {
		oss << "(COMPLETED)";
	}
	
	// output start, end date, time or deadline
	oss << endl;
	if(!task.getStartDate().empty()){
		oss << "From " << setw(16) << task.getStartDate() << "," << task.getStartTime() << endl
			<< "To " << setw(18) << task.getEndDate() << "," << task.getEndTime() << endl;
	} else if(!task.getDeadline().empty()){
		oss << "By " << setw(18) <<task.getDeadline() << endl;
	}
	
	return oss.str();
}

// Marks status as COMPLETED or UNCOMPLETED
void Logic::markStatus(){
	int numberToMark=atoi(parsedInformation[1].c_str());
	string status=parsedInformation[2];
	
	if(status == "yes"){
		_listOfTasks[numberToMark-1].setStatus(COMPLETED);
	} else if(status == "no"){
		_listOfTasks[numberToMark-1].setStatus(UNCOMPLETED);
	}
}

// Processes the command and inputs passed from UI
bool Logic::process(string line){

	getParsedInformation(line);
	commandChoice = parsedInformation[0];

	if(commandChoice == "add"){
		Add add;
		if(add.execute(parsedInformation)){
			_listOfTasks.push_back(add.getTask());
			printMessage(SUCCESSFULLY_ADDED);
			updateStorage();
		}

	} else if(commandChoice == "delete"){
		Delete remove;
		if(remove.execute(parsedInformation, getListofTasks())){
			_listOfTasks = remove.getNewList();
			updateStorage();
		} else {
			cout<<"Task List is empty/Wrong task input!"<<endl;
		}

	} else if(commandChoice == "edit"){
		Edit edit;
		if(edit.execute(parsedInformation, getListofTasks())){
			setListOfTasks(edit.getNewList());
			updateStorage();
		} else {
			cout<<"Task NOT edited"<<endl;
		}

	} else if(commandChoice == "display"){
		printMessage(DISPLAYING);
		printMessage2();

	} else if(commandChoice == "mark"){
		//markStatus();
		Mark mark;
		
		if (mark.isValidInput(atoi(parsedInformation[1].c_str()), _listOfTasks.size())) {
			_listOfTasks = mark.execute(parsedInformation, getListofTasks());
			printMessage(SUCCESSFULLY_MARKED);
			updateStorage();
		} else {
			printMessage(ERROR_WRONG_INPUT);
		}

	} else if(commandChoice == "exit"){
		updateStorage();
		return false;
	}
	return true;
}

vector<Task> Logic::getListofTasks(){
	return _listOfTasks;
}

vector<Task> Logic::setListOfTasks(vector<Task> newList){
	_listOfTasks = newList;
	return _listOfTasks;
}
