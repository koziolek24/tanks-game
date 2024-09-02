#pragma once
#include <string>
#include <vector>
#include "Product.h"
class User
{
private:
	std::string name;
	//counters
	unsigned int money;
	unsigned int wins;
	int info[9];

public:
	User() = default;
	User(std::string name, int info1[9], int money = 0, int wins = 0 ) : name(name), money(money), wins(wins) {
		for (int i = 0; i < 9; i++)
		{
			info[i] = info1[i];
		}
	};
	std::string get_name() const;
	void set_name(std::string new_name);
	int get_wins() const;
	void set_money(int money);
	void set_wins(int wins);
	int get_money() const;
	int get_info(int i) const;
	void inc_info(int i);
	void upgrade_lvl(int i);
	void add_item(int i);
	void remove_item(int i, int val);
	bool operator==(const User& usr) const;
	bool operator<(const User& usr) const;
	bool operator>(const User& usr) const;
};

