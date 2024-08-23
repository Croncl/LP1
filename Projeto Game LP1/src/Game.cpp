#include "Game.hpp"
#include "Outsider.hpp"
#include "Projectile.hpp"
#include "Drop.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <sstream> 
#include <random>


// Definição da função checkCollision como um método da classe Game
bool Game::checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

bool Game::loadTexture(sf::Texture& texture, const std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Falha ao carregar " + filename);
    }
    return true;
}

void Game::configureText(sf::Text& text, const sf::Font& font, unsigned int charSize, sf::Color fillColor, sf::Color outlineColor, float outlineThickness, float posX, float posY) {
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setFillColor(fillColor);
    text.setOutlineColor(outlineColor);
    text.setOutlineThickness(outlineThickness);
    text.setPosition(posX, posY);
}

std::vector<std::string> Game::wrapText(const std::string& text, float maxWidth, const sf::Font& font, unsigned int characterSize) {
    std::vector<std::string> lines;
    std::string line;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        std::string testLine = line + word + " ";
        sf::Text testText(testLine, font, characterSize);
        if (testText.getLocalBounds().width > maxWidth) {
            lines.push_back(line);
            line = word + " ";
        } else {
            line = testLine;
        }
    }
    lines.push_back(line);
    return lines;
}


// Função para escolher a textura do projétil com base na textura do defender
std::string chooseProjectileTexture(const std::string& defenderFile) {
    if (defenderFile == "assets/001defender.png") {
        return "assets/005projectile.png";
    } else if (defenderFile == "assets/002defender.png") {
        return "assets/006projectile.png";
    } else if (defenderFile == "assets/004defender.png") {
        return "assets/011projectile.png";
    } else if (defenderFile == "assets/003defender.png") {
        return "assets/008projectile.png";
    } else {
        throw std::runtime_error("Unknown defender texture: " + defenderFile);
    }
}

Game::Game() : window(*(new sf::RenderWindow(sf::VideoMode(800, 600), "Game"))) {
    // Inicialização do jogo
}

// Construtor da classe Game
Game::Game(const std::string& scenarioFile, const std::string& defenderFile, sf::RenderWindow& window)
    : window(window), defenderFile(defenderFile), defender(sf::Vector2f(400, 300), defenderFile, chooseProjectileTexture(defenderFile)) { // Inicializa o Defender aqui
    
    
    // Carrega a textura de fundo
    loadTexture(backgroundTexture, scenarioFile);
    background.setTexture(backgroundTexture);

    // Carrega a fonte para os textos de saúde e mana
    if (!font.loadFromFile("assets/ChronoType.ttf")) {
        throw std::runtime_error("Falha ao carregar a fonte assets/ChronoType.ttf");
    }

    // Configura o texto de saúde do defensor
    configureText(healthText, font, 24, sf::Color::White, sf::Color::Black, 2, 700, 1);

    // Configura o texto de mana do defensor
    configureText(manaText, font, 24, sf::Color::White, sf::Color::Black, 2, 700, 20);

    // Configura o texto de saúde da base
    configureText(baseHealthText, font, 20, sf::Color::Red, sf::Color::Black, 2, 340, 1);

    // Configura o texto do timer
    configureText(timerText, font, 20, sf::Color::White, sf::Color::Black, 2, 340, 580);

    // Configura o texto de fim de jogo
    configureText(endGameText, font, 30, sf::Color::Yellow, sf::Color::Black, 2, 400, 300);

    // Inicialização da textura e sprite da base
    std::string baseFile;
    if (scenarioFile == "assets/001cenario.png") {
        baseFile = "assets/001base.png";
    } else if (scenarioFile == "assets/002cenario.png") {
        baseFile = "assets/002base.png";
    } else if (scenarioFile == "assets/003cenario.png") {
        baseFile = "assets/003base.png";
    } else {
        throw std::runtime_error("Falha ao carregar o cenário");
    }

    loadTexture(baseTexture, baseFile);
    baseSprite.setTexture(baseTexture);

    // Centraliza a base na tela
    sf::Vector2u windowSize = window.getSize();
    baseSprite.setOrigin(baseSprite.getGlobalBounds().width / 2, baseSprite.getGlobalBounds().height / 2);
    baseSprite.setPosition(windowSize.x / 2, windowSize.y / 2);

    // Carrega a textura do defensor
    loadTexture(defenderTexture, defenderFile);

    // Configura o sprite do defensor
    defenderSprite.setTexture(defenderTexture);
    defenderSprite.setPosition((windowSize.x - defenderSprite.getGlobalBounds().width) / 2,
                               windowSize.y - defenderSprite.getGlobalBounds().height - 50); // Ajuste a posição conforme necessário

    // Carrega as texturas dos "Outsiders"
    std::vector<std::string> outsiderFiles = {
        "assets/001outsider.png",
        "assets/002outsider.png",
        "assets/003outsider.png",
        "assets/004outsider.png",
        "assets/005outsider.png",
        "assets/006outsider.png",
        "assets/007outsider.png"
    };

    for (const auto& file : outsiderFiles) {
        sf::Texture texture;
        loadTexture(texture, file);
        outsiderTextures.push_back(texture);
    }

    // Carrega as texturas dos "Drops"
    loadTexture(healthDropTexture, "assets/healthdrop.png");
    loadTexture(manaDropTexture, "assets/manadrop.png");

    // Inicialize o retângulo preto para cobrir toda a janela
    fadeRectangle.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    fadeRectangle.setFillColor(sf::Color(0, 0, 0, 0)); // Inicialmente transparente
}

