#include "game.h"
#include "tank.h"
#include "board.h"
#include "shoot.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include "User.h"
#include "creator.h"
#include <string>

int get_int(std::string value)
{
    try
    {
        int n_value = std::stoi(value);
        return n_value;
    }
    catch (std::invalid_argument const& e)
    {
        return -1;
    }
}


void clearConsole()
{
    std::system("cls");
}

void getInfo(Board &board, Tank tank, Tank opponent)
{
    clearConsole();
    board.print_board();
    std::cout << "Your health: " << tank.get_cur_health() << " ";
    std::cout << "(shield: " << tank.get_shield() << ")\n";
    std::cout << "Opponent's health: " << opponent.get_cur_health() << " ";
    std::cout << "(shield: " << opponent.get_shield() << ")\n";
    std::cout << "Your consumables: " << tank.inventory_info() << "\n";
}

void get_move(Tank& player1, Tank& player2, Board& board, User user)
{
    std::cout << "Choose your move:\n";
    std::cout << "Build obstacle: 1\n";
    std::cout << "Shoot: 2\n";
    std::cout << "Move: 3\n";
    std::cout << "Shield: 4\n";
    std::cout << "RepairKit: 5\n";
    int ready = 0;
    while (!ready) {
        std::string move;
        std::cin >> move;

        if (move == "1")
        {
            ready = 1;
            make_obstacle(board);

        }
        else if (move == "2")
        {
            ready = 1;
            get_side(player1, player2, board, user);
        }
        else if (move == "3")
        {
            ready = 1;
            make_move(player1, board);
        }
        else if (move == "4")
        {
            if (player1.use_shield())
                ready = 1;
            else
                std::cout << "You don't have any more shields\n";
        }
        else if (move == "5")
        {
            
            if (player1.use_repair())
                ready = 1;
            else
            {
                std::cout << "You don't have any more repair kits\n";
            }
        }
        else
        {
            std::cout << "Invalid option\n";
        }
    }
}

void game_display(Tank& player1, Tank& player2, Board board, User& user)
{
    std::string ready;
    while (true)
    {
        getInfo(board, player1, player2);
        std::cout << "Turn of player 1\n";
        get_move(player1, player2, board, user);
        if (!player2.get_if_alive() or player2.get_current_load() == 0)
        {
            clearConsole();
            std::cout << "Player 1 won\n";
            int akt_money = user.get_money();
            user.set_money(akt_money + 100);
            int akt_wins = user.get_wins();
            user.set_wins(akt_wins + 1);
            return;
        }
        std::getline(std::cin, ready);
        std::getline(std::cin, ready);
        getInfo(board, player1, player2);
        std::cout << "Press anything to continue\n";
        std::getline(std::cin, ready);
        board.remove_bullet();
        getInfo(board, player2, player1);
        std::cout << "Turn of player 2\n";
        get_move(player2, player1, board, user);
        if (!player1.get_if_alive() or player1.get_current_load() == 0)
        {
            clearConsole();
            std::cout << "Player 2 won\n";
            int akt_money = user.get_money();
            user.set_money(akt_money + 50);
            return;
        }
        std::getline(std::cin, ready);
        std::getline(std::cin, ready);
        getInfo(board, player2, player1);
        std::cout << "Press anything to continue\n";
        std::getline(std::cin, ready);
        board.remove_bullet();
    }
}

void get_coords(Tank& tank, Board board)
{
    int x, y;
    std::cout << "Input your base x position ";
    std::cin >> x;
    y = board.get_height(x);
    tank.set_coords(x, y);
}

void get_bot_coords(Tank& tank, Board board)
{
    int x, y;
    // to do ustawic jak¹œ losow¹ wartoœæ
    x = board.get_x_size() - 1;
    y = board.get_height(x);
    tank.set_coords(x, y);
}

