#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Physics/Shape.h"
#include "Physics/Vec2.h"
#include <memory>

class RigidBody
{
public:
	RigidBody(const Vec2& position, float mass, std::unique_ptr<Shape> shape);

	void applyForce(const Vec2& force); // Aplicar una fuerza
	void integrate(float dt); // Resolver el movimiento del cuerpo en un tiempo dt

	void setPosition(const Vec2& position);
	const Vec2& getPosition() const;

	void setVelocity(const Vec2& velocity);
	const Vec2& getVelocity() const;

	float getMass() const;
	float getInverseMass() const;

	Shape& getShape();
	const Shape& getShape() const;

private:
	Vec2 m_position;
	Vec2 m_velocity;
	Vec2 m_force;

	float m_mass;
	float m_inverseMass;

	std::unique_ptr<Shape> m_shape; // cada RigidBody tiene forma propia, no compartida
};

#endif
