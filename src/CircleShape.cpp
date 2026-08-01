#include "Physics/CircleShape.h"

CicleShape(float radius)
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
