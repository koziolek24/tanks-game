#include "board.h"

Board& Board::operator=(const Board& other)
{
	if (this == &other) {
		return *this;
	}
}

char Board::get_char_at(unsigned int x, unsigned int y) const
{
	if (x <= x_size && y <= y_size) {
		return board[y][x];
	}
	else {
		std::cout << "Coordinates exceeded.\n";
		return 'Q';
	}
}

void Board::set_char(unsigned int x, unsigned int y, char ch)
{
	if (x <= x_size && y <= y_size) {
		board[y][x] = ch;
	}
}

std::vector<char> Board::get_row(unsigned int y) const
{
	if (y <= y_size) {
		return board[y];
	}
}

void Board::add_player(Tank& t)
{
	for (Tank* tank : players) {
		if (tank->get_x() == t.get_x()) {
			std::cout << "There already is a tank on that x: " << tank->get_x() << " coordinate.\n";
			return;
		}
	}
	players.push_back(&t);
}

void Board::add_player(Tank& t, Tank& tt)
{
	for (Tank* tank : players) {
		if (tank->get_x() == t.get_x()) {
			std::cout << "There already is a tank on that x: " << tank->get_x() << " coordinate.\n";
			return;
		}
	}
	players.push_back(&t);

	for (Tank* tank : players) {
		if (tank->get_x() == tt.get_x()) {
			std::cout << "There already is a tank on that x: " << tank->get_x() << " coordinate.\n";
			return;
		}
	}
	players.push_back(&tt);
}

void Board::print_board()
{
	for (int i = this->get_y_size() - 1; i >= 0; --i) {
		for (char ch : board[i]) {
			if (ch != 'X' && ch != '{') {
				std::cout << ch;
			}
			else {
				const char* u_code = "\033[4m";
				const char* r_code = "\033[0m";
				std::cout << u_code << ch << r_code;
			}

		}
		std::cout << '\n';
	}
}

void Board::set_all_clear()
{
	board.resize(y_size + 1, std::vector<char>(x_size + 1, ' '));
}

void Board::set_size(unsigned int x, unsigned int y)
{
	x_size = x;
	y_size = y;
	this->set_all_clear();
}

void Board::base_terrain(unsigned int y)
{
	this->remove_tanks();

	if (y > y_size) {
		std::cout << "The height of the board is " << y_size << " you may not exceed that number.\n";
	}
	else {
		this->set_all_clear();
		for (char& ch : board[y]) {
			ch = '_';
		}
	}
	this->measure_heights();
	this->place_tanks();
}

void Board::raise_terrain(unsigned int x)
{
	this->remove_tanks();
	unsigned int height = this->get_height(x);
	unsigned int height_l = get_height_left(x);
	unsigned int height_r = get_height_right(x);

	if (height + 1 > y_size) {
		//std::cout << "Already at max height: " << height << " \n";
		return;
	}
	// not on edge
	if (height_l != 999 && height_r != 999) {
		if (height_l > height && height_r > height) {
			if (board[height][x - 1] == '|') {
				board[height][x - 1] = ' ';
			}
			if (board[height][x + 1] == '|') {
				board[height][x + 1] = ' ';
			}
			board[height][x] = ' ';
		}
		else {
			board[height][x] = '|';
		}
	}
	// left edge
	else if (height_l == 999 && height_r != 999) {
		if (height_r > height) {
			if (board[height][x + 1] == '|') {
				board[height][x + 1] = ' ';
			}
			board[height][x] = ' ';
		}
		else {
			board[height][x] = '|';
		}
	}
	// right edge
	else if (height_l != 999 && height_r == 999) {
		if (height_l > height) {
			if (board[height][x - 1] == '|') {
				board[height][x - 1] = ' ';
			}
			board[height][x] = ' ';
		}
		else {
			board[height][x] = '|';
		}
	}
	board[height + 1][x] = '_';
	this->measure_heights();
	this->place_tanks();
}

void Board::lower_terrain(unsigned int x)
{
	this->remove_tanks();
	unsigned int height = get_height(x);

	if (height <= 1) {
		//std::cout << "Already at min height.\n";
		return;
	}
	board[height][x] = ' ';
	board[height - 1][x] = '_';
	this->fill_sides(x);
	this->measure_heights();
	this->place_tanks();
}

