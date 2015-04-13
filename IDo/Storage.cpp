//@author A0115465H
#include "Storage.h"

const string Storage::BACKUP = "backup.txt";

Storage::Storage () {
	ifstream readFile ("filename.txt");
	string directory;
	getline (readFile,directory);
	if (directory.empty()) {
		ofstream writeFile ("filename.txt");
		writeFile << "output.txt" << endl;
		directory = "output.txt";
	}
	assert (!directory.empty());
	_storageFileName=directory;
}

//output start date & time or end date & time
string Storage::dateAndTime (Task task, bool isStartTrue) {
	ostringstream oss;
	if (isStartTrue) {
		oss << task.getStartDate() << endl << task.getStartTime() << endl;
	} else {
		oss << task.getEndDate() << endl << task.getEndTime() << endl;
	}
	return oss.str();
}

// returns the priority in string
string Storage::priorityDecider (Priority priority) {
	string answer;
	switch (priority) {
		case high:
			answer = "high";
			break;

		case medium:
			answer = "medium";
			break;

		case low:
			answer = "low";
			break;
	}
	return answer; 
}

// return the status in string
string Storage::statusDecider (Status status) {
	string answer;
	switch (status) {
		case notdone:
			answer = "notdone";
			break;

		case done:
			answer = "done";
			break;
	}
	return answer;
}

// change the status of the task 
void Storage::setTempStatus (Task &task, string status) {
	if (status == "done") {
		task.setStatus(done);
	} else if (status == "notdone") {
		task.setStatus(notdone);
	}
}

// change the priority of the task
void Storage::setTempPriority (Task &task, string priority) {
	if (priority == "high") {
		task.setPriority(high);
	} else if (priority == "medium") {
		task.setPriority(medium);
	} else if (priority == "low") {
		task.setPriority(low);
	} 
}

// returns the current directory of the storage file
string Storage::getStorageFileName () {
	return _storageFileName;
}

// changes the directory of the storage file and the directory in filename.txt
void Storage::editStorageFileName (string name) {
	_storageFileName=name;
	ofstream writeFile ("filename.txt");
	writeFile << _storageFileName << endl;
	writeFile.close();
}

// store the vector of data into file
void Storage::updateFile (vector <Task> &taskList, bool isUndoTrue) {
	string fileName;

	if (!isUndoTrue) {
		fileName = _storageFileName;
	} else {
		fileName = BACKUP;
	}

	ofstream writeFile (fileName);
	int _size = taskList.size();
	
	for (int i = 0 ; i < _size ; i++) {
		writeFile << taskList[i].getTaskName() << endl;
		writeFile << taskList[i].getRecurringIndex() << endl;
		if (!taskList[i].getStartDate().empty()) {
			writeFile << dateAndTime(taskList[i],1);
		}
		if (!taskList[i].getEndDate().empty()) {
			writeFile << dateAndTime(taskList[i],0);
		}
	writeFile << statusDecider(taskList[i].getStatus()) << endl;
	writeFile << priorityDecider(taskList[i].getPriority()) << endl;
	writeFile << taskList[i].getLabel() << endl;
	writeFile << "__________" << endl;
	}

	if (_size > 0) {
		writeFile << "_____" << endl;
	}
	writeFile.close();

	if (!isUndoTrue) {
		_log.log("Updated storage file");
	} else {
		_log.log("Backed up file");
	}
}

// read the data from file and store in the vector
void Storage::readFile (vector <Task> &taskList, bool isUndoTrue) {
	string fileName;
	string line;
	vector <string> infoFromFile;

	if (!isUndoTrue) {
		fileName = _storageFileName;
	} else {
		fileName = BACKUP;
	}
	ifstream readFile (fileName);

	getline(readFile,line);
	if (!line.empty()) {
		while (line != "_____") {
			while (line != "__________") {
				infoFromFile.push_back(line);
				getline (readFile,line);
			}
			
			Task task;
			int size = infoFromFile.size();
			string taskName = infoFromFile[0];
			int recurringIndex = atoi(infoFromFile[1].c_str());
			string startDate;
			string startTime;
			string endDate;
			string endTime;
			string status = infoFromFile[size-3];
			string priority = infoFromFile[size-2];
			string label = infoFromFile[size-1];
			
			if (size == 9) {
				startDate = infoFromFile[2];
				startTime = infoFromFile[3];
				endDate = infoFromFile[4];
				endTime = infoFromFile[5];
			}
	
			if (size == 7) {
				endDate = infoFromFile[2];
				endTime = infoFromFile[3];
			}

			task.setTaskName(taskName);
			task.setRecurringIndex(recurringIndex);
			task.setStartDate(startDate);
			task.setStartTime(startTime);
			task.setEndDate(endDate);
			task.setEndTime(endTime);
			setTempStatus(task,status);
			setTempPriority(task,priority);
			task.setLabel(label);

			taskList.push_back(task);
			infoFromFile.clear();
			getline(readFile,line);
		}
	}
	if (!isUndoTrue) {
		_log.log("Updated data from storage file");
	} else {
		_log.log("Restored data from back up file");
	}
}