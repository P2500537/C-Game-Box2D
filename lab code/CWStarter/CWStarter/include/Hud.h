/*!
\file Hud.h
*/
/*! \Hud Hud
\The Hud class creates Hud
*/
#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
class Hud : public sf::Drawable
{
private:
	int score; //!< score variable
	int H, M, S, C; //!< Hours, minutes and seconds variables
	int S1, S2, M1, M2, H1, H2, C1, C2; //!< Hours, minutes and seconds variables
	enum m_numberState { Zero,One, Two, Three, Four, Five, Six, Seven, Eight, Nine }; 
	m_numberState m_numberState; //!< m_numberState enum variable
	sf::Texture Coins, Colon, Zero0, One1, Two2, Three3, Four4, Five5, Six6, Seven7, Eight8, Nine9, CorrectNumber; //!< Textures for numbers, colon and Coins text
	sf::Texture T_TimeCounter[8]; //!< Texture timeCounter
	sf::Texture T_CoinCounter[3]; //!< Texture coinCounter
	sf::RectangleShape S_TimeCounter[8];  //!< timeCounter Shape
	sf::RectangleShape S_CoinCounter[3]; //!< coinCounter Shape
public:
	Hud() {};//!< Default Constructor
	Hud(b2World * world); //!< A constructor creating an object and determining its properties
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< drawing function
	~Hud();
	void update(sf::Clock time, int score); //!< Update rendering infomation
	void TimeCheck(sf::Clock time); //!< TimeCheck function
	void CoinCheck(int score);  //!< CoinCheck function
	sf::Texture NumberCheck(int number); //!< texture NumberCheck function
	void T_TextureUpdate(sf::Texture* Texture, int i); //!< Updating texture for time counter
	void C_TextureUpdate(sf::Texture* Texture, int i); //!< Updating texture for coin counter
};

