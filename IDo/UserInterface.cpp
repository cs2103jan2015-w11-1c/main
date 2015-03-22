#include "UserInterface.h"

using namespace std;

UserInterface::UserInterface() {
}

UserInterface::~UserInterface() {
} 

// displays today's date at the launch of the program
void UserInterface::displayDate() {
    char date[9];
	_strdate_s(date);
	cout << "------------------------- " << date << " -------------------------" << endl;
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
        cout << "Quote of the day: " << endl;
        cout << randomQuote_vect[randomQuote_int] << endl << endl;
        quoteFile.close();
	}
}

void UserInterface::displayDivider() {
	cout << " " << endl;
    cout << "*************************************************************" << endl;
	cout << " " << endl;
}

string UserInterface::welcomeMessage() {
    string welcome =  "Good day, Jimmy. How productive would you like to be today? :)";
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

//Take in user inputs
string UserInterface::receiveInput() {
	string fromUser;
	getline(cin, fromUser);
	_userInput = fromUser;

	return _userInput;
}

//Get UserInputs
string UserInterface::getUserInputs() {
	return _userInput;
}