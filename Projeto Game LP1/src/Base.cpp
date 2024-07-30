#include "Base.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

// Construtor padrão
Base::Base() : health(100) {
    // Inicialização do sprite e textura padrão
    if (!texture.loadFromFile("assets/001base.png")) {
        throw std::runtime_error("Falha ao carregar textura padrão 'assets/001base.png'");
    }
    sprite.setTexture(texture);
    sprite.setPosition(400, 300); // Posição padrão (centralizada)
}

Base::Base(int cenario) : health(100) {
    initialize(cenario);
}

Base::Base(sf::Vector2f position, int health, int cenario) 
    : health(health) {
    sprite.setPosition(position);
    initialize(cenario);
}

void Base::initialize(int cenario) {
    std::string textureFile;
    int baseWidth, baseHeight;

    switch (cenario) {
        case 1:
            textureFile = "assets/001base.png";
            baseWidth = 160;
            baseHeight = 120;
            health = 300; // Valor de saúde padrão para cenário 1
            break;
        case 2:
            textureFile = "assets/002base.png";
            baseWidth = 160;
            baseHeight = 120;
            health = 200; // Valor de saúde padrão para cenário 2
            break;
        case 3:
            textureFile = "assets/003base.png";
            baseWidth = 120;
            baseHeight = 120;
            health = 200; // Valor de saúde padrão para cenário 3
            break;
        default:
            throw std::invalid_argument("Cenário inválido");
    }

    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Falha ao carregar textura '" + textureFile + "'");
    }
    sprite.setTexture(texture);

    // Calcula a posição central para o sprite
    float x = (800 - baseWidth) / 2.0f; // 800 é a largura da tela
    float y = (600 - baseHeight) / 2.0f; // 600 é a altura da tela
    sprite.setPosition(x, y);
}

// Implementação das outras funções da classe Base

sf::Vector2f Base::getPosition() const {
    return sprite.getPosition();
}

const sf::Sprite& Base::getSprite() const {
    return sprite;
}

int Base::getHealth() const {
    return health;
}

void Base::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}