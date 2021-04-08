#pragma once

/*!
\file StaticBoxSensor.h
*/
/*! \class StaticBoxSensor
\brief A simple StaticBoxSensor which can not move or rotate and does not coliide with enemies
*/

#include "staticSensor.h"


class StaticBoxSensor : public StaticSensor
{
private:
	sf::Texture c_chest; //!< chest texture variable
public:
	bool open;
	StaticBoxSensor() {}; //!< Default constructor
	StaticBoxSensor(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation, sf::Texture* texture);
	void onAction(); //!< On action function 
	void offAction(); //!< Off action function 
	void OpenChest(); //!< Open chest function 
};