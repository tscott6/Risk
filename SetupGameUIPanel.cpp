#include "SetupGameUIPanel.h"

SetupGameUIPanel::SetupGameUIPanel(sf::Vector2i res, tgui::Gui& gui) : UIPanel(res, 0, 0, res.x, res.y) {
	m_ButtonWidth = 150;
	m_ButtonHeight = 50;

	m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
	m_Text.setFont(m_Font);

	initializeButtons(gui);
	initializeComboBoxes(gui);
}

void SetupGameUIPanel::initializeButtons(tgui::Gui& gui) {
	addButton(sf::Vector2f(500, 500), m_ButtonWidth, m_ButtonHeight, "Test1", gui);
	addButton(sf::Vector2f(700, 500), m_ButtonWidth, m_ButtonHeight, "Back", gui);
}

void SetupGameUIPanel::initializeComboBoxes(tgui::Gui& gui) {
	addComboBox(sf::Vector2f(500, 700), sf::Vector2f(200, 50), "PlayerNumber", { "Player Number", "2", "3", "4" }, gui);
	addComboBox(sf::Vector2f(800, 700), sf::Vector2f(200, 50), "PlayerColour", { "Player Colour", "Red", "Blue", "Green", "Yellow" }, gui);
}

void SetupGameUIPanel::draw(sf::RenderWindow& window) {
	show();
	UIPanel::draw(window);
	window.draw(m_Text);
}
