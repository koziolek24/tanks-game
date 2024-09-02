#pragma once
#include "Product.h"
class RepairKit : public Product
{
private:
	int heal;
public:
	RepairKit(int heal);
	int get_heal() const;
};

