#include "Alien.hpp"
#include "constants.hpp"

Alien::Alien(const unsigned int ID, const sf::Vector2f &position)
{
    texture.loadFromFile(C_alien_file_path);
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