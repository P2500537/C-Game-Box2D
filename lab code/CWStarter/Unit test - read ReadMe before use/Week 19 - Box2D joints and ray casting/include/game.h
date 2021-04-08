#pragma once

/*!
\file game.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "SFMLDebugDraw.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include "Hud.h"
#include "staticBlock.h"
#include "KinematicBlock.h"
#include "staticSensor.h"
#include "staticBoxSensor.h"
#include "Coins.h"
#include "BlockPlayerContactListener.h"
#include "ray.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Hud.h"
#include "EnemyMarkI.h"
#include "EnemySensor.h"
#include "Win.h"
/*! \game game
\brief Holds all information about the game, blocks, balls etc and allows updating and rendering.
*/

class Game : public sf::Drawable {
private:
	sf::View m_mainView; //!< The view maps from physical co-ordinates to rendering co-ordinates
	sf::View m_HudView;
	//sf::View m_HudView;
	sf::Vector2f m_worldSize = sf::Vector2f(8.f, 6.f); //!< Size of the physical worlds is 8 X 6 metres
	

	b2World* m_pWorld = nullptr; //!< Pointer to the Box2D world.  Using pointers as BOX2D has it's own memory management
	const int mk_iVelIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int mk_iPosIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 mk_gravity = b2Vec2(0.f, 9.81f); //!< Standard earth gravity will be used (negate the value ofcourse!)
	sf::Clock clock; //!< Time of my game
	float m_blockDirection; //!<
	sf::Texture m_ChestTexture;//!< chest texture
	sf::Texture m_CoinTexture;//!< coin texture
	sf::Texture m_BulletTexture;//!< bullet texture
	sf::Texture T_Head;//!< Head texture for Player
	sf::Texture T_Body;//!< Body texture for Player
	sf::Texture T_Arm;//!< Arm texture for Player
	sf::Texture T_Legs;//!< Legs texture for Player
	sf::Texture t_Background;//!< Background texture
	sf::Texture GameOver;//!< GameOver text texture
	sf::Texture Congrats;//!< Congrats text texture
	sf::Texture Vault;//!< Vault texture
	sf::RectangleShape s_Background;//!< Rectangle shape used for drawing background texture
	sf::RectangleShape s_Background2;//!< Rectangle shape used for drawing background texture
	sf::RectangleShape s_GO; //!< Rectangle shape used for drawing GameOver texture
	sf::RectangleShape s_CO; //!< Rectangle shape used for drawing Congrats texture
	sf::RectangleShape s_V; //!< Rectangle shape used for drawing Vault texture
	int Collectedcoins = 0; //!< Number of collected coins
	
	Hud H_Hud; //!< Hud class object
	Player m_PlayerOne; //!< Player class object
	Ray m_ray; //!< Ray class object
	std::vector<Bullet> m_Bullets; //!< vector objects of Bullet class
	std::vector<EnemyBullet> m_EBullets; //!< vector objects of EnemyBullet class
	sf::Mouse::Button m_code; //!< Mouse::Button object

	std::vector<StaticBlock> m_staticBlocks; //!< vector objects of StaticBlock class
	std::vector <KinematicBlock> m_kinematicBlocks; //!< vector objects of KinematicBlock class
	std::vector <EnemyMarkI> m_Enemy; //!< vector objects of EnemyMarkI class
	std::vector<StaticBoxSensor> m_chests; //!< vector objects of StaticBoxSensor class
	std::vector<Coins> m_coins; //!< vector objects of Coins class
	std::vector<EnemySensor> m_esensor; //!< vector objects of EnemySensor class
	BlockPlayerContactListener m_listener; //!< BlockPlayerContactListener class object
	bool m_debug = false; //!< Toggle for debug drawing
	SFMLDebugDraw m_debugDraw; //!< Box2D debug drawing
	bool stop = false; //!<  Variable used to stop the game after losing a life
	Win victory;  //!< Win class object
public:
	sf::Vector2f m_Direction; //!< Direction of the rey
	Game(); //!< Constructor which sets up the game
	~Game(); //!< Destructor which cleans all the pointer memory up
	void update(float timestep); //!< Update the game with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game to the render context
	void toggleDebug(); //!< Toggle for debug drawing
	void launchBlock(); //!< Give dynamic block some impluse to launch it upwards
	void processKeyPress(sf::Keyboard::Key code, bool press); //!< function checking if buttons have been pressed (Debug Mode)
	void processMousePress(sf::Mouse::Button code); //!< function checking if mouse buttons have been pressed
	void onMouseMoved(sf::Vector2f xy); //!< function checking if mause have been moved
	void Getkeys(bool W, bool S, bool A, bool D); //!< function checking if buttons have been pressed
};
