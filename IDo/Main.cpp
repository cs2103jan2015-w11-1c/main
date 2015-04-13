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
* The intended text file for editing must first be created in the same directory as TextBuddy
* To use function add, which adds strings with an ordinal number preceding it type: add {string}
* To use function display, which displays all existing strings type: display
* To use function delete, which deletes an entry of choice type: delete {position of string}
* To use function clear, which deletes all the entries type: clear
* To use function exit, which ends user operation type: exit
* After exiting, the desired text file will be updated and saved to disk
* Press the Enter key after typing the desired functions in the prescribed manner
* The program expects an input otherwise it will not continue to prompt for commands
* The command format is given by the sample interaction below:
c:> TextBuddy.exe mytextfile.txt
Welcome to TextBuddy. mytextfile.txt is ready for use
command: add little brown fox
added to mytextfile.txt: “little brown fox”
command: display
1. little brown fox
command: add jumped over the moon
added to mytextfile.txt: “jumped over the moon”
command: display
1. little brown fox
2. jumped over the moon
command: delete 2
deleted from mytextfile.txt: “jumped over the moon”
command: display
1. little brown fox
command: clear
all content deleted from mytextfile.txt
command: display
mytextfile.txt is empty
command: exit
c:>
@author group w11-1c
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

