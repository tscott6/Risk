#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class Button
{
public:
	Button(sf::Vector2f position, float width, float height, std::string text, tgui::Gui& gui);
	void setVisible(tgui::Gui& gui, std::string buttonName, bool isVisible);
	void setEnabled(tgui::Gui& gui, std::string buttonName, bool isEnabled);
};

