#include "Product.h"

bool Product::check_statistic(double statistic) const
{
	if (statistic >= 0)return true;
	return false;
}

bool Product::check_type(Type type)
{
	if (type == lightammo
		|| type == heavyammo
		|| type == shield
		|| type == repairkit
		|| type == freeammo)return true;
	else return false;
}

std::string Product::type_name(Type type)
{
	switch (type) {
	case Type::lightammo:
		return "Light-Ammo";
		break;
	case Type::heavyammo:
		return "Heavy-Ammo";
		break;
	case Type::shield:
		return "Shield";
		break;
	case Type::repairkit:
		return "Repair-Kit";
		break;
	case Type::freeammo:
		return "Free-Ammo";
		break;
	default:
		return "Invalid type";
	}
}

std::string Product::type_str()
{
	return type_name(static_cast<Type>(this->type));;
}

std::string Product::cost_str()
{
	return std::to_string(this->cost) + "G";
}

Product::Product(Type type, int cost)
{
	if (check_type(type) && check_statistic(cost))
	{
		this->type = type;
		this->cost = cost;
	}
	else
	{
		throw std::invalid_argument("Arguments cannot be negative");
	}
}

std::string Product::get_info()
{
	std::string info = "";
	int sep = 25 - int(cost_str().size()) - int(type_str().size());
	info = type_str() + std::string(sep, '-') + "\33[0;49;93m" + cost_str() +"\33[0;49;37m";
	return info;
}

Type Product::get_type()
{
	return this->type;
}

int Product::get_cost()
{
	return this->cost;
}

void Product::set_cost(int new_cost)
{
	if (check_statistic(new_cost))
	{
		this->cost = new_cost;
	}
	else
	{
		throw std::invalid_argument("Arguments cannot be negative");
	}
}

bool Product::operator==(const Product& other)
{
	if (this->get_type() == other.type && this->get_cost() == other.cost) return true;
	else return false;
}

bool Product::operator!=(const Product& other)
{
	if (this->get_type() != other.type || this->get_cost() != other.cost) return true;
	else return false;
}