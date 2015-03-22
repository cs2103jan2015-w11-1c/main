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
	for (int i = 0 ; i < temp.size() ; i++) {
		writeFile << temp[i].getTaskName() << endl;
		if(!temp[i].getStartDate().empty()){
			writeFile << temp[i].getStartDate() << endl;
			writeFile << temp[i].getStartTime() << endl;
			writeFile << temp[i].getEndDate() << endl;
			writeFile << temp[i].getEndTime() << endl;
		} else if(!temp[i].getDeadline().empty()){
			writeFile << temp[i].getDeadline() << endl;
		}
		writeFile << endl;
	}
	writeFile.close();
}