/*!
\file Ray.h
*/
/*! \Ray Ray
\The Ray class creates Ray used by the player
*/
#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Ray : public sf::Drawable
{
private:
	b2World * m_pWorld; //!< Pointer to the Box2D world
	sf::VertexArray m_line; //!< Line to render the ray
	sf::Vector2f m_direction; //!< Direction of the ray
	float m_maxLength; //!< Maximum length of the ray
public:
	Ray() {}; //!< Default constructor
	Ray(b2World * world, float maxLength, sf::Color colour); //!< Full constructor
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void cast(sf::Vector2f start); //!< Cast the ray
	void setDirection(sf::Vector2f direction); //!< Set ray direction
};