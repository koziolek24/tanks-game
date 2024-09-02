#include "Obstacle.h"

Obstacle::Obstacle()
{
	this->x = 0u;
	this->y = 0u;
	this->name = "obstacle";
}

Obstacle::Obstacle(std::string name, unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
	this->name = name;
}

void Obstacle::set_name(std::string name)
{
	this->name = name;
}

void Obstacle::set_x(unsigned int x)
{
	this->x = x;
}

void Obstacle::set_y(unsigned int y)
{
	this->y = y;
}

std::string Obstacle::get_name() const
{
	return name;
}

unsigned int Obstacle::get_x() const
{
	return x;
}

unsigned int Obstacle::get_y() const
{
	return y;
}
