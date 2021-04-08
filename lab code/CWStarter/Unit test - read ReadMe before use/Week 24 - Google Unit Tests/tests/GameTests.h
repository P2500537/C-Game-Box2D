#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "game.h"

TEST(GameInternals, ToggleDebug) {
	Game game;

	bool debugBefore = game.m_debug;
	game.toggleDebug();
	bool debugAfter = game.m_debug;

	EXPECT_NE(debugBefore, debugAfter);
}

TEST(GameInternals, Tab) {
	Game game;

	bool debugBefore = game.m_debug;
	sf::Keyboard::Key key = sf::Keyboard::Tab;
	game.processKeyPress(key, true);
	bool debugAfter = game.m_debug;

	EXPECT_NE(debugBefore, debugAfter);
}

TEST(GameInternals, D) {
	Game game;
	float PlayerDirectionBefore = game.m_PlayerOne.D;
	sf::Keyboard::Key key = sf::Keyboard::D;
	game.Getkeys(0, 0, 0, key);
	float PlayerDirectionAfter = game.m_PlayerOne.D;

	EXPECT_NE(PlayerDirectionBefore, PlayerDirectionAfter);
}
TEST(GameInternals, A) {
	Game game;
	float PlayerDirectionBefore = game.m_PlayerOne.A;
	sf::Keyboard::Key key = sf::Keyboard::A;
	game.Getkeys(0, 0, key, 0);
	float PlayerDirectionAfter = game.m_PlayerOne.A;

	EXPECT_NE(PlayerDirectionBefore, PlayerDirectionAfter);
}

TEST(GameInternals, W) {
	Game game;
	float PlayerDirectionBefore = game.m_PlayerOne.W;
	sf::Keyboard::Key key = sf::Keyboard::W;
	game.Getkeys(key, 0, 0, 0);
	float PlayerDirectionAfter = game.m_PlayerOne.W;

	EXPECT_NE(PlayerDirectionBefore, PlayerDirectionAfter);
}

TEST(GameInternals, LeftMouseButton) {
	Game game;
	float PlayerDirectionBefore = game.m_Bullets.size();
	sf::Mouse::Button key = sf::Mouse::Button::Left;
	game.processMousePress(key);
	float PlayerDirectionAfter = game.m_Bullets.size();

	EXPECT_NE(PlayerDirectionBefore, PlayerDirectionAfter);
}
