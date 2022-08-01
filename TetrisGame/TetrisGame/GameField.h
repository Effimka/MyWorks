#pragma once
#include "Point.h"
#include "Tetramino.h"

class GameField
{
	int xField;
	int yField;
	char** Field;
	int** CollisionField;

public:

	GameField(int xValue = 12, int yValue = 18);
	~GameField();

	void UpdateField(Tetramino& const tetramin, int& Score);
	void RotateTetramino(Tetramino& tetramin);

	void FixTetraminoOnField(Tetramino& tetramin);
	void AssembleRow(int& Score);

	// Collision
	bool CheckYDownCollision(Point* const PointToCheck);
	bool CheckYUpCollision();
	bool CheckXLeftCollision(Point* const PointToCheck);
	bool CheckXRightCollision(Point* const PointToCheck);


};