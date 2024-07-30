#include "Projectile.hpp"
#include <cmath>

Projectile::Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::Texture& texture, float speed)
    : valid(true) {
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);

    // Calcular a direção e velocidade do projétil
    sf::Vector2f direction = targetPosition - startPosition;
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = direction / magnitude * speed;
}

void Projectile::update(sf::Time deltaTime) {
    sprite.move(velocity * deltaTime.asSeconds());

    // Check if projectile is out of bounds (e.g., screen boundaries)
    if (sprite.getPosition().x < 0 || sprite.getPosition().x > 800 || // Assuming screen width is 800
        sprite.getPosition().y < 0 || sprite.getPosition().y > 600) { // Assuming screen height is 600
        markForRemoval();
    }
}

sf::FloatRect Projectile::getBounds() const {
    return sprite.getGlobalBounds();
}

const sf::Sprite& Projectile::getSprite() const {
    return sprite;
}

bool Projectile::isInBounds() const {
    return valid;
}

void Projectile::markForRemoval() {
    valid = false;
}

bool Projectile::isMarkedForRemoval() const {
    return !valid;
}