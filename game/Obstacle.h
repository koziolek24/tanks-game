#pragma once
#include <string>

class Obstacle {
protected:
	unsigned int x;
	unsigned int y;
	std::string name;
public:
	Obstacle();
	Obstacle(std::string name, unsigned int x, unsigned int y);
	~Obstacle() {};
	
	void set_name(std::string name);
	void set_x(unsigned int x);
	void set_y(unsigned int y);

	std::string get_name() const;
	unsigned int get_x() const;
	unsigned int get_y() const;
};