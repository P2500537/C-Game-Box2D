/*!
\file KinematicBlock.cpp
*/
#include "KinematicBlock.h"
KinematicBlock::KinematicBlock(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, float range, char VorH, CollisionFilter type, sf::Texture* texture)
{
	this->VorH = VorH; // vertical or horizontal movement
	firstposition = position;
	lastposition = firstposition;
	lastposition.x += range;
	lastposition.y += range;

	orientation = 0.f;
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	l_bodyDef.type = b2_kinematicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;


	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this); // used by our contact listener;

	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;
	l_fixtureDef.filter.categoryBits = PhysicalThing::GREENBOX;

	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;
	l_fixtureDef.shape = &l_shape;

	m_body->CreateFixture(&l_fixtureDef);

	Kinematic_Body.setPosition(position);
	Kinematic_Body.setSize(size);
	Kinematic_Body.setOrigin(size * 0.5f);
	Kinematic_Body.setRotation(orientation);
	Kinematic_Body.setOutlineThickness(0.f);

	Kinematic_Body.setTexture(texture);
	texture->setRepeated(true);
	if (size.y > size.x)
	{
		Kinematic_Body.setTextureRect(sf::IntRect(0, 0, 25, 296));
	}
	else {
		Kinematic_Body.setTextureRect(sf::IntRect(0, 0, 296, 20));
	}
	

	l_fixtureDef.shape = &RectangleSensor;
	l_fixtureDef.isSensor = true;
	l_fixtureDef.filter.categoryBits = Player_SENSOR;
	l_fixtureDef.filter.maskBits = PLAYER;//radar only collides with PLAYER
	m_body->CreateFixture(&l_fixtureDef);
	Kinematic_BodySensor.setPosition(position);
	Kinematic_BodySensor.setSize(size);
	Kinematic_BodySensor.setOrigin(size.x * 0.5f,size.y * 0.5f );
	Kinematic_BodySensor.setRotation(orientation);
	Kinematic_BodySensor.setOutlineThickness(0.f);
	Kinematic_BodySensor.setFillColor(sf::Color::Transparent);
	
}
void KinematicBlock::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(Kinematic_Body);
	target.draw(Kinematic_BodySensor);
}
void KinematicBlock::update()
{
	int velx = 0;
	b2Vec2 pos = m_body->GetPosition();
	//std::cout <<"body " <<m_body->GetPosition().x << std::endl;
	Kinematic_Body.setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	Kinematic_Body.setRotation(angle);
	Kinematic_BodySensor.setPosition(pos.x, pos.y);
	Kinematic_BodySensor.setRotation(angle);
	//std::cout << "kinematic " <<Kinematic_Body.getPosition().x << std::endl;
	if(VorH =='H')
	{ 
	if (pos.x >= lastposition.x)
	{
		right = false;
	}
	else if (pos.x <= firstposition.x-0.1f)
	{
		right = true;
	}
	if (right)
	{
		velx = 1;
	}
	else
	{
		velx = -1;
	}
	m_body->SetLinearVelocity(b2Vec2(velx, 0));
	}
	else {
		if (pos.y >= lastposition.y)
		{
			right = false;
		}
		else if (pos.y <= firstposition.y - 0.1f)
		{
			right = true;
		}
		if (right)
		{
			velx = 1;
		}
		else
		{
			velx = -1;
		}
		m_body->SetLinearVelocity(b2Vec2(0, velx));
	}
}
void KinematicBlock::updateTexture(sf::Texture* texture) {
	Kinematic_Body.setTexture(texture);
}
void KinematicBlock::onAction()
{
	right = !right;
}