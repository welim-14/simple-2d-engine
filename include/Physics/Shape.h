/**
 * Shape.h
 * Clase base para las formas
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "Physics/Vec2.h"

// Tipos de formas
enum class ShapeType
{
	Circle,
	Box
};

// Caja alineada a los ejes, en el mismo espacio que min/max fueron calculados
// (local si viene de getLocalBounds(), mundo si se le sumo la posicion del body)
struct AABB
{
	Vec2 min;
	Vec2 max;
};

class Shape
{
public:
	virtual ~Shape() = default;
	virtual ShapeType getType() const = 0; // Método virtual para obtener el tipo de forma
	virtual AABB getLocalBounds() const = 0; // AABB en espacio local, centrado en (0,0)
};

#endif
