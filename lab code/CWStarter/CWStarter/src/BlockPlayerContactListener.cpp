/*!
\file BlockPlayerContactListener.cpp
*/
#include "BlockPlayerContactListener.h"

void BlockPlayerContactListener::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	std::pair<std::string, void *> dataA = *(std::pair<std::string, void *>*) bodyA->GetUserData();
	std::pair<std::string, void *> dataB = *(std::pair<std::string, void *>*) bodyB->GetUserData();

//staticSensor
	bool isSensorA = contact->GetFixtureA()->IsSensor();
	bool isSensorB = contact->GetFixtureB()->IsSensor();

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();


	

	if (isSensorA)
	{
		if (typeid(Player).name() == dataB.first)
		{
			StaticSensor * sensor = static_cast<StaticSensor *>(dataA.second);
			if (sensor->id == 1 || sensor->id == 2)
			{
				sensor->onAction();
			}else
			{
				EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataA.second);
				Player * player = static_cast<Player*>(dataB.second);
				enemy->radarAcquiredPlayer(player);

			}
		
			return;
		}
		if (typeid(EnemyMarkI).name() == dataB.first)
		{
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataB.second);
			enemy->onAction();

		}

	}

	if (isSensorB)
	{
		if (typeid(Player).name() == dataA.first)
		{
			StaticSensor * sensor = static_cast<StaticSensor*>(dataB.second);
			if (sensor->id == 1 || sensor->id == 2)
			{
			sensor->onAction();
			}
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataB.second);
			if (enemy->id == 4)
			{
				Player * player = static_cast<Player*>(dataA.second);
				enemy->radarAcquiredPlayer(player);

			}
			return;
		}
		if (typeid(EnemyMarkI).name() == dataA.first)
		{
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataA.second);
			enemy->onAction();

		}

	}
	if (typeid(Bullet).name() == dataA.first)
	{
		Bullet* bullet = static_cast<Bullet*>(dataA.second);
		bullet->onAction();
		
		if (typeid(EnemyMarkI).name() == dataB.first)
		{
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataB.second);
			enemy->HealthLoss();

		}
	}

	if (typeid(Bullet).name() == dataB.first)
	{
		Bullet * bullet = static_cast<Bullet*>(dataB.second);
		bullet->onAction();
		if (typeid(EnemyMarkI).name() == dataA.first)
		{
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataA.second);
			enemy->HealthLoss();

		}

	}

	if (typeid(EnemyBullet).name() == dataA.first)
	{
		EnemyBullet* bullet = static_cast<EnemyBullet*>(dataA.second);
		bullet->onAction();
		if (typeid(Player).name() == dataB.first)
		{
			Player * player = static_cast<Player*>(dataB.second);
			player->HealthLoss('B');
		}
	}

	if (typeid(EnemyBullet).name() == dataB.first)
	{
		EnemyBullet * bullet = static_cast<EnemyBullet*>(dataB.second);
		bullet->onAction();
		if (typeid(Player).name() == dataA.first)
		{
			Player * player = static_cast<Player*>(dataA.second);
			player->HealthLoss('B');
		}
	}

	if (typeid(StaticBlock).name() == dataA.first)
	{
		if (typeid(Player).name() == dataB.first)
		{
			StaticBlock * block = static_cast<StaticBlock*>(dataA.second);
			Player * player = static_cast<Player*>(dataB.second);
			player->onAction();
		}
	}

	if (typeid(StaticBlock).name() == dataB.first)
	{
		if (typeid(Player).name() == dataA.first)
		{
			StaticBlock * block = static_cast<StaticBlock*>(dataB.second);

			Player * player = static_cast<Player*>(dataA.second);
			player->onAction();
		}
	}


	if (typeid(KinematicBlock).name() == dataA.first)
	{
		if (typeid(Player).name() == dataB.first)
		{
			KinematicBlock * block = static_cast<KinematicBlock*>(dataA.second);

			Player * player = static_cast<Player*>(dataB.second);
			player->onAction();
		}
	}

	if (typeid(KinematicBlock).name() == dataB.first)
	{
		if (typeid(Player).name() == dataA.first)
		{
			KinematicBlock * block = static_cast<KinematicBlock*>(dataB.second);

			Player * player = static_cast<Player*>(dataA.second);
			player->onAction();
		}
	}
	
	if (typeid(EnemyMarkI).name() == dataA.first)
	{
		
		if (typeid(Player).name() == dataB.first)
		{
			Player * player = static_cast<Player*>(dataB.second);
			player->HealthLoss('T');

		}
		if (typeid(StaticBlock).name() == dataB.first)
		{
			StaticBlock * block = static_cast<StaticBlock*>(dataB.second);

		}
	}
	if (typeid(EnemyMarkI).name() == dataB.first)
	{
		if (isSensorB)
		{
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataA.second);
			enemy->onAction();

		}
		if (typeid(Player).name() == dataA.first)
		{
			Player * player = static_cast<Player*>(dataA.second);
			player->HealthLoss('T');

		}
		if (typeid(StaticBlock).name() == dataA.first)
		{
			StaticBlock * block = static_cast<StaticBlock*>(dataA.second);
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataA.second);
			enemy->Sensor2;

		}
	}
	
	numFootContacts++;
}

