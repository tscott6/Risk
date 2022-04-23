#pragma once
#include "UIPanel.h"

class HomeUIPanel : public UIPanel
{
private:
	void initializeButtons(tgui::Gui& gui);

public:
	HomeUIPanel(sf::Vector2i res, tgui::Gui& gui);

	virtual void draw(sf::RenderWindow& window);
};

