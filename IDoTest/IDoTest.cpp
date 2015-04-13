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
		
		TEST_METHOD(UpdateStorage)
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

		TEST_METHOD(ReadFromStorage)
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

		TEST_METHOD(EditStorageFile)
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
		TEST_METHOD(ParseMarkInformation)
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
		TEST_METHOD(ParseDeadLineTaskInformation)
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
		TEST_METHOD(ParseTimedTaskInformation)
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
		TEST_METHOD(ParseFloatingTaskInformation)
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
		TEST_METHOD(ParseEditInformation)
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
		TEST_METHOD(ParseWrongStartDateInformation)
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
//@author A0115465H
namespace IntegrationTest
{
	TEST_CLASS (LogicTest)
	{
	public:
		TEST_METHOD(AddNonRecurringTest)
		{
			Logic logicAddTest;
			vector <Task> results;
			int numOfTask;
			int expected = 2; 
			string expected2 = "submit CS";
			string expected3 = "inform instructor abt venue change";
			logicAddTest.process("add submit CS by 5/13");
			logicAddTest.process("add inform instructor abt venue change");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected, numOfTask);
			Assert::AreEqual(expected2,results[0].getTaskName());
			Assert::AreEqual(expected3,results[1].getTaskName());
		}

		TEST_METHOD(AddNonRecurringTest2)
		{
			Logic logicAddTest;
			Dates dates;
			vector <Task> results;
			int numOfTask;
			int expected = 3;
			string expected2 = "submit v0.5";
			string expected3 = dates.getTodayDate();
			string expected4 = "2300";
			string expected5 = dates.getTodayDate();
			string expected6 = "2359";
			string expected7 = "holiday";
			string expected8 = "2015-Jun-03";
			string expected9 = "0300";
			string expected10 = "2015-Jun-07";
			string expected11 = "0800";
			string expected12 = "dental appointment";
			string expected13 = "2015-Jun-05";
			string expected14 = "1000";
			string expected15 = "2015-Jun-05";
			string expected16 = "1200";
			logicAddTest.process("add submit v0.5 from 2300 to 2359");
			logicAddTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicAddTest.process("add dental appointment from 6/5 1000 to 1200");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected, numOfTask);
			Assert::AreEqual(expected2, results[0].getTaskName());
			Assert::AreEqual(expected3, results[0].getStartDate());
			Assert::AreEqual(expected4, results[0].getStartTime());
			Assert::AreEqual(expected5, results[0].getEndDate());
			Assert::AreEqual(expected6, results[0].getEndTime());
			Assert::AreEqual(expected7, results[1].getTaskName());
			Assert::AreEqual(expected8, results[1].getStartDate());
			Assert::AreEqual(expected9, results[1].getStartTime());
			Assert::AreEqual(expected10, results[1].getEndDate());
			Assert::AreEqual(expected11, results[1].getEndTime());
			Assert::AreEqual(expected12, results[2].getTaskName());
			Assert::AreEqual(expected13, results[2].getStartDate());
			Assert::AreEqual(expected14, results[2].getStartTime());
			Assert::AreEqual(expected15, results[2].getEndDate());
			Assert::AreEqual(expected16, results[2].getEndTime());
		}

		TEST_METHOD(AddRecurringTest)
		{
			Logic logicAddTest;
			int numOfTask;
			int expected = 5; 
			logicAddTest.process("add submit CS by 6/13 every 3 day");
			numOfTask = (logicAddTest.getListOfTasks()).size();
			Assert::AreEqual(expected, numOfTask);
		}

		TEST_METHOD(AddRecurringTest2)
		{
			Logic logicAddTest;
			vector <Task> results;
			int numOfTask;
			int expected = 9; 
			string expected2 = "submit CS";
			logicAddTest.process("add submit CS by 6/13 every 7 day for 2 month");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected, numOfTask);
			for (int i = 0 ; i < numOfTask ; i++) {
				Assert::AreEqual(expected2, results[i].getTaskName());
			}
		}

		TEST_METHOD(AddRecurringTest3)
		{
			Logic logicAddTest;
			vector <Task> results;
			int numOfTask;
			int expected = 30;
			string expected2 = "eat medicine";
			string expected3 = "2358";
			string expected4 = "2359";
			logicAddTest.process("add eat medicine from 2358 to 2359 every 1 day for 1 month");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected, numOfTask);
			for (int i = 0 ; i < numOfTask ; i++) {
				Assert::AreEqual(expected2, results[i].getTaskName());
				Assert::AreEqual(expected3, results[i].getStartTime());
				Assert::AreEqual(expected4, results[i].getEndTime());
			}
		}

		TEST_METHOD(AddRecurringTest4)
		{
			Logic logicAddTest;
			vector <Task> results;
			int numOfTask;
			int expected = 100;
			string expected2 = "birthday";
			string expected3 = "2015-Sep-08";
			string expected4 = "2016-Sep-08";
			string expected5 = "2017-Sep-08";
			string expected6 = "2114-Sep-08";
			logicAddTest.process("add birthday from 9/8 0000 to 2359 every 1 year for 100 year");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected, numOfTask);
			for (int i = 0 ; i < numOfTask ; i++) {
				Assert::AreEqual(expected2, results[i].getTaskName());
			}
			Assert::AreEqual(expected3, results[0].getStartDate());
			Assert::AreEqual(expected4, results[1].getStartDate());
			Assert::AreEqual(expected5, results[2].getStartDate());
			Assert::AreEqual(expected6, results[99].getStartDate());
		}

		TEST_METHOD(DeleteSingleTest)
		{
			Logic logicAddTest;
			Delete remove;
			vector <Task> results;
			int numOfTask;
			int expected = 2;
			string expected2 = "holiday";
			string expected3 = "dental appointment";
			logicAddTest.process("add submit v0.5 from 2300 to 2359");
			logicAddTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicAddTest.process("add dental appointment from 6/5 1000 to 1200");
			logicAddTest.process("delete 1");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected,numOfTask);
			Assert::AreEqual(expected2,results[0].getTaskName());
			Assert::AreEqual(expected3,results[1].getTaskName());
		}

		TEST_METHOD(DeleteMultipleTest)
		{
			Logic logicAddTest;
			Delete remove;
			vector <Task> results;
			int numOfTask;
			int expected = 1;
			string expected2 = "holiday";
			string expected3 = "dental appointment";
			logicAddTest.process("add submit v0.5 from 2300 to 2359");
			logicAddTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicAddTest.process("add dental appointment from 6/5 1000 to 1200");
			logicAddTest.process("delete 1 3");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected,numOfTask);
			Assert::AreEqual(expected2,results[0].getTaskName());
		}

		TEST_METHOD(DeleteRecurringTest)
		{
			Logic logicAddTest;
			Delete remove;
			vector <Task> results;
			int numOfTask;
			int expected = 2;
			string expected2 = "submit v0.5";
			string expected3 = "holiday";
			logicAddTest.process("add submit v0.5 from 2300 to 2359");
			logicAddTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicAddTest.process("add dental appointment from 6/5 1000 to 1200 every 7 day for 2 month");
			logicAddTest.process("delete all 3");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected,numOfTask);
			Assert::AreEqual(expected2,results[0].getTaskName());
			Assert::AreEqual(expected3,results[1].getTaskName());
		}

		TEST_METHOD(DeleteRecurringTest2)
		{
			Logic logicAddTest;
			Delete remove;
			vector <Task> results;
			int numOfTask;
			int expected = 9;
			string expected2 = "holiday";
			string expected3 = "dental appointment";
			logicAddTest.process("add submit v0.5 from 2300 to 2359");
			logicAddTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicAddTest.process("add dental appointment from 6/5 1000 to 1200 every 7 day for 2 month");
			logicAddTest.process("delete all 1");
			results = logicAddTest.getListOfTasks();
			numOfTask = results.size();
			Assert::AreEqual(expected,numOfTask);
			Assert::AreEqual(expected2,results[0].getTaskName());
			Assert::AreEqual(expected3,results[1].getTaskName());
		}

		TEST_METHOD(EditTest)
		{
			Logic logicEditTest;
			vector<Task> listOfTasks;
			string expected = "holiday";
			string expected2 = "internship";
			string expected3 = "2015-Jun-05";
			string expected4 = "0700";
			string expected5 = "2015-Aug-08";
			string expected6 = "1800";
			logicEditTest.process("add holiday from 6/1 0300 to 6/7 0800");
			listOfTasks = logicEditTest.getListOfTasks();
			Assert::AreEqual(expected, listOfTasks[0].getTaskName());
			logicEditTest.process("edit 1 taskname internship");
			listOfTasks = logicEditTest.getListOfTasks();
			Assert::AreEqual(expected2, listOfTasks[0].getTaskName());	
			logicEditTest.process("edit 1 startdate 6/5");
			listOfTasks = logicEditTest.getListOfTasks();
			Assert::AreEqual(expected3, listOfTasks[0].getStartDate());	
			logicEditTest.process("edit 1 starttime 0700");
			listOfTasks = logicEditTest.getListOfTasks();
			Assert::AreEqual(expected4, listOfTasks[0].getStartTime());	
			logicEditTest.process("edit 1 enddate 8/8");
			listOfTasks = logicEditTest.getListOfTasks();
			Assert::AreEqual(expected5, listOfTasks[0].getEndDate());	
			logicEditTest.process("edit 1 endtime 1800");
			listOfTasks = logicEditTest.getListOfTasks();
			Assert::AreEqual(expected6, listOfTasks[0].getEndTime());	
		}

		TEST_METHOD(ClearTest)
		{
			Logic logicClearTest;
			vector<Task> listOfTasks;
			int expected = 0;
			int size; 
			logicClearTest.process("add submit v0.5 from 2300 to 2359");
			logicClearTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicClearTest.process("add dental appointment from 6/5 1000 to 1200");
			logicClearTest.process("clear");
			listOfTasks = logicClearTest.getListOfTasks();
			size = listOfTasks.size();
			Assert::AreEqual(expected, size);	
		}

		TEST_METHOD(MarkStatusTest)
		{
			Logic logicMarkTest;
			vector<Task> listOfTasks;
			Status expected = done;
			int size; 
			logicMarkTest.process("add submit v0.5 from 2350 to 2359");
			logicMarkTest.process("mark 1 done");
			listOfTasks = logicMarkTest.getListOfTasks();
			size = listOfTasks.size();
			Assert::AreEqual(expected, listOfTasks[0].getStatus());	
		}

		TEST_METHOD(MarkLabelTest)
		{
			Logic logicMarkTest;
			vector<Task> listOfTasks;
			string expected = "school";
			int size; 
			logicMarkTest.process("add submit v0.5 from 2350 to 2359");
			logicMarkTest.process("mark 1 school");
			listOfTasks = logicMarkTest.getListOfTasks();
			size = listOfTasks.size();
			Assert::AreEqual(expected, listOfTasks[0].getLabel());	
		}

		TEST_METHOD(StoreChangeTest)
		{
			Logic logicMarkTest;
			string file;
			string expected = "new.txt";
			logicMarkTest.process("store new");
			ifstream readFile ("filename.txt");
			getline(readFile,file);
			readFile.close();
			Assert::AreEqual(expected, file);	
		}

		TEST_METHOD(SortNameTest)
		{
			Logic logicSortTest;
			vector<Task> listOfTasks;
			string expected = "dental appointment";
			string expected2 = "holiday";
			string expected3 = "submit v0.5";
			logicSortTest.process("add submit v0.5 from 2350 to 2359");
			logicSortTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicSortTest.process("add dental appointment from 6/5 1000 to 1200");
			logicSortTest.process("sort taskname");
			listOfTasks = logicSortTest.getListOfTasks();
			Assert::AreEqual(expected, listOfTasks[0].getTaskName());
			Assert::AreEqual(expected2, listOfTasks[1].getTaskName());
			Assert::AreEqual(expected3, listOfTasks[2].getTaskName());
		}

		TEST_METHOD(SortFromTest)
		{
			Logic logicSortTest;
			vector<Task> listOfTasks;
			string expected = "submit v0.5";
			string expected2 = "holiday";
			string expected3 = "dental appointment";
			logicSortTest.process("add submit v0.5 from 2350 to 2359");
			logicSortTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicSortTest.process("add dental appointment from 6/5 1000 to 1200");
			logicSortTest.process("sort from");
			listOfTasks = logicSortTest.getListOfTasks();
			Assert::AreEqual(expected, listOfTasks[0].getTaskName());
			Assert::AreEqual(expected2, listOfTasks[1].getTaskName());
			Assert::AreEqual(expected3, listOfTasks[2].getTaskName());
		}

		TEST_METHOD(SortToTest)
		{
			Logic logicSortTest;
			vector<Task> listOfTasks;
			string expected = "submit v0.5";
			string expected2 = "dental appointment";
			string expected3 = "holiday";
			logicSortTest.process("add submit v0.5 from 2350 to 2359");
			logicSortTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicSortTest.process("add dental appointment from 6/5 1000 to 1200");
			logicSortTest.process("sort to");
			listOfTasks = logicSortTest.getListOfTasks();
			Assert::AreEqual(expected, listOfTasks[0].getTaskName());
			Assert::AreEqual(expected2, listOfTasks[1].getTaskName());
			Assert::AreEqual(expected3, listOfTasks[2].getTaskName());
			logicSortTest.process("undo");
			logicSortTest.process("sort by");
			listOfTasks = logicSortTest.getListOfTasks();
			Assert::AreEqual(expected, listOfTasks[0].getTaskName());
			Assert::AreEqual(expected2, listOfTasks[1].getTaskName());
			Assert::AreEqual(expected3, listOfTasks[2].getTaskName());
		}

		TEST_METHOD(SortDeadlineTest)
		{
			Logic logicSortTest;
			vector<Task> listOfTasks;
			string expected = "submit v0.5";
			string expected2 = "holiday";
			string expected3 = "dental appointment";
			logicSortTest.process("add submit v0.5 from 2350 to 2359");
			logicSortTest.process("add dental appointment from 5/5 1000 to 1200");
			logicSortTest.process("add holiday from 5/3 0300 to 5/7 0800");
			logicSortTest.process("sort deadline");
			listOfTasks = logicSortTest.getListOfTasks();
			Assert::AreEqual(expected, listOfTasks[0].getTaskName());
			Assert::AreEqual(expected2, listOfTasks[1].getTaskName());
			Assert::AreEqual(expected3, listOfTasks[2].getTaskName());
		}

		TEST_METHOD(InvalidSortTest)
		{
			Logic logicSortTest;
			vector<Task> listOfTasks;
			string expected = "submit v0.5";
			string expected2 = "dental appointment";
			string expected3 = "holiday";
			logicSortTest.process("add submit v0.5 from 2300 to 2359");
			logicSortTest.process("add dental appointment from 6/5 1000 to 1200");
			logicSortTest.process("add holiday from 6/3 0300 to 6/7 0800");
			logicSortTest.process("sort priority");
			listOfTasks = logicSortTest.getListOfTasks();
			Assert::AreEqual(expected, listOfTasks[0].getTaskName());
			Assert::AreEqual(expected2, listOfTasks[1].getTaskName());
			Assert::AreEqual(expected3, listOfTasks[2].getTaskName());
		}
	};
}
//@author A0114010L
namespace LogicTest
{
	TEST_CLASS (DeleteTest)
	{
	public:
		TEST_METHOD(DeleteIsValidInput)
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
			string expected4 = "2015-May-14";
			string expected5 = "2359";
			string expected6 = "2015-May-13";
			string expected7 = "1800";
			testLogic.process("add exercise everyday");
			testLogic.process("add finish CS by 5/14 2359");
			testLogic.process("add attend lecture from 5/13 1600 to 1800");
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
			testLogic.process("add finish CS by 5/14 2359");
			testLogic.process("add attend lecture from 5/13 1600 to 1800");
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

		TEST_METHOD(SearchDateTest)
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
			task.setStartDate("2015-May-01");
			task.setStartTime("1200");
			task.setEndDate("2015-May-01");
			task.setEndTime("2000");
			task2.setTaskName("do send email");
			task2.setStartDate("2015-May-01");
			task2.setStartTime("1800");
			task2.setEndDate("2015-May-01");
			task2.setEndTime("2000");
			task3.setTaskName("send letter");
			task3.setStartDate("2015-May-02");
			task3.setStartTime("2000");
			task3.setEndDate("2015-May-02");
			task3.setEndTime("2100");
			task4.setTaskName("read book");
			task4.setStartDate("2015-May-03");
			task4.setStartTime("2000");
			task4.setEndDate("2015-May-01");
			task4.setEndTime("2000");
			testVector.push_back(task);
			testVector.push_back(task2);
			testVector.push_back(task3);
			testVector.push_back(task4);
			parse.push_back("search");
			parse.push_back("5/1");
			testSearch.setSearchWord(parse[1]);
			testSearch.execute(testVector);
			results = testSearch.getListOfFoundTasks();
			numberOfFoundTasks = testSearch.getListOfFoundTaskNum();
			Assert::AreEqual(expected,numberOfFoundTasks[0]);
			Assert::AreEqual(expected2,numberOfFoundTasks[1]);
			Assert::AreEqual(expected3,results[0].getTaskName());
			Assert::AreEqual(expected4,results[1].getTaskName());
		}

