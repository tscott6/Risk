#include "Button.h"

Button::Button(sf::Vector2f position, float width, float height, std::string text, tgui::Gui& gui) {
	auto m_Button = tgui::Button::create();

	m_Button->setPosition(position.x, position.y);
	m_Button->setText(text);
	m_Button->setSize(width, height);

	gui.add(m_Button, text);
}

void Button::setVisible(tgui::Gui& gui, std::string buttonName, bool isVisible) {
	gui.get<tgui::Button>(buttonName)->setVisible(isVisible);
}

void Button::setEnabled(tgui::Gui& gui, std::string buttonName, bool isEnabled) {
	gui.get<tgui::Button>(buttonName)->setEnabled(isEnabled);
}
