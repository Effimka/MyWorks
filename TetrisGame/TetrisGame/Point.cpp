#include "Point.h"

void Point::SetPoint(int xValue, int yValue)
{
	x = xValue;
	y = yValue;
}

void Point::SetX(int xValue)
{
	x = xValue;
}

int Point::GetX()
{
	return x;
}

void Point::SetY(int yValue)
{
	y = yValue;
}

int Point::GetY()
{
	return y;
}
