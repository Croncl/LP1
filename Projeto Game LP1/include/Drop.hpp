#ifndef DROP_HPP
#define DROP_HPP

#include <SFML/Graphics.hpp>

enum class DropType {
    Health,
    Ammo
};

class Drop {
public:
    Drop(DropType type, const sf::Vector2f& position, const sf::Texture& texture);

    DropType getType() const;
    const sf::Sprite& getSprite() const;
    bool isMarkedForRemoval() const;
    void update(sf::Time deltaTime); // Adicionando a declaração do método update
    void draw(sf::RenderWindow& window) const; // Adicionando a declaração do método draw
    sf::FloatRect getBounds() const; // Adicionando a declaração do método getBounds

    static DropType getRandomDropType();

private:
    DropType type;
    sf::Sprite sprite;
    sf::Texture dropTexture; // Adicionando a textura do drop
    bool valid = true;
    sf::Time lifetime; // tempo de vida do drop
};

#endif // DROP_HPP