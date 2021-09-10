#ifndef GAME
#define GAME

#include <vector>
#include <SFML/Graphics.hpp>

#include "Ship.hpp"
#include "Alien.hpp"

class Game
{
private:
    sf::RenderWindow window;
    std::vector<Alien*> alien_fleet;
    Ship ship;

    void handle_key_events(sf::Event &event);
    void render();
    void create_fleet();
public:
    Game();
    void game_loop();
};

#endif