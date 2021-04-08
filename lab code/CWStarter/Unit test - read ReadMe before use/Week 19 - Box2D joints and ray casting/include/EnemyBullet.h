/*!
\file EnemyBullet.h
*/
/*! \EnemyBullet EnemyBullet
\The EnemyBullet class creates projectiles used by the enemy 
*/
#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "physicalThing.h"
class EnemyBullet : public sf::Drawable, public PhysicalThing
{
private:
	sf::RectangleShape Bullet_Body;//!< Bullet Body
	float rotation; //!< Rotation variable
public:
	EnemyBullet() {}; //!< Default Constructor
	EnemyBullet(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const float orientation, CollisionFilter type);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;//!< drawing function
	void update(); //!< Update rendering infomation 
	bool m_delete;//!< variable to object deletion
	void SetRotation(float rotation); //!< Set rotation function 
	void onAction(); //!< On action function
	bool shouldDelete(); //!< a function that adds an object to the list to be deleted
};

