#pragma once
class Point
{
	int x;
	int y;
public:
	Point(int xValue, int yValue) : x(xValue), y(yValue) {}
	Point() : x(0), y(0) {}


	void SetPoint(int xValue, int yValue);

	//Getter & Setter X
	void SetX(int xValue);
	int GetX();

	//Getter & SetterY
	void SetY(int yValue);
	int GetY();
};
