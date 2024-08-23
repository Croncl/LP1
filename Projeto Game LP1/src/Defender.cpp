#include "Defender.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stdexcept>
#include <cmath>

// Construtor da classe Defender
Defender::Defender(sf::Vector2f position, const std::string& textureFile, const std::string& projectileTextureFile)
    : textureFile(textureFile), health(100), mana(21), maxMana(100), speed(200.0f), shootCooldown(sf::seconds(0.2f)) { // Inicializa com 20 projéteis e cooldown de 0.2s
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Falha ao carregar " + textureFile);
    }
    if (!projectileTexture.loadFromFile(projectileTextureFile)) {
        throw std::runtime_error("Falha ao carregar " + projectileTextureFile);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

// Método update da classe Defender
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
        sf::Vector2f target = window.mapPixelToCoords(mousePosition);

        // Direção original
        shoot(target, projectiles);

        // Verificar se o arquivo de textura do projétil é "assets/003defender.png"
        if (textureFile == "assets/003defender.png") {
            // Calcular a direção original
            sf::Vector2f direction = target - sprite.getPosition();
            float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= magnitude;

            // Calcular direções com +10 e -10 graus
            float angle = std::atan2(direction.y, direction.x);
            float anglePlus10 = angle + 10 * (M_PI / 180.0f); // 10 graus em radianos
            float angleMinus10 = angle - 10 * (M_PI / 180.0f); // -10 graus em radianos

            sf::Vector2f directionPlus10(std::cos(anglePlus10), std::sin(anglePlus10));
            sf::Vector2f directionMinus10(std::cos(angleMinus10), std::sin(angleMinus10));

            // Disparar projéteis nas novas direções
            shoot(sprite.getPosition() + directionPlus10 * magnitude, projectiles);
            shoot(sprite.getPosition() + directionMinus10 * magnitude, projectiles);
            // Incrementar mana em 1
            addMana(1);
        }

        shootClock.restart();
    }
}

// Outros métodos da classe Defender
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
    if (health > maxHealth) {
        health = maxHealth;
    }
    if (health < 0) {
        health = 0;
    }
}

int Defender::getMana() const {
    return mana;
}

void Defender::addMana(int amount) {
    mana += amount;
    if (mana > maxMana) {
        mana = maxMana;
    }
}

void Defender::shoot(const sf::Vector2f& target, std::vector<Projectile>& projectiles) {
    if (mana > 0) {
        float projectileSpeed = 300.0f; // Aumente este valor conforme necessário
        Projectile projectile(sprite.getPosition(), target, projectileTexture, projectileSpeed);
        projectiles.push_back(projectile);
        mana--;
    }
}

void Defender::reload(int amount) {
    mana += amount;
    if (mana > maxMana) {
        mana = maxMana;
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