#include "AmmoRack.h"

bool AmmoRack::check_overload()
{
	if (this->current_load >= this->max_load) return true;
	else return false;
}

AmmoRack::AmmoRack(int max)
{
	this->current_load = 0;
	this->max_load = max;
}

void AmmoRack::add_ammo(Ammo& ammo)
{
	if (check_overload()) throw std::runtime_error("Rack already full. Cannot add more ammo");
	else
	{
		this->current_load++;
		stored_ammo.push_back(ammo);
	}

}

void AmmoRack::delete_ammo(Ammo ammo)
{
	auto it = std::find(stored_ammo.begin(), stored_ammo.end(), ammo);
	if (it != stored_ammo.end()) {
		stored_ammo.erase(it);
		current_load--;
	}
	else
	{
		throw std::invalid_argument("No such ammo in ammo rack");
	}
}

int AmmoRack::find_ammo(Ammo ammo)
{
	auto it = std::find(stored_ammo.begin(), stored_ammo.end(), ammo);
	if (it != stored_ammo.end()) {
		return ammo.get_damage();
	}
	else
	{
		throw std::invalid_argument("No such ammo in ammo rack");
	}
}


void AmmoRack::fill()
{
	FreeAmmo free;
	while (this->current_load < this->max_load)
	{
		add_ammo(free);
	}
}

int AmmoRack::get_max_load()
{
	return this->max_load;
}

void AmmoRack::set_max_load(int new_load)
{
	if (new_load > 0) this->max_load = new_load;
	else throw std::invalid_argument("Damage cannot be negative");
}

int AmmoRack::get_current_load()
{
	return this->current_load;
}
