#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include "UserInterface.h"
#include "Logic.h"
#include "Parser.h"
#include "Task.h"
#include "Storage.h"

using namespace std;

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
	
	system("pause");
    return 0;
}

