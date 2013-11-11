#include <algorithm>
#include "GameEngine.h"
#include "Log.h"


GameEngine::GameEngine()
	: world(data.settings),
	  menu(NULL),
	  window(NULL)
{
	logLevel = LOG_DEBUG;

	data.state = UNINITIALIZED;
	
	initialize();
	loadContent();
}


GameEngine::~GameEngine()
{
	unloadContent();
	uninitialize();
}


void GameEngine::run()
{
	if (window == NULL)
	{
		logLevel = LOG_ERROR;
		outLog << "GameEngine::run(): NULL window ptr";
		throw new std::exception("NULL window ptr");
	}

	data.state = MAIN_MENU;

	while (data.state != CLOSING)
    {
		sf::Time elapsedTime = data.clock.restart();
		update(elapsedTime);

		if (data.state != UNINITIALIZED && data.state != CLOSING)
		{
			draw();
			display();
		}
    }
}


void GameEngine::close()
{
	if (window->isOpen())
		window->close();
	if (data.music.getStatus() != sf::SoundSource::Stopped)
		data.music.stop();
}


void GameEngine::initialize()
{
	data.settings.windowWidth = 1280;
	data.settings.windowHeight = 720;
	
	sf::ContextSettings sfmlSettings;
	sfmlSettings.antialiasingLevel = 8;
	
	window = new sf::RenderWindow(sf::VideoMode(data.settings.windowWidth, data.settings.windowHeight), "Snake", sf::Style::Default, sfmlSettings);

	data.settings.rowsNb = 30;
	data.settings.colsNb = 30;
	data.settings.unit = std::min(static_cast<int>(data.settings.windowWidth / data.settings.colsNb), static_cast<int>(data.settings.windowHeight / data.settings.rowsNb));
	data.settings.viewSize = data.settings.unit * data.settings.colsNb;
	data.settings.viewOffset = (data.settings.windowWidth - data.settings.viewSize) / 2;
	data.settings.limitFPS = true;
	data.settings.maxFPS = 60;
	data.settings.verticalSync = false;
	
	if (data.settings.limitFPS == true)
		window->setFramerateLimit(data.settings.maxFPS);
	else if (data.settings.verticalSync == true)
		window->setVerticalSyncEnabled(data.settings.verticalSync);
	
	window->setKeyRepeatEnabled(false);

	world.initialize();
	
	std::srand(time(NULL));

	menu = new GUIMenu(data);

	data.state = INITIALIZED;
}


void GameEngine::uninitialize()
{
	if (window->isOpen())
		window->close();
	delete window;
	window = NULL;
}


void GameEngine::loadContent()
{
	if (!gui.font.loadFromFile("data/fonts/arial.ttf"))
	{
		// Error
	}

	if (!data.music.openFromFile("data/media/audio/music01.ogg"))
	{
		// Error
	}
	else
	{
		data.music.setLoop(true);
	}

	if (!data.soundBuffer.loadFromFile("data/media/audio/sound01.ogg"))
	{
		// Error
	}
	else
	{
		data.sound.setBuffer(data.soundBuffer);
	}
}


void GameEngine::unloadContent()
{
}


void GameEngine::update(sf::Time &elapsedTime)
{
	handleEvents(elapsedTime);

	switch (data.state)
	{
	case CLOSING:
		return;

	case MAIN_MENU:
		updateMainMenu(elapsedTime);
		break;

	case RUNNING:
		updateGame(elapsedTime);
		break;

	default:
		break;
	}
}


void GameEngine::updateMainMenu(sf::Time &elapsedTime)
{
	menu->update(elapsedTime);
}


void GameEngine::updateGame(sf::Time &elapsedTime)
{
	world.update(elapsedTime);
	
	// Check for self- and wall collisions
	SnakeTail::iterator overlap = std::find(world.snake->tail.begin(), world.snake->tail.end(), world.snake->position);
	if (overlap != world.snake->tail.end()
		|| world.snake->position.x < 0 || world.snake->position.x >= data.settings.colsNb
		|| world.snake->position.y < 0 || world.snake->position.y >= data.settings.rowsNb)
	{
		world.snake->die();
		world.snake->spawn();
	}
	
	// Check for collisions with entities
	for (std::vector<AEntity*>::iterator it = world.entities.begin(); it != world.entities.end(); it++)
	{
		AEntity *entity = *it;

		if (world.snake->collidesWith(*entity))
		{
			// Food entity
			if (entity->type == ENTITY_FOOD)
			{
				Food & food = static_cast<Food &>(*entity);
				
				world.snake->eat(food);
				data.sound.play();

				// Put the food at new random positions until it's not on/under the snake anymore
				do
				{
					food.position.x = std::rand() % data.settings.colsNb;
					food.position.y = std::rand() % data.settings.rowsNb;
				}
				while (food.collidesWith(*world.snake));
				
				break;
			}
		}
	}

	gui.update(elapsedTime, world);
}


void GameEngine::draw()
{
    window->clear();

	switch (data.state)
	{
	case RUNNING:
		world.draw(*window);
		gui.draw(*window);
		break;

	case MAIN_MENU:
		menu->draw(*window);
		break;

	default:
		break;
	}
}


void GameEngine::display()
{
	window->display();
}


void GameEngine::handleEvents(sf::Time &elapsedTime)
{
    sf::Event event;
	
    while (window->pollEvent(event))
    {
		switch (event.type)
		{
		case sf::Event::Closed:
			close();
			break;

		case sf::Event::KeyPressed:
			if (data.state == RUNNING)
				handleKeyboardEvent(event, elapsedTime);
			else if (data.state == MAIN_MENU)
				menu->handleKeyboardEvent(event, elapsedTime);
			break;

		default:
			break;
		}
    }
}


void GameEngine::handleKeyboardEvent(sf::Event &event, sf::Time &elapsedTime)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Escape:
		close();
		break;

	// Go up
	case sf::Keyboard::Up:
	case sf::Keyboard::W:
		if (world.snake->prevDirection != DIRECTION_DOWN)
			world.snake->nextDirection = DIRECTION_UP;
		break;

	// Go left
	case sf::Keyboard::Left:
	case sf::Keyboard::A:
		if (world.snake->prevDirection != DIRECTION_RIGHT)
			world.snake->nextDirection = DIRECTION_LEFT;
		break;

	// Go down
	case sf::Keyboard::Down:
	case sf::Keyboard::S:
		if (world.snake->prevDirection != DIRECTION_UP)
			world.snake->nextDirection = DIRECTION_DOWN;
		break;

	// Go right
	case sf::Keyboard::Right:
	case sf::Keyboard::D:
		if (world.snake->prevDirection != DIRECTION_LEFT)
			world.snake->nextDirection = DIRECTION_RIGHT;
		break;

	default:
		break;
	}
}
