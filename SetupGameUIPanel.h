#pragma once
#include "UIPanel.h"

class SetupGameUIPanel : public UIPanel
{
private:
	void initializeButtons(tgui::Gui& gui);
	void initializeComboBoxes(tgui::Gui& gui);

public:
	SetupGameUIPanel(sf::Vector2i res, tgui::Gui& gui);

	virtual void draw(sf::RenderWindow& window);
};

