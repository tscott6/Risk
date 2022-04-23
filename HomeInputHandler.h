#pragma once
#include "InputHandler.h"

class HomeInputHandler : public InputHandler
{
public:
	void handleKeyPressed(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) override;

	void handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui, std::string button) override;
};

