#include <SFML/Graphics.hpp>
#include "Game.hpp"

// Função para mostrar o menu
void showMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text title("Never Back Home", font, 50);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    title.setPosition(window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f, window.getSize().y / 3.0f);

    sf::Text startOption("Iniciar Jogo", font, 30);
    startOption.setFillColor(sf::Color::White);
    startOption.setOutlineColor(sf::Color::Black);
    startOption.setOutlineThickness(2);
    startOption.setPosition(window.getSize().x / 2.0f - startOption.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f);

    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("assets/testemenu.png")) {
        // Handle error
        return;
    }

    sf::Sprite menuBackgroundSprite;
    menuBackgroundSprite.setTexture(menuBackgroundTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (startOption.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return;
                }
            }
        }

        window.clear();
        window.draw(menuBackgroundSprite);
        window.draw(title);
        window.draw(startOption);
        window.display();
    }
}

// Função para selecionar o cenário
std::string selectScenario(sf::RenderWindow& window, sf::Font& font) {
    sf::Text scenario1("1. Metal Bird", font, 30);
    scenario1.setFillColor(sf::Color::White);
    scenario1.setOutlineColor(sf::Color::Black);
    scenario1.setOutlineThickness(2);
    scenario1.setPosition(window.getSize().x / 2.0f - scenario1.getLocalBounds().width / 2.0f, window.getSize().y / 3.0f);

    sf::Text scenario2("2. Space/Time Machine", font, 30);
    scenario2.setFillColor(sf::Color::White);
    scenario2.setOutlineColor(sf::Color::Black);
    scenario2.setOutlineThickness(2);
    scenario2.setPosition(window.getSize().x / 2.0f - scenario2.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f);

    sf::Text scenario3("3. Interdimensional Portal", font, 30);
    scenario3.setFillColor(sf::Color::White);
    scenario3.setOutlineColor(sf::Color::Black);
    scenario3.setOutlineThickness(2);
    scenario3.setPosition(window.getSize().x / 2.0f - scenario3.getLocalBounds().width / 2.0f, window.getSize().y / 1.5f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (scenario1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return "assets/001cenario.png";
                } else if (scenario2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return "assets/002cenario.png";
                } else if (scenario3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return "assets/003cenario.png";
                }
            }
        }

        window.clear();
        window.draw(scenario1);
        window.draw(scenario2);
        window.draw(scenario3);
        window.display();
    }

    return "";
}

// Função para selecionar o personagem
std::string selectCharacter(sf::RenderWindow& window, sf::Font& font) {
    sf::Text character1("1. Vengeful Horned ", font, 30);
    character1.setFillColor(sf::Color::Red);
    character1.setOutlineColor(sf::Color::White);
    character1.setOutlineThickness(2);
    character1.setPosition(window.getSize().x / 2.0f - character1.getLocalBounds().width / 2.0f, window.getSize().y / 3.0f);

    sf::Text character2("2. Master of masters", font, 30);
    character2.setFillColor(sf::Color::Blue);
    character2.setOutlineColor(sf::Color::White);
    character2.setOutlineThickness(2);
    character2.setPosition(window.getSize().x / 2.0f - character2.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f);

    sf::Text character3("3. Eye Spectador", font, 30);
    character3.setFillColor(sf::Color::Black);
    character3.setOutlineColor(sf::Color::White);
    character3.setOutlineThickness(2);
    character3.setPosition(window.getSize().x / 2.0f - character3.getLocalBounds().width / 2.0f, window.getSize().y / 1.5f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (character1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return "assets/001defender.png";
                } else if (character2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return "assets/002defender.png";
                } else if (character3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return "assets/003defender.png";
                }
            }
        }

        window.clear();
        window.draw(character1);
        window.draw(character2);
        window.draw(character3);
        window.display();
    }

    return "";
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Never Back Home");
    sf::Font font;
    if (!font.loadFromFile("assets/ChronoType.ttf")) {
        return -1;
    }

    showMenu(window, font);

    std::string scenarioFile = selectScenario(window, font);
    std::string defenderFile = selectCharacter(window, font);

if (!scenarioFile.empty() && !defenderFile.empty()) {
    Game game(scenarioFile, defenderFile, window); // Passa a janela window
    game.startGame();
}

    return 0;
}