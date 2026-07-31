#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
	float x;
	float y;
	
	//constructor
	Vec2();
	Vec2(float x, float y);

	//operaciones de vectores
	Vec2 operator+(const Vec2 &other) const;
	Vec2 operator-(const Vec2 &other) const;
	Vec2 operator*(float scalar) const;
	Vec2 operator/(float scalar) const;

	Vec2& operator+=(const Vec2 &other);
	Vec2& operator-=(const Vec2 &other);
	Vec2& operator*=(float scalar);
	Vec2& operator/=(float scalar);

	//propiedades del vector
	float length() const;
	float lengthSquared() const; //sin aplicar raiz cuadrada
	Vec2 normalized() const;
	void normalize();

	float dot(const Vec2 &other) const;

	static const Vec2 Zero;
};


#endif
