#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include "Parser.h"
#include "Logic.h"

using namespace std;

class UserInterface {
public:
	void displayDate();
	void qotd();
	void displayDivider();
	void welcomeMessage();
	void commandInput();
};

#endif