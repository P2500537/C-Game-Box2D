#pragma once

/*!
\file physicalThing.h
*/

#include <Box2D/Box2D.h>

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

/*!
\class PhysicalThing
\brief A simple class with common attributes and a few values used in a few places. 
*/
class PhysicalThing {
protected:
	b2Body * m_body = nullptr; //!< Box2D body, no need to delete this as BOX2D will look after it
	float mk_fDensity = 1.0f; //!< Density of the material - used to give mass
	float mk_fFriction = 0.4f; //!< Friction - I guess this is only friction from movement, not when static
	float mk_fRestitution = 0.4f; //!< Restitution - bouncyness of stuff
public:
	void destroyBody() { b2World* w = m_body->GetWorld(); w->DestroyBody(m_body); }; //!< function for destroying a body 
	enum CollisionFilter { Player_SENSOR = 1, GREENBOX = 2, Enemy_SENSOR = 4, Colectables = 8, Enemy = 16, PLAYER = 32, BULLET = 64, RADAR_SENSOR = 128, ENEMY_BULLET = 256}; //!< Enums for collision filtering - hex values converted to decimal for the enum
	void setUserData(void* data) { m_body->SetUserData(data); }; //!< Set the userdata of the body
};
