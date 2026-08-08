#include "Physics/Collision.h"
#include "Physics/CircleShape.h"
#include <algorithm>

//Calcular el AABB en coordenadas mundo
AABB computeWorldAABB(const RigidBody& body)
{
	AABB local = body.getShape().getLocalBounds();
	return AABB{ local.min + body.getPosition(), local.max + body.getPosition() };
}

bool circleVsCircle(const RigidBody& a, const RigidBody& b)
{
	const CircleShape& circleA = static_cast<const CircleShape&>(a.getShape());
	const CircleShape& circleB = static_cast<const CircleShape&>(b.getShape());

	float radiusSum = circleA.getRadius() + circleB.getRadius();
	Vec2 delta = b.getPosition() - a.getPosition();

	// Si la distancia es menor a la suma de los radios, estan colisionando
	return delta.lengthSquared() <= (radiusSum * radiusSum);
}

//Comparar dos Boxes AABB para detectar colision
bool aabbVsAabb(const AABB& a, const AABB& b)
{
	if (a.max.m_x < b.min.m_x || a.min.m_x > b.max.m_x)
		return false;
	if (a.max.m_y < b.min.m_y || a.min.m_y > b.max.m_y)
		return false;

	return true;
}

CollisionInfo checkCollision(const RigidBody& a, const RigidBody& b)
{
	CollisionInfo info;
	//Circulo - circulo
	if (a.getShape().getType() == ShapeType::Circle && b.getShape().getType() == ShapeType::Circle)
	{
		info.colliding = circleVsCircle(a, b);
		if (info.colliding)
		{
			Vec2 delta = b.getPosition() - a.getPosition();
			const CircleShape& circleA = static_cast<const CircleShape&>(a.getShape());
			const CircleShape& circleB = static_cast<const CircleShape&>(b.getShape());
			float radiusSum = circleA.getRadius() + circleB.getRadius();
			float distance = delta.length();
			float overlap = radiusSum - distance;
			Vec2 axis = distance > 0.0f ? delta.normalized() : Vec2(1.0f, 0.0f);
			info.penetration = axis * overlap;
		}
		return info;
	}

	// Box-Box y Circle-Box (mixto, aproximado con AABB): comparar AABBs en espacio-mundo
	AABB boundsA = computeWorldAABB(a);
	AABB boundsB = computeWorldAABB(b);

	info.colliding = aabbVsAabb(boundsA, boundsB);
	if (info.colliding)
	{
		float overlapX = std::min(boundsA.max.m_x, boundsB.max.m_x) - std::max(boundsA.min.m_x, boundsB.min.m_x);
		float overlapY = std::min(boundsA.max.m_y, boundsB.max.m_y) - std::max(boundsA.min.m_y, boundsB.min.m_y);
		info.penetration = Vec2(overlapX, overlapY);
	}

	return info;
}
