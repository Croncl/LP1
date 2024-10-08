#include "Drop.hpp"
#include <random>

// Construtor da classe Drop
Drop::Drop(DropType type, const sf::Vector2f& position, const sf::Texture& texture)
    : type(type), sprite(), dropTexture(texture), valid(true), lifetime(sf::Time::Zero) {
    initialize(position, texture);
}

void Drop::initialize(const sf::Vector2f& position, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

// Método que retorna o tipo do drop
DropType Drop::getType() const {
    return type;
}

// Método que retorna uma referência constante ao sprite do drop
const sf::Sprite& Drop::getSprite() const {
    return sprite;
}

// Método que verifica se o drop está marcado para remoção
bool Drop::isMarkedForRemoval() const {
    return !valid; 
}

void Drop::update(sf::Time deltaTime) {
    // Incrementar o tempo de vida do drop
    lifetime += deltaTime;

    // Verificar se o tempo de vida excedeu 5 segundos
    if (lifetime.asSeconds() > 5.0f) {
        valid = false; // Marcar o drop para remoção
    }
}

// Método que desenha o drop na janela
void Drop::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

// Método que retorna os limites do sprite do drop
sf::FloatRect Drop::getBounds() const {
    return sprite.getGlobalBounds();
}

DropType Drop::getRandomDropType() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 1);
    return dist(gen) == 0 ? DropType::Health : DropType::Mana;
}