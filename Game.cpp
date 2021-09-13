#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "constants.hpp"

Game::Game()
{
    /*Window creation*/
    window.create(sf::VideoMode(dimensionX, dimensionY), "Space Invaders!");
    
    /*Ship initialization*/
    ship.init(sf::Vector2f(dimensionX / 2, dimensionY - ship.get_size().y));
    bullet_num = 3;
    bullet_index = points = 0;
    for(int i = 0; i < bullet_num; ++i)
    {
        bullets.push_back(new Bullet);
    }
    /*Ship initialization*/

    /*alien fleet initialization*/
    cur_movement = Movement::RIGHT;
    create_fleet();
    /*alien fleet initialization*/
}

void Game::game_loop()
{
    while(window.isOpen())
    {
        /*Handle user events*/
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
        /*Handle user events*/

        /*Move bullets that have been fired*/
        for(int i = 0; i < bullet_num; ++i)
        {
            if(!bullets[i]->is_loaded)
            {
                bullets[i]->move(C_bullet_speed);
                if(bullets[i]->getPosition().y < 0.f)
                {
                    reload(i);
                }
            }
        }
        /*Move bullets that have been fired*/

        /*Handle Collision*/
        int len = alien_fleet.size();
        for(int i = 0; i < bullet_num; ++i)
        {
            if(!bullets[i]->is_loaded)
            {
                for(int j = 0; j < len; ++j)
                {
                    if(bullets[i]->getGlobalBounds().intersects(alien_fleet[j]->getGlobalBounds()))
                    {
                        delete alien_fleet[j];
                        alien_fleet[j] = nullptr;
                        alien_fleet.erase(alien_fleet.begin() + j);
                        reload(i);
                        points += 10;
                    }
                }
            }
        }
        /*Handle Collision*/
        move_fleet();
        render();
    }
}

void Game::render()
{
    window.clear(); //might wanna add a cool background here

    window.draw(ship);
    
    /* draw fleet */
    int len = alien_fleet.size();
    for(int i = 0; i < len; ++i)
    {
        alien_fleet[i]->draw_alien(window); 
    }
    /* draw fleet */

    /*draw bullets*/
    for(int i = 0; i < bullet_num; ++i)
    {
        if(!bullets[i]->is_loaded)
        {
            bullets[i]->draw(window);
  //          std::cout << i << " " << bullets[i]->getPosition().y << std::endl; //DEL
        }
    }
    /*draw bullets*/

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
        case sf::Keyboard::Space:
            fire();
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
        int a_id = i + alien_num;
        float left = 0 + (i * alien_size.x);
        float right = dimensionX - ((num_in_row - 1 - i) * alien_size.x) + alien_size.x;
        const sf::Vector2f pos = sf::Vector2f(leftmost_alien_pos.x + (i * alien_size.x), 0.f);
        alien_fleet.push_back(new Alien(a_id, pos, left, right));
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
        if(alien_fleet.back()->getPosition().x + alien.get_size().x >= alien_fleet.back()->get_right_limit()){
            cur_movement = Movement::LEFT;
            if(alien_fleet[0]->getPosition().y + alien_fleet[0]->get_size().y < dimensionY){
                move_fleet_down();
            }
            else signal_gameover();
        }
        
    }
    else if(cur_movement == Movement::LEFT)
    {
        for(int i = 0; i < alien_fleet.size(); ++i)
        {
            alien_fleet[i]->move(C_alien_left_offset);
        }
        if(alien_fleet[0]->getPosition().x <= alien_fleet[0]->get_left_limit())
        {
            cur_movement = Movement::RIGHT;
            if(alien_fleet[0]->getPosition().y + alien_fleet[0]->get_size().y < dimensionY){
                move_fleet_down();
                create_fleet();
            }
            else
            {
                signal_gameover();
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

void Game::fire()
{
    if(bullet_index < bullet_num)
    {
        Alien alien;
        sf::Vector2f ship_pos = ship.getPosition();
        bullets[bullet_index]->setPosition(ship_pos.x + (alien.get_size().x / 2), ship_pos.y);
        bullets[bullet_index]->is_loaded = false;
        bullet_index++;
    }
}

void Game::reload(int i)
{
    if(bullet_index > 2) bullet_index = 0;
    bullets[i]->is_loaded = true;
}

void Game::signal_gameover()
{
    std::cout << points << " GAME OVER" << std::endl;
    window.close();
}