#ifndef CIRCLESHAPE_H
#define CIRCLESAHPE_H

class CircleShape : public Shape
{
public:
	explicit CircleShape(float radius);

	float getRadius() const;
	
private:
	float m_radius;
};

#endif
