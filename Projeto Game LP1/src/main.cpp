#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Menu.hpp"

bool restart = false;

void restartGame() {
    restart = true;
}

int main() {
    do {
        restart = false;
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
            game.run();
        }
    } while (restart);

    return 0;
}