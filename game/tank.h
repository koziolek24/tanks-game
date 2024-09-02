#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Product.h"
#include "Shield.h"
#include "RepairKit.h"
#include "AmmoRack.h"

class Tank {
protected:
	bool if_alive = true;

	std::string name;
	double max_health;
	double cur_health;
	double armor;
	double cur_shield;
	// armor reduces damages on principle:
	// 1 point of armor - 1% of dmg red
	// up to a max of 100 armor

	unsigned int x;
	unsigned int y;
	AmmoRack ammo_rack;
	std::vector<Product> inventory;

public:
	// Default
	Tank() {
		max_health = 10.0,
		cur_health = max_health,
		armor = 0.0,
		cur_shield = 0.0,
		x = 0,
		y = 0;
		ammo_rack = AmmoRack(15);
	}

	Tank(double h, double a) {
		max_health = h,
		cur_health = h,
		armor = a,
		cur_shield = 0.0,
		x = 0,
		y = 0;
		ammo_rack = AmmoRack(15);
	}
	
	~Tank() {}
		
	// Getters and setters
	void set_if_alive(bool b);
	void set_name(std::string n);
	void set_max_health(double h);
	void set_cur_health(double h);
	void set_full_health();
	void set_armor(double a);
	void set_shield(double s);
	void set_coords(unsigned int x_pos, unsigned int y_pos);

	bool get_if_alive() const;
	std::string get_name() const;
	double get_max_health() const;
	double get_cur_health() const;
	double get_armor() const;
	double get_shield() const;
	unsigned int get_x() const;
	unsigned int get_y() const;

	// more 'fun' funcionality
	void take_damage(double d);
	void add_armor(double a);
	void add_max_health(double h);
	void add_shield(double s);
	void heal(double h);
	void add_ammo(Ammo& a);
	void remove_ammo(Ammo& a);
	void add_to_inventory(Product& p);
	void remove_from_inventory(Product p);
	void move(char dir);
	bool use_shield();
	bool use_repair();
	void fill_ammo();
	int get_current_load();

	int get_heavy(int level);
	int get_free();
	int get_light(int level);
	// info
	std::string coord_info() const;
	std::string ammo_info() const;
	std::string tank_info() const;
	std::string inventory_info();

};