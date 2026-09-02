#include"Physics/World.h"
#include <algorithm>

World::World()
{
    m_gravity = Vec2(0.0f, 9.81f);
}

World::World(const Vec2& gravity)
{
    m_gravity = gravity;
}

RigidBody* World::createBody(const Vec2& position, float mass, std::unique_ptr<Shape> shape)
{
    std::unique_ptr<RigidBody> body = std::make_unique<RigidBody>(position, mass, std::move(shape));
    RigidBody* bodyPtr = body.get();
    m_bodies.push_back(std::move(body)); // mandar al vector de unique_ptrs, que toma ownership del RigidBody
    return bodyPtr;
}

void World::removeBody(RigidBody* body)
{
    if (body == nullptr)
        return;

    // busca el puntero en el vector usando find_if
    auto it = std::find_if(m_bodies.begin(), m_bodies.end(),
        [body](const std::unique_ptr<RigidBody>& b) { return b.get() == body; });
    
    // si el puntero no se encuentra, devuelve el elemento final del arreglo
    // si se encuentra, lo elimina del vector
    if (it != m_bodies.end()) {
        m_bodies.erase(it);
    }
}

void World::step(float dt)
{
    for (std::unique_ptr<RigidBody> &body : m_bodies){
        // aplicar gravedad
        if(body->getInverseMass() > 0.0f)
            body->applyForce(m_gravity * body->getMass());

        body->integrate(dt);
    }

    detectCollisions();

    for (CollidingPair& pair : m_collidingPairs)
    {
        resolveCollision(*pair.a, *pair.b, pair.info);
        pair.a->integrate(dt);
        pair.b->integrate(dt);
    }
}

void World::detectCollisions()
{
    m_collidingPairs.clear();

    for (std::size_t i = 0; i < m_bodies.size(); ++i)
    {
        for (std::size_t j = i + 1; j < m_bodies.size(); ++j)
        {
            RigidBody* a = m_bodies[i].get();
            RigidBody* b = m_bodies[j].get();

            CollisionInfo info = checkCollision(*a, *b);
            if (info.colliding)
                m_collidingPairs.push_back(CollidingPair{a, b, info});
        }
    }
}

void World::setGravity(const Vec2& gravity)
{
    m_gravity = gravity;
}

const Vec2& World::getGravity() const
{
    return m_gravity;
}

const std::vector<std::unique_ptr<RigidBody>>& World::getBodies() const
{
    return m_bodies;
}

const std::vector<CollidingPair>& World::getCollidingPairs() const
{
    return m_collidingPairs;
}