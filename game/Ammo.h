#pragma once
#include <string>
#include <iostream>
#include "Product.h"
class Ammo : public Product
{
protected:
	double damage;
	double weight;
	int level;
	bool check_level(int level);
public:
	Ammo() {};
	Ammo(Type type,
		int cost,
		double base_damage,
		double weight,
		int level
	);
	virtual ~Ammo() = default;
	// gettery i settery
	double get_damage() const;
	void set_damage(double new_damage);
	double get_weight() const;
	void set_weight(double new_weight);
	int get_level() const;
	virtual void upgrade() {};
	bool operator==(const Ammo& other) const;
	bool operator!=(const Ammo& other) const;
};