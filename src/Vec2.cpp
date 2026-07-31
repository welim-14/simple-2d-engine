#include"Physics/Vec2.h"
#include<cmath>

Vec2::Vec2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
	return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
	return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 Vec2::operator*(float escalar) const
{
	return Vec2(this->x * escalar, this->y * escalar);
}

Vec2 Vec2::operator/(float escalar) const
{
	return Vec2(this->x / escalar, this->y / escalar);
}

Vec2& Vec2::operator+=(const Vec2 &other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2 &other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vec2& Vec2::operator*=(float escalar)
{
	this->x *= escalar;
	this->y *= escalar;
	return *this;
}

Vec2& Vec2::operator/=(float escalar)
{
	this->x /= escalar;
	this->y /= escalar;
	return *this;
}

float Vec2::lengthSquared() const
{
	float sq_x = x * x;
	float sq_y = y * y;

	return sq_x + sq_y;
}

float Vec2::length() const
{
	float l = lengthSquared();
	return std::sqrt(l);
}

Vec2 Vec2::normalized() const
{
	float l = length();
	if(l == 0.0f)
		return Vec2::Zero;
	return (*this / l);
}

void Vec2::normalize()
{
	*this = normalized();
}

float Vec2::dot(const Vec2 &other) const
{
	float a = this->x * other.x;
	float b = this->y * other.y;

	return (a+b);
}

const Vec2 Vec2::Zero(0.0f, 0.0f);
