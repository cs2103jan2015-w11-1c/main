#include "Storage.h"
#include <assert.h>

const string Storage::BACKUP = "backup.txt";

Storage::Storage () {
	ifstream readFile ("filename.txt");
	string directory;
	getline (readFile,directory);
	_storageFileName=directory;
}

string Storage::getStorageFileName () {
	return _storageFileName;
}

void Storage::editStorageFileName (string name) {
	_storageFileName=name;
	ofstream writeFile ("filename.txt");
	writeFile << _storageFileName << endl;
	writeFile.close();
}

void Storage::updateFile (vector <Task> &temp, bool isUndoTrue) {
	string fileName;
	if (!isUndoTrue) {
		fileName = _storageFileName;
	} else {
		fileName = BACKUP;
	}
	ofstream writeFile (fileName);
	Status status;
	Priority priority;
	string label;
	int _size = temp.size();
	for (int i = 0 ; i < _size ; i++) {
		writeFile << temp[i].getTaskName() << endl;
		writeFile << temp[i].getRecurringIndex() << endl;
		if (!temp[i].getStartDate().empty()) {
			writeFile << temp[i].getStartDate() << endl;
			writeFile << temp[i].getStartTime() << endl;
		}
		if (!temp[i].getEndDate().empty()) {
			writeFile << temp[i].getEndDate() << endl;
			writeFile << temp[i].getEndTime() << endl;
		}

		status = temp[i].getStatus();
		switch (status) {
		case done:
			writeFile << "done" << endl;
			break;

		case notdone:
			writeFile << "notdone" << endl;
			break;
		}

		priority = temp[i].getPriority();
		switch (priority) {
		case high:
			writeFile << "high" << endl;
			break;

		case medium:
			writeFile << "medium" << endl;
			break;

		case low:
			writeFile << "low" << endl;
			break;

		case none:
			writeFile << "none" << endl;
			break;
		}

	label = temp[i].getLabel();
	writeFile << label << endl;
	
	writeFile << "__________" << endl;
	}

	if (_size > 0) {
		writeFile << "_____" << endl;
	}
	writeFile.close();
}

void Storage::readFile (vector <Task> &temp, bool isUndoTrue) {
	string fileName;
	string line;
	string taskName;
	int recurringIndex;
	string startDate;
	string startTime;
	string endDate;
	string endTime;
	string status;
	string priority;
	string label;
	vector <string> tempTask;

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
				tempTask.push_back(line);
				getline (readFile,line);
			}
	
			Task task;
			int size = tempTask.size();
			taskName = tempTask[0];
			recurringIndex = atoi(tempTask[1].c_str());
			task.setTaskName(taskName);
			task.setRecurringIndex(recurringIndex);
			
			if (size == 9) {
				startDate = tempTask[2];
				startTime = tempTask[3];
				endDate = tempTask[4];
				endTime = tempTask[5];
				task.setStartDate(startDate);
				task.setStartTime(startTime);
				task.setEndDate(endDate);
				task.setEndTime(endTime);
			}
	
			if (size == 7) {
				endDate = tempTask[2];
				endTime = tempTask[3];
				task.setEndDate(endDate);
				task.setEndTime(endTime);
			}
	
			status = tempTask[size-3];
			priority = tempTask[size-2];
			label = tempTask[size-1];
	
			if (status == "done") {
				task.setStatus(done);
	
			} else {
				task.setStatus(notdone);
			}
	
	
			if (priority == "high") {
				task.setPriority(high);
	
			} else if (priority == "medium") {
				task.setPriority(medium);
	
			} else if (priority == "low") {
				task.setPriority(low);
	
			} else {
				task.setPriority(medium);
			}
		
			task.setLabel(label);

			temp.push_back(task);
			tempTask.clear();
			getline(readFile,line);
		}
	}
}