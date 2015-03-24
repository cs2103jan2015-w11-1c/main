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
#include "Log.h"

using namespace std;

#pragma once
class UserInterface {
private:
	string _userInput;

public:
	UserInterface();
	~UserInterface();

	void displayDate();
	void qotd();
	void displayDivider();
	string welcomeMessage();
	void process();
	string receiveInput();
	string getUserInputs();
};

#endif