#ifndef SHIP
#define SHIP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Ship : public sf::Sprite
{
private:
    unsigned int points;
    sf::Texture texture;

public:

    Ship();
    void init(const sf::Vector2f &init_position);
    sf::Vector2u get_size();

    sf::Vector2f position;
};

#endif