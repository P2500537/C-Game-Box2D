/*!
\file Win.cpp
*/
#include "Win.h"
Win::Win(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation, sf::Texture* texture)
{
	win = false;
	id = 1;
	initRectangle(world, position, size, orientation, id);
	setTexture(texture);

}
void Win::onAction() {

	win = true;

}