#pragma once
#include "Screen.h"

class HomeScreen : public Screen
{
private:
	ScreenManagerControl* m_ScreenManagerControl;

	sf::Texture m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;

public:
	HomeScreen(ScreenManagerControl* screenControl, sf::Vector2i res, tgui::Gui& gui);

	virtual void draw(sf::RenderWindow& window, tgui::Gui& gui);

	virtual void activateGUI(tgui::Gui& gui);
	virtual void deactivateGUI(tgui::Gui& gui);
	virtual void activateButtons(tgui::Gui& gui);
	virtual void deactivateButtons(tgui::Gui& gui);
};

