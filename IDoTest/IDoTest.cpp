#include "stdafx.h"
#include "CppUnitTest.h"
#include "Add.cpp"
#include "Delete.cpp"
#include "Edit.cpp"
#include "Logic.cpp"
#include "Mark.cpp"
#include "Parser.cpp"
#include "Storage.cpp"
#include "Task.cpp"
#include "UserInterface.cpp"
#include "View.cpp"
#include "Dates.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorageTest
{		
	TEST_CLASS(StorageTest)
	{
	public:
		
		TEST_METHOD(updateStorage)
		{
			Task task;
			vector <Task> testVector;
			Storage storage;
			string temp;
			task.setTaskName("do tutorial");
			task.setStartDate("2015/01/01");
			task.setStartTime("1300");
			task.setEndDate("2015/01/02");
			task.setEndTime("1300");
			testVector.push_back(task);
			storage.updateFile (testVector);
			ifstream readFile ("output.txt");
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getTaskName());
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getStartDate());
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getStartTime());
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getEndDate());
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getEndTime());
		}
	};
}

namespace UITest
{
	TEST_CLASS(UITest)
	{
	public:
		
		TEST_METHOD(testWelcomeMessage)
		{
			UserInterface UI;
			string expected = "Good day, Jimmy. How productive would you like to be today? :)";

			Assert::AreEqual(expected, UI.welcomeMessage());
		}
	};
}

namespace ParserTest
{		
	TEST_CLASS(ParserTest)
	{
	public:

		//Test if parsed inputs are correct for mark function
		//This is a test for equivalence partition [commandchoice][number][content]
		TEST_METHOD(markInformation){
			vector<string> parsedInputs;

			string input = "mark 1 done";

			Parser parser;
			parsedInputs = parser.completeParsing(input);
			int size = parsedInputs.size();

			string expectedResults[]  = {"mark" ,"1", "done"};
			int expectedSize = 3;

			//check if the correct number of items are in the vector
			Assert::AreEqual(expectedSize, (int)parsedInputs.size());

			//check if the correct strings are in the vector
			for(int i=0; i<size; i++){
				Assert::AreEqual (expectedResults[i].c_str(), parsedInputs[i].c_str());
			}

		};

		//Test if parsed inputs are correct if a deadline task is added
		//This is a test for equivalence partition [commandchoice][content][date][time]
		TEST_METHOD(deadLineTaskInformation){
			vector<string> parsedInputs;

			string input = "add task by 9999/9/9,2323";

			Parser parser;
			parsedInputs = parser.completeParsing(input);
			int size = parsedInputs.size();

			string expectedResults[]  = {"add" ,"task ", "9999/9/9" , "2323"};
			int expectedSize = 4;

			//check if the correct number of items are in the vector
			Assert::AreEqual(expectedSize, (int)parsedInputs.size());

			//check if the correct strings are in the vector
			for(int i=0; i<size; i++){
				Assert::AreEqual (expectedResults[i].c_str(), parsedInputs[i].c_str());
			}
		};

		//Test if parsed inputs are correct if a timed-task is added
		TEST_METHOD(timedTaskInformation){
			vector<string> parsedInputs;

			string input = "add task from 5555/9/9,2323 to 9999/9/9,2346";

			Parser parser;
			parsedInputs = parser.completeParsing(input);
			int size = parsedInputs.size();

			string expectedResults[]  = {"add" ,"task ", "5555/9/9" , "2323", "9999/9/9" , "2346"};
			int expectedSize = 6;

			//check if the correct number of items are in the vector
			Assert::AreEqual(expectedSize, (int)parsedInputs.size());

			//check if the correct strings are in the vector
			for(int i=0; i<size; i++){
				Assert::AreEqual (expectedResults[i].c_str(), parsedInputs[i].c_str());
			}
		};

		//Test if parsed inputs are correct if a floating task is added
		TEST_METHOD(floatingTaskInformation){
			vector<string> parsedInputs;

			string input = "add how are you";

			Parser parser;
			parsedInputs = parser.completeParsing(input);
			int size = parsedInputs.size();

			string expectedResults[]  = {"add" ,"how are you"};
			int expectedSize = 1;

			//check if the correct number of items are in the vector
			Assert::AreEqual(expectedSize, (int)parsedInputs.size());

			//check if the correct strings are in the vector
			for(int i=0; i<size; i++){
				Assert::AreEqual (expectedResults[i].c_str(), parsedInputs[i].c_str());
			}
		};

		//Test if parsed inputs are correct for edit function
		TEST_METHOD(editInformation){
			vector<string> parsedInputs;

			string input = "edit 1 taskname testing";

			Parser parser;
			parsedInputs = parser.completeParsing(input);
			int size = parsedInputs.size();

			string expectedResults[]  = {"edit" ,"1", "taskname" , "testing"};
			int expectedSize = 4;

			//check if the correct number of items are in the vector
			Assert::AreEqual(expectedSize, (int)parsedInputs.size());

			//check if the correct strings are in the vector
			for(int i=0; i<size; i++){
				Assert::AreEqual (expectedResults[i].c_str(), parsedInputs[i].c_str());
			}
		};

		//Test if parsed inputs are correct if a timed-task is added
		TEST_METHOD(wrongStartDateInformation){
			vector<string> parsedInputs;

			string input = "add task from 2099/2/30,2323 to 9999/9/9,2346";

			Parser parser;
			parsedInputs = parser.completeParsing(input);
			int size = parsedInputs.size();

			string expectedResults[]  = {"add"};
			int expectedSize = 1;

			//check if the correct number of items are in the vector
			Assert::AreEqual(expectedSize, (int)parsedInputs.size());

			//check if the correct strings are in the vector
			for(int i=0; i<size; i++){
				Assert::AreEqual (expectedResults[i].c_str(), parsedInputs[i].c_str());
			}
		};
	};
}

