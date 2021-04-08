/*!
\file game.cpp
*/
#include "game.h"

Game::Game()
{
	m_mainView.setCenter(0.f, 0.f);
	m_mainView.setSize(m_worldSize);
	m_mainView.setViewport(sf::FloatRect(0,0,1,0.75));

	m_HudView.setCenter(8.f, 0.f);
	m_HudView.setSize(sf::Vector2f(24,6));
	m_HudView.setViewport(sf::FloatRect(0, 0.75, 1, 0.25));


	m_pWorld = new b2World(mk_gravity);
	m_debugDraw.setWorld(m_pWorld);

	
	t_Background.loadFromFile("./assets/textures/Background.jpg");
	if (!t_Background.loadFromFile("./assets/textures/Background.jpg"))
	{
	}
	s_Background.setOrigin(sf::Vector2f(4.f,3.f));
	s_Background.setSize(m_worldSize);
	s_Background.setTexture(&t_Background);
	s_Background2.setOrigin(sf::Vector2f(-4.f, 3.f));
	s_Background2.setSize(sf::Vector2f(16.f, 6.f));
	s_Background2.setTexture(&t_Background);
	GameOver.loadFromFile("./assets/textures/GO.png");
	s_GO.setOrigin(sf::Vector2f(4.f, 1.f));
	s_GO.setSize(sf::Vector2f(8.f, 2.f));
	s_GO.setTexture(&GameOver);
	Congrats.loadFromFile("./assets/textures/Congratulations.png");
	s_CO.setOrigin(sf::Vector2f(4.f, 1.f));
	s_CO.setSize(sf::Vector2f(8.f, 2.f));
	s_CO.setTexture(&Congrats);
	Vault.loadFromFile("./assets/textures/Vault.png");
	victory = Win(m_pWorld, sf::Vector2f(3.4f, -2.4f), sf::Vector2f(0.5f, 0.5f), 0.f, &Vault);
	victory.setUserData(new std::pair<std::string, void *>(typeid(decltype(victory)).name(), &victory));

	H_Hud = Hud(m_pWorld);
	m_staticBlocks.resize(9);
	m_staticBlocks[0] = StaticBlock(m_pWorld, sf::Vector2f(0.0f, -2.85f), sf::Vector2f(8.0f, 0.30f), 0.f, PhysicalThing::CollisionFilter::GREENBOX,&t_Background);
	m_staticBlocks[1] = StaticBlock(m_pWorld, sf::Vector2f(3.85f, 0.0f), sf::Vector2f(0.30f, 6.0f), 0.f, PhysicalThing::CollisionFilter::GREENBOX, &t_Background);
	m_staticBlocks[2] = StaticBlock(m_pWorld, sf::Vector2f(0.f, 2.85f), sf::Vector2f(8.0f, 0.30f), 0.f, PhysicalThing::CollisionFilter::GREENBOX, &t_Background);
	m_staticBlocks[3] = StaticBlock(m_pWorld, sf::Vector2f(-3.85f, 0.0f), sf::Vector2f(0.30f, 6.0f), 0.f, PhysicalThing::CollisionFilter::GREENBOX, &t_Background);

	m_staticBlocks[4] = StaticBlock(m_pWorld, sf::Vector2f(-2.0f, 2.0f), sf::Vector2f(2.0f, 0.30f), 0.f, PhysicalThing::CollisionFilter::GREENBOX, &t_Background);
	m_staticBlocks[5] = StaticBlock(m_pWorld, sf::Vector2f(-0.75f, 0.4f), sf::Vector2f(6.45f, 0.30f), 0.f, PhysicalThing::CollisionFilter::GREENBOX, &t_Background);

	m_staticBlocks[6] = StaticBlock(m_pWorld, sf::Vector2f(0.75f, -1.2f), sf::Vector2f(6.45f, 0.30f), 0.f, PhysicalThing::CollisionFilter::GREENBOX, &t_Background);
	m_staticBlocks[7] = StaticBlock(m_pWorld, sf::Vector2f(-3.0f, -0.6f), sf::Vector2f(1.5f, 0.25f), 30.f, PhysicalThing::CollisionFilter::GREENBOX, &t_Background);
	m_staticBlocks[8] = StaticBlock(m_pWorld, sf::Vector2f(2.0f, -1.9f), sf::Vector2f(4.45f, 0.30f), 0.f, PhysicalThing::CollisionFilter::GREENBOX, &t_Background);

	m_kinematicBlocks.push_back(KinematicBlock(m_pWorld, sf::Vector2f(0.15f, 1.7f), sf::Vector2f(2.0f, 0.30f), 1.35f,'H', PhysicalThing::CollisionFilter::GREENBOX,&t_Background));
	m_kinematicBlocks.push_back(KinematicBlock(m_pWorld, sf::Vector2f(3.f, 0.4f), sf::Vector2f(1.5f, 0.30f), 1.35f, 'V', PhysicalThing::CollisionFilter::GREENBOX, &t_Background));
	for(KinematicBlock& block : m_kinematicBlocks) block.setUserData(new std::pair<std::string, void *>(typeid(decltype(block)).name(), &block));

	m_blockDirection = 0.0f;

	T_Head.loadFromFile("./assets/textures/Head2.png");
	T_Body.loadFromFile("./assets/textures/Body.png");
	T_Arm.loadFromFile("./assets/textures/Arm2.png");
	T_Legs.loadFromFile("./assets/textures/Legs.png");
	m_PlayerOne = Player(m_pWorld, sf::Vector2f(3.0f, 2.0f), sf::Vector2f(0.20f, 0.25f), m_blockDirection, PhysicalThing::CollisionFilter::PLAYER, &T_Head,&T_Body,&T_Arm,&T_Legs);
	m_ray = Ray(m_pWorld, 20.f, sf::Color::Magenta);
	

	if (!m_ChestTexture.loadFromFile("./assets/textures/c_chest.png"))
	{
	}
	m_chests.resize(2);
	m_chests[0] = StaticBoxSensor(m_pWorld, sf::Vector2f(-3.50f, 0.1f), sf::Vector2f(0.35f, 0.35f), 0.f, &m_ChestTexture);
	m_chests[1] = StaticBoxSensor(m_pWorld, sf::Vector2f(3.5f, -1.5f), sf::Vector2f(0.35f, 0.35f), 0.f, &m_ChestTexture);
	for (StaticBoxSensor& sensor : m_chests) sensor.setUserData(new std::pair<std::string, void *>(typeid(decltype(sensor)).name(), &sensor));

	if (!m_CoinTexture.loadFromFile("./assets/textures/coin.png"))
	{
	}

	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-1.f, 2.50f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-1.5f, 2.50f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-2.f, 2.50f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-2.5f, 2.50f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-3.f, 2.50f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-3.5f, 2.f), 0.15f, &m_CoinTexture));

	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-1.55f, 1.65f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-2.05f, 1.65f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-2.55f, 1.65f), 0.15f, &m_CoinTexture));

	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(2.3f, 0.f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(1.8f, -0.5f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(1.30f, 0.0f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(0.80f, -0.5f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(0.30f, 0.0f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-0.20f, -0.5f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-0.70f, 0.f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-1.20f, -0.5f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-1.70f, 0.f), 0.15f, &m_CoinTexture));

	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-3.50f, -2.5f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-2.0f, -1.6f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-1.50f, -2.5f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-1.0f, -1.6f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(-0.5f, -2.5f), 0.15f, &m_CoinTexture));
	m_coins.push_back(Coins(m_pWorld, sf::Vector2f(0.0f, -1.6f), 0.15f, &m_CoinTexture));
	for (Coins& coin : m_coins) coin.setUserData(new std::pair<std::string, void *>(typeid(decltype(coin)).name(), &coin));

	if (!m_BulletTexture.loadFromFile("./assets/textures/Bullets.png"))
	{
	}
	 

	m_esensor.push_back(EnemySensor(m_pWorld, sf::Vector2f(2.3f, 0.f), sf::Vector2f(0.10f, 0.35f), 0.f));
	m_esensor.push_back(EnemySensor(m_pWorld, sf::Vector2f(-3.5f, 0.f), sf::Vector2f(0.10f, 0.35f), 0.f));

	m_esensor.push_back(EnemySensor(m_pWorld, sf::Vector2f(-2.0f, -1.6f), sf::Vector2f(0.10f, 0.35f), 0.f));
	m_esensor.push_back(EnemySensor(m_pWorld, sf::Vector2f(3.0f, -1.6f), sf::Vector2f(0.10f, 0.35f), 0.f));

	m_esensor.push_back(EnemySensor(m_pWorld, sf::Vector2f(0.f, -2.3f), sf::Vector2f(0.10f, 0.35f), 0.f));
	m_esensor.push_back(EnemySensor(m_pWorld, sf::Vector2f(2.0f, -2.3f), sf::Vector2f(0.10f, 0.35f), 0.f));
	for (EnemySensor& sensor : m_esensor) sensor.setUserData(new std::pair<std::string, void *>(typeid(decltype(sensor)).name(), &sensor));


	m_Enemy.push_back( EnemyMarkI(m_pWorld, sf::Vector2f(0.5f, -0.2f), sf::Vector2f(0.20f, 0.25f), 0.f));
	m_Enemy.push_back(EnemyMarkI(m_pWorld, sf::Vector2f(-1.0f, -1.8f), sf::Vector2f(0.20f, 0.25f), 0.f));
	m_Enemy.push_back(EnemyMarkI(m_pWorld, sf::Vector2f(0.5f, -2.8f), sf::Vector2f(0.20f, 0.25f), 0.f));
	for (EnemyMarkI& enemy : m_Enemy) enemy.setUserData(new std::pair<std::string, void *>(typeid(decltype(enemy)).name(), &enemy));
	

	for (StaticBlock& block : m_staticBlocks) block.setUserData(new std::pair<std::string, void *>(typeid(decltype(block)).name(), &block));
	m_PlayerOne.setUserData(new std::pair<std::string, void *>(typeid(decltype(m_PlayerOne)).name(), &m_PlayerOne));
	m_pWorld->SetContactListener(&m_listener);
}

