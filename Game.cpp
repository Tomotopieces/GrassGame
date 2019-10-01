#include "Game.h"

Point::Point()
	:x(0), y(0)
{
}

Point::Point(const Point& pos2)
	: x(pos2.x), y(pos2.y)
{
}

Point::Point(const COORD& pos2)
	: x(pos2.X), y(pos2.Y)
{
}

Point::Point(Point&& pos2)
	: x(pos2.x), y(pos2.y)
{
	pos2.~Point();
}

Point::Point(const int X, const int Y)
	: x(X), y(Y)
{
}

Point& Point::operator=(const Point& pos2)
{
	x = pos2.x;
	y = pos2.y;
	return*this;
}

Point& Point::operator=(const COORD& pos2)
{
	x = pos2.X;
	y = pos2.Y;
	return*this;
}

const int Point::getX() const
{
	return x;
}

const int Point::getY() const
{
	return y;
}

const bool Point::operator==(const Point& pos2) const
{
	return x == pos2.x && y == pos2.y;
}

void Point::ReSet(const int MaxWidth, const int MaxHeight)
{
	x = rand() % MaxWidth;
	y = rand() % MaxHeight;
}