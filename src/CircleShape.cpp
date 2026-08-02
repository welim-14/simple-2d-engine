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
