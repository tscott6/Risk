#include "SetupGameInputHandler.h"

SetupGameInputHandler::SetupGameInputHandler(Screen* setupScreenPtr) {
	setupScreen = setupScreenPtr;
}

void SetupGameInputHandler::handleKeyPressed(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) {}

void SetupGameInputHandler::handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui, std::string widgetName) {
	auto name = gui.get(widgetName)->getWidgetName();

	if (name == "Test1" && 
		gui.get<tgui::ComboBox>("PlayerNumber")->getSelectedItem().toStdString() != "Player Number" &&
		gui.get<tgui::ComboBox>("PlayerColour")->getSelectedItem().toStdString() != "Player Colour") {
		//std::cout << gui.get<tgui::ComboBox>("PlayerNumber")->getSelectedItem().toStdString() << std::endl;
		//std::cout << gui.get<tgui::ComboBox>("PlayerColour")->getSelectedItem().toStdString() << std::endl;

		std::vector<tgui::String> colourList = gui.get<tgui::ComboBox>("PlayerColour")->getItems();
		colourList.erase(colourList.begin());

		getScreenManagerControl()->initializeGameScreen(std::stoi(gui.get<tgui::ComboBox>("PlayerNumber")->getSelectedItem().toStdString()),
			gui.get<tgui::ComboBox>("PlayerColour")->getSelectedItem().toStdString(),
			colourList);
		getScreenManagerControl()->switchScreens("Game", gui);
	}

	if (name == "Back") {
		getScreenManagerControl()->switchScreens("Home", gui);
	}
}

Screen* SetupGameInputHandler::getSetupScreen() {
	return setupScreen;
}
