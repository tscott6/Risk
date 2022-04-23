#pragma once
#include "UIPanel.h"
class GameUIPanel : public UIPanel
{
private:
	void initializeButtons(tgui::Gui& gui);

public:
	GameUIPanel(sf::Vector2i res, tgui::Gui& gui);

	virtual void draw(sf::RenderWindow& window);
};

