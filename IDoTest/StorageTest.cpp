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