#include "HomeInputHandler.h"

void HomeInputHandler::handleKeyPressed(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
	}
}

void HomeInputHandler::handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui, std::string button) {
	auto buttonName = gui.get<tgui::Button>(button)->getWidgetName();

	if (buttonName == "New Game") {
		getScreenManagerControl()->switchScreens("SetupGame", gui);
	}

	if (buttonName == "Quit") {
		window.close();
	}
}
