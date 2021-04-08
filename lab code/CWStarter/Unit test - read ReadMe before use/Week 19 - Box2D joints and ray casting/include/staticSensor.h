#pragma once

/*!
\file staticSensor.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "physicalThing.h"

/*! \class StaticSensor
\brief A simple block which can not move or rotate and does not coliide with enemies
*/

class StaticSensor : public sf::RectangleShape, public PhysicalThing
{
protected:
	void update(sf::Texture* texture); //!< update function for sensor textures
public:
	int id = 0; //!< id variable for sensor check
	void initRectangle(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation, int id); //!<creates a rectangular sensor
	void initCircle(b2World * world, sf::Vector2f position, float radius); //!<creates a circular sensor
	virtual void onAction() = 0; //!< Thing the sensor does when hit
	virtual void offAction() = 0; //!< Thing the sensor does when hit stops


};