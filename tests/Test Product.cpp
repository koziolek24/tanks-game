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
			Product product_test(shield, 10);
			std::string type = "Shield";
			std::string cost = "25G";
			product_test.set_cost(25);
			Assert::AreEqual(product_test.cost_str(), cost);
		}
		TEST_METHOD(Product_TypeName)
		{
			Product product_test(lightammo, 10);
			std::string type = "Light-Ammo";
			Assert::AreEqual(product_test.type_str(), type);
		}

		TEST_METHOD(Product_CostStr)
		{
			Product product_test(lightammo, 10);
			std::string cost = "10G";
			Assert::AreEqual(product_test.cost_str(), cost);
		}
		TEST_METHOD(Product_Info)
		{
			Product product_test(lightammo, 10);
			std::string info = "Light-Ammo------------\33[0;49;93m10G\33[0;49;37m";
			Assert::AreEqual(product_test.get_info(), info);
		}
		TEST_METHOD(Product_Equal)
		{
			Product product_test(lightammo, 10);
			Product product_test2(lightammo, 10);
			Assert::IsTrue(product_test2==product_test);
		}
		TEST_METHOD(Product_NotEqual1)
		{
			Product product_test(lightammo, 20);
			Product product_test2(lightammo, 10);
			Assert::IsTrue(product_test2 != product_test);
		}
		TEST_METHOD(Product_NotEqual2)
		{
			Product product_test(lightammo, 10);
			Product product_test2(heavyammo, 10);
			Assert::IsTrue(product_test2 != product_test);
		}
	};
}