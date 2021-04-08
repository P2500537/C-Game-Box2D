/*!
\file Player.cpp
*/
#include "Player.h"
Player::Player(b2World * world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation, CollisionFilter type, sf::Texture* Headtexture,sf::Texture* Bodytexture, sf::Texture* Armtexture, sf::Texture* Legtexture)
{
	Health = 100;
	Coins = 0;
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	b2FixtureDef l_fixtureDef2;
	b2Vec2 clickedPoint;
	clickedPoint = b2Vec2(0, 20);
	l_bodyDef.type = b2_dynamicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;

	m_body = world->CreateBody(&l_bodyDef);

	m_body->SetUserData(this); // used by our contact listener

	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	l_fixtureDef.density = 0.0f;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 0.f;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.filter.categoryBits = PhysicalThing::PLAYER;
	l_fixtureDef.filter.maskBits = GREENBOX | Enemy | Colectables | RADAR_SENSOR | ENEMY_BULLET;
	m_body->CreateFixture(&l_fixtureDef);

	Player_Body.setPosition(position);
	Player_Body.setSize(size);
	Player_Body.setOrigin(size * 0.5f);
	Player_Body.setRotation(orientation);
	Player_Body.setOutlineThickness(0.f);
	Player_Body.setTexture(Bodytexture);
	l_shape.SetAsBox((size.x * 0.4f), size.y * 0.3f, b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y-0.18), 0);
	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);

	Player_Head.setPosition(sf::Vector2f(position.x, position.y));
	Player_Head.setSize(sf::Vector2f((size.x * 0.4f), size.y * 0.3f)*2.f);
	Player_Head.setOrigin(sf::Vector2f((size.x * 0.4f), size.y * 0.3f + 0.18f));
	Player_Head.setRotation(orientation);
	Player_Head.setOutlineThickness(0.f);
	Player_Head.setTexture(Headtexture);

	l_shape.SetAsBox((size.x * 0.2f)+0.05f, size.y * 0.15f,b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y),0);
	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);

	Player_Hand.setPosition(sf::Vector2f(position.x, position.y));
	Player_Hand.setSize(sf::Vector2f((size.x * 0.2f) + 0.05f, size.y * 0.15f) * 2.f);
	Player_Hand.setOrigin(sf::Vector2f((size.x * 0.2f) + 0.05f, size.y * 0.15f));
	Player_Hand.setRotation(orientation);
	Player_Hand.setOutlineThickness(0.f);
	Player_Hand.setTexture(Armtexture);

	l_shape.SetAsBox((size.x * 0.3f), size.y * 0.3f, b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y), 0);
	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);


	Player_lLeg.setPosition(sf::Vector2f(position.x, position.y));
	Player_lLeg.setSize(sf::Vector2f((size.x * 0.3f), size.y * 0.3f) * 2.f);
	Player_lLeg.setOrigin(sf::Vector2f((size.x * 0.3f), size.y * 0.3f + 0.05f));
	Player_lLeg.setRotation(orientation);
	Player_lLeg.setOutlineThickness(0.f);
	Player_lLeg.setTexture(Legtexture);
	Player_rLeg.setTextureRect(sf::IntRect(101, 0, 101, 221));
	

	l_shape.SetAsBox((size.x * 0.3f), size.y * 0.3f, b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y + 0.2f), 0);
	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);


	Player_rLeg.setPosition(sf::Vector2f(position.x, position.y));
	Player_rLeg.setSize(sf::Vector2f((size.x * 0.3f), size.y * 0.3f) * 2.f);
	Player_rLeg.setOrigin(sf::Vector2f((size.x * 0.3f), size.y * 0.3f +0.05f));
	Player_rLeg.setRotation(orientation);
	Player_rLeg.setOutlineThickness(0.f);
	Player_rLeg.setTexture(Legtexture);
	Player_lLeg.setTextureRect(sf::IntRect(0, 0, 101, 221));

	Player_Health.setPosition(sf::Vector2f(position.x, position.y));
	Player_Health.setSize(sf::Vector2f(size.x*2.f, size.y *2.f * 0.16f));
	Player_Health.setOrigin(sf::Vector2f(size.x,size.y+0.15f));
	Player_Health.setRotation(orientation);
	Player_Health.setFillColor(sf::Color::Red);
	Health100=Player_Health.getSize().x;

	Damage1 = 10;
	Damage2 = 5;
	newHealth = Health;
}
void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(Player_Body);
	target.draw(Player_Head);
	target.draw(Player_Hand);
	target.draw(Player_lLeg);
	target.draw(Player_rLeg);
	target.draw(Player_Health);
}
void Player::update(sf::Clock Clock)
{
	this->Clock = Clock;
	b2Vec2 pos = m_body->GetPosition();
	Player_Body.setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	Player_Body.setRotation(angle);

	Player_Hand.setPosition(sf::Vector2f(pos.x + 0.1f, pos.y));
	//Ray#
	a=atan2(Player_Hand.getPosition().x-ReyVector.x, Player_Hand.getPosition().y-ReyVector.y);
	a *= RAD2DEG;
	a *= -1;
	a += 90;
	
	Player_Head.setRotation(angle);
	Player_Head.setPosition(pos.x, pos.y);
	Player_Hand.setRotation(a);
	Player_Hand.setPosition(pos.x, pos.y);
	Player_lLeg.setPosition(sf::Vector2f(pos.x, pos.y + 0.25f));
	Player_rLeg.setPosition(sf::Vector2f(pos.x, pos.y + 0.25f));
	Player_lLeg.setRotation(angle);
	Player_rLeg.setRotation(angle);
	Player_Health.setPosition(pos.x, pos.y);
	Player_Health.setRotation(angle);
}

