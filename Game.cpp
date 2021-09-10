#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "constants.hpp"

Game::Game()
{
    /*Window creation*/
    window.create(sf::VideoMode(dimensionX, dimensionY), "Space Invaders!");
    ship.init(sf::Vector2f(dimensionX / 2, dimensionY - ship.get_size().y));
    cur_movement = Movement::RIGHT;
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
        move_fleet();
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

/* Currently the function constructs a new fleet from the left, always.
 * New rows are created when function hits left again, at (0.0f, 0.0f).
 * 1. Change needed: the first row must be constructed on one side, and subsequent rows on the other.
 * 2. Change needed: new row should be created when function hits opp of first row site, at (0ordimX, 0-(aliensize/2))
 * Easy enough, but I am too sleepy to bother rn.
 */
void Game::create_fleet()
{
    int i;
    Alien temp_alien;
    sf::Vector2u alien_size = temp_alien.get_size();
    int num_in_row = dimensionX / alien_size.x;
    sf::Vector2f leftmost_alien_pos = sf::Vector2f(0.f, 0.f);
    for(i = 0; i < num_in_row - 1; ++i)
    {
        alien_fleet.push_back(new Alien(i + alien_num, 
        sf::Vector2f(leftmost_alien_pos.x + (i * alien_size.x), 0.f)));
    }
    alien_num += i;
}

void Game::move_fleet()
{
    Alien alien;
    if(cur_movement == Movement::RIGHT)
    {
        for(int i = alien_fleet.size() - 1; i >= 0; --i)
        {
            alien_fleet[i]->move(C_alien_right_offset);
        }
        if(alien_fleet.back()->getPosition().x + alien.get_size().x >= dimensionX){
            cur_movement = Movement::LEFT;
            if(alien_fleet[0]->getPosition().y + alien_fleet[0]->get_size().y < dimensionY){
                move_fleet_down();
            }
        }
        
    }
    else if(cur_movement == Movement::LEFT)
    {
        for(int i = 0; i < alien_fleet.size(); ++i)
        {
            alien_fleet[i]->move(C_alien_left_offset);
        }
        if(alien_fleet[0]->getPosition().x <= 0)
        {
            cur_movement = Movement::RIGHT;
            if(alien_fleet[0]->getPosition().y + alien_fleet[0]->get_size().y < dimensionY){
                move_fleet_down();
                create_fleet();
            }
        }
    }
}

void Game::move_fleet_down()
{
    Alien alien;
    for(int i = 0; i < alien_fleet.size(); ++i)
    {
        alien_fleet[i]->move(0.f, alien.get_size().y / 2);
    }
}