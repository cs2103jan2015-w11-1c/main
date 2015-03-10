#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include "UserInterface.h"
#include "Logic.h"
#include "Parser.h"

using namespace std;

int main() {
	UserInterface UI;
    UI.displayDate();
    UI.qotd();
    UI.displayDivider();
    UI.welcomeMessage();
    UI.displayDivider();
    UI.commandInput();

	system("pause");
    return 0;
}

