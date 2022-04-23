#include "InputHandler.h"
#include <iostream>

void InputHandler::initializeInputHandler(ScreenManagerControl* screenControl, Screen* screen) {

	m_ScreenManagerControl = screenControl;
	m_ParentScreen = screen;
}

void InputHandler::handleInput(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		handleKeyPressed(window, gui, event);
	}
	if (event.type == sf::Event::KeyReleased) {
		handleKeyReleased(window, gui, event);
	}
	if (event.type == sf::Event::MouseButtonReleased) {
		auto getWidget = gui.getWidgetAtPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

		if (getWidget) {
			std::string widgetName = getWidget->getWidgetName().toStdString();
			handleLeftClick(window, gui, widgetName);
		}
		else {
			handleLeftClick(window, gui);
		}
	}
}

void InputHandler::handleKeyPressed(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) {}
void InputHandler::handleKeyReleased(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) {}
void InputHandler::handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui, std::string button) {}
void InputHandler::handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui) {}

sf::View* InputHandler::getUIPanelView() {
	return m_UIPanelView;
}

ScreenManagerControl* InputHandler::getScreenManagerControl() {
	return m_ScreenManagerControl;
}

Screen* InputHandler::getParentScreen() {
	return m_ParentScreen;
}

