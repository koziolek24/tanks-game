#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "Interface.h"

class File
{
public:
	void write_csv(std::string fname, std::vector<User> vct);
	std::vector<User> read_csv(std::string fname);
};

