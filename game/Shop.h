#pragma once
#include <vector>
#include <string>
#include "Product.h"
#include "LightAmmo.h"
#include "HeavyAmmo.h"
#include "Shield.h"
#include "RepairKit.h"
#include "User.h"
#include "Tank.h"

class Shop
{
private:
	User user;
	std::vector<Product> stock;
	int const_prices[5] = { 150, 250, 250, 150, 100 };
public:
	Shop(User& user);
	User get_user();
	void fill_stock();
	void print_shop();
	void buy(int i);
	// gettery
	int get_stock_size();
};

