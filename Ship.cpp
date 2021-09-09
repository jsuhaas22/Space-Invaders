#include "Ship.hpp"
#include "constants.hpp"

Ship::Ship() : sf::Sprite()
{
    texture.loadFromFile(C_ship_file_path);
    this->setTexture(texture);
    points = 0;
};

void Ship::init(const sf::Vector2f &init_position)
{
    position = init_position;
    this->setPosition(position);
}

sf::Vector2u Ship::get_size()
{
    return texture.getSize();
}