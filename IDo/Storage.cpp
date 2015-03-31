#include "Storage.h"
#include <assert.h>

Storage::Storage () {
	ifstream readFile ("filename.txt");
	string directory;
	getline (readFile,directory);
	storageFileName=directory;
}

string Storage::getStorageFileName () {
	return storageFileName;
}

void Storage::editStorageFileName (string name) {
	storageFileName=name;
}

void Storage::updateFile (vector <Task> &temp) {
	ofstream writeFile (storageFileName);
	Status status;
	Priority priority;
	Label label;
	int _size = temp.size();
	for (int i = 0 ; i < _size ; i++) {
		writeFile << temp[i].getTaskName() << endl;
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
		switch (label) {
		case studies:
			writeFile << "studies" << endl;
			break;

		case cca:
			writeFile << "cca" << endl;
			break;

		case friends:
			writeFile << "friends" << endl;
			break;

		case family:
			writeFile << "family" << endl;
			break;

		case misc:
			writeFile << "misc" << endl;
			break;
		}

		writeFile << "__________" << endl;
	}
	writeFile << "_____" << endl;
	writeFile.close();
}

void Storage::readFile (vector <Task> &temp) {
	ifstream readFile (storageFileName);
	string line;
	string taskName;
	string startDate;
	string startTime;
	string endDate;
	string endTime;
	string status;
	string priority;
	string label;
	vector <string> tempTask;

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
			task.setTaskName(taskName);
	
			if (size == 8) {
				startDate = tempTask[1];
				startTime = tempTask[2];
				endDate = tempTask[3];
				endTime = tempTask[4];
				task.setStartDate(startDate);
				task.setStartTime(startTime);
			}
	
			if (size == 6) {
				endDate = tempTask[1];
				endTime = tempTask[2];
			}
	
			status = tempTask[size-3];
			priority = tempTask[size-2];
			label = tempTask[size-1];
	
			task.setEndDate(endDate);
			task.setEndTime(endTime);
	
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
			
	
			if (label == "studies") {
				task.setLabel(studies);
	
			} else if (label == "cca") {
				task.setLabel(cca);
	
			} else if (label == "friends") {
				task.setLabel(friends);
	
			} else if (label == "family") {
				task.setLabel(family);
	
			}  else {
				task.setLabel(misc);
			}
	
			temp.push_back(task);
			tempTask.clear();
			getline(readFile,line);
		}
	}
}