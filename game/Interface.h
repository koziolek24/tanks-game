#pragma once
#include <vector>
#include <exception>
#include <iostream>
#include <algorithm>
#include "User.h"
#include "File.h"
#include "game.h"
#include "Shop.h"

class Interface
{
private:
	std::vector<User> users;
	void wait_for_input(std::string info) const;
	bool check_if_convertable(std::string to_convert) const;
public:
	Interface();
	
	void add_user(const User user);
	void remove_user(int index);

	void start(std::string path);
};

