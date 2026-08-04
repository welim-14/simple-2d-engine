/**
 * Shape.h
 * Clase base para las formas
 */

#ifndef SHAPE_H
#define SHAPE_H

// Tipos de formas
enum class ShapeType
{
	Circle,
	Box
};

class Shape
{
public:
	virtual ~Shape() = default;
	virtual ShapeType getType() const = 0; // Método virtual para obtener el tipo de forma
};

#endif
