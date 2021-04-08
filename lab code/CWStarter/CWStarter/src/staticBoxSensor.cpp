/*!
\file StaticBoxSensor.cpp
*/
#include "StaticBoxSensor.h"

StaticBoxSensor::StaticBoxSensor(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation, sf::Texture* texture)
{
	open = false;
	c_chest.loadFromFile("./assets/textures/o_chest.png");
	id = 1;
	initRectangle(world, position, size, orientation, id);
	setTexture(texture);

}
void StaticBoxSensor::onAction(){
	update(&c_chest);
	open = true;

}
void StaticBoxSensor::offAction() {

	open = false;
}
void StaticBoxSensor::OpenChest() {

	//if (open==true) {
	//	update(&c_chest);
	//}
}