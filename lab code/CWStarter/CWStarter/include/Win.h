/*!
\file Win.h
*/
/*! \Win Win
\The Win class decide whether to display the congratulations inscription
*/
#pragma once
#include "staticSensor.h"
class Win : public StaticSensor
{
public:
	bool win; //!< win variable
	Win() {};//!< Default Constructor
	Win(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation, sf::Texture* texture); //!< A constructor creating an object and determining its properties
	void onAction(); //!< On action function 
	void offAction() {}; //!< Off action function 

};

