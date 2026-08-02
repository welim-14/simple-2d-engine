#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

#include "Physics/Shape.h"

class CircleShape : public Shape
{
public:
	explicit CircleShape(float radius);

	float getRadius() const;

	ShapeType getType() const override;
	
private:
	float m_radius;
};

#endif
