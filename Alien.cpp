#include "Alien.hpp"
#include "constants.hpp"

Alien::Alien(const unsigned int ID, const sf::Vector2f &position, const float left, const float right)
{
    texture.loadFromFile(C_alien_file_path);
    this->left_limit = left;
    this->right_limit = right;
    this->setTexture(texture);
    this->setPosition(position);
    this->id = ID;
}

sf::Vector2u Alien::get_size() const
{
    return texture.getSize();
}

void Alien::draw_alien(sf::RenderWindow &window)
{
    window.draw(*this); //sf::RenderWindow::draw(...) doesn't accept pointers.
}

unsigned int Alien::get_id() const
{
    return id;
}

float Alien::get_left_limit()
{
    return left_limit;
}

float Alien::get_right_limit()
{
    return right_limit;
}