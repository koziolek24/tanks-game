#include "CppUnitTest.h"
#include "../Projekt PROI/RepairKit.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestRepairKit
{
	TEST_CLASS(REPAIRKIT)
	{
	public:

		TEST_METHOD(RepairKit_Create)
		{
			RepairKit rep(500);
			std::string s = "Repair-Kit";
			Assert::AreEqual(rep.type_str(), s);
			Assert::AreEqual(rep.get_heal(), 500);
		}

	};
}