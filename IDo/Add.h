#ifndef ADD_H
#define ADD_H

#include <string>
#include <vector>
#include <iostream>
#include "Logic.h"
#include "Task.h"

using namespace std;

class Add {
	private:


	public:
		
		Add();
		~Add();
		Task _task;
		Task getTask();
		bool execute(vector<string> parsedInformation);
};

#endif