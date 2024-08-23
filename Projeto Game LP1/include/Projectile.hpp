#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::Texture& texture, float speed);

    void update(sf::Time deltaTime);
    sf::FloatRect getBounds() const;
    const sf::Sprite& getSprite() const;
    bool isInBounds() const;
    void markForRemoval();
    bool isMarkedForRemoval() const;

private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool valid;
};

#endif // PROJECTILE_HPP