Game::GameState Game::getGameState() const {
    if (defender.getHealth() <= 0 || base.getHealth() >= 100) {
        return GameState::Defeat;
    } else if (timeRemaining <= 0) {
        return GameState::Victory;
    }
    return GameState::Playing;
}

void Game::checkGameOver() {
    // Mapeia as condições de fim de jogo para as respectivas mensagens de texto
    std::map<std::string, std::string> endGameConditions = {
        {"defender", "When victory seemed within reach, reality unveiled itself once more. The journey continues, where the end is but a beginning, and the hope of returning home fades, like sand slipping through fingers."},
        {"base", "Time, relentless, did not wait for them. Even when all seemed lost, the young still have a long road ahead. Perhaps one day, in some distant place, they will uncover the truth... or remain forever lost in the mist of the unknown."},
        {"time", "And so, when the heroes believed they had found the way home, they realized the shadows were always one step ahead. Fate, whimsical and cruel, has prepared for them a new cycle of challenges... in the eternal quest to return."}
    };

    // Inicializa uma string para armazenar a condição que levou ao fim do jogo
    std::string condition = "";
    
    // Verifica se o defensor perdeu toda a vida
    if (defender.getHealth() <= 0) {
        condition = "defender";
    }
    // Verifica se a base atingiu 100% de vida
    else if (base.getHealth() >= 100) {
        condition = "base";
    }
    // Verifica se o tempo restante acabou
    else if (timeRemaining <= 0) {
        condition = "time";
    }
    
    // Se alguma condição de fim de jogo foi atendida
    if (!condition.empty()) {
        isGameOver = true;  // Marca o jogo como terminado
        gameOverClock.restart(); // Reinicia o relógio do fim do jogo
        fullEndGameText = endGameConditions[condition]; // Define o texto de fim de jogo correspondente
        currentCharIndex = 0; // Reinicia o índice de caracteres para a animação de digitação
        typingClock.restart(); // Reinicia o relógio da animação de digitação

        // Configurar o texto de reinício/saídad
        configureText(restartExitText, *endGameText.getFont(), 20, sf::Color::White, sf::Color::Black, 1.0f, window.getSize().x - 300, window.getSize().y - 50);
        restartExitText.setString("Play again? press enter then Esc\nEsc: Exit Game");
    }
}


void Game::run() {
    while (window.isOpen()) {
        processEvents(); // Processa eventos
        sf::Time deltaTime = clock.restart(); // Calcula o tempo decorrido
        update(deltaTime); // Atualiza o estado do jogo
        render(); // Renderiza o jogo
    }
}


void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (isGameOver) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    restartGame();
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
    }
}

