#include "CppUnitTest.h"
#include "../Projekt PROI/LightAmmo.h"
#include "../Projekt PROI/HeavyAmmo.h"
#include "../Projekt PROI/FreeAmmo.h"

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
			Assert::AreEqual(hammo.get_cost(), 30);
			Assert::AreEqual(hammo.get_weight(), 4.5);
			Assert::AreEqual(hammo.get_damage(), 100.0);
		}
		TEST_METHOD(FreeAmmo_Create)
		{
			FreeAmmo free;
			std::string s = "Free-Ammo";
			Assert::AreEqual(free.type_str(), s);
			Assert::AreEqual(free.get_level(), 1);
			Assert::AreEqual(free.get_cost(), 0);
			Assert::AreEqual(free.get_weight(), 3.5);
			Assert::AreEqual(free.get_damage(), 30.0);
		}
		TEST_METHOD(HeavyAmmo_Upgrade)
		{
			HeavyAmmo hammo(1);
			std::string s = "Heavy-Ammo";
			hammo.upgrade();
			Assert::AreEqual(hammo.type_str(), s);
			Assert::AreEqual(hammo.get_level(), 2);
			Assert::AreEqual(hammo.get_cost(), 30);
			Assert::AreEqual(hammo.get_weight(), 4.5);
			Assert::AreEqual(hammo.get_damage(), 100.0);
		}
		TEST_METHOD(LightAmmo_Upgrade)
		{
			LightAmmo lammo(1);
			std::string s = "Light-Ammo";
			lammo.upgrade();
			Assert::AreEqual(lammo.type_str(), s);
			Assert::AreEqual(lammo.get_level(), 2);
			Assert::AreEqual(lammo.get_cost(), 15);
			Assert::AreEqual(lammo.get_weight(), 3.0);
			Assert::AreEqual(lammo.get_damage(), 70.0);
		}
		TEST_METHOD(Ammo_Equal)
		{
			HeavyAmmo hammo(1);
			HeavyAmmo jammo(1);
			Assert::IsTrue(hammo==jammo);
		}
		TEST_METHOD(Ammo_NotEqual)
		{
			HeavyAmmo hammo(1);
			HeavyAmmo jammo(2);
			Assert::IsTrue(hammo != jammo);
		}
	};
}