Game::~Game()
{
	// Iterator all data strucuter destorying bodies
	for (auto& b : m_staticBlocks) b.destroyBody();
	m_PlayerOne.destroyBody();
	for (auto& b : m_chests) b.destroyBody();
	for (auto& b : m_coins) b.destroyBody();
	for (auto& b : m_Enemy) b.destroyBody();
	for (auto& b : m_esensor) b.destroyBody();
	for (auto& b : m_kinematicBlocks) b.destroyBody();

	delete m_pWorld;
	m_pWorld = nullptr;
}

void Game::update(float timestep)
{
	// Update the world
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);
	//Update each dynamic element
	
	
	if (!stop && !victory.win )
	{

	//--------------------------------Player-----------------------------------
	m_PlayerOne.update(clock);
	m_ray.setDirection(m_Direction);
	m_ray.cast(m_PlayerOne.getPosition());
	m_PlayerOne.HandRotation(m_Direction);
	if (m_PlayerOne.m_delete)
	{
		stop = true;
	}
	
	
	//--------------------------------Player-----------------------------------
	for (auto &block : m_kinematicBlocks) {
		block.update();
	}
	//--------------------------------Coins-----------------------------------
	for (auto &it : m_coins)
	{
		if (it.m_delete)
		{
			Collectedcoins++;
			std::cout << "Collected:" << Collectedcoins << std::endl;
			
		}
	}
	int i = 0;
	for (auto it = m_coins.begin(); it != m_coins.end(); ++it)
	{
		if (it->shouldDelete())
		{
			it->destroyBody();
			m_coins.erase(it);

			break;
			i++;
		}
	}
	for (int j = i; j < m_coins.size(); j++)
	{
		m_coins.at(j).setUserData(new std::pair<std::string, void *>(typeid(Bullet).name(), &m_coins.at(j)));
	}
	//--------------------------------Coins-----------------------------------
	//--------------------------------Bullets---------------------------------
	for (auto &bullet : m_Bullets) {
		bullet.update();
	}
	i = 0;
	for (auto it = m_Bullets.begin(); it != m_Bullets.end(); ++it)
	{

		if (it->shouldDelete())
		{
			it->destroyBody();
			m_Bullets.erase(it);

			break;
			i++;
		}
	}
	
	for (int j = i; j < m_Bullets.size(); j++)
	{
		m_Bullets.at(j).setUserData(new std::pair<std::string, void *>(typeid(Bullet).name(), &m_Bullets.at(j)));
	}
	
	//--------------------------------Bullets---------------------------------
	//--------------------------------Enemy---------------------------------
	for (auto &block : m_Enemy) {
		block.update(clock);
		block.PlayerPos(m_PlayerOne.getPosition());
		if (block.bullet)
		{
			sf::Vector2f bulletDirection = m_PlayerOne.getPosition() - block.getPosition();
			float angle = atan2f(bulletDirection.y, bulletDirection.x);
			angle = angle * RAD2DEG;
			m_EBullets.push_back(EnemyBullet(m_pWorld, sf::Vector2f(block.getPosition()), sf::Vector2f(0.2f, 0.1f), &m_BulletTexture, angle, PhysicalThing::CollisionFilter::ENEMY_BULLET));
			m_EBullets.at(m_EBullets.size() - 1).setUserData(new std::pair<std::string, void *>(typeid(EnemyBullet).name(), &m_EBullets.at(m_EBullets.size() - 1)));
			block.BulletDelay(clock);
		}
	}

	for (auto &it : m_Enemy)
	{
		if (it.m_delete)
		{
			Collectedcoins+=10;
			std::cout << "+10 coins (for killing an enemy)" << Collectedcoins << std::endl;

		}
	}
	i = 0;
	for (auto it = m_Enemy.begin(); it != m_Enemy.end(); ++it)
	{
		if (it->shouldDelete())
		{
			it->destroyBody();
			m_Enemy.erase(it);

			break;
			i++;
		}
	}
	for (int j = i; j < m_Enemy.size(); j++)
	{
		m_Enemy.at(j).setUserData(new std::pair<std::string, void *>(typeid(EnemyMarkI).name(), &m_Enemy.at(j)));
	}
	//--------------------------------Enemy---------------------------------
	//--------------------------------Enemy Bullets---------------------------------
	for (auto &bullet : m_EBullets) {
		bullet.update();
	}
	i = 0;
	for (auto it = m_EBullets.begin(); it != m_EBullets.end(); ++it)
	{

		if (it->shouldDelete())
		{
			it->destroyBody();
			m_EBullets.erase(it);

			break;
			i++;
		}
	}

	for (int j = i; j < m_EBullets.size(); j++)
	{
		m_EBullets.at(j).setUserData(new std::pair<std::string, void *>(typeid(EnemyBullet).name(), &m_EBullets.at(j)));
	}

	//--------------------------------Enemy Bullets---------------------------------
	H_Hud.update(clock, Collectedcoins);
	
	
	
	}
	else
	{
	}
	if (m_debug) m_debugDraw.clear();
	
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Set the view
	
	target.setView(m_mainView);

	target.draw(s_Background);
	target.draw(victory);
	
	for (auto block : m_staticBlocks) target.draw(block);
	for (auto block : m_kinematicBlocks) target.draw(block);

	target.draw(m_PlayerOne);
	target.draw(m_ray);
	for (auto &chests : m_chests) {
		target.draw(chests);
	}
	for (auto &coin : m_coins) {
		target.draw(coin);
	}
	for (auto bullet : m_Bullets) {
		target.draw(bullet);
	}
	for (auto bullet : m_EBullets) {
		target.draw(bullet);
	}
	for (auto &esensor : m_esensor) {
		target.draw(esensor);
	}
	for (auto &block : m_Enemy) {
		target.draw(block);
	}
	if (stop)
	{
		target.draw(s_GO);
	}
	if (victory.win)
	{
		target.draw(s_CO);
	}
	// Debug Draw
	if (m_debug) target.draw(m_debugDraw);


	// Drawing minimap
	target.setView(m_HudView);
	target.draw(s_Background2);
	target.draw(s_Background);
	target.draw(victory);
	for (auto block : m_staticBlocks) target.draw(block);
	for (auto block : m_kinematicBlocks) target.draw(block);
	target.draw(m_PlayerOne);
	target.draw(m_ray);
	for (auto &chests : m_chests) {
		target.draw(chests);
	}
	for (auto &coin : m_coins) {
		target.draw(coin);
	}
	for (auto bullet : m_Bullets) {	
		target.draw(bullet);
	}
	for (auto bullet : m_EBullets) {
		target.draw(bullet);
	}
	for (auto &block : m_Enemy) {
		target.draw(block);
	}
	target.draw(H_Hud);
	
	target.setView(m_mainView);
	
}

