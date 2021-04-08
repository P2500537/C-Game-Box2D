/*!
\file Coins.cpp
*/
#include "Coins.h"

Coins::Coins(b2World * world, sf::Vector2f position, float radius, sf::Texture* texture)
{
	initCircle(world, position, radius);
	setPosition(position);
	setSize(sf::Vector2f(radius * 2.0f, radius * 2.0f));
	setOrigin(getSize() * 0.5f); 
	setTexture(texture);
	id = 2;
}

void Coins::onAction() {
	registerForDeletion();
}
void Coins::registerForDeletion()
{
	m_delete = true;
}
bool Coins::shouldDelete()
{
	return m_delete;
}

