#include "stdafx.h"
#include "CppUnitTest.h"
#include "Add.cpp"
#include "Dates.cpp"
#include "Delete.cpp"
#include "Edit.cpp"
#include "Log.cpp"
#include "Logic.cpp"
#include "Mark.cpp"
#include "Parser.cpp"
#include "RTask.cpp"
#include "Search.cpp"
#include "Sort.cpp"
#include "Storage.cpp"
#include "Task.cpp"
#include "UserInterface.cpp"
#include "View.cpp"

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
			string directory;
			task.setTaskName("do tutorial");
			task.setStartDate("2015-Apr-13");
			task.setStartTime("1300");
			task.setEndDate("2015-Apr-14");
			task.setEndTime("1300");
			testVector.push_back(task);
			storage.updateFile (testVector,0);
			ifstream readDirectory ("filename.txt");
			getline(readDirectory,directory);
			readDirectory.close();
			ifstream readFile (directory);
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getTaskName());
			getline(readFile,temp);
			Assert::AreEqual (atoi(temp.c_str()), 0);
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getStartDate());
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getStartTime());
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getEndDate());
			getline(readFile,temp);
			Assert::AreEqual (temp, task.getEndTime());
			readFile.close();
		}

		TEST_METHOD(readFromStorage)
		{
			Task task;
			vector <Task> testVector;
			vector <Task> readVector;
			Storage storage;
			string temp;
			string directory;
			task.setTaskName("do tutorial");
			task.setStartDate("2015-Apr-13");
			task.setStartTime("1300");
			task.setEndDate("2015-Apr-14");
			task.setEndTime("1300");
			testVector.push_back(task);
			storage.updateFile (testVector,0);
			storage.readFile (readVector,0);
			Assert::AreEqual (testVector[0].getTaskName(), readVector[0].getTaskName());
			Assert::AreEqual (testVector[0].getStartDate(), readVector[0].getStartDate());
			Assert::AreEqual (testVector[0].getStartTime(), readVector[0].getStartTime());
			Assert::AreEqual (testVector[0].getEndDate(), readVector[0].getEndDate());
			Assert::AreEqual (testVector[0].getEndTime(), readVector[0].getEndTime());
		}

		TEST_METHOD(editStorageFile)
		{
			Storage storage;
			string newFile = "newfile!.txt";
			string expected = "newfile!.txt";
			string read;
			storage.editStorageFileName("newfile!.txt");
			ifstream readFile ("filename.txt");
			getline(readFile,read);
			Assert::AreEqual(expected,read);
			read = storage.getStorageFileName();
			Assert::AreEqual(expected,read);
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

			string input = "add task by 9999/9/9 2323";

			Parser parser;
			parsedInputs = parser.completeParsing(input);
			int size = parsedInputs.size();

			string expectedResults[]  = {"add" ,"task", "9999-Sep-09" , "2323"};
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

			string input = "add task from 5555/9/9 2323 to 9999/9/9 2346";

			Parser parser;
			parsedInputs = parser.completeParsing(input);
			int size = parsedInputs.size();

			string expectedResults[]  = {"add" ,"task", "5555-Sep-09" , "2323", "9999-Sep-09" , "2346"};
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
			int expectedSize = 2;

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
	TEST_CLASS (LogicTest)
	{
	public:
		TEST_METHOD(isValidInput)
		{
			Logic logic;
			Mark markStatus;
			vector <Task> test;
			Status expected = done;
			logic.process("add hello");
			logic.process("mark 1 done");
			test = logic.getListOfTasks();
			Assert::AreEqual (expected,test[0].getStatus());	
		};

		TEST_METHOD(AddNRTest)
		{
			Logic logicAddTest;
			int numOfTask;
			int expected = 2; 
			Assert::AreEqual(0, numOfTask);	
			logicAddTest.process("add submit CS by 4/13");
			logicAddTest.process("add inform instructor abt venue change");
			numOfTask = logicAddTest.getListOfTasks().size();
			Assert::AreEqual(expected, numOfTask);
		};

		TEST_METHOD(AddRTest)
		{
			Logic logicAddTest;
			int numOfTask;
			Assert::AreEqual(0, numOfTask);
			logicAddTest.process("add submit CS by 4/13 every 3 day");
			numOfTask = (logicAddTest.getListOfTasks()).size();
			Assert::AreEqual(5, numOfTask);
		};

		TEST_METHOD(EditTest)
		{
			Logic logicEditTest;
			vector<Task> listOfTasks;
				
			logicEditTest.process("add CS presentation prep");
			listOfTasks = logicEditTest.getListOfTasks();
				
			string taskname;
			taskname = listOfTasks[0].getTaskName();
			string expected = "CS presentation prep";
			Assert::AreEqual(expected, taskname);
			logicEditTest.process("edit 1 taskname CS presentation final");
			listOfTasks = logicEditTest.getListOfTasks();
			taskname = listOfTasks[0].getTaskName();
			expected = "CS presentation final";
			Assert::AreEqual(expected, taskname);	
		}
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