void Board::fill_sides(unsigned int x)
{
	unsigned int height_l = get_height_left(x);
	unsigned int height_r = get_height_right(x);
	if (height_l != 999) {
		while (height_l > get_height(x)) {
			height_l -= 1;
			board[height_l][x - 1] = '|';
		}
	}
	if (height_r != 999) {
		while (height_r > get_height(x)) {
			height_r -= 1;
			board[height_r][x + 1] = '|';
		}
	}
}

unsigned int Board::get_height(unsigned int x)
{
	unsigned int q = 0;
	char c;
	for (std::vector<char>& row : board) {
		c = board[q][x];
		if (c == '_' || c == 'X') break;
		q++;
	}
	return q;
}

unsigned int Board::get_height_left(unsigned int x)
{
	if (x == 0) {
		return 999;
	}

	unsigned int q = 0;
	char c;
	for (std::vector<char>& row : board) {
		c = board[q][x - 1];
		if (c == '_') break;
		q++;
	};
	return q;
}

unsigned int Board::get_height_right(unsigned int x)
{
	if (x > x_size - 1) {
		return 999;
	}
	unsigned int q = 0;
	char c;
	for (std::vector<char>& row : board) {
		c = board[q][x + 1];
		if (c == '_') break;
		q++;
	};
	return q;
}

void Board::set_terrain_height(unsigned int x, unsigned int height)
{
	unsigned int current_height = get_height(x);
	if (current_height == height) {
		//std::cout << "Already at x: " << height << "\n";
		return;
	}

	if (x > x_size) {
		std::cout << "X coordinate exceeded.\n";
		return;
	}

	if (height == current_height) return;
	else if (height > current_height) {
		while (height > current_height) {
			this->raise_terrain(x);
			current_height += 1;
		}
	}
	else if (height < current_height) {
		while (height < current_height) {
			this->lower_terrain(x);
			current_height -= 1;
		}
	}
}

void Board::make_hill(unsigned int x_center, unsigned int height)
{
	unsigned int cur_height = get_height(x_center);
	if (x_center >= x_size || cur_height + height > y_size) {
		std::cout << "Wrong parameters.\n";
		return;
	}
	this->remove_tanks();

	for (unsigned int dx = 0; dx <= height; ++dx) {
		int x_left = x_center - dx;
		unsigned int x_right = x_center + dx;

		unsigned int hill_height = cur_height + height - dx;

		if (x_left >= 0) {
			this->set_terrain_height(x_left, hill_height);
		}
		if (x_right <= x_size) {
			this->set_terrain_height(x_right, hill_height);
		}
	}
	this->place_tanks();
}

void Board::make_round_hill(unsigned int x_center, unsigned int height)
{
	unsigned int cur_height = get_height(x_center);
	if (x_center > x_size || cur_height + height > y_size) {
		std::cout << "Wrong parameters.\n";
		return;
	}
	double x = height + cur_height;
	this->set_terrain_height(x_center, height);
	while (x > 0) {

	}


	this->place_tanks();
}

void Board::measure_heights()
{
	all_heights.clear();
	for (int x = 0; x <= x_size; ++x) {
		unsigned int h = get_height(x);
		all_heights.push_back(h);
	}
}

void Board::set_all_heights()
{
	for (int q = 0; q <= x_size; ++q) {
		this->set_char(q, all_heights[q], '_');
	}
}

void Board::place_tanks()
{
	this->remove_tanks();
	for (Tank* t : players) {
		unsigned int x = t->get_x();
		char c = board[t->get_y()][x];
		if (c == '_' || c=='O') {
			board[t->get_y()][x] = 'X';
		}
		else {
			unsigned int height = get_height(x);
			board[height][x] = 'X';
			t->set_coords(x, height);
		}
	}
}

void Board::remove_tanks()
{
	for (std::vector<char>& row : board) {
		for (char& ch : row) {
			if (ch == 'X') {
				ch = '_';
			}
		}
	}
}

