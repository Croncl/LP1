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

// Declaração da função restartGame
void restartGame();

// Classe principal do jogo
class Game {
public:
    Game(); // Construtor padrão
    Game(const std::string& scenarioFile, const std::string& defenderFile, sf::RenderWindow& window);

    void run(); // Executa o loop principal do jogo
    enum class GameState { Playing, Victory, Defeat }; // Estados do jogo
    GameState gameState;

    // Declaração da função getGameState
    GameState getGameState() const;
    std::vector<std::string> wrapText(const std::string& text, float maxWidth, const sf::Font& font, unsigned int characterSize);
    void restartGame() {
        ::restartGame(); // Chama a função global restartGame
    }

private:
    void processEvents(); // Processa eventos de entrada do usuário
    void update(sf::Time deltaTime); // Atualiza o estado do jogo
    void render(); // Renderiza os elementos do jogo na tela
    void handleCollisions(); // Lida com colisões entre objetos
    void spawnOutsider(); // Gera novos inimigos
    bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2); // Verifica colisão entre dois sprites
    bool loadTexture(sf::Texture& texture, const std::string& filename); // Carrega uma textura a partir de um arquivo
    void configureText(sf::Text& text, const sf::Font& font, unsigned int charSize, sf::Color fillColor, sf::Color outlineColor, float outlineThickness, float posX, float posY); // Configura um texto
    void checkEndGameConditions(); // Função para verificar condições de fim de jogo
    void checkGameOver(); // Função para verificar se o jogo acabou

    // Janela de renderização do SFML
    sf::RenderWindow& window;

    // Arquivos de cenário e defensor
    std::string scenarioFile;
    std::string defenderFile;
    std::vector<std::string> outsiderFiles;;


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
    sf::Texture manaDropTexture; // Textura do drop de munição

    // Fontes e textos
    sf::Font font; // Fonte para textos
    sf::Text healthText; // Texto para exibir a saúde
    sf::Text manaText; // Texto para exibir a munição
    sf::Text baseHealthText; // Texto para exibir a saúde da base
    sf::Text timerText; // Texto para exibir a saúde da base
    sf::Text endGameText, restartExitText; // Texto de fim de jogo

    // Relógios
    sf::Clock outsiderSpawnClock; // Relógio para controlar o spawn de inimigos
    sf::Clock clock; // Relógio geral do jogo
    sf::Clock waveClock; // Relógio para controlar duracao da wave
    sf::Clock gameOverClock; // Relógio para medir o tempo desde que o jogo entrou em estado de "game over"

    sf::RectangleShape fadeRectangle; // Retângulo preto para o efeito de esmaecimento

    // Variáveis de controle texto
    std::vector<std::string> endGameLines;
    sf::Clock typingClock;
    size_t currentCharIndex = 0;
    std::string fullEndGameText;

    // Parâmetros do jogo
    int currentOutsiderType = 0; // Tipo atual de inimigo
    int timeRemaining = 120;
    const float OUTSIDER_SPAWN_INTERVAL = 5.5f; // Intervalo de spawn de inimigos
    const int OUTSIDER_DAMAGE = 10; // Dano causado pelos inimigos
    const int BASE_DAMAGE = 5; // Dano causado à base
    const int DEFENDER_DAMAGE = 6; // Dano causado ao defensor
    bool isGameOver = false;

    // Objetos do jogo
    Defender defender; // Objeto defensor
    Base base; // Objeto base
    std::vector<Projectile> projectiles; // Vetor de projéteis do defensor
    std::vector<Projectile> outsiderProjectiles; // Vetor de projéteis dos inimigos
    std::vector<Outsider> outsiders; // Vetor de inimigos
};

#endif // GAME_HPP