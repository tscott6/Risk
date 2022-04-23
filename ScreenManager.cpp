#include "ScreenManager.h"
#include "HomeScreen.h"
#include "SetupGameScreen.h"
#include "GameScreen.h"

ScreenManager::ScreenManager(sf::Vector2i res, tgui::Gui& gui) {
	m_Screens["Home"] = std::unique_ptr<HomeScreen>(new HomeScreen(this, res, gui));
	m_Screens["SetupGame"] = std::unique_ptr<SetupGameScreen>(new SetupGameScreen(this, res, gui));
	m_Screens["Game"] = std::unique_ptr<GameScreen>(new GameScreen(this, res, gui));

	m_Screens["Home"]->activateGUI(gui);
}

void ScreenManager::handleInput(sf::RenderWindow& window, tgui::Gui& gui) {
	m_Screens[m_CurrentScreen]->handleInput(window, gui);
}

void ScreenManager::update() {
	m_Screens[m_CurrentScreen]->update();
}

void ScreenManager::draw(sf::RenderWindow& window, tgui::Gui& gui) {
	m_Screens[m_CurrentScreen]->draw(window, gui);
}
