/*!
\file Hud.cpp
*/
#include "Hud.h"
Hud::Hud(b2World * world)
{	
	//Time Counter
	Colon.loadFromFile("./assets/textures/Colon.png");
	Zero0.loadFromFile("./assets/textures/Zero.png");
	One1.loadFromFile("./assets/textures/One.png");
	Two2.loadFromFile("./assets/textures/Two.png");
	Three3.loadFromFile("./assets/textures/Three.png");
	Four4.loadFromFile("./assets/textures/Four.png");
	Five5.loadFromFile("./assets/textures/Five.png");
	Six6.loadFromFile("./assets/textures/Six.png");
	Seven7.loadFromFile("./assets/textures/Seven.png");
	Eight8.loadFromFile("./assets/textures/Eight.png");
	Nine9.loadFromFile("./assets/textures/Nine.png");

	T_TimeCounter[0] = Zero0;
	T_TimeCounter[1] = Zero0;
	T_TimeCounter[2] = Colon;
	T_TimeCounter[3] = Zero0;
	T_TimeCounter[4] = Zero0;
	T_TimeCounter[5] = Colon;
	T_TimeCounter[6] = Zero0;
	T_TimeCounter[7] = Zero0;
	for(int i = 0; i<=7;i++)
	{
		T_TextureUpdate(&T_TimeCounter[i], i);
		S_TimeCounter[i].setSize(sf::Vector2f(1.f, 2.f));
		S_TimeCounter[i].setPosition(sf::Vector2f(4.5f+2.f*i, -2.8f));
	}
	//Time Counter
	//Score
	Coins.loadFromFile("./assets/textures/Coins.png");

	T_CoinCounter[0] = Coins;
	T_CoinCounter[1] = Zero0;
	T_CoinCounter[2] = Zero0;

	C_TextureUpdate(&T_CoinCounter[0], 0);
	S_CoinCounter[0].setSize(sf::Vector2f(4.f, 2.f));
	S_CoinCounter[0].setPosition(sf::Vector2f(4.5f, 0.f));
	for (int i = 1; i <= 2; i++)
	{
		C_TextureUpdate(&T_CoinCounter[i], i);
		S_CoinCounter[i].setSize(sf::Vector2f(1.f, 2.f));
		S_CoinCounter[i].setPosition(sf::Vector2f(7.f + 2.f*i, 0.f));
	}
	//Score
}

void Hud::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i <= 7; i++)
	{
		target.draw(S_TimeCounter[i]);
	}
	for (int i = 0; i <= 2; i++)
	{
		target.draw(S_CoinCounter[i]);
	}
	//target.draw((sf::Text)*this);
	//target.draw(Tx);
}
Hud::~Hud()
{
}

void Hud::update(sf::Clock time,int score)
{
	TimeCheck(time);
	CoinCheck(score);

}

void Hud::TimeCheck(sf::Clock time)
{
	int t = time.getElapsedTime().asSeconds();
	if (t < 60)
	{
		S = t;
		M = 0;
		H = 0;
	}
	else if (t > 60)
	{
		S = t % 60;
		M = t / 60;
		H = 0;
	}
	else if (t / 60 > 60)
	{
		S = t % 60;
		M = t % 3600;
		H = t / 3600;
	}

	S1 = S % 10;
	T_TimeCounter[7] = NumberCheck(S1);
	S2 = S / 10;
	T_TimeCounter[6] = NumberCheck(S2);

	T_TimeCounter[5] = Colon;

	M1 = M % 10;
	T_TimeCounter[4] = NumberCheck(M1);
	M2 = M / 10;
	T_TimeCounter[3] = NumberCheck(M2);
	H1 = H % 10;

	T_TimeCounter[2] = Colon;

	T_TimeCounter[1] = NumberCheck(H1);
	H2 = H / 10;
	T_TimeCounter[0] = NumberCheck(H2);

	//std::cout << "S" << S1 << " " << S2 << std::endl;
	for (int i = 0; i <= 7; i++)
	{
		T_TextureUpdate(&T_TimeCounter[i], i);
	}
}

void Hud::CoinCheck(int score)
{
	int c = score;
	C1 = c % 10;
	T_CoinCounter[2] = NumberCheck(C1);
	C2 = c / 10;
	T_CoinCounter[1] = NumberCheck(C2);
	T_CoinCounter[0] = Coins;
	for (int i = 0; i <= 3; i++)
	{
		C_TextureUpdate(&T_CoinCounter[i], i);
	}
}

sf::Texture Hud::NumberCheck(int number)
{

	switch (number)
	{
	case 0:
		m_numberState = Zero;
		break;
	case 1:
		m_numberState = One;
		break;
	case 2:
		m_numberState = Two;
		break;
	case 3:
		m_numberState = Three;
		break;
	case 4:
		m_numberState = Four;
		break;
	case 5:
		m_numberState = Five;
		break;
	case 6:
		m_numberState = Six;
		break;
	case 7:
		m_numberState = Seven;
		break;
	case 8:
		m_numberState = Eight;
		break;
	case 9:
		m_numberState = Nine;
		break;
	}
	switch (m_numberState)
	{
	case Zero:  CorrectNumber = Zero0; break;
	case One:  CorrectNumber = One1; break;
	case Two: CorrectNumber = Two2; break;
	case Three: CorrectNumber = Three3; break;
	case Four: CorrectNumber = Four4; break;
	case Five: CorrectNumber = Five5; break;
	case Six: CorrectNumber = Six6; break;
	case Seven: CorrectNumber = Seven7; break;
	case Eight: CorrectNumber = Eight8; break;
	case Nine: CorrectNumber = Nine9; break;
	}
	return CorrectNumber;
}

void Hud::T_TextureUpdate(sf::Texture * Texture, int i)
{
	S_TimeCounter[i].setTexture(Texture);
}

void Hud::C_TextureUpdate(sf::Texture * Texture, int i)
{
	S_CoinCounter[i].setTexture(Texture);
}
