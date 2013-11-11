#include <sstream>

#include "GUI.h"


GUI::GUI(void)
	: font(),
	  text()
{
}


GUI::~GUI(void)
{
}


void GUI::update(sf::Time &elapsedTime, WorldManager &world)
{
	sf::Text newText;
	
	newText.setFont(font);
	newText.setCharacterSize(24);
	newText.setColor(sf::Color::White);
	newText.setStyle(sf::Text::Regular);

	std::ostringstream ostr;
	ostr << "Score: " << world.snake->score
			<< "\nLives: " << world.snake->lives
			<< "\nSize: " << world.snake->tail.size() + 1
			<< "\nSpeed: " << static_cast<int>(200 - (world.snake->movementDelay.asSeconds() / world.snake->initialMovementDelay.asSeconds() * 100)) << "%";
	newText.setString(std::string(ostr.str()));
	newText.setPosition(20, 20);

	text.clear();
	text.push_back(newText);
}


void GUI::draw(sf::RenderWindow &window)
{
	for (std::vector<sf::Text>::iterator it = text.begin(); it != text.end(); it++)
		window.draw(*it);
}