void Game::update(sf::Time deltaTime) {
    if (isGameOver) {
        // Atualiza a opacidade do retângulo preto
        float elapsedTime = gameOverClock.getElapsedTime().asSeconds();
        if (elapsedTime < 5.0f) {
            int alpha = static_cast<int>((elapsedTime / 5.0f) * 255);
            fadeRectangle.setFillColor(sf::Color(0, 0, 0, alpha));
        } else {
            fadeRectangle.setFillColor(sf::Color(0, 0, 0, 255)); // Totalmente preto após 5 segundos
        }
        // Atualiza o texto de fim de jogo
        if (typingClock.getElapsedTime().asSeconds() > 0.05f && currentCharIndex < fullEndGameText.size()) {
            currentCharIndex++;
            typingClock.restart();
        }
        return;
    }

    defender.update(deltaTime, window, projectiles); // Atualiza o defensor

    for (auto& outsider : outsiders) {
        outsider.moveTowards(base.getPosition(), deltaTime.asSeconds());
        if (outsider.canShoot()) {
            outsider.shoot(defender.getSprite().getPosition(), outsiderProjectiles);
        }
    }

    for (auto& projectile : projectiles) {
        projectile.update(deltaTime);
    }

    for (auto& outsiderProjectile : outsiderProjectiles) {
        outsiderProjectile.update(deltaTime);
    }

    // Atualizar drops
    for (auto& drop : drops) {
        drop.update(deltaTime);
    }

    // Decrementa o tempo restante a cada segundo
    if (waveClock.getElapsedTime().asSeconds() >= 1) {
        if (timeRemaining > 0) {
            timeRemaining--;
        }
        waveClock.restart(); // Reinicia o relógio após decrementar o tempo
    }

    // Chama spawnOutsider a cada 5 segundos enquanto timeRemaining for maior que 0
    if (timeRemaining > 0 && outsiderSpawnClock.getElapsedTime().asSeconds() >= OUTSIDER_SPAWN_INTERVAL) {
        spawnOutsider();
        outsiderSpawnClock.restart(); // Reinicia o relógio após spawnar um outsider
    }

    handleCollisions();

    // Remover projéteis fora dos limites ou marcados para remoção
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& projectile) {
            return !projectile.isInBounds() || projectile.isMarkedForRemoval();
        }), projectiles.end());

    outsiderProjectiles.erase(std::remove_if(outsiderProjectiles.begin(), outsiderProjectiles.end(),
        [](const Projectile& outsiderProjectile) {
            return !outsiderProjectile.isInBounds() || outsiderProjectile.isMarkedForRemoval();
        }), outsiderProjectiles.end());

    // Remover drops marcados para remoção
    drops.erase(std::remove_if(drops.begin(), drops.end(), [](const Drop& drop) {
        return drop.isMarkedForRemoval();
    }), drops.end());

    outsiders.erase(std::remove_if(outsiders.begin(), outsiders.end(),
        [](const Outsider& outsider) {
            return outsider.isDead();
        }), outsiders.end());

    healthText.setString("Health: " + std::to_string(defender.getHealth()));
    manaText.setString("Mana: " + std::to_string(defender.getMana()));
    baseHealthText.setString("Progress: " + std::to_string(base.getHealth()) + "%");
    timerText.setString("Time: " + std::to_string(timeRemaining));

    // Verifique se o jogo acabou
    checkGameOver();
}

void Game::render() {
    
    window.clear();

    // Desenhar todos os elementos do jogo
    window.draw(background);
    window.draw(baseSprite);
    window.draw(defender.getSprite());

    for (const auto& outsider : outsiders) {
        outsider.draw(window);
    }

    for (const auto& projectile : projectiles) {
        window.draw(projectile.getSprite());
    }

    for (const auto& outsiderProjectile : outsiderProjectiles) {
        window.draw(outsiderProjectile.getSprite());
    }

    for (const auto& drop : drops) {
        drop.draw(window);
    }

    window.draw(healthText);
    window.draw(manaText);
    window.draw(baseHealthText);
    window.draw(timerText);

    // Desenhar o retângulo preto com opacidade variável por último
    if (isGameOver) {
        window.draw(fadeRectangle);

        // Desenhar o texto de fim de jogo
        std::string displayedText = fullEndGameText.substr(0, currentCharIndex);
        endGameLines = wrapText(displayedText, 600, *endGameText.getFont(), endGameText.getCharacterSize());

        float yOffset = (window.getSize().y - endGameLines.size() * endGameText.getCharacterSize()) / 2;
        for (const auto& line : endGameLines) {
            endGameText.setString(line);
            sf::FloatRect textRect = endGameText.getLocalBounds();
            endGameText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            endGameText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, yOffset));
            window.draw(endGameText);
            yOffset += endGameText.getCharacterSize();
        }
        // Desenhar o texto de reinício/saída
        window.draw(restartExitText);
    }
    window.display();
}


void Game::spawnOutsider() {
    int numOutsidersToSpawn = rand() % 6 + 2; // Spawna entre 1 e 6 outsiders
    for (int i = 0; i < numOutsidersToSpawn; ++i) {
        Outsider outsider(outsiderTextures[currentOutsiderType]);
        outsider.setRandomPositionOnEdge(window.getSize());
        outsiders.push_back(outsider);

        // Avança para o próximo tipo de outsider
        currentOutsiderType = (currentOutsiderType + 1) % outsiderTextures.size();
    }
}

