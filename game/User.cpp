#include "User.h"


std::string User::get_name() const
{
    return this->name;
}

void User::set_name(std::string new_name)
{
    this->name = new_name;
}

int User::get_wins() const
{
    return this->wins;
}

void User::set_money(int money)
{
    this->money = money;
}

int User::get_money() const
{
    return this->money;
}

int User::get_info(int i) const
{
    return this->info[i];
}

void User::inc_info(int i)
{
    this->info[i] += 1;
}

void User::upgrade_lvl(int i)
{
    if (this->get_info(i) >= 5) throw std::invalid_argument("Cannot upgrade further");
    this->inc_info(i);
}

void User::add_item(int i)
{
    this->inc_info(i);
}

bool User::operator==(const User& usr) const
{
    return (this->name == usr.get_name()) && (this->wins == usr.get_wins()) && (this->money == usr.get_money());
}

bool User::operator<(const User& usr) const
{
    return this->wins < usr.get_wins();
}

bool User::operator>(const User& usr) const
{
    return this->wins > usr.get_wins();
}

void User::remove_item(int i, int val)
{
    info[i] -= val;
}

void User::set_wins(int new_wins)
{
    wins = new_wins;
}