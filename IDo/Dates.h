#ifndef DATES_H
#define DATES_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>
#include "boost/date_time/gregorian/gregorian.hpp" 

using namespace std;
using namespace boost::gregorian;

class Dates{
private:

	int year;
	int month;
	int day;
	string todayDate;
	string dateCheckedFormat;

	vector<string> store;
	bool checkDelimiters(string date);
	bool checkYearMthDayFormat();;
	bool storeDates(string, string, string);

public:
	
	Dates();
	~Dates();
	bool checkDateFormat(string date);
	bool isDateValid(string input);
	bool checkDateWithToday();
	string getFormattedDates();
	string getTodayDate();
	int checkDay(string);
	string datesGivenDays(string, string);
	string datesFromToday(int);
};

#endif