/*!
\file Coins.h
*/
/*! \Coins Coins
\The Coins class creates coins used by the player
*/
#pragma once

#include "staticSensor.h"
class Coins : public StaticSensor
{
private:
	sf::Texture c_coin;
public:
	bool m_delete = false; //!< variable to object deletion
	Coins() {}; //!< Default constructor
	Coins(b2World * world, sf::Vector2f position, float radius, sf::Texture* texture);//!< A constructor creating an object and determining its properties
	void onAction(); //!< On action function 
	void offAction(){}; //!< Off action function 
	void registerForDeletion(); //!< a function that adds an object to the list to be deleted
	bool shouldDelete(); //!< a function that adds an object to the list to be deleted
};

