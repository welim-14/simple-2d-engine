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

AABB BoxShape::getLocalBounds() const
{
	/*
		Se define como la mitad izquierda y superior en negativo, y la mitad derecha e inferior en positivo
		Esto tomando en cuenta que el origen del rectangulo es (0, 0) y que el rectangulo se centra en su origen
	*/
	return AABB{ Vec2(-m_width / 2.0f, -m_height / 2.0f), Vec2(m_width / 2.0f, m_height / 2.0f) };
}
