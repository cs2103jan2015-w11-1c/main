#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{		
	TEST_CLASS(MarkTest)
	{
	public:
		
		TEST_METHOD(isValidInput)
		{
			int userInputNum = 3;
			Mark mark(userInputNum);
			int vectorSize = 4;
			bool isValid = mark.isValidInput(vectorSize);
				Assert::IsTrue(isValid);

			//Mark mark;
			//Task task;
			//task.setTaskName("do CS");
			//Status expected = NOTDONE;
			//Assert::AreEqual (expected, task.getStatus());

			//mark.setContentToMark("done");
			//task = mark.markStatus(task);
			//expected = DONE;
			//Assert::AreEqual (expected, task.getStatus());

		}

	};
}