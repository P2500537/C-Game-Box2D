/*!
\file Bullet.cpp
*/
#include "Bullet.h"

Bullet::Bullet(b2World * world, sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, const float orientation, CollisionFilter type)
{
	m_delete = false;
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	l_bodyDef.type = b2_dynamicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;
	l_bodyDef.bullet=true;
	m_body = world->CreateBody(&l_bodyDef);

	m_body->SetBullet(true);
	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;
	l_fixtureDef.filter.categoryBits = type;
	
	l_fixtureDef.filter.maskBits = PhysicalThing::GREENBOX | PhysicalThing::Enemy;//PhysicalThing::
	
	l_fixtureDef.density = 0.0f;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 0.f;

	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);


	Bullet_Body.setPosition(position);
	Bullet_Body.setSize(size);

	Bullet_Body.setOrigin(size*0.5f);
	Bullet_Body.setRotation(orientation);
	Bullet_Body.setOutlineThickness(0.f);
	Bullet_Body.setTexture(texture);
	
	m_body->SetGravityScale(0.1);
	m_body->ApplyLinearImpulse(b2Vec2(cos(orientation*DEG2RAD)*10.f,sin(orientation*DEG2RAD)*10.f), m_body->GetLocalCenter(), true);

}
void Bullet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(Bullet_Body);
}
void Bullet::update()
{

	float orientation = m_body->GetAngle();
	orientation *= RAD2DEG;
	b2Vec2 pos = m_body->GetPosition();
	Bullet_Body.setRotation(orientation);
	Bullet_Body.setPosition(pos.x, pos.y);

}

void Bullet::SetRotation(float rotation)
{
	this->rotation = rotation;
}
void Bullet::onAction() {

	m_delete = true;
}

bool Bullet::shouldDelete()
{
	return m_delete;
}
