#ifndef DEFENDER_HPP
#define DEFENDER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Projectile.hpp"

class Defender {
public:
    Defender() = default; // Construtor padrão
    Defender(sf::Vector2f position, const std::string& textureFile, const std::string& projectileTextureFile);

    void update(sf::Time deltaTime, const sf::RenderWindow& window, std::vector<Projectile>& projectiles);
    sf::Vector2f getPosition() const;
    sf::Sprite& getSprite();
    int getHealth() const;
    void setHealth(int amount);
    int getAmmo() const;
    void addAmmo(int amount);
    void shoot(const sf::Vector2f& target, std::vector<Projectile>& projectiles);

    // Novos métodos
    void reload(int amount);
    void takeDamage(int damage);
    bool isAlive() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture projectileTexture;
    int health;
    int ammo;
    int maxAmmo = 13; // Definindo o valor máximo de munição
    float speed;
    sf::Clock shootClock;
    sf::Time shootCooldown;
};

#endif // DEFENDER_HPP