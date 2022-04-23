#pragma once
#include "InputHandler.h"
#include "GameScreen.h"

class GameInputHandler : public InputHandler
{
private:
	GameScreen* gameScreen;
public:
	GameInputHandler(GameScreen* screen);
	void handleKeyPressed(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) override;

	void handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui, std::string button) override;
	void handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui) override;
};

