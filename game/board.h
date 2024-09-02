#pragma once
#include "tank.h"
#include <fstream>
#include <algorithm>
#include "Obstacle.h"

class Board {
protected:
	std::vector<Tank*> players;
	// x_size == max x coordinate
	unsigned int x_size;
	// x_size == max y coordinate
	unsigned int y_size;
	std::vector<std::vector<char>> board;
	
	char alphabet[6] = { ' ', '_', '|', 'X', 'O', '{'};
	unsigned int bx;
	unsigned int by;


public:
	std::vector<unsigned int> all_heights;
	std::vector<Obstacle*> obstacles;
	Board& operator=(const Board& other);
	Board() {
		x_size = 20,
		y_size = 10,
		this->set_all_clear();
	};
	Board(unsigned int x, unsigned int y) {
		x_size = x,
		y_size = y,
		this->set_all_clear();
	}
	~Board() {}
	char get_char_at(unsigned int x, unsigned int y) const;
	void set_char(unsigned int x, unsigned int y, char ch);
	std::vector<char>get_row(unsigned int y) const;

	void add_player(Tank& t);
	void add_player(Tank& t, Tank& tt);
	void print_board();
	void set_all_clear();
	void set_size(unsigned int x, unsigned int y);
	void base_terrain(unsigned int y);
	void raise_terrain(unsigned int x);
	void lower_terrain(unsigned int x);
	void fill_sides(unsigned int x);
	unsigned int get_height(unsigned int x);
	unsigned int get_height_left(unsigned int x);
	unsigned int get_height_right(unsigned int x);
	void set_terrain_height(unsigned int x, unsigned int height);
	// make_hille() works only on flat surface
	void make_hill(unsigned int x_center, unsigned int height);
	void make_round_hill(unsigned int x_center, unsigned int height);
	void measure_heights();
	void set_all_heights();
	void place_tanks();
	void remove_tanks();

	// bulleting 
	void set_bullet_coords(unsigned int x, unsigned int y);
	unsigned int get_x_bulled() const;
	unsigned int get_y_bullet() const;
	void place_bullet();
	void remove_bullet();
	void move(Tank& t, char dir);

	// obstacles
	void add_obstacle(Obstacle& o);
	void remove_obstacle(Obstacle* o);
	void place_obstacles();
	void remove_obstacles();
	void randomize_obstacles();
	void generate_obstacles(unsigned int count);

	void read_board_from_file(const std::string& path);
	void save_board_to_file(const std::string& path) const;

	std::vector<Tank*> get_players() const;
	unsigned int get_x_size() const;
	unsigned int get_y_size() const;
};