		TEST_METHOD(SearchFirstAlphabetTest)
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
			int expected2 = 3;
			string expected3 = "do work";
			string expected4 = "do send email";
			string expected5 = "do send email";
			string expected6 = "send letter";
			task.setTaskName("do work");
			task2.setTaskName("send letter");
			task3.setTaskName("do send email");
			task4.setTaskName("read book");
			testVector.push_back(task);
			testVector.push_back(task2);
			testVector.push_back(task3);
			testVector.push_back(task4);
			parse.push_back("search");
			parse.push_back("d");
			testSearch.setSearchWord(parse[1]);
			testSearch.execute(testVector);
			results = testSearch.getListOfFoundTasks();
			numberOfFoundTasks = testSearch.getListOfFoundTaskNum();
			Assert::AreEqual(expected,numberOfFoundTasks[0]);
			Assert::AreEqual(expected2,numberOfFoundTasks[1]);
			Assert::AreEqual(expected3,results[0].getTaskName());
			Assert::AreEqual(expected4,results[1].getTaskName());
		}

		TEST_METHOD(SearchSubstringTest)
		{
			Task task;
			Task task2;
			Task task3;
			vector <Task> testVector;
			vector <Task> results;
			vector <Task> results2;
			vector <int> numberOfFoundTasks;
			vector <string> parse;
			Search testSearch;
			Search testSearch2;
			int expected = 1;
			int expected2 = 2;
			string expected3 = "do functions";
			string expected4 = "have fun";
			string expected5 = "average your data";
			int expected6 = 3;
			task.setTaskName("do functions");
			task2.setTaskName("have fun");
			task3.setTaskName("average your data");
			testVector.push_back(task);
			testVector.push_back(task2);
			testVector.push_back(task3);
			parse.push_back("search");
			parse.push_back("fun");
			testSearch.setSearchWord(parse[1]);
			testSearch.execute(testVector);
			results = testSearch.getListOfFoundTasks();
			numberOfFoundTasks = testSearch.getListOfFoundTaskNum();
			Assert::AreEqual(expected,numberOfFoundTasks[0]);
			Assert::AreEqual(expected2,numberOfFoundTasks[1]);
			Assert::AreEqual(expected3,results[0].getTaskName());
			Assert::AreEqual(expected4,results[1].getTaskName());
			parse.pop_back();
			parse.push_back("ave");
			testSearch2.setSearchWord(parse[1]);
			testSearch2.execute(testVector);
			results2 = testSearch2.getListOfFoundTasks();
			numberOfFoundTasks = testSearch2.getListOfFoundTaskNum();
			Assert::AreEqual(expected2,numberOfFoundTasks[0]);
			Assert::AreEqual(expected6,numberOfFoundTasks[1]);
			Assert::AreEqual(expected4,results2[0].getTaskName());
			Assert::AreEqual(expected5,results2[1].getTaskName()); 
		}

		TEST_METHOD(SearchMultipleWordsTest)
		{
			Task task;
			Task task2;
			Task task3;
			vector <Task> testVector;
			vector <Task> results;
			vector <Task> results2;
			vector <int> numberOfFoundTasks;
			vector <string> parse;
			Search testSearch;
			Search testSearch2;
			int expected = 1;
			int expected2 = 2;
			string expected3 = "enjoy your life to the fullest";
			string expected4 = "bring grandma to the hospital";
			string expected5 = "do not waste your life";
			int expected6 = 3;
			task.setTaskName("enjoy your life to the fullest");
			task2.setTaskName("bring grandma to the hospital");
			task3.setTaskName("do not waste your life");
			testVector.push_back(task);
			testVector.push_back(task2);
			testVector.push_back(task3);
			parse.push_back("search");
			parse.push_back("to the");
			testSearch.setSearchWord(parse[1]);
			testSearch.execute(testVector);
			results = testSearch.getListOfFoundTasks();
			numberOfFoundTasks = testSearch.getListOfFoundTaskNum();
			Assert::AreEqual(expected,numberOfFoundTasks[0]);
			Assert::AreEqual(expected2,numberOfFoundTasks[1]);
			Assert::AreEqual(expected3,results[0].getTaskName());
			Assert::AreEqual(expected4,results[1].getTaskName());
			parse.pop_back();
			parse.push_back("your life");
			testSearch2.setSearchWord(parse[1]);
			testSearch2.execute(testVector);
			results2 = testSearch2.getListOfFoundTasks();
			numberOfFoundTasks = testSearch2.getListOfFoundTaskNum();
			Assert::AreEqual(expected,numberOfFoundTasks[0]);
			Assert::AreEqual(expected6,numberOfFoundTasks[1]);
			Assert::AreEqual(expected3,results2[0].getTaskName());
			Assert::AreEqual(expected5,results2[1].getTaskName()); 
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