#include "creator.h"

Board& board_canyon(Board& board) {
	// Tutorial
	// x in (0, 10) -> narrow     y in (0, 10) -> short
	// x in [10, 50) -> normal	  y in [10, 20) -> tall
	// x in [50, inf) -> biiig	  y in [20, inf) -> taaaall
	unsigned int x = board.get_x_size();
	unsigned int y = board.get_y_size();
	unsigned int border = x / 10;
	unsigned int can_height = y * 0.6;
	unsigned int h_len = can_height;
	h_len *= 4;
	board.set_all_clear();
	board.base_terrain(can_height / 2);
	for (unsigned int z = 0; z < x; z++) {
		if (z <= border || z >= x - border) {
			unsigned int height = can_height + (rand() % 3);
			if (height <= y) {
				board.set_terrain_height(z, height);
			}
		}
		if (z > border && z < x - border) {
			double temp = (h_len * h_len) / 320;
			unsigned int h = temp;
			if (z < x / 2) { h_len -= 1; };
			if (z > x / 2) { h_len += 1; };
			board.set_terrain_height(z, h);
		}
	}
	return board;
}

Board& board_hills(Board& board) {
	unsigned int x = board.get_x_size();
	unsigned int y = board.get_y_size();
	unsigned int can_height = y * 0.2;
	board.base_terrain(can_height);
	can_height = y * 0.5;
	board.make_hill(x/2, can_height);
	board.make_hill(x / 8, can_height / 2);
	board.make_hill(x * 0.875, can_height / 2);

	return board;
}

Board& board_city(Board& board)
{
	unsigned int x = board.get_x_size();
	unsigned int y = board.get_y_size();
	unsigned int can_height = y * 0.2;
	board.base_terrain(can_height);
	unsigned int delta = x / 10;
	unsigned int counter = 1;
	int id = 0;
	while (counter <= 10) {
		unsigned int dx = rand() % (y/4);
		for (int q=0; q<10; ++q)
		{
			if (id <= x) {
				board.set_terrain_height(id, dx);
				++id;
			}
		}
		counter += 1;
	}
	return board;
}

Board& board_caves(Board& board)
{
	unsigned int x = board.get_x_size();
	unsigned int y = board.get_y_size();
	unsigned int can_height = y * 0.2;
	board.base_terrain(can_height);

	for (int id = 0; id <= x; ++id) {
		can_height = rand() % (y / 4);
		board.set_terrain_height(id, can_height);
	}
	return board;
}

Board& board_battlefield(Board& board)
{
	unsigned int x = board.get_x_size();
	unsigned int y = board.get_y_size();
	unsigned int can_height = y * 0.2;
	board.base_terrain(can_height);
	can_height = y * 0.3;
	int dx = x / 15;
	
	for (int q = 0; q <= x; ++q) {
		if (q > 2*dx && q <= 4 * dx) {
			board.set_terrain_height(q, can_height);
		}
		if (q > 12*dx && q <= 14 * dx) {
			board.set_terrain_height(q, can_height);
		}
		if (q > x / 2 - 2 && q <= x / 2 + 2) {
			board.set_terrain_height(q, y / 2);
		}
	}
	board.set_terrain_height(2 * dx, can_height - 1);
	board.set_terrain_height(2 * dx-1, can_height - 2);
	board.set_terrain_height(2 * dx-2, can_height - 3);
	board.set_terrain_height(2 * dx-3, can_height - 4);

	board.set_terrain_height(14 * dx+1, can_height - 1);
	board.set_terrain_height(14 * dx+2, can_height - 2);
	board.set_terrain_height(14 * dx+3, can_height - 3);
	board.set_terrain_height(14 * dx+4, can_height - 4);

	return board;
}