void game_with_bot(Tank& player, Tank& bot, Board board, int probability, User& user)
{
    std::string ready;
    int bot_damage;
    if (probability == 7)
    {
        bot_damage = 30;
    }
    else if (probability == 5)
    {
        bot_damage = 50;
    }
    else
    {
        bot_damage = 70;
    }
    while (true)
    {
        getInfo(board, player, bot);
        std::cout << "Your turn player\n";
        get_move(player, bot, board, user);
        if (!bot.get_if_alive())
        {
            clearConsole();
            std::cout << "You won\n";
            int akt_money = user.get_money();
            user.set_money(akt_money + 100);
            int akt_wins = user.get_wins();
            user.set_wins(akt_wins + 1);
            
            return;
        }
        std::getline(std::cin, ready);
        std::getline(std::cin, ready);
        getInfo(board, player, bot);
        std::cout << "Press anything to continue\n";
        std::getline(std::cin, ready);
        board.remove_bullet();


        getInfo(board, player, bot);
        std::cout << "Bot's turn\n";
        int val = rand() % 10;
        if (val >= probability)
        {

            
            player.take_damage(bot_damage);
            std::cout << "You've been hit\n";
        }
        else
        {
            std::cout << "He missed\n";
        }
        if (!player.get_if_alive() or player.get_current_load() == 0)
        {
            clearConsole();
            int akt_money = user.get_money();
            user.set_money(akt_money + 50);
            std::cout << "You lost\n";
            return;
        }
        std::cout << "Press anything to continue\n";
        std::getline(std::cin, ready);

    }
}

void config_player(Tank& player, Tank& opponent, User& player1, int mode)
{
    // konfiguracja swoja
    clearConsole();
    std::cout << "Configuration of player\n";
    double multiply = player1.get_info(2) - 1;
    double max_health = 200 + 50 * multiply;
    player.set_max_health(max_health);
    player.set_cur_health(max_health);
    if (mode == 1)
    {
        opponent.set_max_health(max_health);
        opponent.set_cur_health(max_health);
    }
    std::cout << "Choose your ammo:\n";
    int light_num = player1.get_info(5);
    int heavy_num = player1.get_info(6);
    LightAmmo new_light(player1.get_info(0));
    HeavyAmmo new_heavy(player1.get_info(1));

    std::cout << "Light ammo: " << light_num << "\n";
    std::cout << "Heavy ammo: " << heavy_num << "\n";
    std::string input;
    int light = 16;
    while (light > 15) {
        std::cout << "How many light ammo: ";
        std::cin >> input;
        light = get_int(input);
        if (light > 15 or light > light_num or light < 0)
        {
            light = 16;
            std::cout << "Invalid numer of light ammo\n";
        }
    }

    for (int i = 0; i < light; i++)
    {
        player.add_ammo(new_light);
        if (mode == 1)
        {
            opponent.add_ammo(new_light);
        }
    }
    
    int heavy = 16;
    while (heavy > 15) {
        std::cout << "How many heavy ammo: ";
        std::cin >> input;
        heavy = get_int(input);
        if (heavy + light > 15 or heavy > heavy_num or heavy < 0)
        {
            heavy = 16;
            std::cout << "Invalid numer of heavy ammo\n";
        }
    }
    
    for (int i = 0; i < heavy; i++)
    {
        player.add_ammo(new_heavy);
        if (mode == 1)
        {
            opponent.add_ammo(new_heavy);
        }
    }


    player1.remove_item(5, light);
    player1.remove_item(6, heavy);
    player.fill_ammo();
    opponent.fill_ammo();

    //consumables
    int shield_num = player1.get_info(7);
    int repair_num = player1.get_info(8);
    int shield = 0;
    int repair = 0;
    std::cout << "Pick your number of consumables:\n";
    std::cout << "Shields " << shield_num << "\n";
    std::cout << "Repairs " << repair_num << "\n";
    while (true) {
        std::cout << "How many shields: ";
        std::cin >> input;
        shield = get_int(input);
        if (shield >= 0 and shield <= shield_num)
        {
            break;
        }
        std::cout << "Invalid number of shields\n";
    }

    player1.remove_item(7, shield);

    for (int i = 0; i < shield; i++)
    {
        Shield new_shield(50);
        player.add_to_inventory(new_shield);
        if (mode == 1)
        {
            Shield op_shield(50);
            opponent.add_to_inventory(op_shield);
        }
    }

    while (true) {
        std::cout << "How many repairs ";
        std::cin >> input;
        repair = get_int(input);
        if (repair >= 0 and repair <= repair_num)
        {
            break;
        }
        std::cout << "Invalid number of repairs\n";
    }

    player1.remove_item(8, repair);
    for (int i = 0; i < repair; i++)
    {
        RepairKit new_repair(50);
        player.add_to_inventory(new_repair);
        if (mode == 1)
        {
            RepairKit op_repair(50);
            opponent.add_to_inventory(op_repair);
        }
    }
    //koniec konfig
}

