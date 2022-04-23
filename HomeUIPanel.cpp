#include "HomeUIPanel.h"

HomeUIPanel::HomeUIPanel(sf::Vector2i res, tgui::Gui& gui) : UIPanel(res, 0, 0, res.x, res.y) {
	m_ButtonWidth = 150;
	m_ButtonHeight = 50;
	m_ButtonPadding = res.x / 100;

	m_Text.setFillColor(sf::Color(0, 255, 0, 255));
	m_Text.setString("Risk");

	m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
	m_Text.setFont(m_Font);

	m_Text.setPosition(sf::Vector2f(m_ButtonPadding, m_ButtonHeight + (m_ButtonPadding * 2)));

	m_Text.setCharacterSize(120);

	initializeButtons(gui);
}

void HomeUIPanel::initializeButtons(tgui::Gui& gui) {
	addButton(sf::Vector2f(500, 500), m_ButtonWidth, m_ButtonHeight, "New Game", gui);
	addButton(sf::Vector2f(700, 500), m_ButtonWidth, m_ButtonHeight, "Quit", gui);
}

void HomeUIPanel::draw(sf::RenderWindow& window) {
	show();
	UIPanel::draw(window);
	window.draw(m_Text);
}
