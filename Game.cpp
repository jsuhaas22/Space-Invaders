#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "constants.hpp"

Game::Game()
{
    /*Window creation*/
    window.create(sf::VideoMode(dimensionX, dimensionY), "Space Invaders!");
    ship.init(sf::Vector2f(dimensionX / 2, dimensionY - ship.get_size().y));
}

void Game::game_loop()
{
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                handle_key_events(event);
            }
        }
        window.clear();
        window.draw(ship);
        window.display();
    }
}

void Game::handle_key_events(sf::Event &event)
{
    switch(event.key.code)
    {
        case sf::Keyboard::Right:
            if(ship.position.x < dimensionX - ship.get_size().x){
                ship.move(C_right_offset);
                ship.position = ship.position + C_right_offset;
            }
            break;
        case sf::Keyboard::Left:
            if(ship.position.x > 0.f){
                ship.move(C_left_offset);
                ship.position = ship.position + C_left_offset;
            }
            break;
    }
}