//@author A0114010L
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include "UserInterface.h"
#include "Logic.h"
#include "Parser.h"
#include "Storage.h"

using namespace std;

/**
* This is a project that works as a scheduler that has many functions.
* By default data will be stored in output.txt as the same file as where this program is located. 
* This program will generate backup.txt, filename.txt in the same folder as where this program is located. 
* You can add a text file named quotes.txt in the same folder where this program  is located. 
* A random quote will be selected at the launch of the program. 
* Do not name the file to store your data the same as above names in the same folder. 
* After exiting, the desired text file will be updated with database
* Press the Enter key after typing the desired functions in the prescribed manner
* The program expects an input otherwise it will not continue to prompt for commands
* The command format is given by the sample interaction below:
* Example command: add study hard (add floating task)
* Example command: add hand in tutorial by 2359 (add deadline task)
* Example command: edit 1 taskname exercise everyday (edit task name)
* Example command: view all (list all the tasks added)
* Example command: delete 1 (delete the first task)
* Example command: view done (view all done tasks)
* Example command: view high (view all high priority tasks)
* Example command: clear (clear all tasks)
* Example command: mark 1 high (mark the first task as priority high)
* Example command: mark 1 school (label the first task as school)
* Example command: search exercise (search for exercise)
* Example command: store new (change the file to store data to new.txt)
* Example command: sort deadline (sort by deadline)
*/

int main() {
	UserInterface UI;

    UI.displayDate();
    UI.qotd();
    UI.displayDivider();
    UI.welcomeMessage();
    UI.displayDivider();
	UI.instructMessage();
	UI.displayDivider();
	UI.process();
    return 0;
}

