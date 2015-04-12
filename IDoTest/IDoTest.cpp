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

//@author A0115465H
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
//@author A0111624W
namespace ParserTest
{		
	TEST_CLASS(ParserTest)
	{
	public:

		//Test if parsed inputs are correct for mark function
		//This is a test for equivalence partition [commandchoice][number][content]
		TEST_METHOD(markInformation)
		{
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
		}

		//Test if parsed inputs are correct if a deadline task is added
		//This is a test for equivalence partition [commandchoice][content][date][time]
		TEST_METHOD(deadLineTaskInformation)
		{
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
		}

		//Test if parsed inputs are correct if a timed-task is added
		TEST_METHOD(timedTaskInformation)
		{
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
		}

		//Test if parsed inputs are correct if a floating task is added
		TEST_METHOD(floatingTaskInformation)
		{
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
		}

		//Test if parsed inputs are correct for edit function
		TEST_METHOD(editInformation)
		{
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
		}

		//Test if parsed inputs are correct if a timed-task is added
		TEST_METHOD(wrongStartDateInformation)
		{
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

namespace IntegrationTest
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
		}

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
		}

		TEST_METHOD(AddRTest)
		{
			Logic logicAddTest;
			int numOfTask;
			Assert::AreEqual(0, numOfTask);
			logicAddTest.process("add submit CS by 4/13 every 3 day");
			numOfTask = (logicAddTest.getListOfTasks()).size();
			Assert::AreEqual(5, numOfTask);
		}

		TEST_METHOD(EditTest)
		{
			Logic logicEditTest;
			vector<Task> listOfTasks;
				
			logicEditTest.process("add CS presentation prep");
			listOfTasks = logicEditTest.getListOfTasks();
				
			string taskname;
			taskname = listOfTasks[0].getTaskName();
			string expected = "CS presentation prep";
			string expected2 = "CS presentation final";
			Assert::AreEqual(expected, taskname);
			logicEditTest.process("edit 1 taskname CS presentation final");
			listOfTasks = logicEditTest.getListOfTasks();
			taskname = listOfTasks[0].getTaskName();
			Assert::AreEqual(expected2, taskname);	
		}
	};
}

namespace LogicTest
{
	TEST_CLASS (DeleteTest)
	{
	public:
		TEST_METHOD(isValidInput)
		{
			Task task;
			Task task2;
			vector <Task> testVector;
			vector <string> parse;
			Delete testDelete;
			string expected = "exercise";
			task.setTaskName("do work");
			task2.setTaskName("exercise");
			testVector.push_back(task);
			testVector.push_back(task2);
			parse.push_back("delete");
			parse.push_back("1");
			Assert::IsTrue(testDelete.isValidInput(parse,testVector.size()));
			parse.pop_back();
			parse.push_back("5");
			Assert::IsFalse(testDelete.isValidInput(parse,testVector.size()));
		}

		TEST_METHOD(DeletingTask)
		{
			Task task;
			Task task2;
			vector <Task> testVector;
			vector <string> parse;
			Delete testDelete;
			string expected = "exercise";
			task.setTaskName("do work");
			task2.setTaskName("exercise");
			testVector.push_back(task);
			testVector.push_back(task2);
			parse.push_back("delete");
			parse.push_back("1");
			testDelete.isValidInput(parse,testVector.size());
			testDelete.execute(testVector);
			Assert::AreEqual(expected,testVector[0].getTaskName());
		}
	};

	TEST_CLASS (EditTest)
	{
	public:
		TEST_METHOD(EditTaskName)
		{
			Task task;
			vector <Task> testVector;
			vector <string> parse;
			Edit testEdit;
			string expected = "study everyday";
			task.setTaskName("do work");
			testVector.push_back(task);
			parse.push_back("edit");
			parse.push_back("1");
			parse.push_back("taskname");
			parse.push_back("study everyday");
			testEdit.execute(parse,testVector);
			testVector=testEdit.getList();
			Assert::AreEqual(expected,testVector[0].getTaskName());
		}

		TEST_METHOD(EditStart)
		{
			Task task;
			vector <Task> testVector;
			vector <string> parse;
			Edit testEdit;
			string expected = "2015-May-20";
			string expected2 = "2000";
			task.setTaskName("do work");
			task.setStartDate("2015-May-19");
			task.setStartTime("1800");
			task.setEndDate("2015-May-21");
			task.setEndTime("1900");
			testVector.push_back(task);
			parse.push_back("edit");
			parse.push_back("1");
			parse.push_back("startdate");
			parse.push_back("5/20");
			testEdit.execute(parse,testVector);
			testVector=testEdit.getList();
			Assert::AreEqual(expected,testVector[0].getStartDate());
			parse.pop_back();
			parse.pop_back();
			parse.push_back("starttime");
			parse.push_back("2000");
			testEdit.execute(parse,testVector);
			testVector=testEdit.getList();
			Assert::AreEqual(expected2,testVector[0].getStartTime());
		}

		TEST_METHOD(EditEnd)
		{
			Task task;
			vector <Task> testVector;
			vector <string> parse;
			Edit testEdit;
			string expected = "2015-May-22";
			string expected2 = "2000";
			task.setTaskName("do work");
			task.setEndDate("2015-May-21");
			task.setEndTime("1900");
			testVector.push_back(task);
			parse.push_back("edit");
			parse.push_back("1");
			parse.push_back("enddate");
			parse.push_back("5/22");
			testEdit.execute(parse,testVector);
			testVector=testEdit.getList();
			Assert::AreEqual(expected,testVector[0].getEndDate());
			parse.pop_back();
			parse.pop_back();
			parse.push_back("endtime");
			parse.push_back("2000");
			testEdit.execute(parse,testVector);
			testVector=testEdit.getList();
			Assert::AreEqual(expected2,testVector[0].getEndTime());
		}
	};

