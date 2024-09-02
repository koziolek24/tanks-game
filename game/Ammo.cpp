#include "Ammo.h"

bool Ammo::check_level(int level)
{
	if (level > 0 && level < 6)return true;
	return false;
}

Ammo::Ammo(Type type, int cost, double damage, double weight, int level = 1) : Product(type, cost)
{
	if (check_statistic(weight) == false || check_statistic(damage) == false || check_level(level) == false)
	{
		throw std::invalid_argument("Arguments cannot be negative");
	}
	else
	{
		this->damage = damage;
		this->weight = weight;
		this->level = level;
	}
}

double Ammo::get_damage() const
{
	return this->damage;
}

void Ammo::set_damage(double new_damage)
{
	if (check_statistic(new_damage) == true)
	{
		//new_damage = std::ceil(new_damage * 100.0) / 100.0;
		this->damage = new_damage;
	}
	else throw std::invalid_argument("Damage cannot be negative");
}

double Ammo::get_weight() const
{
	return this->weight;
}

void Ammo::set_weight(double new_weight)
{
	if (check_statistic(new_weight) == true)
	{
		//new_weight = std::ceil(new_weight * 100.0) / 100.0;
		this->weight = new_weight;
	}
	else throw std::invalid_argument("Weight cannot be negative");
}

int Ammo::get_level() const
{
	return this->level;
}

bool Ammo::operator==(const Ammo& other) const
{
	return this->type == other.type && this->get_level() == other.get_level();
}

bool Ammo::operator!=(const Ammo& other) const
{
	return this->type != other.type || this->get_level() != other.get_level();
}
