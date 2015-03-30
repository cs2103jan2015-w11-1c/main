#include "Storage.h"
#include <assert.h>

Storage::Storage () {
	storageFileName="output.txt";
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
		
	}
	writeFile.close();
}