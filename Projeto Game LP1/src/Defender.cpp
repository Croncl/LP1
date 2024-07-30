#include "Defender.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stdexcept>

Defender::Defender(sf::Vector2f position, const std::string& textureFile, const std::string& projectileTextureFile)
    : health(100), ammo(20), maxAmmo(100), speed(200.0f), shootCooldown(sf::seconds(0.2f)) { // Inicializa com 20 projéteis e cooldown de 0.2s
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Falha ao carregar " + textureFile);
    }
    if (!projectileTexture.loadFromFile(projectileTextureFile)) {
        throw std::runtime_error("Falha ao carregar " + projectileTextureFile);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Defender::update(sf::Time deltaTime, const sf::RenderWindow& window, std::vector<Projectile>& projectiles) {
    // Movimento com WSAD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.move(0, -speed * deltaTime.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0, speed * deltaTime.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.move(-speed * deltaTime.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move(speed * deltaTime.asSeconds(), 0);
    }

    // Limitar o movimento do defensor dentro da janela
    sf::Vector2f position = sprite.getPosition();
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + sprite.getGlobalBounds().width > window.getSize().x) {
        position.x = window.getSize().x - sprite.getGlobalBounds().width;
    }
    if (position.y + sprite.getGlobalBounds().height > window.getSize().y) {
        position.y = window.getSize().y - sprite.getGlobalBounds().height;
    }
    sprite.setPosition(position);

    // Disparo com clique do mouse
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootClock.getElapsedTime() >= shootCooldown) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        shoot(window.mapPixelToCoords(mousePosition), projectiles);
        shootClock.restart();
    }
}

sf::Vector2f Defender::getPosition() const {
    return sprite.getPosition();
}

sf::Sprite& Defender::getSprite() {
    return sprite;
}

int Defender::getHealth() const {
    return health;
}

void Defender::setHealth(int amount) {
    health += amount;
    if (health < 0) {
        health = 0;
    }
}

int Defender::getAmmo() const {
    return ammo;
}

void Defender::addAmmo(int amount) {
    ammo += amount;
    if (ammo > maxAmmo) {
        ammo = maxAmmo;
    }
}

void Defender::shoot(const sf::Vector2f& target, std::vector<Projectile>& projectiles) {
    if (ammo > 0) {
        float projectileSpeed = 300.0f; // Aumente este valor conforme necessário
        Projectile projectile(sprite.getPosition(), target, projectileTexture, projectileSpeed);
        projectiles.push_back(projectile);
        ammo--;
    }
}

void Defender::reload(int amount) {
    ammo += amount;
    if (ammo > maxAmmo) {
        ammo = maxAmmo;
    }
}

void Defender::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

bool Defender::isAlive() const {
    return health > 0;
}
