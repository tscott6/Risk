#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#include "ScreenManagerControl.h"
#include "InputHandler.h"
#include "UIPanel.h"

class InputHandler;

class Screen
{
private:
	std::vector<std::shared_ptr<InputHandler>> m_InputHandlers;
	std::vector<std::unique_ptr<UIPanel>> m_Panels;

protected:
	void addPanel(std::unique_ptr<UIPanel> panel, ScreenManagerControl* screenControlPtr, std::shared_ptr<InputHandler> inputHandler);

public:
	virtual void initialize();
	virtual void update();
	virtual void draw(sf::RenderWindow& window, tgui::Gui& gui);
	void handleInput(sf::RenderWindow& window, tgui::Gui& gui);

	virtual void activateGUI(tgui::Gui& gui);
	virtual void deactivateGUI(tgui::Gui& gui);
	virtual void activateButtons(tgui::Gui& gui);
	virtual void deactivateButtons(tgui::Gui& gui);
	virtual void activateComboBoxes(tgui::Gui& gui);
	virtual void deactivateComboBoxes(tgui::Gui& gui);

	virtual void initializeGame(int playerNumber, std::string playerColour, std::vector<tgui::String> colourList);

	//sf::View m_View;

};

