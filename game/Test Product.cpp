#include "CppUnitTest.h"
#include "../Projekt PROI/Product.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProduct
{
	TEST_CLASS(PRODUCT)
	{
	public:

		TEST_METHOD(Product_Create)
		{
			Product product_test(lightammo, 10);
			std::string type = "Light-Ammo";
			std::string cost = "10G";
			Assert::AreEqual(product_test.type_str(), type);
			Assert::AreEqual(product_test.cost_str(), cost);
		}
		TEST_METHOD(Product_Set_Cost)
		{
			Product product_test(armor, 10);
			std::string type = "Armor";
			std::string cost = "25G";
			product_test.set_cost(25);
			Assert::AreEqual(product_test.cost_str(), cost);
		}
		TEST_METHOD(Product_Info)
		{
			Product product_test(lightammo, 10);
			std::string info = "Light-Ammo------------10G";
			Assert::AreEqual(product_test.get_info(), info);
		}
	};
}