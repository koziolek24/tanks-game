#pragma once
#include <iostream>
#include <string>

enum Type { lightammo, heavyammo, shield, repairkit, freeammo };

class Product
{
protected:
	Type type;
	int cost;
	bool check_statistic(double statistic) const;
	bool check_type(Type type);
	std::string type_name(Type type);
public:
	Product() {};
	virtual ~Product() {};
	std::string type_str();
	std::string cost_str();
	Product(Type type, int cost);
	std::string get_info();
	// gettery i settery
	Type get_type();
	int get_cost();
	void set_cost(int new_cost);

	// operators
	bool operator==(const Product& other);
	bool operator!=(const Product& other);
};