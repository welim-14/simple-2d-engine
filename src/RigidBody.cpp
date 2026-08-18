#include "Physics/RigidBody.h"

RigidBody::RigidBody(const Vec2& position, float mass, std::unique_ptr<Shape> shape)
{
	m_position = position;
	m_velocity = Vec2::Zero;
	m_force = Vec2::Zero;
	m_mass = mass;
    // para inverseMass, si la masa es mayor a 0, calculamos su inverso, de lo contrario, pasamos 0
	m_inverseMass = (mass > 0.0f) ? 1.0f / mass : 0.0f;
	m_restitution = 0.5f;
	m_shape = std::move(shape);
}

void RigidBody::applyForce(const Vec2& force)
{
    m_force += force;
}

void RigidBody::integrate(float dt)
{
    if (dt <= 0.0f)
    {
        m_force = Vec2::Zero; //limpia las fuerzas actuantes
        return;
    }

    if (m_inverseMass > 0.0f)
    {
        const Vec2 acceleration = m_force * m_inverseMass; // a = F/m
        m_velocity += acceleration * dt; // v = v0 + a * dt
    }

    m_position += m_velocity * dt; // p = p0 + v * dt
    m_force = Vec2::Zero;
}

void RigidBody::setPosition(const Vec2& position)
{
    m_position = position;
}

const Vec2& RigidBody::getPosition() const
{
    return m_position;
}

void RigidBody::setVelocity(const Vec2& velocity)
{
    m_velocity = velocity;
}

const Vec2& RigidBody::getVelocity() const
{
    return m_velocity;
}

float RigidBody::getMass() const
{
    return m_mass;
}

float RigidBody::getInverseMass() const
{
    return m_inverseMass;
}

void RigidBody::setRestitution(float restitution)
{
    m_restitution = restitution;
}

float RigidBody::getRestitution() const
{
    return m_restitution;
}

Shape& RigidBody::getShape()
{
    return *m_shape;
}

const Shape& RigidBody::getShape() const
{
    return *m_shape;
}
