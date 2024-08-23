#ifndef DROP_HPP
#define DROP_HPP

#include <SFML/Graphics.hpp>

enum class DropType {
    Health,
    Mana
};

class Drop {
public:
    Drop(DropType type, const sf::Vector2f& position, const sf::Texture& texture);

    DropType getType() const;
    const sf::Sprite& getSprite() const;
    bool isMarkedForRemoval() const;
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

    static DropType getRandomDropType();

private:
    void initialize(const sf::Vector2f& position, const sf::Texture& texture); // Declaração do método initialize

    DropType type;
    sf::Sprite sprite;
    sf::Texture dropTexture;
    bool valid = true;
    sf::Time lifetime;
};

#endif // DROP_HPP