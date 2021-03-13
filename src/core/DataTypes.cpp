#include "lo28/DataTypes.h"

pkt2d& pkt2d::operator+= (const pkt2d& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}
pkt2d& pkt2d::operator-= (const pkt2d& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

pkt2d& pkt2d::operator*= (const int rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}
pkt2d& pkt2d::operator/= (const int rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

pkt2d& pkt2d::operator*= (const float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}
pkt2d& pkt2d::operator/= (const float rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

pkt2d pkt2d::operator+ (const pkt2d& rhs)
{
	pkt2d temp(*this);
	return temp += rhs;
}
pkt2d pkt2d::operator- (const pkt2d& rhs)
{
	pkt2d temp(*this);
	return temp -= rhs;
}

pkt2d pkt2d::operator* (const int rhs)
{
	pkt2d temp(*this);
	return temp *= rhs;
}
pkt2d pkt2d::operator/ (const int rhs)
{
	pkt2d temp(*this);
	return temp /= rhs;
}

pkt2d pkt2d::operator* (const float rhs)
{
	pkt2d temp(*this);
	return temp *= rhs;
}
pkt2d pkt2d::operator/ (const float rhs)
{
	pkt2d temp(*this);
	return temp /= rhs;
}