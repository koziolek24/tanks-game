#include "Interface.h"

void Interface::wait_for_input(std::string info) const
{
	std::cout << info;
	std::string plc_holder;
	std::getline(std::cin, plc_holder);
	std::getline(std::cin, plc_holder);
}

bool Interface::check_if_convertable(std::string to_convert) const
{
	try
	{
		std::stoi(to_convert);
		return true;
	}
	catch (std::invalid_argument const& e)
	{
		return false;
	}
}

Interface::Interface()
{
}

void Interface::add_user(const User user)
{
	this->users.emplace_back(user);
}

void Interface::remove_user(int index)
{
	if (index >= this->users.size())
	{
		throw std::invalid_argument("Index out of range!");
	}
	this->users.erase(this->users.begin() + index);
}

void Interface::start(std::string path)
{
	File file;
	this->users = file.read_csv(path);
	int user_index = -1;
	while (true)
	{
		std::cout << "\33[0;49;34mUsers:\n\33[0;49;37m";
		int i = 1;
		for (auto user : this->users)
		{
			std::cout << i << ". " << user.get_name() << std::endl;
			i++;
		}
		std::cout << "\33[0;49;32mType '0' to add new user!\n\33[0;49;37m";
		std::cout << "Choose user:\n";
		std::string user_index_str;
		std::cin >> user_index_str;
		if (not this->check_if_convertable(user_index_str))
		{
			user_index = -1;
		}
		else
		{
			user_index = std::stoi(user_index_str);
		}
		if (user_index == 0)
		{
			std::system("cls");
			std::string user_name;
			while (true)
			{
				std::cout << "Type user's name: ";
				std::cin >> user_name;
				int cnt = 0;
				for (auto user : this->users)
				{
					if (user.get_name() == user_name)
					{
						cnt = 1;
						std::system("cls");
						std::cout << "\33[0;49;31mThis user's name is already taken!\33[0;49;37m\n";
					}
				}
				if (cnt != 1)
				{
					break;
				}
			}
			std::system("cls");
			int table_base[9] = { 1,1,1,1,1,0,0,0,0 };
			User user(user_name, table_base);
			this->add_user(user);
			user_index = this->users.size() - 1;
			break;
		}
		else
		{
			user_index--;
			if (user_index < 0 || user_index >= this->users.size())
			{
				std::system("cls");
				std::cout << "\33[0;49;31mInvalid user index!\n\33[0;49;31m";
			}
			else
			{
				std::system("cls");
				break;
			}
		}
	}
	while (true)
	{
		std::cout << "\33[7;49;36mCurrent user -> " << this->users[user_index].get_name() << "\33[0;49;37m" << std::endl;
		std::cout << "(1) " << "\33[0;49;32mPlay\33[0;49;37m" << std::endl;
		std::cout << "(2) " << "Shop" << std::endl;
		std::cout << "(3) " << "Leaderboard" << std::endl;
		std::cout << "(4) " << "Player statistics" << std::endl;
		std::cout << "(5) " << "\33[0;49;31mQuit\33[0;49;37m" << std::endl;
		std::cout << "Choose option:\n";
		int option = -1;
		std::string option_str;
		std::cin >> option_str;
		if (not this->check_if_convertable(option_str))
		{
			option = -1;
		}
		else
		{
			option = std::stoi(option_str);
		}
		if (option == 1)
		{
			std::system("cls");
			game_mode(this->users[user_index]);
		}
		else if (option == 2)
		{
			std::system("cls");
			while (true)
			{
				
				Shop shop(this->users[user_index]);
				shop.print_shop();
				int shop_choice;
				std::string shop_choice_str;
				std::cout<<"\33[0;49;94mChoose product you want to buy/upgrade (1-9).\nType '10' to go back\33[0;49;37m\n";
				std::cin >> shop_choice_str;
				if (not this->check_if_convertable(shop_choice_str))
				{
					shop_choice = -1;
				}
				else
				{
					shop_choice = std::stoi(shop_choice_str);
				}
				if (shop_choice == 10) break;
				else if (shop_choice != -1)
				{
					try
					{
						shop.buy(shop_choice-1);
						this->users[user_index] = shop.get_user();
						std::system("cls");
						std::cout << "\33[0;49;32mSuccessful purchase!\33[0;49;37m\n";
						
					}
					catch(std::out_of_range const& e)
					{
						goto x;
					}
					catch (std::invalid_argument const& e)
					{
						std::system("cls");
						std::cout << "\33[0;49;31mCannot upgrade further!\33[0;49;37m\n";
					}
					catch (std::domain_error const& e)
					{
						std::system("cls");
						std::cout << "\33[0;49;31mInsufficient money!\33[0;49;37m\n";
					}
				}
				else
				{
					x:
					std::system("cls");
					std::cout << "\33[0;49;31mInvalid shop choice!\33[0;49;37m\n";
				}
			}
			std::system("cls");
		}
		else if (option == 3)
		{
			std::system("cls");
			std::cout << "\33[0;49;34m(index|user name|wins)\33[0;49;37m\n";
			std::cout << "Players ranking:\n";
			std::vector<User> sorted_users = this->users;
			std::sort(sorted_users.begin(), sorted_users.end(), std::greater<>{});
			int i = 1;
			for (auto user : sorted_users)
			{
				std::cout << i << ". ";
				if (user == this->users[user_index])
				{
					std::cout << "\33[0;49;32m";
				}
				std::cout << user.get_name() << " ";
				std::cout << user.get_wins() << "\33[0;49;37m" << std::endl;
				i++;
			}
			this->wait_for_input("\33[0;49;94mType anything to go back to main menu!\33[0;49;37m\n");
			std::system("cls");
		}
		else if (option == 4)
		{
			std::system("cls");
			std::cout << "Number of wins -> " << this->users[user_index].get_wins() << std::endl;
			std::cout << "Amount of money -> " << this->users[user_index].get_money() << std::endl;
			std::cout << "Amount of heavy ammo -> " << this->users[user_index].get_info(6) << std::endl;
			std::cout << "Amount of light ammo -> " << this->users[user_index].get_info(5) << std::endl;
			std::cout << "Amount of shield -> " << this->users[user_index].get_info(7) << std::endl;
			std::cout << "Amount of repair kit -> " << this->users[user_index].get_info(8) << std::endl;
			this->wait_for_input("\33[0;49;94mType anything to go back to main menu!\33[0;49;37m\n");
			std::system("cls");
		}
		else if (option == 5)
		{
			std::system("cls");
			break;
		}
		else
		{
			std::system("cls");
			std::cout << "\33[0;49;31mInvalid option!\33[0;49;37m\n";
		}
	}
	file.write_csv(path, this->users);
}
