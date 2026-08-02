#include "Physics/BoxShape.h"


BoxShape::BoxShape(float width, float height)
{
	m_width = width;
	m_height = height;
}

float BoxShape::getWidth() const
{
	return m_width;
}

float BoxShape::getHeight() const
{
	return m_height;
}

ShapeType BoxShape::getType() const
{
	return ShapeType::Box;
}
