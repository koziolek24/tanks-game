#include "File.h"

void File::write_csv(std::string fname, std::vector<User> vct)
{
	std::fstream file;
	file.open(fname, std::ios::out);
	for (auto user : vct)
	{
		file << user.get_name() << ',';
		for (int i = 0; i < 9; i++)
		{
			file<< user.get_info(i) << ',';
		}
		file << user.get_money() << ',' << user.get_wins() << "\n";
	}
	file.close();
}

std::vector<User> File::read_csv(std::string fname)
{
	std::vector<User> users = {};
	std::fstream file;
	file.open(fname, std::ios::in);
	std::vector<std::string> row;
	std::string word, temp;
	while (file >> temp)
	{
		row.clear();
		std::stringstream s(temp);
		while (std::getline(s, word, ','))
		{
			row.push_back(word);
		}
		int table[9];
		for (int i = 0; i < 9; i++)
		{
			table[i] = std::stoi(row[i + 1]);
		}
		User user(row[0],table, std::stoi(row[10]), std::stoi(row[11]));
		users.emplace_back(user);
	}
	return users;
}
