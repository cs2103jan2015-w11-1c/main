#include "UserInterface.h"
#include <Windows.h>
#include <iomanip>

using namespace std;

UserInterface::UserInterface() {
}

UserInterface::~UserInterface() {
} 

void UserInterface::SetColor1(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

// displays today's date at the launch of the program
void UserInterface::displayDate() {
    char date[9];
	_strdate_s(date);
	cout << "------------------------- " << date << " -------------------------" << endl;
}

// displays commands available at launch of program
void UserInterface::instructMessage() {
	cout << "Here are some commands: " << endl; 

	SetColor1(2);
	cout << setw(15) << "add";
	SetColor1(2);
	cout << setw(15) << "edit";
	SetColor1(2);
	cout << setw(15) << "delete";
	SetColor1(2);
	cout << setw(15) << "clear" << endl;
	SetColor1(5);
	cout << setw(22) << "search";
	SetColor1(5);
	cout << setw(15) << "mark";
	SetColor1(5);
	cout << setw(15) << "view" << endl;

	SetColor1(7);
	cout << "Let's get started!" << endl;
}

// displays quote of the day at the launch of the program
void UserInterface::qotd() {
    int lineCount = 0;
    int randomQuote_int = 0;
    string line = "";
    vector<string>randomQuote_vect;
    
    ifstream quoteFile ("quotes.txt");
    
    srand(time_t(0));
    if (quoteFile.is_open()) {
		while (!quoteFile.eof()) {
                getline(quoteFile, line);
                if (line != " ") {
                    randomQuote_vect.push_back(line);
                    lineCount++;
				}
            }
		randomQuote_int = rand() % lineCount;
		SetColor1(6); // yellow
        cout << "Quote of the day: " << endl;
        cout << randomQuote_vect[randomQuote_int] << endl << endl;
        quoteFile.close();
	}
}

void UserInterface::displayDivider() {
	cout << " " << endl;
	SetColor1(3); // cyan
    cout << "*************************************************************" << endl;
	cout << " " << endl;
}

string UserInterface::welcomeMessage() {
    string welcome =  "Good day, Jim. How productive would you like to be today? :)";
	SetColor1(15); // bright white
	cout << welcome;
	return welcome;
}

void UserInterface::process() {
	bool carryOn = true;
	Logic logic;

	while(carryOn){
		carryOn = logic.process(receiveInput());
	}
}

// Take in user inputs
string UserInterface::receiveInput() {
	string fromUser;

	getline(cin, fromUser);
	_userInput = fromUser;
	return _userInput;
}

// Getter for UserInputs
string UserInterface::getUserInputs() {
	return _userInput;
}