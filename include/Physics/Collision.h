/**
 * Collision.h
 * Deteccion de colisiones entre RigidBody (circulo-circulo, caja-caja,
 * y circulo-caja aproximado via AABB). No resuelve/empuja cuerpos todavia.
 */

#ifndef COLLISION_H
#define COLLISION_H

#include "Physics/RigidBody.h"

// Resultado de una prueba de colision: si hay colision y cuanto se superponen
// los cuerpos en cada eje. penetration solo es valido si colliding == true.
// Se calcula aunque todavia no se use para resolver, ya que es el mismo
// calculo que la deteccion y evita rediseñar la firma cuando se agregue
// la resolucion de colisiones.
struct CollisionInfo
{
	bool colliding = false;
	Vec2 penetration = Vec2::Zero;
};

AABB computeWorldAABB(const RigidBody& body);

bool circleVsCircle(const RigidBody& a, const RigidBody& b);
bool aabbVsAabb(const AABB& a, const AABB& b);

// Prueba generica: despacha segun ShapeType de cada body (Circle/Box).
// Circulo-vs-caja se aproxima como AABB-vs-AABB (el circulo usa su AABB
// circunscrito), ya que no hay SAT circulo-caja fino en este alcance.
CollisionInfo checkCollision(const RigidBody& a, const RigidBody& b);

#endif
