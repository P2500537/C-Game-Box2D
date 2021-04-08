/*!
\file EnemyMarkI.h
*/
/*! \EnemyMarkI EnemyMarkI
\The EnemyMarkI class creates enemies
*/
#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "physicalThing.h"
class EnemyMarkI : public sf::RectangleShape, public PhysicalThing
{
private:
	float Clock; //!< Clock variable
	float timestamp; //!< timestamp variable
	float BulletTimestamp = 0; //!< Bullet timestamp variable
	char m_type; //!< type variable
	sf::RectangleShape Enemy_Body; //!< Enemy Body Rectangle Shape
	sf::RectangleShape Enemy_Legs; //!< Enemy Legs Rectangle Shape
	sf::RectangleShape Enemy_Arm; //!< Enemy Arm Rectangle Shape
	sf::RectangleShape Enemy_Health; //!< Enemy Health Rectangle Shape
	b2PolygonShape RectangleSensor1; //!< Rectangle sensor Polygon Shape
	b2PolygonShape RectangleSensor2; //!< Rectangle sensor Polygon Shape
	bool right = true;  //!< movement variable
	float Health100;   //!< Health variable
	float newHealth;  //!< Health variable
	float Damage;  //!< Damage variable
	float newHealth100;  //!< Health variable
	int i = 0; //!< i variable
	float velx = 0; //!< velocity x variable
	std::vector<Player*> visibleEnemies; //!< visible enemies vector 
	sf::Vector2f Playerxy; //!< Player x and y variable
	float a = 0;
public:
	bool bullet = true; //!< decisive variable whether to shoot
	int id = 4; //!< id variable for sensor check
	bool m_delete = false; //!< variable to object deletion
	float Health; //!< Health variable
	sf::RectangleShape Sensor1; //!< sensor Shape
	sf::RectangleShape Sensor2; //!< sensor Shape
	EnemyMarkI() {}; //!< Default Constructor
	EnemyMarkI(b2World * world, sf::Vector2f position, sf::Vector2f size, const float orientation); //!< A constructor creating an object and determining its properties
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< drawing function
	void update(sf::Clock Clock);  //!< Update rendering infomation 
	void onAction(); //!< On action function 
	void offAction(); //!< Off action function 
	void HealthLoss(); //!< Health loss function 
	void registerForDeletion();//!< a function that adds an object to the list to be deleted
	bool shouldDelete(); //!< a function that adds an object to the list to be deleted
	void radarAcquiredPlayer(Player* player);//!< function checking if the player is in the field of view
	void radarLostPlayer(Player* player); //!< function checking if the player is in the field of view
	void PlayerPos(sf::Vector2f xy); //!< Player position function
	void BulletDelay(sf::Clock T); //!< Bullet delay
	sf::Vector2f getPosition();
};
	