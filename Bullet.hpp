#ifndef BULLET
#define BULLET

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Bullet : public sf::RectangleShape
{
public:

    bool is_loaded;

    Bullet();
    void draw(sf::RenderWindow &window);
};


#endif