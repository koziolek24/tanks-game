#pragma once
#include "LightAmmo.h"
#include "HeavyAmmo.h"
#include "FreeAmmo.h"
#include <vector>
#include <string>

class AmmoRack
{
private:
	int max_load;
	int current_load;
	bool check_overload();
public:
	std::vector<Ammo> stored_ammo;
	AmmoRack() = default;
	AmmoRack(int max);
	virtual ~AmmoRack() {};
	void add_ammo(Ammo& ammo);
	void delete_ammo(Ammo ammo);
	int find_ammo(Ammo ammo);
	void fill();
	// gettery i settery
	int get_max_load();
	void set_max_load(int new_load);
	int get_current_load();
};