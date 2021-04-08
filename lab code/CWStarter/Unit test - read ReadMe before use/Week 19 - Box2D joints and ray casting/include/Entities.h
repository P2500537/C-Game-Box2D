#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "physicalThing.h"
class Entities : public sf::RectangleShape, public PhysicalThing
{
protected:
	void update(sf::Texture* texture);
public:
	void initBullet(b2World * world, sf::Vector2f Playerxy,sf::Vector2f size);

};

