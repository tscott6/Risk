#include "GameUIPanel.h"

GameUIPanel::GameUIPanel(sf::Vector2i res, tgui::Gui& gui) : UIPanel(res, 0, 0, res.x, res.y) {
	m_ButtonWidth = 150;
	m_ButtonHeight = 50;

	m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
	m_Text.setFont(m_Font);

	initializeButtons(gui);
}

void GameUIPanel::initializeButtons(tgui::Gui& gui) {
	addButton(sf::Vector2f(5, 5), m_ButtonWidth, m_ButtonHeight, "Menu", gui);
	addButton(sf::Vector2f(544, 291), m_ButtonWidth, m_ButtonHeight, "Resume", gui);
	addButton(sf::Vector2f(544, 341), m_ButtonWidth, m_ButtonHeight, "Main Menu", gui);
	addButton(sf::Vector2f(544, 391), m_ButtonWidth, m_ButtonHeight, "Exit Game", gui);
	addButton(sf::Vector2f(605, 855), 100, 40, "End Attack", gui);
	addButton(sf::Vector2f(1095, 855), 100, 40, "End Turn", gui);

	gui.get<tgui::Button>("Resume")->setText("End Phase");
}

void GameUIPanel::draw(sf::RenderWindow& window) {
	show();
	UIPanel::draw(window);
	window.draw(m_Text);
}