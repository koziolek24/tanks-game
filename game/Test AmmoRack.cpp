#include "CppUnitTest.h"
#include "../Projekt PROI/AmmoRack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestAmmoRack
{
	TEST_CLASS(AMMORACK)
	{
	public:

		TEST_METHOD(AmmoRack_Create)
		{
			AmmoRack ammorack(15);
			Assert::AreEqual(ammorack.get_max_load(), 15);
			Assert::AreEqual(ammorack.get_current_load(), 0);
		}
		TEST_METHOD(AmmoRack_AddAmmo)
		{
			AmmoRack ammorack(15);
			HeavyAmmo hammo(2);
			ammorack.add_ammo(hammo);
			LightAmmo lammo(1);
			ammorack.add_ammo(lammo);
			Assert::AreEqual(ammorack.get_current_load(), 2);
		}
		TEST_METHOD(AmmoRack_DeleteAmmo)
		{
			AmmoRack ammorack(15);
			HeavyAmmo hammo(2);
			ammorack.add_ammo(hammo);
			HeavyAmmo hammo1(2);
			ammorack.delete_ammo(hammo1);
			Assert::AreEqual(ammorack.get_current_load(), 0);
		}
	};
}