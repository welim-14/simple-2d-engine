/**
 * World.h
 * Orquesta la simulacion: posee los RigidBody, aplica fuerzas globales
 * (gravedad) y avanza la simulacion en el tiempo
 */

#ifndef WORLD_H
#define WORLD_H

#include "Physics/Collision.h"
#include "Physics/RigidBody.h"
#include "Physics/Vec2.h"
#include <memory>
#include <vector>

// Par de bodies detectados en colision durante el ultimo step(), junto con
// el resultado de la prueba (penetracion incluida, aun sin usar para resolver)
struct CollidingPair
{
	RigidBody* a;
	RigidBody* b;
	CollisionInfo info;
};

class World
{
public:
	World();
	explicit World(const Vec2& gravity);

	// Crea un RigidBody, el World toma ownership; devuelve un puntero no-owning
	RigidBody* createBody(const Vec2& position, float mass, std::unique_ptr<Shape> shape);
	void removeBody(RigidBody* body);

	void step(float dt); // Aplica gravedad, integra cuerpos y detecta colisiones

	void setGravity(const Vec2& gravity);
	const Vec2& getGravity() const;

	const std::vector<std::unique_ptr<RigidBody>>& getBodies() const;
	const std::vector<CollidingPair>& getCollidingPairs() const;


private:
	std::vector<std::unique_ptr<RigidBody>> m_bodies;
	std::vector<CollidingPair> m_collidingPairs;
	Vec2 m_gravity;

	void detectCollisions(); // O(n^2) sobre m_bodies, llena m_collidingPairs
};

#endif
