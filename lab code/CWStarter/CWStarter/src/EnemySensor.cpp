/*!
\file EnemyMarkI.cpp
*/
#include "EnemySensor.h"
EnemySensor::EnemySensor(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation)
{
	id = 3;
	initRectangle(world, position, size, orientation, id);
	setFillColor(sf::Color::Transparent);
}

void EnemySensor::onAction()
{
}

void EnemySensor::offAction()
{
}
