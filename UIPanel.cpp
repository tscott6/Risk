#include "UIPanel.h"

UIPanel::UIPanel(sf::Vector2i res, int x, int y, float w, float h)
{
	m_UIPanel.setPosition(sf::Vector2f(res.x, res.y));
	m_UIPanel.setSize(sf::Vector2f(w, h)); // Size of UI panel in pixels

	/*m_View.setSize(sf::Vector2f(w, h)); //  Size of UI view in pixels

	m_View.setCenter(w / 2, h / 2); // Ensures centre of UI view is focused on centre of m_UIPanel

	float viewportStartX = 1.f / (res.x / x);
	float viewportStartY = 1.f / (res.y / y);
	float viewportSizeX = 1.f / (res.x / w);
	float viewportSizeY = 1.f / (res.y / h);

	m_View.setViewport(sf::FloatRect(viewportStartX, viewportStartY, viewportSizeX, viewportSizeY));*/

}

void UIPanel::addButton(sf::Vector2f position, float width, float height, std::string text, tgui::Gui& gui) {
	auto tempButton = Button(position, width, height, text, gui);
}

void UIPanel::addComboBox(sf::Vector2f position, sf::Vector2f dimensions, std::string name, std::vector<std::string> items, tgui::Gui& gui) {
	auto tempBox = ComboBox(position, dimensions, name, items, gui);
}

void UIPanel::draw(sf::RenderWindow& window)
{
	//window.setView(m_View);

	if (!m_IsHidden) {
		window.draw(m_UIPanel);
	}
}

void UIPanel::show()
{
	m_IsHidden = false;
}

void UIPanel::hide()
{
	m_IsHidden = true;
}
