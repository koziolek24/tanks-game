#include "shoot.h"
#include "tank.h"
#include "board.h"
#include "User.h"
#include <math.h>
//zmienic na template
#define pi 3.14

bool shoot_right(Tank& player, Tank& opponent, Board &board, int power, int angle, int damage)
{
    int start_pos = player.get_x();
    int start_height = player.get_y();
    int end_pos = start_pos + power;
    int opponent_pos = opponent.get_x();
    // do konca tablicy
    for (int i = start_pos + 1; i < board.get_x_size(); i++)
    {
        double height = board.get_height(i);
        double shoot_height = double(i - start_pos) * double(i - end_pos) * tan(angle * pi / 180) / (start_pos - end_pos);
        shoot_height += start_height;

        
        board.set_bullet_coords(i, int(shoot_height));
        board.place_bullet();

        if (i == opponent_pos)
        {
            if (shoot_height - height < 1 and shoot_height - height > -1) {
                opponent.take_damage(damage);
                return 1;
            }
        }
        if (shoot_height - height <= 0 and i < opponent_pos)
        {
            std::cout << opponent_pos - i << " too close\n";
            return 0;
        }
        if (shoot_height - height <= 0 and i > opponent_pos)
        {
            std::cout << i - opponent_pos << " too far\n";
            return 0;
        }
    }
    std::cout << "too far\n";
    return 0;
}


bool shoot_left(Tank& player, Tank& opponent, Board &board, int power, int angle, int damage)
{
    int start_pos = player.get_x();
    int start_height = player.get_y();
    int end_pos = start_pos - power;
    int opponent_pos = opponent.get_x();
    for (int i = start_pos - 1; i >= 0; i--)
    {
        double height = board.get_height(i);
        double shoot_height = double(i - start_pos) * double(i - end_pos) * tan(angle * pi / 180) / (end_pos - start_pos);
        shoot_height += start_height;

        
        board.set_bullet_coords(i, int(shoot_height));
        board.place_bullet();

        if (i == opponent_pos)
        {
            if (shoot_height - height < 1 and shoot_height - height > -1) {
                opponent.take_damage(damage);
                return 1;
            }
        }

        if (shoot_height - height <= 0 and i > opponent_pos) {
            std::cout << i - opponent_pos << " too close\n";
            return 0;
        }

        if (shoot_height - height <= 0 and i < opponent_pos) {
            std::cout << opponent_pos - i << " too far\n";
            return 0;
        }

    }
    std::cout << "too far";
    return 0;

}


void get_side(Tank& player, Tank& opponent, Board& board, User user)
{
    int power; int angle;
    std::cout << "Input your power\n";
    std::cin >> power;
    std::cout << "Input your angle\n";
    std::cin >> angle;
    std::cout << "Choose your ammo\n";
    std::cout << "1 for free ammo\n";
    std::cout << "2 for heavy ammo\n";
    std::cout << "3 for light ammo\n";
    std::string ammo_type;
    int damage = 0;
    while (true) {
        std::cin >> ammo_type;
        if (ammo_type == "1") 
        {

            damage = player.get_free();
            if (damage) {
                break;
            }
        }
        else if (ammo_type == "2")
        {
            int level = user.get_info(1);
            damage = player.get_heavy(level);
            if (damage) {
                break;
            }
        }
        else if (ammo_type == "3")
        {
            int level = user.get_info(0);
            damage = player.get_light(level);
            if (damage) {

                break;
            }
        }
        else 
        {
            std::cout << "Invalid choice\n";
        }
    }
    
    if (player.get_x() < opponent.get_x()) {
        shoot_right(player, opponent, board, power, angle, damage);
    }
    else
    {
        shoot_left(player, opponent, board, power, angle, damage);
    }
}


void make_obstacle(Board& board)
{
    int x, y;
    std::cout << "Input x position:\n";
    std::cin >> x;
    std::cout << "Input height:\n";
    std::cin >> y;
    board.set_terrain_height(x, y);
}

void make_move(Tank& player, Board& board)
{
    char Dir;
    std::cout << "Input direction\n";
    std::cout << "R for right, L for Left\n";
    while (true)
    {
        std::cin >> Dir;
        if (Dir == 'L' or Dir == 'R')
        {
            break;
        }
        std::cout << "Invalid direction\n";

    }
    board.move(player, Dir);
}