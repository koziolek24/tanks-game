#include "CppUnitTest.h"
#include "../Projekt PROI/tank.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestTank
{
	TEST_CLASS(TestTank)
	{
	public:
		
		TEST_METHOD(Tank_default_constructor)
		{
			Tank tank;
			Assert::AreEqual(true, tank.get_if_alive());
			Assert::AreEqual(10.0, tank.get_max_health());
			Assert::AreEqual(10.0, tank.get_cur_health());
			Assert::AreEqual(0.0, tank.get_armor());
			Assert::AreEqual(0.0, tank.get_shield());
			Assert::AreEqual(0u, tank.get_x());
			Assert::AreEqual(0u, tank.get_y());
		}
		TEST_METHOD(Tank_constructor_parametrized)
		{
			Tank tank(25.0, 5.0);
			Assert::AreEqual(true, tank.get_if_alive());
			Assert::AreEqual(25.0, tank.get_max_health());
			Assert::AreEqual(25.0, tank.get_cur_health());
			Assert::AreEqual(5.0, tank.get_armor());
			Assert::AreEqual(0.0, tank.get_shield());
			Assert::AreEqual(0u, tank.get_x());
			Assert::AreEqual(0u, tank.get_y());
		}
		TEST_METHOD(Tank_setters_basic_correct)
		{
			Tank tank;
			tank.set_if_alive(false);
			tank.set_max_health(100.0);
			tank.set_cur_health(75.0);
			tank.set_armor(50.0);
			tank.set_coords(10u, 7u);

			Assert::AreEqual(false, tank.get_if_alive());
			Assert::AreEqual(100.0, tank.get_max_health());
			Assert::AreEqual(75.0, tank.get_cur_health());
			Assert::AreEqual(50.0, tank.get_armor());
			Assert::AreEqual(0.0, tank.get_shield());
			Assert::AreEqual(10u, tank.get_x());
			Assert::AreEqual(7u, tank.get_y());
		}
		TEST_METHOD(Tank_setters_basic_too_low)
		{
			Tank tank;
			tank.set_max_health(-10);
			tank.set_cur_health(-10);
			tank.set_armor(-10);
			tank.set_shield(-10);

			Assert::AreEqual(1.0, tank.get_max_health());
			Assert::AreEqual(1.0, tank.get_cur_health());
			Assert::AreEqual(0.0, tank.get_armor());
			Assert::AreEqual(0.0, tank.get_shield());
		}
		TEST_METHOD(Tank_setters_basic_too_high)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_cur_health(150);
			tank.set_armor(130);

			Assert::AreEqual(100.0, tank.get_cur_health());
			Assert::AreEqual(100.0, tank.get_armor());
		}
		TEST_METHOD(Tank_take_damage_no_armor)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_full_health();
			tank.set_armor(0);
			tank.take_damage(20);
			Assert::AreEqual(80.0, tank.get_cur_health());
			tank.take_damage(30);
			Assert::AreEqual(50.0, tank.get_cur_health());
			Assert::AreEqual(true, tank.get_if_alive());
			tank.take_damage(50);
			Assert::AreEqual(0.0, tank.get_cur_health());
			Assert::AreEqual(false, tank.get_if_alive());
		}

		TEST_METHOD(Tank_take_damage_with_armor)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_full_health();
			tank.set_armor(10);
			tank.take_damage(50);
			Assert::AreEqual(55.0, tank.get_cur_health());
			tank.take_damage(20);
			Assert::AreEqual(37.0, tank.get_cur_health());
		}

		TEST_METHOD(Tank_take_damage_with_shield_no_armor)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_full_health();
			tank.set_shield(20);
			tank.take_damage(10);
			Assert::AreEqual(100.0, tank.get_cur_health());
			Assert::AreEqual(10.0, tank.get_shield());
		}

		TEST_METHOD(Tank_take_damage_with_shield_no_armor_overflow)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_full_health();
			tank.set_shield(20);
			tank.take_damage(30);
			Assert::AreEqual(90.0, tank.get_cur_health());
			Assert::AreEqual(0.0, tank.get_shield());
		}

		TEST_METHOD(Tank_take_damage_with_shield_with_armor)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_full_health();
			tank.set_shield(20);
			tank.set_armor(10);
			tank.take_damage(10);
			Assert::AreEqual(100.0, tank.get_cur_health());
			Assert::AreEqual(11.0, tank.get_shield());
		}

		TEST_METHOD(Tank_take_damage_with_shield_with_armor_overflow)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_full_health();
			tank.set_shield(20);
			tank.set_armor(10);
			tank.take_damage(30);
			Assert::AreEqual(93.0, tank.get_cur_health());
			Assert::AreEqual(0.0, tank.get_shield());
		}
		TEST_METHOD(Tank_take_damage_max_armor)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_full_health();
			tank.set_armor(100);
			tank.take_damage(50);
			Assert::AreEqual(100.0, tank.get_cur_health());
		}

		TEST_METHOD(Tank_take_damage_dead)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_full_health();
			tank.set_armor(20);
			tank.take_damage(100000);
			Assert::AreEqual(0.0, tank.get_cur_health());
			Assert::AreEqual(false, tank.get_if_alive());
		}
		TEST_METHOD(Tank_add_stats)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_armor(50);
			tank.set_shield(15);

			tank.add_max_health(50);
			tank.add_armor(15);
			tank.add_shield(30);

			Assert::AreEqual(150.0, tank.get_max_health());
			Assert::AreEqual(65.0, tank.get_armor());
			Assert::AreEqual(45.0, tank.get_shield());
		}

		TEST_METHOD(Tank_add_stats_too_high)
		{
			Tank tank;
			tank.set_armor(50);
			tank.add_armor(60);
			Assert::AreEqual(100.0, tank.get_armor());
		}

		TEST_METHOD(Tank_add_stats_too_low)
		{
			Tank tank;
			tank.set_max_health(100);
			tank.set_armor(50);
			tank.set_shield(15);

			tank.add_max_health(-150);
			tank.add_armor(-100);
			tank.add_shield(-50);

			Assert::AreEqual(1.0, tank.get_max_health());
			Assert::AreEqual(0.0, tank.get_armor());
			Assert::AreEqual(0.0, tank.get_shield ());
		}

		TEST_METHOD(Tank_move)
		{
			Tank tank;
			tank.set_coords(10u, 10u);
			tank.move('L');
			Assert::AreEqual(9u, tank.get_x());
			tank.move('R');
			tank.move('R');
			Assert::AreEqual(11u, tank.get_x());
		}
	};
}
