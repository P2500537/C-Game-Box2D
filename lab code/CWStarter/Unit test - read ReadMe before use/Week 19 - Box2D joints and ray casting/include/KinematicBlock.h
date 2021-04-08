/*!
\file KinematicBlock.h
*/
/*! \KinematicBlock KinematicBlock
\The KinematicBlock class creates kinematic blocks
*/
#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "physicalThing.h"
#include <iostream>
class KinematicBlock : public sf::RectangleShape, public PhysicalThing
{
private:
sf::RectangleShape Kinematic_Body; //!< Kinematic Body 
b2PolygonShape RectangleSensor; //!< Rectangle Sensor Polygon Shape
bool right=true; //!< movement variable
char VorH; //!< Vertical or horizontal movement variable
sf::Vector2f firstposition; //!< firstposition variable
sf::Vector2f lastposition; //!< lastposition variable
float orientation; //!< orientation variable
float range; //!< range variable
public:
	sf::RectangleShape Kinematic_BodySensor; //!< Kinematic Sensor Body 
	KinematicBlock() {}; //!< Default Constructor
	KinematicBlock(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, float range,char VorH, CollisionFilter type, sf::Texture* texture);//!< A constructor creating an object and determining its properties
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Update rendering infomation 
	void update(); //!< Update rendering infomation 
	void updateTexture(sf::Texture* texture); //!< updateTexture function 
	void onAction(); //!< On action function 

};

