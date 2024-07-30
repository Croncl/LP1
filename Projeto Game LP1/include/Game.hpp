#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Defender.hpp" 
#include "Base.hpp"     
#include "Projectile.hpp" 
#include "Outsider.hpp" 
#include "Drop.hpp"

// Classe principal do jogo
class Game {
public:
    Game(); // Construtor padrão
    Game(const std::string& scenarioFile, const std::string& defenderFile, sf::RenderWindow& window);

    void startGame(); // Inicia o jogo
    void run(); // Executa o loop principal do jogo

private:
    void processEvents(); // Processa eventos de entrada do usuário
    void update(sf::Time deltaTime); // Atualiza o estado do jogo
    void render(); // Renderiza os elementos do jogo na tela
    void handleCollisions(); // Lida com colisões entre objetos
    void spawnOutsider(); // Gera novos inimigos
    bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2); // Verifica colisão entre dois sprites
    bool loadTexture(sf::Texture& texture, const std::string& filename); // Carrega uma textura a partir de um arquivo

    // Controle das ondas de inimigos
    int waveNumber; // Número da onda atual
    sf::Time waveDuration; // Duração de cada onda
    sf::Time lastWaveTime; // Tempo da última onda
    sf::Text waveDurationText; // Texto para exibir a duração da onda
    sf::Text nextWaveText; // Texto para exibir o tempo para a próxima onda

    // Janela de renderização do SFML
    sf::RenderWindow& window; 

    // Arquivos de cenário e defensor
    std::string scenarioFile; 
    std::string defenderFile; 

    // Texturas e sprites
    sf::Texture backgroundTexture; // Textura do fundo
    sf::Sprite background; // Sprite do fundo
    sf::Texture baseTexture; // Textura da base
    sf::Sprite baseSprite; // Sprite da base
    sf::Texture defenderTexture; // Textura do defensor
    sf::Sprite defenderSprite; // Sprite do defensor
    std::vector<sf::Texture> outsiderTextures; // Vetor para armazenar as texturas dos inimigos

    // Drops (itens que caem)
    std::vector<Drop> drops; 
    sf::Texture healthDropTexture; // Textura do drop de saúde
    sf::Texture ammoDropTexture; // Textura do drop de munição

    // Fontes e textos
    sf::Font font; // Fonte para textos
    sf::Text healthText; // Texto para exibir a saúde
    sf::Text ammoText; // Texto para exibir a munição
    sf::Text baseHealthText; // Texto para exibir a saúde da base

    // Relógios
    sf::Clock outsiderSpawnClock; // Relógio para controlar o spawn de inimigos
    sf::Clock clock; // Relógio geral do jogo

    // Parâmetros do jogo
    int currentOutsiderType = 0; // Tipo atual de inimigo
    const float OUTSIDER_SPAWN_INTERVAL = 5.0f; // Intervalo de spawn de inimigos
    const int OUTSIDER_DAMAGE = 10; // Dano causado pelos inimigos
    const int BASE_DAMAGE = 10; // Dano causado à base
    const int DEFENDER_DAMAGE = 5; // Dano causado ao defensor

    // Objetos do jogo
    Defender defender; // Objeto defensor
    Base base; // Objeto base
    std::vector<Projectile> projectiles; // Vetor de projéteis do defensor
    std::vector<Projectile> outsiderProjectiles; // Vetor de projéteis dos inimigos
    std::vector<Outsider> outsiders; // Vetor de inimigos
};

#endif // GAME_HPP