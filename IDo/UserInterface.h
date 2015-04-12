#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <ctime>
#include <time.h>
#include <Windows.h>
#include "Logic.h"
#include "Log.h"


using namespace std;

#pragma once
class UserInterface {
private:
	string _userInput;
	Logic _logic;
	Log _log;

	void SetColor1(int value);
	void readFile();
	string receiveInput();

public:
	UserInterface();
	~UserInterface();

	void displayDate();
	void qotd();
	void displayDivider();
	string welcomeMessage();
	void instructMessage();
	void process();
	string getUserInputs();
};

#endif