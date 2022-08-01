#pragma once
#include "Point.h"

class Tetramino
{
	Point LocalPoints[4];
	Point GlobalPoints[4];
	char matrix[4][4];
	int SpawnLocationX;
	int SpawnLocationY;
	unsigned Color;
public:

	Tetramino(int LocationX = 4, int LocationY = 1);

	void SetTetramino(int tetramin);
	void TempRotatePoints(Point* LocaclLocation, Point* GlobalLocation);
	void SetRotateTetramino(Point* LocaclLocation, Point* GlobalLocation);

	Point* GetLocalPoints();
	Point* GetGlobalPoints();
	unsigned GetColor();
};