void Game::toggleDebug()
{
	if (!stop && !victory.win)
	{
		m_debug = !m_debug;
	}
}

void Game::launchBlock()
{
	// Add some code here!
}
void Game::processKeyPress(sf::Keyboard::Key code , bool press)
{
	
	
	switch (code)
	{
	case sf::Keyboard::Tab:
		toggleDebug();
		break;
	}
	

}
void Game::processMousePress(sf::Mouse::Button code)
{
	m_code = code;
	if (!stop && !victory.win)
	{
		switch (code)
		{
		case sf::Mouse::Button::Left:
			sf::Vector2f bulletDirection = m_Direction - m_PlayerOne.getPosition();
			float angle = atan2f(bulletDirection.y, bulletDirection.x);
			angle = angle * RAD2DEG;
			m_Bullets.push_back(Bullet(m_pWorld, sf::Vector2f(m_PlayerOne.getPosition()), sf::Vector2f(0.2f, 0.1f), &m_BulletTexture, angle, PhysicalThing::CollisionFilter::BULLET));
			m_Bullets.at(m_Bullets.size() - 1).setUserData(new std::pair<std::string, void *>(typeid(Bullet).name(), &m_Bullets.at(m_Bullets.size() - 1)));

			break;
		}
		if (code == sf::Mouse::Button::Right && m_debug) {

			m_PlayerOne.Transform();
		}
	}
}
void Game::onMouseMoved(sf::Vector2f xy)
{
	if (!stop && !victory.win)
	{
		m_Direction = xy;
	}
}

void Game::Getkeys(bool W, bool S, bool A, bool D)
{
	if (!stop && !victory.win)
	{
		m_PlayerOne.Getkeys(W, S, A, D);
	}
}