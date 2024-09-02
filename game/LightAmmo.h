#pragma once
#include "Ammo.h"
class LightAmmo : public Ammo
{
public:
	LightAmmo() : Ammo() {};
	LightAmmo(int level);
	void upgrade() override;
};