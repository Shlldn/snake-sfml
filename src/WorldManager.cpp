#include "WorldManager.h"
#include "Log.h"


WorldManager::WorldManager(GameSettings &settings)
	: snake(NULL),
	  settings(settings),
	  entities()
{
}


WorldManager::~WorldManager()
{
}


void WorldManager::initialize()
{
	snake = new Snake();
	snake->spawn();
	
	Food *food = new Food();
	food->position = sf::Vector2i(std::rand() % settings.colsNb, std::rand() % settings.rowsNb);
	addEntity(food);
}


void WorldManager::addEntity(AEntity *entity)
{
	entities.push_back(entity);
}


void WorldManager::removeEntity(AEntity *entity)
{
}


void WorldManager::update(sf::Time & elapsedTime)
{
	std::vector<AEntity*> itemsToDelete;

	// Put all the "dead" entities in a list to delete them afterwards
	for (std::vector<AEntity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		AEntity *entity = *it;

		entity->update(elapsedTime);
		if (!entity->isAlive)
			itemsToDelete.push_back(*it);
	}

	// Safely delete and erase the "dead" entities
	for (std::vector<AEntity*>::iterator it = itemsToDelete.begin(); it != itemsToDelete.end(); it++)
	{
		std::vector<AEntity*>::iterator entityIterator;
		AEntity *entity = *it;
		
		entityIterator = std::find(entities.begin(), entities.end(), entity);
		if (entityIterator != entities.end())
		{
			entities.erase(entityIterator);
			delete entity;
		}
	}

	snake->update(elapsedTime);
}

void WorldManager::draw(sf::RenderWindow &window)
{
	sf::RectangleShape background(sf::Vector2f(static_cast<float>(settings.viewSize), static_cast<float>(settings.viewSize)));
	background.setFillColor(sf::Color(15, 30, 25));
	background.setOutlineThickness(4);
	background.setOutlineColor(sf::Color(5, 20, 15));
	background.setPosition(static_cast<float>(settings.viewOffset), .0f);
	window.draw(background);
	
	for (std::vector<AEntity *>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		AEntity *entity = *it;
		
		sf::CircleShape food(settings.unit/2.f);
		food.setFillColor(sf::Color(240, 85, 70));
		food.setOutlineThickness(2);
		food.setOutlineColor(sf::Color(200, 45, 30));
		food.setPosition(static_cast<float>(settings.viewOffset + entity->position.x * settings.unit), static_cast<float>(entity->position.y * settings.unit));
		window.draw(food);
	}
	
	// Snake (head displayed last)
	sf::CircleShape circle(settings.unit/2.f);
	circle.setFillColor(sf::Color(40, 225, 60));
	circle.setOutlineThickness(2);
	circle.setOutlineColor(sf::Color(0, 185, 20));
	// Tail
	for (SnakeTail::reverse_iterator it = snake->tail.rbegin(); it != snake->tail.rend(); it++)
	{
		circle.setPosition(static_cast<float>(settings.viewOffset + (*it).x * settings.unit), static_cast<float>((*it).y * settings.unit));
		window.draw(circle);
	}
	// Head
	circle.setPosition(static_cast<float>(settings.viewOffset + snake->position.x * settings.unit), static_cast<float>(snake->position.y * settings.unit));
	window.draw(circle);
}

