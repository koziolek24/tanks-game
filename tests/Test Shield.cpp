#include "CppUnitTest.h"
#include "../Projekt PROI/Shield.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestShield
{
	TEST_CLASS(SHIELD)
	{
	public:

		TEST_METHOD(Shield_Create)
		{
			Shield shield(500);
			std::string s = "Shield";
			Assert::AreEqual(shield.type_str(), s);
			Assert::AreEqual(shield.get_points(), 500);
		}
		
	};
}