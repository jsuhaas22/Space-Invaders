#include "Bullet.hpp"

Bullet::Bullet() : sf::RectangleShape(sf::Vector2f(3.f, 10.f))
{
    this->setFillColor(sf::Color::Red);
    this->is_loaded = true;
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(*this);
}
