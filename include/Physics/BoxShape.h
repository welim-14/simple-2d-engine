#ifndef BOXSHAPE_H
#define BOXSHAPE_H

#include "Physics/Shape.h"

class BoxShape : public Shape
{
public:
	BoxShape(float width, float height);

	float getWidth() const;
	float getHeight() const;

	ShapeType getType() const override;

private:
	float m_width;
	float m_height;
};

#endif
