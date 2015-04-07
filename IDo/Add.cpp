#include "Add.h"

bool Add::isRecurring(vector <string> parsedInfo) {
	int size = parsedInfo.size();

	for (int i = 0; i < size; i++) {
		cout << "Parsedinfo: "<< parsedInfo[i] << endl;
	}
	cout << "parsedInfo size:" << size << endl;
	if (size > 4 && parsedInfo[4] == "every") {
		return true;
	} else if(size > 6 &&  parsedInfo[6] == "every") {
		return true;
	} else {
		cout << "im here" << endl;
		return false;
	}

	return true;
}

bool Add::execute(vector<string> parsedInformation){
	int size = parsedInformation.size();

	for (int i = 0; i < size; i++) {
		cout << parsedInformation[i] << endl;
	}

	cout << "adddexecute" << endl;
	if (isRecurring(parsedInformation)) {	//recurring
		if (size == 7) {	//deadline recurring no "for"
			RTask rtask;
			int interval = stoi(parsedInformation[5]);
			cout << "interval reached" << endl;
			rtask.setAbstrInfo(parsedInformation);
			cout << "setabstrInfor reached" << endl;
			rtask.setInterval(interval);
			cout << "setInterval reached" << endl;
			rtask.setPeriod(parsedInformation[6]);
			cout << "set Period" << endl;
			rtask.setNoOfOccurrences(5);
			cout << "setnoof occureencessfs" << endl;
			rtask.setFirstOccur(parsedInformation);
			cout << "setfirstovver" << endl;
			rtask.generateOccurs();
			cout << "generateoccursrs" << endl;

			_listOfOccurrences = rtask.getListOfOccurrences();
		} else if(size == 9) { //timetask recurring no "for"
			RTask rtask;

			rtask.setAbstrInfo(parsedInformation);
			cout << "setabstrInfor reached" << endl;
			rtask.setInterval(stoi(parsedInformation[7]));
			cout << "setInterval reached" << endl;
			
			rtask.setPeriod(parsedInformation[8]);
			cout << "set Period" << endl;
			
			rtask.setNoOfOccurrences(5);
			cout << "setnoof occureencessfs" << endl;

			rtask.setFirstOccur(parsedInformation);
			cout << "setfirstovver" << endl;
			rtask.generateOccursForTimedTask();
			cout << "generateoccursrs" << endl;

			_listOfOccurrences = rtask.getListOfOccurrences();
		} else if(size == 10) {
			RTask rtask;

			rtask.setAbstrInfo(parsedInformation);
			cout << "setabstrInfor reached" << endl;
			rtask.setInterval(stoi(parsedInformation[5]));
			cout << "setInterval reached" << endl;
			
			rtask.setPeriod(parsedInformation[6]);
			cout << "set Period" << endl;
			
			rtask.setPeriod2(parsedInformation[9]);
			cout << "set Period2 reched" << endl;

			rtask.setLimit(parsedInformation[8]);
			cout << "set limit reched" <<endl;

			rtask.setFirstOccur(parsedInformation);
			cout << "setfirstovver" << endl;
			rtask.generateOccurs();
			cout << "generateoccursrs" << endl;

			_listOfOccurrences = rtask.getListOfOccurrences();
		} else if(size == 12) {
			RTask rtask;

			rtask.setAbstrInfo(parsedInformation);
			cout << "setabstrInfor reached" << endl;
			rtask.setInterval(stoi(parsedInformation[7]));
			cout << "setInterval reached" << endl;
			
			rtask.setPeriod(parsedInformation[8]);
			cout << "set Period" << endl;
			
			rtask.setPeriod2(parsedInformation[11]);
			cout << "set Period2 reched" << endl;

			rtask.setLimit(parsedInformation[10]);
			cout << "set limit reched" <<endl;

			rtask.setFirstOccur(parsedInformation);
			cout << "setfirstovver" << endl;
			rtask.generateOccursForTimedTask();
			cout << "generateoccursrs" << endl;

			_listOfOccurrences = rtask.getListOfOccurrences();
		} 
	} else if(!isRecurring(parsedInformation)){
		cout << "sizzze: " << size <<endl;
			if (size == 2) {
				_task.setTaskName(parsedInformation[1]);
			} else if (size == 4){ //task with deadlines only i.e. add tutorials by 12/12/2015,2323
				_task.setTaskName(parsedInformation[1]);
				_task.setEndDate(parsedInformation[2]);
				_task.setEndTime(parsedInformation[3]);
			} else if (size == 6) { //timed-task i.e. add tutorials from 2015/12/12,2323 to 2015/12/12,2323
				_task.setTaskName(parsedInformation[1]);
				_task.setStartDate(parsedInformation[2]);
				_task.setStartTime(parsedInformation[3]);
				_task.setEndDate(parsedInformation[4]);
				_task.setEndTime(parsedInformation[5]);
			} else  {
				return false;
			}
	} else {
		return false;
	}
	
	return true;
}

vector <Task> Add::getOccurrences () {
		return _listOfOccurrences;
}

Task Add::getTask(){
	return _task;
}
