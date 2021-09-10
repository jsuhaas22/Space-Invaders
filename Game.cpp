#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "constants.hpp"

Game::Game()
{
    /*Window creation*/
    window.create(sf::VideoMode(dimensionX, dimensionY), "Space Invaders!");
    ship.init(sf::Vector2f(dimensionX / 2, dimensionY - ship.get_size().y));
    create_fleet();
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
        render();
    }
}

void Game::render()
{
    window.clear();

    window.draw(ship);
    
    /* drawing the fleet */
    int len = alien_fleet.size();
    for(int i = 0; i < len; ++i)
    {
        alien_fleet[i]->draw_alien(window); 
    }
    /* drawing the fleet */

    window.display();
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

void Game::create_fleet()
{
    Alien temp_alien;
    sf::Vector2u alien_size = temp_alien.get_size();
    int num_in_row = dimensionX / alien_size.x;
    sf::Vector2f leftmost_alien_pos = sf::Vector2f(0.f, 0.f);
    for(int i = 0; i < num_in_row - 1; ++i)
    {
        alien_fleet.push_back(new Alien(sf::Vector2f(leftmost_alien_pos.x + (i * alien_size.x), 0.f)));
    }
}