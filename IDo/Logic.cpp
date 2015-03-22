#include "Logic.h"
#include <sstream>
#include <assert.h>


const string SUCCESSFULLY_ADDED = "[Added Successfully]";
const string DISPLAYING = "[List of Tasks]";
const string ERROR_WRONG_INPUT = "Error: Wrong Input!";

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
		printMessage2(display());
	} else if(commandChoice == "mark"){
		markStatus();
	} else if(commandChoice == "exit"){
		updateStorage();
		return false;
	}
	return true;
}

void Logic::getParsedInformation(string line){

	Parser parser;

	userInput = line;

	//pass to parser and process
	parsedInformation = parser.completeParsing(userInput);

}

void Logic::updateStorage () {
	Storage saveToDisk;
	saveToDisk.updateFile (_listOfTasks);
}

void Logic::printMessage(string message){
	cout << endl <<  message <<  endl << endl;
}

void Logic::printMessage2(string message){
	cout << message <<  endl;
}

//Pre-condition:none
//strings all the tasks in the vector 
//Post: returns the string
string Logic::display(){

	ostringstream oss;
	int size=_listOfTasks.size();
	for (int i = 0; i < size; i++) {

		oss << endl;
		oss << i+1 << ". "  << _listOfTasks[i].getTaskName();
		if(_listOfTasks[i].getStatus() == UNCOMPLETED) {
			oss << "(UNCOMPLETED)"; 
		} else {
			oss << "(COMPLETED)";
		}
		oss << endl;
		if(!_listOfTasks[i].getStartDate().empty()){
			oss << "From " << setw(16) << _listOfTasks[i].getStartDate() << "," << _listOfTasks[i].getStartTime() << endl
				<< "To " << setw(18) << _listOfTasks[i].getEndDate() << "," << _listOfTasks[i].getEndTime() << endl;
		} else if(!_listOfTasks[i].getDeadline().empty()){
			oss << "By " << setw(18) <<_listOfTasks[i].getDeadline() << endl;
		}
	}
	return oss.str();
}

void Logic::markStatus(){
	int numberToMark=atoi(parsedInformation[1].c_str());
	string status=parsedInformation[2];
	if(status == "yes"){
		_listOfTasks[numberToMark-1].setStatus(COMPLETED);
	} else if(status == "no"){
		_listOfTasks[numberToMark-1].setStatus(UNCOMPLETED);
	}
}

vector<Task> Logic::getListofTasks(){
	return _listOfTasks;
}

vector<Task> Logic::setListOfTasks(vector<Task> newList){
	_listOfTasks = newList;
	return _listOfTasks;
}