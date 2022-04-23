#include "ComboBox.h"

ComboBox::ComboBox(sf::Vector2f position, sf::Vector2f dimensions, std::string name, std::vector<std::string> items, tgui::Gui& gui) {
	auto box = tgui::ComboBox::create();

	box->setSize(dimensions.x, dimensions.y);
	box->setPosition(position.x, position.y);

	auto start = items.begin();
	auto end = items.end();

	for (start; start != end; ++start) {
		box->addItem(*start);
	}

	box->setSelectedItemByIndex(0);

	gui.add(box, name);
}

void ComboBox::resetComboBoxSelection(tgui::Gui& gui, std::string name, std::string defaultSelection) {
	gui.get<tgui::ComboBox>(name)->deselectItem();
	gui.get<tgui::ComboBox>(name)->setSelectedItem(defaultSelection);
}

void ComboBox::setVisible(tgui::Gui& gui, std::string boxName, bool isEnabled) {
	gui.get<tgui::ComboBox>(boxName)->setVisible(isEnabled);
}
