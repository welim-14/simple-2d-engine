#ifndef SHAPE_H
#define SHAPE_H

enum class ShapeType
{
	Circle,
	Box
};

class Shape
{
public:
	virtual ~Shape() = default;
	virtual ShapeType getType() const = 0;
};

#endif