namespace LogicTest
{
	TEST_CLASS (MarkTest)
	{
	public:
		TEST_METHOD(isValidInput)
		{
			vector <string> parsedInfo;
			parsedInfo.push_back("mark");
			parsedInfo.push_back("1");
			parsedInfo.push_back("done");

			//set the task list from logic size = 1
			int taskListSize = 1;

			Mark markstatus;
			bool isValidInput = markstatus.isValidInput(parsedInfo, taskListSize);
			Assert::IsTrue(isValidInput);
		};

		TEST_METHOD(execute)
		{
			vector <Task> taskListFromLogic;
			Task task;
			task.setTaskName("have dinner with anna");
			task.setStatus(notdone);
			taskListFromLogic.push_back(task);

			Status expectedstatus = notdone;
			Status outputstatus = task.getStatus();
			Assert::AreEqual(expectedstatus, outputstatus);
			
			vector <string> parsedInfo;
			parsedInfo = { "mark", "1", "done" };
			
			Mark markStatus;
			markStatus.execute(parsedInfo, taskListFromLogic);

			expectedstatus = done;
			outputstatus = taskListFromLogic[0].getStatus();
			Assert::AreEqual(expectedstatus, outputstatus);

		};
	};
}

//creating a template specialization of the ToString function
//for unit testing of enum Status type
namespace Microsoft{
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<>
			static std::wstring ToString<Status>(const Status  & status) {
				return L"notdone";
			}

		}
	}
}

namespace LogicTest
{
	TEST_CLASS(Add)
	{
	public:
		TEST_METHOD(execute)
		{
			vector <string> parsedInfo;
			parsedInfo.push_back("add");
			parsedInfo.push_back("cut nails");

			vector <Task> listOfTasks;
			Logic add;
			add.setListOfTasks(listOfTasks);
			Add adding;
			adding.execute();

			}
		};
	};
}