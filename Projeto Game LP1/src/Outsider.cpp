#include "Outsider.hpp"
#include "Projectile.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <stdexcept>

// Construtor da classe Outsider
Outsider::Outsider(const sf::Texture& texture) : speed(100.0f), health(10), shootInterval(sf::seconds(2.0f)), markedForRemoval(false) {
    sprite.setTexture(texture);
    if (!projectileTexture.loadFromFile("assets/001projectil.png")) {
        throw std::runtime_error("Failed to load projectile texture");
    }
}

// Define uma posição aleatória na borda da janela
void Outsider::setRandomPositionOnEdge(const sf::Vector2u& windowSize) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distSide(0, 3);
    static std::uniform_int_distribution<> distX(0, windowSize.x);
    static std::uniform_int_distribution<> distY(0, windowSize.y);

    int side = distSide(gen);
    switch (side) {
        case 0: // Topo
            sprite.setPosition(distX(gen) % (windowSize.x - static_cast<int>(sprite.getGlobalBounds().width)), 0);
            break;
        case 1: // Fundo
            sprite.setPosition(distX(gen) % (windowSize.x - static_cast<int>(sprite.getGlobalBounds().width)), windowSize.y - sprite.getGlobalBounds().height);
            break;
        case 2: // Esquerda
            sprite.setPosition(0, distY(gen) % (windowSize.y - static_cast<int>(sprite.getGlobalBounds().height)));
            break;
        case 3: // Direita
            sprite.setPosition(windowSize.x - sprite.getGlobalBounds().width, distY(gen) % (windowSize.y - static_cast<int>(sprite.getGlobalBounds().height)));
            break;
    }
}

// Move o Outsider em direção a um alvo
void Outsider::moveTowards(const sf::Vector2f& target, float deltaTime) {
    sf::Vector2f direction = target - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
        sprite.move(direction * speed * deltaTime);
    }
}

// Desenha o Outsider na janela
void Outsider::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

// Retorna os limites do sprite do Outsider
sf::FloatRect Outsider::getBounds() const {
    return sprite.getGlobalBounds();
}

// Retorna o sprite do Outsider
const sf::Sprite& Outsider::getSprite() const {
    return sprite;
}

// Aplica dano ao Outsider
void Outsider::takeDamage(int damage) {
    health -= damage;
}

// Verifica se o Outsider está morto
bool Outsider::isDead() const {
    return health <= 0;
}

// Verifica se o Outsider pode atirar
bool Outsider::canShoot() const {
    return shootClock.getElapsedTime() >= shootInterval;
}

// Reseta o relógio de tiro
void Outsider::resetShootClock() {
    shootClock.restart();
}

// Retorna o intervalo de tiro
sf::Time Outsider::getShootInterval() const {
    return shootInterval;
}

// Faz o Outsider atirar
void Outsider::shoot(const sf::Vector2f& target, std::vector<Projectile>& projectiles) {
    if (canShoot()) {
        Projectile projectile(sprite.getPosition(), target, projectileTexture, 100.0f);
        projectiles.push_back(projectile);
        resetShootClock();
    }
}

// Marca o Outsider para remoção
void Outsider::markForRemoval() {
    markedForRemoval = true;
}

// Verifica se o Outsider está marcado para remoção
bool Outsider::isMarkedForRemoval() const {
    return markedForRemoval;
}