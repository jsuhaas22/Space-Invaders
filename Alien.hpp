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
    unsigned int id;
    float left_limit, right_limit;

public:
    Alien(const unsigned int ID = 0, const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
    const float left = 0, const float right = 0);

    sf::Vector2u get_size() const;

    void draw_alien(sf::RenderWindow &window);
    float get_left_limit();
    float get_right_limit();
    unsigned int get_id() const;
};

#endif