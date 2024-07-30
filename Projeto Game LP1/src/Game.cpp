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

Game::Game() : window(*(new sf::RenderWindow(sf::VideoMode(800, 600), "Game"))) {
    // Inicialização do jogo
}

Game::Game(const std::string& scenarioFile, const std::string& defenderFile, sf::RenderWindow& window)
    : window(window), defenderFile(defenderFile), defender(sf::Vector2f(400, 300), defenderFile, "assets/004projectil.png") { // Inicializa o Defender aqui
    
    // Carrega a textura de fundo
    loadTexture(backgroundTexture, scenarioFile);
    background.setTexture(backgroundTexture);

    // Carrega a fonte para os textos de saúde e munição
    if (!font.loadFromFile("assets/ChronoType.ttf")) {
        throw std::runtime_error("Falha ao carregar a fonte assets/ChronoType.ttf");
    }

    // Configura o texto de saúde do defensor
    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setFillColor(sf::Color::White);
    healthText.setOutlineColor(sf::Color::Black);
    healthText.setOutlineThickness(2);
    healthText.setPosition(700, 1);

    // Configura o texto de munição do defensor
    ammoText.setFont(font);
    ammoText.setCharacterSize(24);
    ammoText.setFillColor(sf::Color::White);
    ammoText.setOutlineColor(sf::Color::Black);
    ammoText.setOutlineThickness(2);
    ammoText.setPosition(700, 20);

    // Configura o texto de saúde da base
    baseHealthText.setFont(font);
    baseHealthText.setCharacterSize(24);
    baseHealthText.setFillColor(sf::Color::Red);
    baseHealthText.setOutlineColor(sf::Color::Black);
    baseHealthText.setOutlineThickness(2);
    baseHealthText.setPosition(700, 41);

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
        "assets/006outsider.png"
    };

    for (const auto& file : outsiderFiles) {
        sf::Texture texture;
        loadTexture(texture, file);
        outsiderTextures.push_back(texture);

    // Carrega as texturas dos "Drops"
    loadTexture(healthDropTexture, "assets/healthdrop.png");
    loadTexture(ammoDropTexture, "assets/ammodrop.png");    
    }
}


void Game::startGame() {
    // Inicializa o jogo com o cenário e personagem selecionados
    run();
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
    }
}

void Game::update(sf::Time deltaTime) {
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

    // Remover projéteis fora dos limites ou marcados para remoção
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile& projectile) {
            return !projectile.isInBounds() || projectile.isMarkedForRemoval();
        }), projectiles.end());

    outsiderProjectiles.erase(std::remove_if(outsiderProjectiles.begin(), outsiderProjectiles.end(),
        [](const Projectile& outsiderProjectile) {
            return !outsiderProjectile.isInBounds() || outsiderProjectile.isMarkedForRemoval();
        }), outsiderProjectiles.end());


    // Atualizar drops
    for (auto& drop : drops) {
        drop.update(deltaTime);
    }

    // Remover drops marcados para remoção
    drops.erase(std::remove_if(drops.begin(), drops.end(),
        [](const Drop& drop) {
            return drop.isMarkedForRemoval();
        }), drops.end());


    if (outsiderSpawnClock.getElapsedTime().asSeconds() > OUTSIDER_SPAWN_INTERVAL) {
        spawnOutsider();
        outsiderSpawnClock.restart(); // Reinicia o relógio após spawnar um outsider
    }

    handleCollisions();

    outsiders.erase(std::remove_if(outsiders.begin(), outsiders.end(),
        [](const Outsider& outsider) {
            return outsider.isDead();
        }), outsiders.end());

    healthText.setString("Health: " + std::to_string(defender.getHealth()));
    ammoText.setString("Ammo: " + std::to_string(defender.getAmmo()));
    baseHealthText.setString("Base: " + std::to_string(base.getHealth()));
}

void Game::render() {
    window.clear();
    window.draw(background);
    window.draw(baseSprite);
    window.draw(defender.getSprite());

    // Desenhar outsiders
    for (const auto& outsider : outsiders) {
        outsider.draw(window);
    }

    // Desenhar projéteis do defensor
    for (const auto& projectile : projectiles) {
        window.draw(projectile.getSprite());
    }
    // Desenhar projéteis dos outsiders
    for (const auto& outsiderProjectile : outsiderProjectiles) {
        window.draw(outsiderProjectile.getSprite());
    }
    // Desenhar drops
    for (const auto& drop : drops) {
        drop.draw(window); // Usar o método draw da classe Drop
    }

    window.draw(healthText);
    window.draw(ammoText);
    window.draw(baseHealthText);

    window.display();
}

void Game::spawnOutsider() {
    int numOutsidersToSpawn = rand() % 6 + 1; // Spawna entre 1 e 6 outsiders
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

                // Gerar um drop com 10% de chance para Health
                DropType dropType = Drop::getRandomDropType();
                const sf::Texture& dropTexture = (dropType == DropType::Health) ? healthDropTexture : ammoDropTexture;
                drops.emplace_back(dropType, outsider.getSprite().getPosition(), dropTexture);
            }
        }
    }

    //colisao outsider e base
    for (auto& outsider : outsiders) {
        if (checkCollision(outsider.getSprite(), baseSprite)) {
            base.takeDamage(BASE_DAMAGE);
            outsider.takeDamage(BASE_DAMAGE / 2);
            outsider.markForRemoval(); // Marca o outsider para remoção
        }
    }
    //colisao outsiderprojetil e base
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

                // Gerar um drop de munição
                drops.emplace_back(DropType::Ammo, outsiderProjectile.getSprite().getPosition(), ammoDropTexture);
            }
        }
    }


    // Verificar colisão do defensor com drops
    for (auto it = drops.begin(); it != drops.end();) {
        if (checkCollision(defender.getSprite(), it->getSprite())) {
            if (it->getType() == DropType::Health) {
                defender.setHealth(10); // Restaurar 10 de saúde
            } else if (it->getType() == DropType::Ammo) {
                defender.addAmmo(3); // Adicionar 3 de munição
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
}