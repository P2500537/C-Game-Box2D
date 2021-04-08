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

TEST(GameInternals, Right) {
	Game game;
	float PlayerDirectionBefore = game.m_PlayerOne.getPosition().x;
	sf::Keyboard::Key key = sf::Keyboard::D;
	game.Getkeys(0,0,0,key);
	float PlayerDirectionAfter = game.m_PlayerOne.getPosition().x;

	EXPECT_NE(PlayerDirectionBefore, PlayerDirectionAfter);
}
TEST(GameInternals, Left) {
	Game game;
	float PlayerDirectionBefore = game.m_PlayerOne.getPosition().x;
	sf::Keyboard::Key key = sf::Keyboard::A;
	game.Getkeys(0, 0, key, 0);
	float PlayerDirectionAfter = game.m_PlayerOne.getPosition().x;

	EXPECT_NE(PlayerDirectionBefore, PlayerDirectionAfter);
}

TEST(GameInternals, Up) {
	Game game;
	float PlayerDirectionBefore = game.m_PlayerOne.getPosition().x;
	sf::Keyboard::Key key = sf::Keyboard::A;
	game.Getkeys(key, 0, 0, 0);
	float PlayerDirectionAfter = game.m_PlayerOne.getPosition().x;

	EXPECT_NE(PlayerDirectionBefore, PlayerDirectionAfter);
}