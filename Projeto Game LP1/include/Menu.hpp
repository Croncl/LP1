#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

void configureText(sf::Text& text, const sf::Font& font, unsigned int size, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness);
bool isMouseOverText(const sf::RenderWindow& window, const sf::Text& text);
void showMenu(sf::RenderWindow& window, sf::Font& font);
std::string selectScenario(sf::RenderWindow& window, sf::Font& font);
std::string selectCharacter(sf::RenderWindow& window, sf::Font& font);

#endif // MENU_HPP