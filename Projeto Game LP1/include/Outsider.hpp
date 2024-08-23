#ifndef OUTSIDER_HPP
#define OUTSIDER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include "Projectile.hpp" // Certifique-se de incluir o cabeçalho do Projectile

class Outsider {
public:
    Outsider(const sf::Texture& texture);
    void setRandomPositionOnEdge(const sf::Vector2u& windowSize); // Removido const
    void moveTowards(const sf::Vector2f& target, float deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    const sf::Sprite& getSprite() const; // Alterado para const
    void takeDamage(int damage);
    bool isDead() const;
    bool canShoot() const;
    void resetShootClock();
    sf::Time getShootInterval() const; // Adicionado getter para shootInterval
    void shoot(const sf::Vector2f& target, std::vector<Projectile>& projectiles); // Adicionada a função shoot
    void markForRemoval(); // Adicionado método para marcar para remoção
    bool isMarkedForRemoval() const; // Adicionado método para verificar se está marcado para remoção

private:
    sf::Sprite sprite;
    float speed;
    int health;
    sf::Clock shootClock;
    sf::Time shootInterval;
    sf::Texture projectileTexture; // Adicionada a textura do projétil
    sf::CircleShape projectileShape; // Adicionado o shape circular do projétil
    bool markedForRemoval; // Adicionado membro para marcar para remoção
};

#endif // OUTSIDER_HPP
