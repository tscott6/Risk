#pragma once
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "ScreenManagerControl.h"
#include "Screen.h"

class ScreenManager : public ScreenManagerControl
{
private:
	std::map<std::string, std::unique_ptr<Screen>> m_Screens;

protected:
	std::string m_CurrentScreen = "Home";

public:
	ScreenManager(sf::Vector2i resolution, tgui::Gui& gui);

	void update();
	void draw(sf::RenderWindow& window, tgui::Gui& gui);
	void handleInput(sf::RenderWindow& window, tgui::Gui& gui);

	void ScreenManagerControl::initializeGameScreen(int playerNumber, std::string playerColour, std::vector<tgui::String> colourList) {
		m_Screens["Game"]->initializeGame(playerNumber, playerColour, colourList);
	}

	void ScreenManagerControl::switchScreens(std::string switchToScreen, tgui::Gui& gui) {
		m_Screens[m_CurrentScreen]->deactivateGUI(gui);

		m_CurrentScreen = switchToScreen;
		m_Screens[m_CurrentScreen]->activateGUI(gui);
		m_Screens[m_CurrentScreen]->initialize();
	}
};

