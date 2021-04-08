/*!
\file ray.cpp
*/
#include "ray.h"
Ray::Ray(b2World * world, float maxLength, sf::Color colour)
{
	m_pWorld = world;

	m_direction = sf::Vector2f(0.f, 0.f);
	m_maxLength = maxLength;

	m_line.resize(2);
	m_line.setPrimitiveType(sf::Lines);
	m_line[0].color = colour;
	m_line[1].color = colour;
}	  

void Ray::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_line);
}

void Ray::cast(sf::Vector2f start)
{
	// Calculate ray from start in direction with max length
	b2Vec2 p1 = b2Vec2(start.x, start.y);
	b2Vec2 p2 = b2Vec2(m_direction.x, m_direction.y);

	// Cast ray
	b2RayCastInput input;
	input.p1 = p1;
	input.p2 = p2;
	input.maxFraction = 1; // t = 1

	// Check every fixture of every body to find closest
	float closestFraction = input.maxFraction;
	b2Vec2 intersectionNormal(0, 0); // useful if you want to cast additional reflected rays
	for (b2Body* body = m_pWorld->GetBodyList(); body; body = body->GetNext()) {
		for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
			b2RayCastOutput output;
			if (!fixture->RayCast(&output, input, 1))
			{// something went wrong
			}
			//else if (output.fraction < closestFraction) // Use this line if you want the ray to hit sensors
			else if (output.fraction < closestFraction && !fixture->IsSensor())
			{
				closestFraction = output.fraction;
				intersectionNormal = output.normal;
			}
		}
	}

	// Parametric line calculation
	b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

	// Set render points
	m_line[0].position = start;
	m_line[1].position = sf::Vector2f(intersectionPoint.x, intersectionPoint.y);


}

void Ray::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}
