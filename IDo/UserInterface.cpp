#include "UserInterface.h"
#include "Logic.h"
#include "Parser.h"
#include "Task.h"
#include "Storage.h"

using namespace std;

UserInterface::UserInterface(void){
}

UserInterface::~UserInterface(void){
}

void UserInterface::displayDate() {
    char date[9];
	_strdate_s(date);
	cout << "------------------------- " << date << " -------------------------" << endl;
}

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
	cout<<welcome;

	return welcome;
}


void UserInterface::commandInput() {
	string command;
	cin >> command;
	
	while (command != "exit") {
		if (command == "add") {
			string inputLine;
			cin.ignore();
			getline (cin, inputLine);
			scheduler.add (inputLine);
		}
		else if (command == "display") {
			displayDivider();
			cout << endl << scheduler.display();
		}
		else if (command == "delete") {
			int numberToDelete;
			cin >> numberToDelete;
			cout << endl << scheduler.del (numberToDelete-1);
		}
		else if (command == "edit") {
			string inputLine;
			getline (cin, inputLine);
			cout << scheduler.edit(inputLine);
		}
		else{

			cout<<"Wrong Command";
		}

		displayDivider();

		cin >> command;
	}
	scheduler.updateStorage();
}