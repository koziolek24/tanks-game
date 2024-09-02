#include "Shop.h"

Shop::Shop(User& user)
{
	this->user = user;
	fill_stock();
}

User Shop::get_user()
{
	return this->user;
}

void Shop::fill_stock()
{
	// user's LightAmmo
	LightAmmo lammo(user.get_info(0));
	stock.push_back(lammo);
	// user's HeavyAmmo
	HeavyAmmo hammo(user.get_info(1));
	stock.push_back(hammo);
	// user's Shield
	Shield shield(500);
	stock.push_back(shield);
	// user's RepairKit
	RepairKit rep(300);
	stock.push_back(rep);
}

void Shop::print_shop()
{
	std::string result = "-----------\33[0;49;93mShop\33[0;49;37m------------\n";
	result += std::string(18, ' ') + "Money: \33[0;49;93m" + std::to_string(this->user.get_money()) + "G\33[0;49;37m\n\n";
	result += "Ammo uprades:\n";
	result += "1.Light(lvl." + std::to_string(user.get_info(0)) + ")---------\33[0;49;93m150G\33[0;49;37m\n";
	result += "2.Heavy(lvl." + std::to_string(user.get_info(1)) + ")---------\33[0;49;93m250G\33[0;49;37m\n\n";
	result += "Tank uprades:\n";
	result += "3.HP(lvl." + std::to_string(user.get_info(2)) + ")------------\33[0;49;93m250G\33[0;49;37m\n";
	result += "4.Engine(lvl." + std::to_string(user.get_info(3)) + ")--------\33[0;49;93m150G\33[0;49;37m\n";
	result += "5.Power(lvl." + std::to_string(user.get_info(4)) + ")---------\33[0;49;93m100G\33[0;49;37m\n\n";
	result += "Battle equipment:\n";
	int i = 6;
	for (auto& product : stock)
	{
		result += std::to_string(i) + "." + product.get_info() + "\n";
		i++;
	}
	result += "\n";
	std::cout << result;
}

void Shop::buy(int i)
{
	if (i >= 0 && i < 5)
	{
		if(user.get_money()<this->const_prices[i]) throw std::domain_error("Insufficient money.");
		else
		{
			this->user.upgrade_lvl(i);
			this->user.set_money(this->user.get_money() - this->const_prices[i]);
		}
	}
	else if (i >= 5 && i < 9)
	{
		if (user.get_money() < this->stock[static_cast<std::vector<Product, std::allocator<Product>>::size_type>(i) - 5].get_cost()) throw std::domain_error("Insufficient money.");
		else
		{
			this->user.add_item(i);
			this->user.set_money(this->user.get_money() - this->stock[static_cast<std::vector<Product, std::allocator<Product>>::size_type>(i) - 5].get_cost());
		}
	}
	else throw std::out_of_range("Invalid index for level upgrade.");
}

int Shop::get_stock_size()
{
	return this->stock.size();
}
