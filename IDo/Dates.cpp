//@author A0111624W
#include "Dates.h"

Dates::Dates(){
//	getTodayDate();
}

Dates::~Dates(){

}

string Dates::getTodayDate(){
	time_t currentTime;
	struct tm localTime;

	time( &currentTime );                   // Get the current time
	localtime_s( &localTime , &currentTime );  // Convert the current time to the local time

	day    = localTime.tm_mday;
	month  = localTime.tm_mon + 1;
	year   = localTime.tm_year + 1900;

	date d(year, month, day);
	todayDate = to_simple_string(d);

	return todayDate;
}

//Post: Returns true if string contains the required delimiters for dates i.e. 10/10, 2009/10/10
bool Dates::checkDelimiters(string date){
	
	store.clear();
	string input = date;
	string temp;
	string delimiters = "./";

	int count=0;

	//Extract the year month day of date
	size_t found = input.find_first_of(delimiters);
	while(found!=string::npos && found!=0) {
		temp = input.substr(0,found);

		for(int i = 0; i < temp.size(); i++) { 
			if(!isdigit(temp[i])){
				return false;
			}
		}

		store.push_back(temp);
		input = input.substr(found+1, input.size()-1);
		found = input.find_first_of(delimiters);
		count ++;
	} 

	if(count == 2 && !input.empty()) {
		store.push_back(input);
	} else if (count == 1 && !input.empty()) {
		store.push_back(input);
	} else {
		return false;
	}
	
	return true;
}
//Post:: Returns true if format is YYYY/MM/DD or DD/MM/YYYY or MM/DD or DD/MM

bool Dates::checkYearMthDayFormat(){
	int storeSize = store.size();
	string tempYear;
	string tempMth;
	string tempDay;

	if(storeSize == 3) {
		if (store[0].size() == 4) {
			tempYear =  store[0];
			tempMth = store[1];
			tempDay = store[2];
			storeDates(tempYear, tempMth, tempDay);
		} else {
			return false;
		}
	} else if (storeSize == 2) {
		if(store[0].size() == 2 || store[0].size() == 1) {
			tempYear = "2015";
			tempMth = store[0];
			tempDay = store[1];
			storeDates(tempYear, tempMth, tempDay);
		} else {
			return false;
		}
	} else {
		return false;
	}

	return true;
}

//Post: Returns true if there are 2/3 pieces of numbers stored.
//		Stores year, month, day if store size is 3.
//		Stores month, day if store size is 2.
//		Returns false if others.
bool Dates::storeDates(string tempYear, string tempMth, string tempDay){

	if(store.size() == 3) {
		year = atoi(tempYear.c_str());
		month = atoi(tempMth.c_str());
		day = atoi(tempDay.c_str());
	} else if (store.size() == 2) {
		year = atoi(tempYear.c_str());
		month = atoi(tempMth.c_str());
		day = atoi(tempDay.c_str());
	} else {
		return false;
	}

	return true;
}


int Dates::checkDay(string daysInName) {
	if(daysInName == "mon" || daysInName == "monday") {
		return 1;
	} else if (daysInName == "tues" || daysInName == "tuesday") {
		return 2;
	} else if (daysInName == "wed" || daysInName == "wednesday") {
		return 3;
	} else if (daysInName == "thurs" || daysInName == "thursday") {
		return 4;
	} else if (daysInName == "fri" || daysInName == "friday") {
		return 5;
	} else if (daysInName == "sat" || daysInName == "saturday") {
		return 6;
	} else if (daysInName == "sun" || daysInName == "sunday") {
		return 7;
	} else {
		return 8;
	}
}

string Dates::datesGivenDays(string inputDate, string daysInName) {

	date d(from_string(inputDate));

	greg_weekday day(checkDay(daysInName));
	
	string date = to_simple_string(next_weekday(d, day));

	return date;
}

string Dates::datesFromToday(int numberOfDays){

	date d1(from_simple_string(getTodayDate()));
	date_duration dd(numberOfDays);
	string newDate;
	newDate = to_simple_string(d1 + dd);

	return newDate;
}

//Post: Returns a string of date in the format of year/month/day
bool Dates::checkDateFormat(string input){
	
	if(!checkDelimiters(input)) {
//		cout << "Error: Date format is wrong." <<endl;
		return false;
	} 

	if(!checkYearMthDayFormat()){
//		cout << "Error: Date format1 is wrong." <<endl;
		return false;
	} 

	return true;
}

//This checks if date is valid
//Post: Returns true if valid, Returns false if invalid
bool Dates::isDateValid(string dateinput){

	if(!checkDateFormat(dateinput)) {
		return false;
	} else {
		try{
			date d(year, month, day);
			dateCheckedFormat = to_simple_string(d);
		} catch (exception& e) {
			cout<< "[ERROR] " << e.what() << endl << endl;
			return false;
		}
	}
	
	date today = day_clock::local_day();

	int size = dateCheckedFormat.size();
	
	try{
		date dateToCheck(from_simple_string(dateCheckedFormat));
		days difference = dateToCheck - today;

		if (difference < days(0)) {
			cout << "[ERROR] Check that the date is not before today " << today << endl << endl;
			return false;
		}
	} catch (exception& e) {
		cout<< "[ERROR] " << e.what() << endl << endl;
		return false;
	}
	
	return true;
}


string Dates::getFormattedDates(){
	return dateCheckedFormat;
}

