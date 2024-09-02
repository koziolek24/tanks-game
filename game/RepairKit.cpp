#include "RepairKit.h"

RepairKit::RepairKit(int heal) : Product(repairkit, 30)
{
	if (check_statistic(heal)) this->heal = heal;
	else throw std::invalid_argument("Arguments cannot be negative");
}

int RepairKit::get_heal() const
{
	return this->heal;
}
