#pragma once
#include "InputHandler.h"
class SetupGameInputHandler : public InputHandler
{
private:
	Screen* setupScreen;
public:
	SetupGameInputHandler(Screen* setupScreenPtr);

	void handleKeyPressed(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) override;

	void handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui, std::string button) override;

	Screen* getSetupScreen();
};

