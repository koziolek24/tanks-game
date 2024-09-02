#include "HeavyAmmo.h"

HeavyAmmo::HeavyAmmo(int level)
	: Ammo(heavyammo, 20 + ((level - 1) * 10), 75 + ((level - 1) * 25), 4 + ((level - 1) * 0.5), level) {}

void HeavyAmmo::upgrade()
{
	if (this->level < 5)
	{
		this->level++;
		set_damage(this->damage + 25);
		set_weight(this->weight + 0.5);
		set_cost(this->cost + 10);
	}
	else throw std::invalid_argument("Cannot upgrade further");
}