#ifndef BASE_HPP
#define BASE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Base {
public:
    Base();
    Base(int cenario);
    Base(sf::Vector2f position, int health, int cenario);

    sf::Vector2f getPosition() const;
    const sf::Sprite& getSprite() const;
    int getHealth() const;
    void takeDamage(int amount);

private:
    void initialize(int cenario);

    sf::Texture texture;
    sf::Sprite sprite;
    int health;
    int currentFrame;
    float frameDuration;
};

#endif // BASE_HPP