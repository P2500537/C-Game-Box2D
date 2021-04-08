#pragma once

/*!
\file BlockPlayerContactListener.h
*/

#include <Box2D\Box2D.h>
#include "Player.h"
#include "EnemyMarkI.h"
#include "staticBlock.h"
#include "staticSensor.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "KinematicBlock.h"
/*! \class BlockPlayerContactListener
\brief A listener which listens for contacts between game objects
*/
class BlockPlayerContactListener : public b2ContactListener
{
public:
	int numFootContacts; //!< Number of foot contacts 
	void BeginContact(b2Contact* contact); //!< Called when two fixtures begin to touch
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to touch

};