#ifndef GAME
#define GAME

#include <vector>
#include <SFML/Graphics.hpp>

#include "Ship.hpp"
#include "Alien.hpp"

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
    Ship ship;
    Movement cur_movement;
    int alien_num = 0;

    void handle_key_events(sf::Event &event);
    void render();
    void create_fleet();
    void move_fleet();
    void move_fleet_down();
public:
    Game();
    void game_loop();
};

#endif