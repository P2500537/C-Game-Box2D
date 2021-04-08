/*!
\file EnemyMarkI.cpp
*/
#include "EnemyMarkI.h"
EnemyMarkI::EnemyMarkI(b2World * world, sf::Vector2f position, sf::Vector2f size, const float orientation)
{

	Health = 100;
	m_type = 'R';
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	l_bodyDef.type = b2_dynamicBody;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;


	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this); // used by our contact listener

	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;
	l_fixtureDef.filter.categoryBits = PhysicalThing::Enemy;
	l_fixtureDef.filter.maskBits = PhysicalThing::GREENBOX | PhysicalThing::PLAYER | PhysicalThing::BULLET | PhysicalThing::Enemy_SENSOR;
	l_fixtureDef.density = 0.f;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 0.f;
	l_fixtureDef.shape = &l_shape;


	m_body->CreateFixture(&l_fixtureDef);

	Enemy_Body.setPosition(position);
	Enemy_Body.setSize(size);
	Enemy_Body.setOrigin(size * 0.5f);
	Enemy_Body.setRotation(orientation);
	Enemy_Body.setOutlineThickness(0.f);
	Enemy_Body.setFillColor(sf::Color::Cyan);
	// Arm
	l_shape.SetAsBox(size.x / 2.f / 2.f + 0.05f, size.y / 2.f / 4.f, b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y), 0.f);
	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);
	Enemy_Arm.setPosition(sf::Vector2f(position.x, position.y));
	Enemy_Arm.setSize(sf::Vector2f(size.x / 2.f + 0.05f, size.y / 4.f));
	Enemy_Arm.setOrigin(sf::Vector2f(Enemy_Arm.getGlobalBounds().width*0.5f, Enemy_Arm.getGlobalBounds().height*0.5f));

	Enemy_Arm.setRotation(orientation);
	Enemy_Arm.setOutlineThickness(0.f);
	Enemy_Arm.setFillColor(sf::Color::Blue);
	// Legs

	l_shape.SetAsBox(size.x, size.y * 0.16f, b2Vec2(m_body->GetLocalCenter().x, m_body->GetLocalCenter().y + 0.17f), 0);
	l_fixtureDef.shape = &l_shape;
	m_body->CreateFixture(&l_fixtureDef);


	Enemy_Legs.setPosition(position);
	Enemy_Legs.setSize(sf::Vector2f(size.x*2.f, size.y *2.f * 0.16f));
	Enemy_Legs.setOrigin(sf::Vector2f(Enemy_Legs.getGlobalBounds().width*0.5f, Enemy_Legs.getGlobalBounds().height*0.5f - 0.17f));

	Enemy_Legs.setRotation(orientation);
	Enemy_Legs.setOutlineThickness(0.f);
	Enemy_Legs.setFillColor(sf::Color::Black);


	RectangleSensor1.SetAsBox(size.x *20.f, size.y *3.f,b2Vec2(Enemy_Body.getGlobalBounds().width * 0.5f, Enemy_Body.getGlobalBounds().height*0.5f-0.5f), 0.f);
	l_fixtureDef.shape = &RectangleSensor1;
	l_fixtureDef.isSensor = true;
	l_fixtureDef.filter.categoryBits = RADAR_SENSOR;
	l_fixtureDef.filter.maskBits = PLAYER;
	m_body->CreateFixture(&l_fixtureDef);
	
	
	Enemy_Health.setPosition(sf::Vector2f(position.x, position.y));
	Enemy_Health.setSize(sf::Vector2f(size.x*2.f, size.y *2.f * 0.16f));
	Enemy_Health.setOrigin(sf::Vector2f(size.x, size.y + 0.10f));
	Enemy_Health.setRotation(orientation);
	Enemy_Health.setFillColor(sf::Color::Red);

	Health100 = Enemy_Health.getSize().x;

	Damage = 10;
	newHealth = Health;
}
void EnemyMarkI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
		target.draw(Enemy_Body);
		target.draw(Enemy_Arm);
		target.draw(Enemy_Legs);
		target.draw(Sensor1);
		target.draw(Sensor2);
		target.draw(Enemy_Health);
	
}
void EnemyMarkI::update(sf::Clock Clock)
{
	this->Clock = Clock.getElapsedTime().asSeconds();
	
	b2Vec2 vel = m_body->GetLinearVelocity();
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle()* RAD2DEG;
	float impulse = 0;
	
	if (visibleEnemies.size() > 0)
	{
		a = atan2(Enemy_Arm.getPosition().x - Playerxy.x , Enemy_Arm.getPosition().y - Playerxy.y );
		a *= RAD2DEG;
		a *= -1;
		a += 90;
	}


	Enemy_Body.setRotation(angle);
	Enemy_Body.setPosition(pos.x, pos.y);
	Enemy_Arm.setRotation(a);
	Enemy_Arm.setPosition(pos.x, pos.y);
	Enemy_Legs.setPosition(sf::Vector2f(pos.x, pos.y));
	Enemy_Legs.setRotation(angle);
	Sensor1.setRotation(angle);
	Sensor1.setPosition(pos.x, pos.y);
	Sensor2.setRotation(angle);
	Sensor2.setPosition(pos.x, pos.y);
	Enemy_Health.setRotation(angle);
	Enemy_Health.setPosition(pos.x, pos.y);
	
	if (i == 0)
	{
		timestamp = this->Clock + 1;
		i++;
	}

	if (BulletTimestamp < this->Clock && visibleEnemies.size() > 0)
	{
		bullet = true;
	}
	else
	{
		bullet = false;
	}

	if (timestamp < this->Clock)
	{
		if (right)
		{
			velx = b2Min(vel.x + 0.5f, 2.5f);
		}
		else
		{
			velx = b2Max(vel.x - 0.5f, -2.5f);
		}
		float velChange = velx - vel.x;
		impulse = m_body->GetMass() * velChange;
		m_body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
	}

	
}

void EnemyMarkI::onAction() {
	right = !right;
}
void EnemyMarkI::offAction() {
	right = true;
}
void EnemyMarkI::HealthLoss()
{
	newHealth = newHealth - Damage;
	newHealth100 = (Health100 *newHealth) / Health;
	Enemy_Health.setSize(sf::Vector2f(newHealth100, Enemy_Health.getSize().y));
	if (newHealth <= 0)
	{
		registerForDeletion();
	}
}
void EnemyMarkI::registerForDeletion()
{
	m_delete = true;
}
bool EnemyMarkI::shouldDelete()
{
	return m_delete;
}
void EnemyMarkI::radarAcquiredPlayer(Player* player) 
{
	visibleEnemies.push_back(player);
}
void EnemyMarkI::radarLostPlayer(Player* player) 
{
	visibleEnemies.erase(std::find(visibleEnemies.begin(), visibleEnemies.end(), player));
}
void EnemyMarkI::PlayerPos(sf::Vector2f xy)
{
	Playerxy = xy;
}

void EnemyMarkI::BulletDelay(sf::Clock T)
{
	BulletTimestamp = T.getElapsedTime().asSeconds() + 2;
}
sf::Vector2f EnemyMarkI::getPosition()
{
	return Enemy_Arm.getPosition();
}