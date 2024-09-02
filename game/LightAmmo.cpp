#include "LightAmmo.h"

LightAmmo::LightAmmo(int level)
	: Ammo(lightammo, 10 + ((level - 1) * 5), 50 + ((level - 1) * 20), 2.5 + ((level - 1) * 0.5), level) {}

void LightAmmo::upgrade()
{
	if (this->level < 5)
	{
		this->level++;
		set_damage(this->damage + 20);
		set_weight(this->weight + 0.5);
		set_cost(this->cost + 5);
	}
	else throw std::invalid_argument("Cannot upgrade further");
}
