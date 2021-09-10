#ifndef ALIEN
#define ALIEN

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Alien : public sf::Sprite
{
private:
    sf::Vector2u size;
    sf::Texture texture;

public:
    Alien(const sf::Vector2f &position = sf::Vector2f(0.f, 0.f));
    sf::Vector2u get_size() const;
    void draw_alien(sf::RenderWindow &window);
};

#endif