#include "Shield.h"

Shield::Shield(int points) : Product(shield, 50)
{
if (check_statistic(points))this->points = points;
	else throw std::invalid_argument("Arguments cannot be negative");
}

int Shield::get_points() const
{
	return this->points;
}
