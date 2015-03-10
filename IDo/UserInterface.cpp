#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include "Storage.h"

using namespace std;

void welcomeMessage();
void displayDate();
void displayDivider();
void qotd();
string commandInput();
void userInstruct();

int main()
{
    displayDate();
    qotd();
    displayDivider();
    welcomeMessage();
    displayDivider();
    userInstruct();
    displayDivider();
//    commandInput();
	Storage testStorage;
	string fileName;
	cin >> fileName;
	testStorage.editStorageFileName(fileName);
	testStorage.readFromFile();
    system("pause");
    return 0;
}

void welcomeMessage() {
    cout << "Good day, Jimmy. How efficient would you like to be today? :)" << endl << endl;
    return;
}

void displayDivider() {
    cout << "*************************************************************" << endl;
	cout << " " << endl;
}

void displayDate() {
    char date[9];
	_strdate(date);
	cout << "------------------------- " << date << " -------------------------" << endl;
}

void qotd()
{
	/*
    int lineCount = 0;
    int randomQuote_int = 0;
    string line = "";
    vector<string>randomQuote_vect;
    
    ifstream quoteFile ("quotes.txt");
    
    {
        srand(time_t(0));
        if (quoteFile.is_open())
        {
            while (!quoteFile.eof())
            {
                getline(quoteFile, line);
                if (line != " ")
                {
                    randomQuote_vect.push_back(line);
                    lineCount++;
                }
            }
            randomQuote_int = rand() % lineCount;
			*/
            cout << "Quote of the day: " << endl;
//            cout << randomQuote_vect[randomQuote_int] << endl;
//          quoteFile.close();
//        }
            
//    }
}

string commandInput() {
    string inputString;
    getline (cin, inputString);
    return inputString;
}

void userInstruct() {
    cout << "To add a task, type 'add <task> from <time> to <time>'." << endl;
    cout << "To edit a task, type 'edit...." << endl;
    cout << "To delete task, type 'delete..." << endl << endl;
    
    return;
}