#include "Menu.hpp"

void configureText(sf::Text& text, const sf::Font& font, unsigned int size, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness) {
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(fillColor);
    text.setOutlineColor(outlineColor);
    text.setOutlineThickness(outlineThickness);
}

bool isMouseOverText(const sf::RenderWindow& window, const sf::Text& text) {
    return text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

void showMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text title;
    configureText(title, font, 50, sf::Color::White, sf::Color::Black, 2);
    title.setString("Never Back Home");
    title.setPosition(window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f, window.getSize().y / 3.0f);

    sf::Text startOption;
    configureText(startOption, font, 30, sf::Color::White, sf::Color::Black, 2);
    startOption.setString("Iniciar Jogo");
    startOption.setPosition(window.getSize().x / 2.0f - startOption.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f);

    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("assets/000telainicial.png")) {
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
                if (isMouseOverText(window, startOption)) {
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

std::string selectScenario(sf::RenderWindow& window, sf::Font& font) {
    sf::Text instruction;
    configureText(instruction, font, 30, sf::Color::Yellow, sf::Color::Black, 2);
    instruction.setString("Choose your adventure today:");
    instruction.setPosition(window.getSize().x / 2.0f - instruction.getLocalBounds().width / 2.0f, window.getSize().y / 6.0f);

    sf::Text scenario1, scenario2, scenario3;
    configureText(scenario1, font, 30, sf::Color::White, sf::Color::Black, 2);
    scenario1.setString("1. Metal Bird");
    scenario1.setPosition(window.getSize().x / 2.0f - scenario1.getLocalBounds().width / 2.0f, window.getSize().y / 3.0f);

    configureText(scenario2, font, 30, sf::Color::White, sf::Color::Black, 2);
    scenario2.setString("2. Space/Time Machine");
    scenario2.setPosition(window.getSize().x / 2.0f - scenario2.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f);

    configureText(scenario3, font, 30, sf::Color::White, sf::Color::Black, 2);
    scenario3.setString("3. Interdimensional Portal");
    scenario3.setPosition(window.getSize().x / 2.0f - scenario3.getLocalBounds().width / 2.0f, window.getSize().y / 1.5f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            scenario1.setFillColor(isMouseOverText(window, scenario1) ? sf::Color::Yellow : sf::Color::White);
            scenario2.setFillColor(isMouseOverText(window, scenario2) ? sf::Color::Yellow : sf::Color::White);
            scenario3.setFillColor(isMouseOverText(window, scenario3) ? sf::Color::Yellow : sf::Color::White);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(window, scenario1)) {
                    return "assets/001cenario.png";
                } else if (isMouseOverText(window, scenario2)) {
                    return "assets/002cenario.png";
                } else if (isMouseOverText(window, scenario3)) {
                    return "assets/003cenario.png";
                }
            }
        }

        window.clear();
        window.draw(instruction);
        window.draw(scenario1);
        window.draw(scenario2);
        window.draw(scenario3);
        window.display();
    }

    return "";
}

std::string selectCharacter(sf::RenderWindow& window, sf::Font& font) {
    sf::Text title;
    configureText(title, font, 30, sf::Color::Yellow, sf::Color::Black, 2);
    title.setString("Choose your defender:");
    title.setPosition(window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f, window.getSize().y / 6.0f);

    sf::Text character1, character2, character3, character4;
    configureText(character1, font, 30, sf::Color::Red, sf::Color::White, 2);
    character1.setString("1. Vengeful Horned");
    character1.setPosition(window.getSize().x / 2.0f - character1.getLocalBounds().width / 2.0f, window.getSize().y / 3.0f);

    configureText(character2, font, 30, sf::Color::Blue, sf::Color::White, 2);
    character2.setString("2. Eye Spectator");
    character2.setPosition(window.getSize().x / 2.0f - character2.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f);

    configureText(character3, font, 30, sf::Color::Black, sf::Color::White, 2);
    character3.setString("3. Dragon God");
    character3.setPosition(window.getSize().x / 2.0f - character3.getLocalBounds().width / 2.0f, window.getSize().y / 1.5f);

    configureText(character4, font, 30, sf::Color::Black, sf::Color::Black, 2);
    character4.setString("Master of Masters");
    character4.setPosition(window.getSize().x / 2.0f - character4.getLocalBounds().width / 2.0f, window.getSize().y / 1.2f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            character1.setFillColor(isMouseOverText(window, character1) ? sf::Color::Yellow : sf::Color::Red);
            character2.setFillColor(isMouseOverText(window, character2) ? sf::Color::Yellow : sf::Color::Blue);
            character3.setFillColor(isMouseOverText(window, character3) ? sf::Color::Yellow : sf::Color::Black);
            character4.setFillColor(isMouseOverText(window, character4) ? sf::Color::White : sf::Color::Black);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverText(window, character1)) {
                    return "assets/001defender.png";
                } else if (isMouseOverText(window, character2)) {
                    return "assets/002defender.png";
                } else if (isMouseOverText(window, character3)) {
                    return "assets/003defender.png";
                } else if (isMouseOverText(window, character4)) {
                    return "assets/004defender.png";
                }
            }
        }

        window.clear();
        window.draw(title);
        window.draw(character1);
        window.draw(character2);
        window.draw(character3);
        window.draw(character4);
        window.display();
    }

    return "";
}