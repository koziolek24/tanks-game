#include "CppUnitTest.h"
#include "../Projekt PROI/Shop.h"
#include "../Projekt PROI/User.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestShop
{
	TEST_CLASS(SHOP)
	{
	public:

		TEST_METHOD(Shop_Create)
		{
			int info[9] = { 1,2,3,4,5,6,7,8,9 };
			User test_user("ajax", info);
			Shop shop(test_user);
			Assert::AreEqual(shop.get_stock_size(), 4);
		}

	};
}