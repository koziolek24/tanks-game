#include "CppUnitTest.h"
#include "../Projekt PROI/board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBoard
{
	TEST_CLASS(TestBoard)
	{
	public:
		TEST_METHOD(Construcor_default)
		{
			Board board;
			Assert::AreEqual(20u, board.get_x_size());
			Assert::AreEqual(10u, board.get_y_size());
		}
		TEST_METHOD(Constructor_parametrized)
		{
			Board board(100u, 200u);
			Assert::AreEqual(100u, board.get_x_size());
			Assert::AreEqual(200u, board.get_y_size());
		}
		TEST_METHOD(Clear_by_default)
		{
			Board board(50u, 40u);
			for (int y = board.get_y_size() - 1; y >= 0; --y) {
				for (int x = 0; x <= board.get_x_size(); ++x) {
					Assert::AreEqual(' ', board.get_char_at(x, y));
				}
			}
		}
		TEST_METHOD(Set_size)
		{
			Board board(40u, 50u);
			Assert::AreEqual(40u, board.get_x_size());
			Assert::AreEqual(50u, board.get_y_size());
			board.set_size(10u, 20u);
			Assert::AreEqual(10u, board.get_x_size());
			Assert::AreEqual(20u, board.get_y_size());
		}
		TEST_METHOD(Base_terrain)
		{
			Board board(50u, 20u);
			board.base_terrain(5);

			for (int y = board.get_y_size() - 1; y >= 0; --y) {
				for (int x = 0; x <= board.get_x_size(); ++x) {
					if (y != 5) {
						Assert::AreEqual(' ', board.get_char_at(x, y));
					}
					if (y == 5) {
						Assert::AreEqual('_', board.get_char_at(x, y));
					}
				}
			}
		}
		TEST_METHOD(Get_Height)
		{
			Board board(50u, 20u);
			board.base_terrain(10);
			
			for (int x = 0; x <= board.get_x_size(); ++x) {
				Assert::AreEqual(10u, board.get_height(x));
			}
		}
		TEST_METHOD(Get_Height_999)
		{
			Board board(50u, 20u);
			board.base_terrain(10);

			Assert::AreEqual(999u, board.get_height_left(0));
			Assert::AreEqual(999u, board.get_height_right(50));
		}
		TEST_METHOD(Add_players_single)
		{
			Board board;
			Tank tank1;
			tank1.set_name("tank1");
			tank1.set_coords(10, 10);
			Tank tank2;
			tank2.set_name("tank2");
			tank2.set_coords(15, 10);
			board.add_player(tank1);
			board.add_player(tank2);
			Assert::AreEqual(board.get_players()[0]->get_name(), tank1.get_name());
			Assert::AreEqual(board.get_players()[1]->get_name(), tank2.get_name());
			size_t expected = 2;
			Assert::AreEqual(board.get_players().size(), expected);
		}
		TEST_METHOD(Add_players_multiple)
		{
			Board board;
			Tank tank1;
			tank1.set_name("tank1");
			tank1.set_coords(10, 10);
			Tank tank2;
			tank2.set_name("tank2");
			tank2.set_coords(15, 10);
			board.add_player(tank1, tank2);
			Assert::AreEqual(board.get_players()[0]->get_name(), tank1.get_name());
			Assert::AreEqual(board.get_players()[1]->get_name(), tank2.get_name());
			size_t expected = 2;
			Assert::AreEqual(board.get_players().size(), expected);
		}
		TEST_METHOD(Raise_terrain_basic_1)
		{
			Board board(50u, 20u);
			board.base_terrain(10u);
			for (int i = 0; i < 5; ++i) {
				board.raise_terrain(i);
			}

			for (int y = board.get_y_size() - 1; y >= 0; --y) {
				for (int x = 0; x <= board.get_x_size(); ++x) {
					if (y == 11 && x >= 0 && x < 5) {
						Assert::AreEqual('_', board.get_char_at(x, y));
					}
					else if (y == 10 && x >= 5) {
						Assert::AreEqual('_', board.get_char_at(x, y));
					}
					else if (y == 10 && x >= 0 && x < 5) {
						Assert::AreEqual('|', board.get_char_at(x, y));
					}
					else {
						Assert::AreEqual(' ', board.get_char_at(x, y));
					}
				}
			}

		}
		TEST_METHOD(Raise_terrain_basic_2)
		{
			Board board(50u, 20u);
			board.base_terrain(10u);
			for (int i = 0; i < 5; ++i) {
				for (int q = 0; q < i; ++q) {
					board.raise_terrain(i);
				}
			}
			for (int y = board.get_y_size() - 1; y >= 0; --y) {
				for (int x = 0; x <= board.get_x_size(); ++x) {
					if (y == 10 && x >= 5) {
						Assert::AreEqual('_', board.get_char_at(x, y));
					}
					else if (x >= 0 && x < 5 && y == 10) {
						Assert::AreEqual('_', board.get_char_at(x, y + x));
						if (x >= 1 && x < 5) {
							Assert::AreEqual('|', board.get_char_at(x, y + x - 1));
						}
					}
				}
			}
		}

	};	
}