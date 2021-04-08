/*!
\file EnemySensor.h
*/
/*! \EnemySensor EnemySensor
\The EnemySensor class creates sensor used by enemies
*/
#pragma once
#include "staticSensor.h"

class EnemySensor : public StaticSensor
{
public:
	EnemySensor() {}; //!< Default Constructor
	EnemySensor(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation); //!< A constructor creating an object and determining its properties
	void onAction(); //!< On action function 
	void offAction(); //!< Off action function 
};