void Player::applyImpulse(b2Vec2 impulse)
{
	
	m_body->ApplyLinearImpulseToCenter(impulse, true);
}
void Player::Step()
{

	
}

bool Player::isStopped() const
{
	return m_stopped;
}

void Player::Move(bool pw,unsigned char key)
{
	b2Vec2 vel = m_body->GetLinearVelocity();
	float desiredVel = 0;
	float desiredjVel = 0;
	float impulse = 0;
	float jimpulse = 0;
	if(!pw)
	{
	switch (key)
	{
	case char('A') :
		moveState = m_LEFT;
	break;
	case char('D') :
		moveState = m_RIGHT;
	break;
	default:
		moveState = m_STOP;
	break;
	}
	switch (moveState)
	{
	case m_LEFT:  desiredVel = b2Max(vel.x - 0.5f, -2.5f); break;
	case m_STOP: desiredVel = vel.x * 0.98f;break;
	case m_RIGHT: desiredVel = b2Min(vel.x + 0.5f, 2.5f); break;
	}
	}
	else
	{
	switch (key)
	{
	case char('A') :
	moveState = m_LEFT;
	break;
	case char('D') :
	moveState = m_RIGHT;
	break;
	default:
	moveState = m_STOP;
	break;
	}
	switch (moveState)
	{
	case m_LEFT:  desiredVel = vel.x -2.5f; break;
	case m_STOP: desiredVel = vel.x * 0.98f; break;
	case m_RIGHT: desiredVel = vel.x + 2.5f; break;
	}

	}


	switch (pw)
	{
	case 1:
	jumpState = j_JUMP;
	break;
	case 0 :
	jumpState = j_STOP;
	break;
	}
	switch (jumpState)
	{
	case j_JUMP:  if (timestamp < Clock.getElapsedTime().asSeconds()) { desiredjVel = 10.5f; break; }
	case j_STOP: desiredjVel = vel.y  * 0.98f; break;
	}

	float velChange = desiredVel - vel.x;
	float jvelChange = desiredjVel - vel.y;
	impulse = m_body->GetMass() * velChange; //<!disregard time factor
	jimpulse = m_body->GetMass() * jvelChange;
	if (pw ==1 && timestamp < Clock.getElapsedTime().asSeconds())
	{
		timestamp = Clock.getElapsedTime().asSeconds() + 1;
	}

	m_body->ApplyLinearImpulseToCenter(b2Vec2(impulse, jimpulse),true);
}

void Player::Transform()
{
	b2Vec2 xy;
	xy.x = ReyVector.x;
	xy.y = ReyVector.y;
	m_body->SetTransform(xy, 0.f);
	
}
void Player::HandRotation(sf::Vector2f xy)
{
	ReyVector = xy;
}

sf::Vector2f Player::getPosition()
{
	return Player_Hand.getPosition();
}
float Player::getHandRotation()
{
	return Player_Hand.getRotation();
}
void Player::addCoins(int addCoins)
{
	Coins += addCoins;
}
void Player::Getkeys(bool W, bool S, bool A, bool D)
{
	this->W = W;
	this->S = S;
	this->D = D;
	this->A = A;

	
	if (this->D)
	{
		if(m_stopped)
		{ 
		Move(this->W, 'D');
		}
		else
		{
		Move(false, 'D');
		}
	}
	if (this->A)
	{
		if (m_stopped)
		{
		Move(this->W, 'A');
		}
		else
		{
		Move(false, 'A');
		}
	}
	if (this->W && m_stopped)
	{
		Move(this->W, 'N');
	}
}
void Player::onAction() {
	m_stopped = true;
}
void Player::offAction() {
	m_stopped = false;
}
void Player::HealthLoss(char enemy)
{
	b2Vec2 vel = m_body->GetLinearVelocity();
	switch (enemy)
	{
	case 'T':
		newHealth = newHealth - Damage1; // Damage when touching an opponent
		m_body->ApplyLinearImpulse(b2Vec2(-vel.x, 0.8f), m_body->GetLocalCenter(), true);
		break;
	case 'B':
		newHealth = newHealth - Damage2; // Damage when touching an bullet
		break;
	default:
		break;
	}

	newHealth100 = (Health100 *newHealth) / Health;
	if (newHealth < 0)
	{
		registerForDeletion();
	}else
	{
	Player_Health.setSize(sf::Vector2f(newHealth100, Player_Health.getSize().y));
	}
	
}
void Player::registerForDeletion()
{
	m_delete = true;
}
bool Player::shouldDelete()
{
	return m_delete;
}