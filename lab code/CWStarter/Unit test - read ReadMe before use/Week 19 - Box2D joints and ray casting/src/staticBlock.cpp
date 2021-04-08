/*!
\file staticBlock.cpp
*/

#include "staticBlock.h"

StaticBlock::StaticBlock(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, const float& orientation, CollisionFilter type, sf::Texture* texture)
{
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_staticBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;

	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this); // used by our contact listener

	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;
	l_fixtureDef.filter.categoryBits = PhysicalThing::GREENBOX;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	m_body->CreateFixture(&l_fixtureDef);

	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setOutlineThickness(0.f);
	setTexture(texture);
	texture->setRepeated(true);
	if (size.y> size.x)
	{
		setTextureRect(sf::IntRect(0, 0, 25, 296));
	}
	else{
	setTextureRect(sf::IntRect(0, 0, 296, 20));
	}
	
	
	
	t = type;
	
	
}