void Game::handleCollisions() {
    // Colisão entre projétil e outsider
    for (auto& outsider : outsiders) {
        for (auto& projectile : projectiles) {
            if (checkCollision(projectile.getSprite(), outsider.getSprite())) {
                outsider.takeDamage(OUTSIDER_DAMAGE);
                projectile.markForRemoval();

                // Gerar um drop com 50% de chance
                if (rand() % 2 == 0) { // rand() % 2 retorna 0 ou 1, então há 50% de chance
                    DropType dropType = Drop::getRandomDropType();
                    const sf::Texture& dropTexture = (dropType == DropType::Health) ? healthDropTexture : manaDropTexture;
                    drops.emplace_back(dropType, outsider.getSprite().getPosition(), dropTexture);
                }
            }
        }
    }

    // Colisão entre outsider e base
    for (auto& outsider : outsiders) {
        if (checkCollision(outsider.getSprite(), baseSprite)) {
            base.takeDamage(BASE_DAMAGE);
            outsider.takeDamage(BASE_DAMAGE / 2);
            outsider.markForRemoval(); // Marca o outsider para remoção
        }
    }

    // Colisão entre outsider e defensor
    for (auto& outsider : outsiders) {
        if (checkCollision(outsider.getSprite(), defender.getSprite())) {
            defender.takeDamage(OUTSIDER_DAMAGE); // Ajuste o valor do dano conforme necessário
            outsider.takeDamage(DEFENDER_DAMAGE); // Ajuste o valor do dano conforme necessário
            outsider.markForRemoval(); // Marca o outsider para remoção
        }
    }

    // Colisão entre projéteis dos outsiders e defensor
    for (auto& outsiderProjectile : outsiderProjectiles) {
        if (checkCollision(outsiderProjectile.getSprite(), defender.getSprite())) {
            defender.takeDamage(DEFENDER_DAMAGE);
            outsiderProjectile.markForRemoval();
        }
    }

    // Colisão entre projéteis do defensor e projéteis dos outsiders
    for (auto& projectile : projectiles) {
        for (auto& outsiderProjectile : outsiderProjectiles) {
            if (checkCollision(projectile.getSprite(), outsiderProjectile.getSprite())) {
                outsiderProjectile.markForRemoval();

                // Gerar um drop com 50% de chance
                if (rand() % 2 == 0) { // rand() % 2 retorna 0 ou 1, então há 50% de chance
                    drops.emplace_back(DropType::Mana, outsiderProjectile.getSprite().getPosition(), manaDropTexture);
                }
            }
        }
    }

    // Colisão entre projéteis dos outsiders
    for (auto it1 = outsiderProjectiles.begin(); it1 != outsiderProjectiles.end(); ++it1) {
        for (auto it2 = it1 + 1; it2 != outsiderProjectiles.end(); ++it2) {
            if (checkCollision(it1->getSprite(), it2->getSprite())) {
                it1->markForRemoval();
                it2->markForRemoval();

                // Gerar um drop com 33% de chance
                if (rand() % 3 == 0) {
                    drops.emplace_back(DropType::Mana, it1->getSprite().getPosition(), manaDropTexture);
                }
            }
        }
    }

    // Verificar colisão do defensor com drops
    for (auto it = drops.begin(); it != drops.end();) {
        if (checkCollision(defender.getSprite(), it->getSprite())) {
            if (it->getType() == DropType::Health) {
                defender.setHealth(10); // Restaurar 10 de saúde
            } else if (it->getType() == DropType::Mana) {
                defender.addMana(3); // Adicionar 4 de mana
            }
            it = drops.erase(it); // Remover o drop coletado
        } else {
            ++it;
        }
    }

    // Remove outsiders marcados para remoção
    outsiders.erase(std::remove_if(outsiders.begin(), outsiders.end(),
        [](const Outsider& outsider) {
            return outsider.isMarkedForRemoval();
        }), outsiders.end());

    // Remove projéteis marcados para remoção
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& projectile) {
            return projectile.isMarkedForRemoval();
        }), projectiles.end());

    // Remove projéteis dos outsiders marcados para remoção
    outsiderProjectiles.erase(std::remove_if(outsiderProjectiles.begin(), outsiderProjectiles.end(),
        [](const Projectile& projectile) {
            return projectile.isMarkedForRemoval();
        }), outsiderProjectiles.end());

    // Remove drops marcados para remoção
    drops.erase(std::remove_if(drops.begin(), drops.end(),
        [](const Drop& drop) {
            return drop.isMarkedForRemoval();
        }), drops.end());
}