#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class ComboBox
{
public:
	ComboBox(sf::Vector2f position, sf::Vector2f dimensions, std::string name, std::vector<std::string> items, tgui::Gui& gui);
	void resetComboBoxSelection(tgui::Gui& gui, std::string name, std::string defaultSelection);

	void setVisible(tgui::Gui& gui, std::string boxName, bool isVisible);
};

