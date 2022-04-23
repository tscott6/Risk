#include "SetupGameScreen.h"
#include "SetupGameInputHandler.h"
#include "SetupGameUIPanel.h"

SetupGameScreen::SetupGameScreen(ScreenManagerControl* screenControl, sf::Vector2i res, tgui::Gui& gui) {
	auto setupUI = std::make_unique<SetupGameUIPanel>(res, gui);
	auto setupInput = std::make_shared<SetupGameInputHandler>(this);

	addPanel(std::move(setupUI), screenControl, setupInput);

	m_ScreenManagerControl = screenControl;

	m_BackgroundTexture.loadFromFile("graphics/background.png");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	playerNumber = 0;
	playerColour = "NONE";

	//Prevent gui widgets from displaying upon screen instantiation (TGUI stores all widgets in common container)
	deactivateGUI(gui);
}

void SetupGameScreen::setPlayerNumber(int number) {
	playerNumber = number;
}

int SetupGameScreen::getPlayerNumber() {
	return playerNumber;
}

void SetupGameScreen::setPlayerColour(std::string colour) {
	playerColour = colour;
}

std::string SetupGameScreen::getPlayerColour() {
	return playerColour;
}

void SetupGameScreen::draw(sf::RenderWindow& window, tgui::Gui& gui) {
	window.draw(m_BackgroundSprite);

	Screen::draw(window, gui);
}

void SetupGameScreen::activateButtons(tgui::Gui& gui) {
	gui.get<tgui::Button>("Test1")->setVisible(true);
	gui.get<tgui::Button>("Back")->setVisible(true);
}

void SetupGameScreen::deactivateButtons(tgui::Gui& gui) {
	gui.get<tgui::Button>("Test1")->setVisible(false);
	gui.get<tgui::Button>("Back")->setVisible(false);
}

void SetupGameScreen::activateComboBoxes(tgui::Gui& gui) {
	gui.get<tgui::ComboBox>("PlayerNumber")->setVisible(true);
	gui.get<tgui::ComboBox>("PlayerColour")->setVisible(true);
}
void SetupGameScreen::deactivateComboBoxes(tgui::Gui& gui) {
	gui.get<tgui::ComboBox>("PlayerNumber")->deselectItem();
	gui.get<tgui::ComboBox>("PlayerNumber")->setSelectedItem("Player Number");
	gui.get<tgui::ComboBox>("PlayerNumber")->setVisible(false);

	gui.get<tgui::ComboBox>("PlayerColour")->deselectItem();
	gui.get<tgui::ComboBox>("PlayerColour")->setSelectedItem("Player Colour");
	gui.get<tgui::ComboBox>("PlayerColour")->setVisible(false);
}

void SetupGameScreen::activateGUI(tgui::Gui& gui) {
	activateButtons(gui);
	activateComboBoxes(gui);
}
void SetupGameScreen::deactivateGUI(tgui::Gui& gui) {
	deactivateButtons(gui);
	deactivateComboBoxes(gui);

	// Combo boxes reset when screens switch, make sure variables do too
	setPlayerNumber(0);
	setPlayerColour("NONE");
}
