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


using namespace std;

#pragma once
class UserInterface {
private:
	string _userInput;
	Logic logic;

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
	void SetColor1(int value);
	void instructMessage();
};

#endif