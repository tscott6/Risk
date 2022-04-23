#pragma once
#include "Screen.h"
class SetupGameScreen : public Screen
{
private:
	ScreenManagerControl* m_ScreenManagerControl;

	sf::Texture m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;

	int playerNumber;
	std::string playerColour;

public:
	SetupGameScreen(ScreenManagerControl* screenControl, sf::Vector2i res, tgui::Gui& gui);

	void setPlayerNumber(int number);
	int getPlayerNumber();

	void setPlayerColour(std::string colour);
	std::string getPlayerColour();

	virtual void draw(sf::RenderWindow& window, tgui::Gui& gui);

	virtual void activateGUI(tgui::Gui& gui);
	virtual void deactivateGUI(tgui::Gui& gui);
	virtual void activateButtons(tgui::Gui& gui);
	virtual void deactivateButtons(tgui::Gui& gui);
	virtual void activateComboBoxes(tgui::Gui& gui);
	virtual void deactivateComboBoxes(tgui::Gui& gui);
};

