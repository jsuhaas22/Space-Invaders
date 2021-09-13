#ifndef GAME
#define GAME

#include <vector>
#include <SFML/Graphics.hpp>

#include "Ship.hpp"
#include "Alien.hpp"
#include "Bullet.hpp"

enum Movement {
    DOWN,
    LEFT,
    RIGHT
};

class Game
{
private:
    sf::RenderWindow window;

    std::vector<Alien*> alien_fleet;
    std::vector<Bullet*> bullets;
    Ship ship;
    Movement cur_movement;
    int alien_num, bullet_index, bullet_num, points;

    void render();
    void handle_key_events(sf::Event &event);
    void create_fleet();
    void move_fleet();
    void move_fleet_down();
    void fire();
    void reload(int i);
    void signal_gameover();

public:
    Game();
    void game_loop();
};

#endif