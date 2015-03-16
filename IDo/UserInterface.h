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
#include "Task.h"
#include "Storage.h"

using namespace std;

#pragma once
class UserInterface {
private:

	string GUIfeedback;
	Logic scheduler;

public:

	UserInterface(void);
	~UserInterface(void);

	void displayDate();
	void qotd();
	void displayDivider();
	string welcomeMessage();
	void commandInput();
};

#endif