	TEST_CLASS (LogicTest)
	{
	public:
		TEST_METHOD(AddTask)
		{
			Logic testLogic;
			vector <Task> testVector;
			string expected = "exercise everyday";
			string expected2 = "finish CS";
			string expected3 = "attend lecture";
			string expected4 = "2015-Apr-14";
			string expected5 = "2359";
			string expected6 = "2015-Apr-13";
			string expected7 = "1800";
			testLogic.process("add exercise everyday");
			testLogic.process("add finish CS by 4/14 2359");
			testLogic.process("add attend lecture from 4/13 1600 to 1800");
			testVector = testLogic.getListOfTasks();
			Assert::AreEqual(expected,testVector[0].getTaskName());
			Assert::AreEqual(expected2,testVector[1].getTaskName());
			Assert::AreEqual(expected3,testVector[2].getTaskName());
			Assert::AreEqual(expected4,testVector[1].getEndDate());
			Assert::AreEqual(expected5,testVector[1].getEndTime());
			Assert::AreEqual(expected6,testVector[2].getEndDate());
			Assert::AreEqual(expected7,testVector[2].getEndTime());
		}

		TEST_METHOD(UndoTest)
		{
			Logic testLogic;
			vector <Task> testVector;
			int expected = 3;
			int expected2 = 2;
			int size;
			testLogic.process("add exercise everyday");
			testLogic.process("add finish CS by 4/14 2359");
			testLogic.process("add attend lecture from 4/13 1600 to 1800");
			testVector = testLogic.getListOfTasks();
			size = testVector.size();
			Assert::AreEqual(expected,size);
			testLogic.process("undo");
			testVector = testLogic.getListOfTasks();
			size = testVector.size();
			Assert::AreEqual(expected2,size);
		}
	};

	TEST_CLASS (MarkTest)
	{
	public:
		TEST_METHOD(MarkStatusTest)
		{
			Task task;
			vector <Task> testVector;
			vector <string> parse;
			Mark testMark;
			Status expected = done;
			task.setTaskName("do work");
			testVector.push_back(task);
			parse.push_back("mark");
			parse.push_back("2");
			parse.push_back("done");
			Assert::IsFalse(testMark.isValidInput(parse,1));
			parse.pop_back();
			parse.pop_back();
			parse.push_back("1");
			parse.push_back("done");
			testMark.execute(parse,testVector);
			Assert::AreEqual(expected,testVector[0].getStatus());
		}

		TEST_METHOD(MarkLabelTest)
		{
			Task task;
			Task task2;
			vector <Task> testVector;
			vector <string> parse;
			Mark testMark;
			string expected = "school";
			string expected2 = "family";
			task.setTaskName("do CS");
			task2.setTaskName("visit grandma");
			testVector.push_back(task);
			testVector.push_back(task2);
			parse.push_back("mark");
			parse.push_back("1");
			parse.push_back("school");
			testMark.execute(parse,testVector);
			Assert::AreEqual(expected,testVector[0].getLabel());
			parse.pop_back();
			parse.pop_back();
			parse.push_back("2");
			parse.push_back("family");
			testMark.execute(parse,testVector);
			Assert::AreEqual(expected2,testVector[1].getLabel()); 
		}
	};

	TEST_CLASS (SearchTest)
	{
	public:
		TEST_METHOD(SearchWordTest)
		{
			Task task;
			Task task2;
			Task task3;
			Task task4;
			vector <Task> testVector;
			vector <Task> results;
			vector <Task> results2;
			vector <int> numberOfFoundTasks;
			vector <string> parse;
			Search testSearch;
			Search testSearch2;
			int expected = 1;
			int expected2 = 2;
			string expected3 = "do work";
			string expected4 = "do send email";
			string expected5 = "do send email";
			string expected6 = "send letter";
			task.setTaskName("do work");
			task2.setTaskName("do send email");
			task3.setTaskName("send letter");
			task4.setTaskName("read book");
			testVector.push_back(task);
			testVector.push_back(task2);
			testVector.push_back(task3);
			testVector.push_back(task4);
			parse.push_back("search");
			parse.push_back("do");
			testSearch.setSearchWord(parse[1]);
			testSearch.execute(testVector);
			results = testSearch.getListOfFoundTasks();
			numberOfFoundTasks = testSearch.getListOfFoundTaskNum();
			Assert::AreEqual(expected,numberOfFoundTasks[0]);
			Assert::AreEqual(expected2,numberOfFoundTasks[1]);
			Assert::AreEqual(expected3,results[0].getTaskName());
			Assert::AreEqual(expected4,results[1].getTaskName());
			parse.pop_back();
			parse.push_back("send");
			testSearch2.setSearchWord(parse[1]);
			testSearch2.execute(testVector);
			results2 = testSearch2.getListOfFoundTasks();
			Assert::AreEqual(expected5,results2[0].getTaskName());
			Assert::AreEqual(expected6,results2[1].getTaskName());
		}
	};

	TEST_CLASS (SortTest)
	{
	public:
/*		TEST_METHOD(Sort)
		{
			Task task;
			Task task2;
			vector <Task> testVector;
			vector <string> parse;
			Sort sortTest;
			string expected = "exercise";
			task.setTaskName("sleep");
			task2.setTaskName("exercise");
			testVector.push_back(task);
			testVector.push_back(task2);
			parse.push_back("delete");
			parse.push_back("1");
			Assert::IsTrue(testDelete.isValidInput(parse,testVector.size()));
			parse.pop_back();
			parse.push_back("5");
			Assert::IsFalse(testDelete.isValidInput(parse,testVector.size()));
		}*/
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