void BlockPlayerContactListener::EndContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	std::pair<std::string, void *> dataA = *(std::pair<std::string, void *>*) bodyA->GetUserData();
	std::pair<std::string, void *> dataB = *(std::pair<std::string, void *>*) bodyB->GetUserData();

//staticSensor
	bool isSensorA = contact->GetFixtureA()->IsSensor();
	bool isSensorB = contact->GetFixtureB()->IsSensor();

	if (isSensorA)
	{
		if (typeid(Player).name() == dataB.first)
		{
			StaticSensor * sensor = static_cast<StaticSensor *>(dataA.second);
			if (sensor->id == 1 || sensor->id == 2)
			{
				sensor->onAction();
			}
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataB.second);
			if (enemy->id == 4)
			{
				Player * player = static_cast<Player*>(dataB.second);
				enemy->radarLostPlayer(player);

			}
			return;
		}
		if (typeid(EnemyMarkI).name() == dataB.first)
		{
			EnemyMarkI * Enemy = static_cast<EnemyMarkI *>(dataB.second);

			return;
		}
	}

	if (isSensorB)
	{
		if (typeid(Player).name() == dataA.first)
		{
			StaticSensor * sensor = static_cast<StaticSensor*>(dataB.second);
			if (sensor->id == 1 || sensor->id == 2)
			{
				sensor->onAction();
			}
			EnemyMarkI * enemy = static_cast<EnemyMarkI*>(dataB.second);
			if(enemy->id==4)
			{
				Player * player = static_cast<Player*>(dataA.second);
				enemy->radarLostPlayer(player);

			}
			return;
		}
		if (typeid(EnemyMarkI).name() == dataA.first)
		{
			EnemyMarkI * Enemy = static_cast<EnemyMarkI *>(dataA.second);

			return;
		}
	}
	

	if (typeid(StaticBlock).name() == dataA.first)
	{
		if (typeid(Player).name() == dataB.first)
		{
			StaticBlock * block = static_cast<StaticBlock*>(dataA.second);

			Player * player = static_cast<Player*>(dataB.second);
			player->offAction();
		}
	
	}

	if (typeid(StaticBlock).name() == dataB.first)
	{
		if (typeid(Player).name() == dataA.first)
		{
			StaticBlock * block = static_cast<StaticBlock*>(dataB.second);

			Player * player = static_cast<Player*>(dataA.second);
			player->offAction();
		}
	
	}


	if (typeid(KinematicBlock).name() == dataA.first)
	{
		if (typeid(Player).name() == dataB.first)
		{
			KinematicBlock * block = static_cast<KinematicBlock*>(dataA.second);

			Player * player = static_cast<Player*>(dataB.second);
			player->offAction();
		}
	}

	if (typeid(KinematicBlock).name() == dataB.first)
	{
		if (typeid(Player).name() == dataA.first)
		{
			KinematicBlock * block = static_cast<KinematicBlock*>(dataB.second);

			Player * player = static_cast<Player*>(dataA.second);
			player->offAction();
		}
	}
	if (typeid(EnemyMarkI).name() == dataA.first)
	{
		
		if (typeid(Player).name() == dataB.first)
		{
			Player * player = static_cast<Player*>(dataB.second);
		
		}
		if (typeid(StaticBlock).name() == dataB.first)
		{
			StaticBlock * block = static_cast<StaticBlock*>(dataB.second);

		}
	}
	if (typeid(EnemyMarkI).name() == dataB.first)
	{
		
		if (typeid(Player).name() == dataA.first)
		{
			Player * player = static_cast<Player*>(dataA.second);

		}
		if (typeid(StaticBlock).name() == dataA.first)
		{
			StaticBlock * block = static_cast<StaticBlock*>(dataA.second);

		}
	}
	numFootContacts--;
}