void Board::set_bullet_coords(unsigned int x, unsigned int y)
{
	if (x <= x_size) {
		bx = x;
	}
	if (y <= y_size) {
		by = y;
	}
}

unsigned int Board::get_x_bulled() const
{
	return bx;
}

unsigned int Board::get_y_bullet() const
{
	return by;
}

void Board::place_bullet()
{
	if (get_height(bx) <= by) {
		board[by][bx] = 'O';
	}
}

void Board::remove_bullet()
{
	this->remove_tanks();
	for (int y = this->get_y_size() - 1; y >= 0; --y) {
		for (int x = 0; x <= x_size; ++x) {
			if (board[y][x] == 'O' && get_height(x) != y) {
				board[y][x] = ' ';
			}
		}
	}
	this->set_all_heights();
	this->place_tanks();
}

void Board::move(Tank& t, char dir)
{
	unsigned int x = t.get_x();
	if (x == 0 && dir == 'L') {
		std::cout << "Cannot move left. Already at left edge.\n";
		return;
	}
	else if (x == x_size && dir == 'R') {
		std::cout << "Cannot move right. Already at right edge.\n";
		return;
	}
	else if (dir == 'R') {
		if (board[get_height(x + 1)][x + 1] == 'X') {
			std::cout << "Cannot move right. Player standing there.\n";
			return;
		}
		else if (get_height(x + 1) > get_height(x) + 3) {
			std::cout << "Cannot move right. Too steep.\n";
			return;
		}
		else {
			t.move('R');
			this->place_tanks();
			return;
		}
	}
	else if (dir == 'L') {
		if (board[get_height(x - 1)][x - 1] == 'X') {
			std::cout << "Cannot move left. Player standing there.\n";
			return;
		}
		else if (get_height(x - 1) > get_height(x) + 3) {
			std::cout << "Cannot move left. Too steep.\n";
			return;
		}
		else {
			t.move('L');
			this->place_tanks();
			return;
		}
	}

}

void Board::add_obstacle(Obstacle& o)
{
	obstacles.push_back(&o);
}

void Board::remove_obstacle(Obstacle* o)
{
	auto it = std::find(obstacles.begin(), obstacles.end(), o);
	if (it != obstacles.end()) {
		obstacles.erase(it);
	}
}

void Board::place_obstacles()
{
	this->remove_obstacles();
	for (Obstacle* o : obstacles) {
		board[o->get_y()][o->get_x()] = '{';
	}
}

void Board::remove_obstacles()
{
	this->set_all_clear();
	this->set_all_heights();
	this->place_tanks();
}

void Board::randomize_obstacles()
{
	for (Obstacle* o : obstacles) {
		while (o->get_y() < get_height(o->get_x())) {
			o->set_y(rand() % y_size);
		}
		o->set_x(rand() & x_size);

	}
}

void Board::generate_obstacles(unsigned int count)
{
	count -= 1;
	while (count < 9999) 
	{
		Obstacle* o = new Obstacle;
		this->add_obstacle(*o);
		count -= 1;
	}
}

void Board::read_board_from_file(const std::string& path)
{
	std::ifstream file(path);
	std::string line;
	std::vector<std::vector<char>> temp;
	board.clear();
	if (file.is_open()) {
		while (std::getline(file, line)) {
			// removes endline symbol
			line.erase(std::remove(line.begin(), line.end(), '\n'), line.cend());
			std::vector<char> row(line.begin(), line.end());
			temp.push_back(row);
		}
	}

	for (int i = temp.size() - 1; i >= 0; --i) {
		board.push_back(temp[i]);
	}
	y_size = board.size() + 1;
	x_size = board[0].size() + 1;
	this->measure_heights();
}

void Board::save_board_to_file(const std::string& path) const
{
	std::ofstream file(path);
	if (file.is_open()) {
		for (int i = this->get_y_size() - 1; i >= 0; --i) {
			std::string content = "";
			for (char ch : board[i]) {
				content += ch;
			}
			file << content << "\n";
		}
	}
}

std::vector<Tank*> Board::get_players() const
{
	return players;
}

unsigned int Board::get_x_size() const
{
	return x_size;
}

unsigned int Board::get_y_size() const
{
	return y_size;
}	