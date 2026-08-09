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
			info.depth = radiusSum - distance;
			info.normal = distance > 0.0f ? delta.normalized() : Vec2(1.0f, 0.0f);
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

		// Eje de menor solapamiento = eje de separacion; la normal apunta de A hacia B
		if (overlapX < overlapY)
		{
			info.depth = overlapX;
			info.normal = Vec2(b.getPosition().m_x < a.getPosition().m_x ? -1.0f : 1.0f, 0.0f);
		}
		else
		{
			info.depth = overlapY;
			info.normal = Vec2(0.0f, b.getPosition().m_y < a.getPosition().m_y ? -1.0f : 1.0f);
		}
	}

	return info;
}

void resolveCollision(RigidBody& a, RigidBody& b, const CollisionInfo& info)
{
	if (!info.colliding)
		return;

	float invMassA = a.getInverseMass();
	float invMassB = b.getInverseMass();
	float invMassSum = invMassA + invMassB;

	if (invMassSum <= 0.0f)
		return; // ambos cuerpos son estaticos, nada que resolver

	// Impulso: solo si los cuerpos todavia se acercan a lo largo de la normal
	Vec2 relativeVelocity = b.getVelocity() - a.getVelocity();
	float velocityAlongNormal = relativeVelocity.dot(info.normal);

	if (velocityAlongNormal <= 0.0f)
	{
		float restitution = std::min(a.getRestitution(), b.getRestitution());
		float j = -(1.0f + restitution) * velocityAlongNormal / invMassSum;
		Vec2 impulse = info.normal * j;

		a.setVelocity(a.getVelocity() - impulse * invMassA);
		b.setVelocity(b.getVelocity() + impulse * invMassB);
	}

	// Correccion posicional: separa los cuerpos repartiendo la penetracion segun masa inversa
	Vec2 correction = info.normal * (info.depth / invMassSum);
	a.setPosition(a.getPosition() - correction * invMassA);
	b.setPosition(b.getPosition() + correction * invMassB);
}
