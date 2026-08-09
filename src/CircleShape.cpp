#include "Physics/CircleShape.h"

CircleShape::CircleShape(float radius)
{
	m_radius = radius;
}

float CircleShape::getRadius() const
{
	return m_radius;
}

ShapeType CircleShape::getType() const
{
	return ShapeType::Circle;
}

AABB CircleShape::getLocalBounds() const
{
	return AABB{ Vec2(-m_radius, -m_radius), Vec2(m_radius, m_radius) };
}
