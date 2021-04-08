/*! \mainpage  - Box2D Game
* Pnumber: p2500537
*/

/*! \file main.cpp
* \brief Main file for the application
*
* Contains the entry point of the application
*/

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>


#include "game.h"

void main() /** Entry point for the application */
{
	//----------bool-------------

	bool bkeyw = false;

	bool bkeya = false;

	bool bkeyd= false;

	bool bkeys = false;

	bool bkeyspace = false;
	
	sf::RenderWindow window(sf::VideoMode(800, 800), "Box2D Game"); // Open main window
	Game game;
	sf::Vector2i mouse;
	float fFrameTime = 1.f / 60.f;

	// Start a clock to provide time for the physics
	sf::Clock clock;

	// Run a game loop
	while (window.isOpen())
	{
		window.clear(sf::Color::White);

		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)

			{


				if (event.key.code == sf::Keyboard::W)
				{
				bkeyw = true; 
				game.processKeyPress(sf::Keyboard::W, bkeyw);
				}

				if (event.key.code == sf::Keyboard::S)
				{
					bkeys = true;
					game.processKeyPress(sf::Keyboard::S, bkeys);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					bkeya = true;
					game.processKeyPress(sf::Keyboard::A, bkeya);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					bkeyd = true;
					game.processKeyPress(sf::Keyboard::D, bkeyd);
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					bkeyspace = true;
					game.processKeyPress(sf::Keyboard::Space, bkeyspace);
				}
				if (event.key.code == sf::Keyboard::Tab)
				{
					game.processKeyPress(sf::Keyboard::Tab,true);
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{

				if (event.key.code == sf::Keyboard::W)
				{
					bkeyw = false;
					game.processKeyPress(sf::Keyboard::W, bkeyw);
				}

				if (event.key.code == sf::Keyboard::S)
				{
					bkeys = false;
					game.processKeyPress(sf::Keyboard::S, bkeys);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					bkeya = false;
					game.processKeyPress(sf::Keyboard::A, bkeya);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					bkeyd = false;
					game.processKeyPress(sf::Keyboard::D, bkeyd);
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					bkeyspace = false;
					game.processKeyPress(sf::Keyboard::Space, bkeyspace);
				}
			}


			if (event.type == sf::Event::MouseMoved)
			{
				mouse = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
				game.onMouseMoved(window.mapPixelToCoords(mouse));
				
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				game.processMousePress(sf::Mouse::Button::Left);
				
			} 
			if (event.mouseButton.button == sf::Mouse::Button::Right)
			{
				game.processMousePress(sf::Mouse::Button::Right);
			
			}
			}

			game.Getkeys(bkeyw, bkeys, bkeya, bkeyd );
		}


		// Find out how much time has elapsed

		float fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past then update the physics
		if (fElapsedTime > fFrameTime)
		{
			game.update(fElapsedTime);
			clock.restart();
		}
		
		window.draw(game);
		window.display();
	}



}
