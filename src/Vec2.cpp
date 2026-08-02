#include"Physics/Vec2.h"
#include<cmath>

Vec2::Vec2()
{
	m_x = 0.0f;
	m_y = 0.0f;
}

Vec2::Vec2(float x, float y)
{
	m_x = x;
	m_y = y;
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
	return Vec2(m_x + other.m_x, m_y + other.m_y);
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
	return Vec2(m_x - other.m_x, m_y - other.m_y);
}

Vec2 Vec2::operator*(float escalar) const
{
	return Vec2(m_x * escalar, m_y * escalar);
}

Vec2 Vec2::operator/(float escalar) const
{
	return Vec2(m_x / escalar, m_y / escalar);
}

Vec2& Vec2::operator+=(const Vec2 &other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2 &other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	return *this;
}

Vec2& Vec2::operator*=(float escalar)
{
	m_x *= escalar;
	m_y *= escalar;
	return *this;
}

Vec2& Vec2::operator/=(float escalar)
{
	m_x /= escalar;
	m_y /= escalar;
	return *this;
}

float Vec2::lengthSquared() const
{
	float sq_x = m_x * m_x;
	float sq_y = m_y * m_y;

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
	float a = m_x * other.m_x;
	float b = m_y * other.m_y;

	return (a+b);
}

const Vec2 Vec2::Zero(0.0f, 0.0f);
