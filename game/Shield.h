#pragma once
#include "Product.h"
class Shield : public Product
{
private:
	int points;
public:
	Shield(int points);
	int get_points() const;
};

