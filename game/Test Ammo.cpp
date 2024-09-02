#include "CppUnitTest.h"
#include "../Projekt PROI/LightAmmo.h"
#include "../Projekt PROI/HeavyAmmo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestAmmo
{
	TEST_CLASS(AMMO)
	{
	public:

		TEST_METHOD(LightAmmo_Create)
		{
			LightAmmo lammo(1);
			std::string s = "Light-Ammo";
			Assert::AreEqual(lammo.type_str(), s);
			Assert::AreEqual(lammo.get_level(), 1);
			Assert::AreEqual(lammo.get_cost(), 10);
			Assert::AreEqual(lammo.get_weight(), 2.5);
			Assert::AreEqual(lammo.get_damage(), 50.0);
		}
		TEST_METHOD(HeavyAmmo_Create)
		{
			HeavyAmmo hammo(2);
			std::string s = "Heavy-Ammo";
			Assert::AreEqual(hammo.type_str(), s);
			Assert::AreEqual(hammo.get_level(), 2);
			Assert::AreEqual(hammo.get_cost(), 20);
			Assert::AreEqual(hammo.get_weight(), 5.25);
			Assert::AreEqual(hammo.get_damage(), 200.0);
		}
	};
}