/**
 * Collision.h
 * Deteccion y resolucion de colisiones entre RigidBody (circulo-circulo,
 * caja-caja, y circulo-caja aproximado via AABB).
 */

#ifndef COLLISION_H
#define COLLISION_H

#include "Physics/RigidBody.h"

// Resultado de una prueba de colision: si hay colision, la normal (unitaria,
// apunta de A hacia B) y cuanto se superponen los cuerpos a lo largo de esa
// normal. normal/depth solo son validos si colliding == true.
struct CollisionInfo
{
	bool colliding = false;
	Vec2 normal = Vec2::Zero;
	float depth = 0.0f;
};

AABB computeWorldAABB(const RigidBody& body);

bool circleVsCircle(const RigidBody& a, const RigidBody& b);
bool aabbVsAabb(const AABB& a, const AABB& b);

// Prueba generica: despacha segun ShapeType de cada body (Circle/Box).
// Circulo-vs-caja se aproxima como AABB-vs-AABB (el circulo usa su AABB
// circunscrito), ya que no hay SAT circulo-caja fino en este alcance.
CollisionInfo checkCollision(const RigidBody& a, const RigidBody& b);

// Resuelve una colision ya detectada: aplica impulso (con restitucion) a las
// velocidades y luego corrige las posiciones para separar los cuerpos.
// No hace nada si ambos cuerpos son estaticos (inverseMass 0).
void resolveCollision(RigidBody& a, RigidBody& b, const CollisionInfo& info);

#endif
