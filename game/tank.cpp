#include "tank.h"
#include "LightAmmo.h"
#include "HeavyAmmo.h"
#include "FreeAmmo.h"


void Tank::set_if_alive(bool b)
{
	if_alive = b;
	if (b == false) {
		set_cur_health(0);
	}
}

void Tank::set_name(std::string n)
{
	name = n;
}

void Tank::set_max_health(double h)
{
	if (h > 0) {
		max_health = h;
	}
	else {
		max_health = 1;
		std::cout << "Max health has to be a positive value. Max health set to 1.\n";
	}
}

void Tank::set_cur_health(double h)
{
	if (cur_health == 0 && h == 0) {
		return;
	}
	if (h > max_health) {
		cur_health = max_health;
		std::cout << "Current health cannot exceed max health. Health set to max: " << max_health << "\n";
	}
	else if (h > 0) {
		cur_health = h;
	}
	else if (h == 0) {
		std::cout << "Health reached 0. Tank destroyed.\n";
		cur_health = 0;
		this->set_if_alive(false);
	}
	else {
		cur_health = 1;
		std::cout << "Current health has to be a non negative value. Health set to 1.\n";
	}
}

void Tank::set_full_health()
{
	cur_health = max_health;
}

void Tank::set_armor(double a)
{
	if (a >= 0 && a <= 100) {
		armor = a;
	}
	else if (a < 0) {
		armor = 0;
		std::cout << "Minimum armor is 0. Armor set to 0.\n";
	} 
	else if (a > 100) {
		armor = 100;
		std::cout << "Maximum armor is 100. Armor set to 100.\n";
	}
}

void Tank::set_shield(double s)
{
	if (s >= 0) {
		cur_shield = s;
	}
	else {
		cur_shield = 0;
		std::cout << "Shield value has to be positive.\n";
		return;
	}
}

void Tank::set_coords(unsigned int x_pos, unsigned int y_pos)
{
	x = x_pos;
	y = y_pos;
}

bool Tank::get_if_alive() const
{
	return if_alive;
}

std::string Tank::get_name() const
{
	return name;
}

double Tank::get_max_health() const
{
	return max_health;
}

double Tank::get_cur_health() const
{
	return cur_health;
}

double Tank::get_armor() const
{
	return armor;
}

double Tank::get_shield() const
{
	return cur_shield;
}

unsigned int Tank::get_x() const
{
	return x;
}

unsigned int Tank::get_y() const
{
	return y;
}

void Tank::take_damage(double d)
{
	if (cur_health == 0 || if_alive == false) {
		std::cout << "Already destroyed.\n";
		return;
	}
	double after_mitigation = 0;
	after_mitigation = d * (1 - armor / 100);
	std::cout << std::to_string(after_mitigation) << " damage taken.\n";
	if (after_mitigation >= cur_shield) {
		after_mitigation -= cur_shield;
		this->set_shield(0);
	}
	else {
		cur_shield -= after_mitigation;
		after_mitigation = 0;
	}
	if (cur_shield == 0 and after_mitigation != 0) {
		if (after_mitigation >= cur_health) {
			set_cur_health(0);
		}
		else {
			set_cur_health(cur_health - after_mitigation);
		}
	}
}

void Tank::add_armor(double a)
{
	double new_armor = armor + a;
	this->set_armor(new_armor);
}

void Tank::add_max_health(double h)
{
	double new_max_health = max_health + h;
	this->set_max_health(new_max_health);
}

void Tank::add_shield(double s)
{
	double new_shield = cur_shield + s;
	this->set_shield(new_shield);
}

void Tank::heal(double h)
{
	if (h <= 0) {
		std::cout << "Heal has to be a positive value.\n";
		return;
	}
	else {
		if (cur_health + h >= max_health) {
			cur_health = max_health;
		}
		else {
			cur_health += h;
		}
	}
}

void Tank::add_ammo(Ammo& a)
{
	this->ammo_rack.add_ammo(a);
}

void Tank::remove_ammo(Ammo& a)
{
	this->ammo_rack.delete_ammo(a);
}

void Tank::add_to_inventory(Product& p)
{
	if(p.get_type() == shield or p.get_type() == repairkit)
		this->inventory.push_back(p);
}

void Tank::remove_from_inventory(Product p)
{
	auto it = std::find(inventory.begin(), inventory.end(), p);
	if (it != inventory.end()) {
		inventory.erase(it);
	}
}

void Tank::move(char dir)
{
	if (dir == 'L') {
		x -= 1;
		return;
	}
	if (dir == 'R') {
		x += 1;
		return;
	}
}

bool Tank::use_shield()
{
	for (auto& p : inventory) {
		if (p.get_type() == shield) {
			Shield& s = static_cast<Shield&>(p);
			
			this->add_shield(50);
			this->remove_from_inventory(s);
			return 1;
		}
	}
	return 0;
}

bool Tank::use_repair()
{
	for (auto p : inventory) {
		if (p.get_type() == repairkit) {
			RepairKit& r = static_cast<RepairKit&>(p);
			this->heal(50);
			this->remove_from_inventory(r);
			return 1;
		}
	}
	return 0;
}

std::string Tank::coord_info() const
{
	std::string info;
	info += name + " x: " + std::to_string(x);
	info += " y: " + std::to_string(y) + "\n";
	return info;
}


void Tank::fill_ammo()
{
	this->ammo_rack.fill();
}


std::string Tank::inventory_info()
{
	int shield_cnt = 0;
	int repair_cnt = 0;
	std::string items = "shield: ";

	for (auto& i : inventory)
	{
		if (i.get_type() == shield)
		{
			shield_cnt++;
		}
		else if (i.get_type() == repairkit)
		{
			repair_cnt++;
		}
	}
	items += std::to_string(shield_cnt);
	items += " repair: ";
	items += std::to_string(repair_cnt);
	return items;
}

int Tank::get_current_load()
{
	return ammo_rack.get_current_load();
}

int Tank::get_heavy(int level)
{
	HeavyAmmo heavy(level);
	try 
	{
		int damage = this->ammo_rack.find_ammo(heavy);
		this->ammo_rack.delete_ammo(heavy);
		return damage;
	}
	catch (std::invalid_argument const& e)
	{
		std::cout << "There are no heavy ammo\n";
		return 0;
	}

}

int Tank::get_light(int level)
{
	LightAmmo light(level);
	try
	{
		int damage = this->ammo_rack.find_ammo(light);
		this->ammo_rack.delete_ammo(light);
		return damage;
	}
	catch (std::invalid_argument const& e)
	{
		std::cout << "There are no light ammo\n";
		return 0;
	}
}

int Tank::get_free()
{
	FreeAmmo free;
	try
	{
		int damage = this->ammo_rack.find_ammo(free);
		this->ammo_rack.delete_ammo(free);
		return damage;
	}
	catch (std::invalid_argument const& e)
	{
		std::cout << "There are no free ammo\n";
		return 0;
	}
}