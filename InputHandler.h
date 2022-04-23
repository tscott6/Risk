#pragma once
#include "Button.h"
#include "Screen.h"
#include "ScreenManagerControl.h"

class Screen;

class InputHandler
{
private:
	Screen* m_ParentScreen;
	sf::View* m_UIPanelView;
	ScreenManagerControl* m_ScreenManagerControl;

public:
	void initializeInputHandler(ScreenManagerControl* screenControl, Screen* screen);

	void handleInput(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event);

	virtual void handleKeyPressed(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event);
	virtual void handleKeyReleased(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event);
	virtual void handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui, std::string button);
	virtual void handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui);

	sf::View* getUIPanelView();
	ScreenManagerControl* getScreenManagerControl();
	Screen* getParentScreen();

};

