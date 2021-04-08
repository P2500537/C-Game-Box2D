/*!
\file Player.h
*/
/*! \Player Player
\The Player class creates enemies
*/
#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "physicalThing.h"
class Player : public sf::Drawable, public PhysicalThing
{
private:
	int Coins; //!< Coins variable
	bool m_stopped = false; //!< jump variable
	sf::RectangleShape Player_Body; //!< Player Body Rectangle Shape
	sf::RectangleShape Player_Head;//!< Player Head Rectangle Shape
	sf::RectangleShape Player_Hand;//!< Player Hand Rectangle Shape
	sf::RectangleShape Player_lLeg;//!< Player lLeg Rectangle Shape
	sf::RectangleShape Player_rLeg;//!< Player rLeg Rectangle Shape
	sf::RectangleShape Player_Health;//!< Player Health Rectangle Shape
	sf::Clock Clock; //!< Clock variable
	float timestamp; //!< timestamp variable
	int Health; //!< Health variable
	float Health100; //!< Health variable
	float newHealth; //!< Health variable
	float Damage1; //!< Damage variable
	float Damage2; //!< Damage variable
	float newHealth100; //!< Health variable
public:
	bool m_delete = false;
	Player() {}; //!< Default Constructor
	Player(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation, CollisionFilter type, sf::Texture* Headtexture, sf::Texture* Bodytexture, sf::Texture* Armtexture, sf::Texture* Legtexture); //!< Complete contructor
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void update(sf::Clock Clock); //!< Update rendering infomation 
	void applyImpulse(b2Vec2 impulse);
	bool isStopped() const;
	void Step();
	enum m_moveState {m_STOP, m_LEFT,m_RIGHT};
	enum m_jumpState { j_STOP, j_JUMP };
	m_moveState moveState;
	m_jumpState  jumpState;
	void Move(bool pw, unsigned char key);
	void onAction();
	void offAction();
	void Transform();
	//Ray 
	sf::Vector2f getPosition();
	float getHandRotation();
	void Player::HandRotation(sf::Vector2f xy);
	sf::Vector2f ReyVector;
	float a;
	float m_HandRotation;
	//coins
	void addCoins(int addCoins);
	bool W;
	bool S;
	bool D;
	bool A;
	void Getkeys(bool W, bool S, bool A, bool D);
	void HealthLoss(char enemy);
	void registerForDeletion();
	bool shouldDelete();
};

