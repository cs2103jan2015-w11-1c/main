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
#include "RTask.cpp"
#include "Search.cpp"
#include "Sort.cpp"
#include "Log.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//system testing
namespace IDoTest {

	TEST_CLASS(LogicTest) 
	{
		public:
			TEST_METHOD(AddNRTest)
			{
				Logic logicAddTest;
				int numOfTask = (logicAddTest.getListOfTasks()).size();

				Assert::AreEqual(0, numOfTask);
				
				logicAddTest.process("add submit CS by 4/13");
				logicAddTest.process("add inform instructor abt venue change");

				numOfTask = (logicAddTest.getListOfTasks()).size();

				Assert::AreEqual(2, numOfTask);

			};

			TEST_METHOD(AddRTest)
			{
				Logic logicAddTest;
				int numOfTask = (logicAddTest.getListOfTasks()).size();

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
				Assert::AreEqual(expected, taskname);
				
				logicEditTest.process("edit 1 taskname CS presentation final");

				listOfTasks = logicEditTest.getListOfTasks();

				taskname = listOfTasks[0].getTaskName();
				expected = "CS presentation final";
				Assert::AreEqual(expected, taskname);
				
			}
	};
}

//unit tests
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
			parsedInfo.push_back("mark");
			parsedInfo.push_back("1");
			parsedInfo.push_back("done");
			
			Mark markStatus;
			markStatus.execute(parsedInfo, taskListFromLogic);

			expectedstatus = done;
			outputstatus = taskListFromLogic[0].getStatus();
			Assert::AreEqual(expectedstatus, outputstatus);

		};
	};
	
	TEST_CLASS(SearchTest)
	{
	public:
		
		TEST_METHOD(setSearchWord)
		{
			Search search;
			search.setSearchWord("CS presentation");
			
			string storedSearchWord;
			storedSearchWord = search.getSearchWord();

			string expected = "CS presentation";

			Assert::AreEqual(expected, storedSearchWord);
		}
		

		TEST_METHOD(execute)
		{
			Task taskInLogic;
			taskInLogic.setTaskName("CS presentation");
			taskInLogic.setEndDate("4/17");

			vector <Task> taskList;
			taskList.push_back(taskInLogic);

			taskInLogic.setTaskName("2150 presentation");
			taskInLogic.setEndDate("4/14");

			taskList.push_back(taskInLogic);

			Search search;
			search.setSearchWord("CS presentation");
			
			int num = search.getNoOfFoundTasks();
			Assert::AreEqual(0, num);

			search.execute(taskList);

			num = search.getNoOfFoundTasks();
			Assert::AreEqual(1, num);
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