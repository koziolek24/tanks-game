#pragma once
#include "Ammo.h"
class HeavyAmmo : public Ammo
{
public:
	HeavyAmmo() : Ammo() {};
	HeavyAmmo(int level);
	void upgrade() override;
};