void config_bot(Tank& bot, int level)
{
    double max_health = 200 + 50 * level;
    bot.set_max_health(max_health);
    bot.set_cur_health(max_health);
}

void game_start(Tank player1, Tank player2, int probability, User& user)
{
    clearConsole();

    Board board(80, 20);

    std::cout << "Pick your board map\n";
    std::cout << "1 Battlefield\n";
    std::cout << "2 Canyon\n";
    std::cout << "3 Caves\n";
    std::cout << "4 City\n";
    std::cout << "5 Hills\n";

    std::string board_n;
    while (true)
    {
        std::cin >> board_n;
        if (board_n == "1")
        {
            board_battlefield(board);
            break;
        }
        else if (board_n == "2")
        {
            board_canyon(board);
            break;
        }
        else if (board_n == "3")
        {
            board_caves(board);
            break;
        }
        else if (board_n == "4")
        {
            board_city(board);
            break;
        }
        else if (board_n == "5")
        {
            board_hills(board);
            break;
        }
        else
        {
            std::cout << "Invalid map\n";
        }
    }


    std::cout << "Player 1\n";
    get_coords(player1, board);

    clearConsole();
    if (probability == 0)
    {
        std::cout << "Player2\n";
        get_coords(player2, board);
    }
    else
    {
        get_bot_coords(player2, board);
    }


    board.add_player(player1);
    board.add_player(player2);
    board.place_tanks();
    if (probability == 0)
    {
        game_display(player1, player2, board, user);
    }
    else
    {
        game_with_bot(player1, player2, board, probability, user);
    }
}

User game_mode(User& player1)
{
    std::cout << "Choose your game mode:\n";
    std::cout << "Player vs Player: 1\n";
    std::cout << "Player vs easy bot: 2\n";
    std::cout << "Player vs medium bot: 3\n";
    std::cout << "Player vs hard bot: 4\n";
    std::string mode;
    int choice;
    while (true)
    {
        std::cin >> mode;
        if (mode == "1")
        {
            choice = 1;
            break;
        }
        else if (mode == "2")
        {
            choice = 2;
            break;
        }
        else if (mode == "3")
        {
            choice = 3; 
            break;
        }
        else if (mode == "4")
        {
            choice = 4;
            break;
        }
        else
        {
            std::cout << "Invalid mode\n";
        }
    }
    int probability = 0;
    Tank player;
    Tank opponent;
    config_player(player, opponent, player1, choice);
    
    clearConsole();
    
    if (choice == 2)
    {
        config_bot(opponent, 1);
        probability = 7;
    }
    else if (choice == 3)
    {
        config_bot(opponent, 2);
        probability = 5;
    }
    else if (choice == 4)
    {
        config_bot(opponent, 4);
        probability = 3;
    }
    game_start(player, opponent, probability, player1);
    return player1;
}

