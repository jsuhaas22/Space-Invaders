#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

#include "Ship.hpp"

class Game
{
private:
    sf::RenderWindow window;
    Ship ship;

    void handle_key_events(sf::Event &event);

public:
    Game();
    void game_loop();
};

#endif