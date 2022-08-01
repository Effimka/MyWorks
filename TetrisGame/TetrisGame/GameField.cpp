#include <iostream>
#include "GameField.h"

GameField::GameField(int xValue, int yValue): xField(xValue), yField(yValue)
{
	//Draw field
	Field = new char* [yValue];
	for (int y = 0; y < yValue; y++)
	{
		Field[y] = new char[xValue];
	}

	//Collision Fiedl
	CollisionField = new int* [yValue];
	for (int y = 0; y < yValue; y++)
	{
		CollisionField[y] = new int[xValue];
	}

	for (int y = 0; y < yValue; y++)
	{
		for (int x = 0; x < xValue; x++)
		{
			if (y == 0 || y == yField - 1 || x == 0 || x == xField - 1)
				CollisionField[y][x] = 9;
			else
				CollisionField[y][x] = 0;
		}
	}

}

GameField::~GameField()
{
	for (int y = 0; y < yField; y++)
	{
		delete[] Field[y];
	}
	delete[] Field;

	for (int y = 0; y < yField; y++)
	{
		delete[] CollisionField[y];
	}
	delete[] CollisionField;
}

void GameField::UpdateField(Tetramino& const tetramin, int& Score)
{
	AssembleRow(Score);

	Point* GlobalTetraminoLocation = tetramin.GetGlobalPoints();
	for (int y = 0; y < yField; y++)
	{
		for (int x = 0; x < xField; x++)
		{
			if (CollisionField[y][x] == 9)
				Field[y][x] = '#';
			else if (CollisionField[y][x] == 0)
				Field[y][x] = '.';
			else if (CollisionField[y][x] == 1)
				Field[y][x] = 'X';
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Field[GlobalTetraminoLocation[i].GetY()][GlobalTetraminoLocation[i].GetX()] = 'X';
	}

	for (int y = 0; y < yField; y++)
	{
		for (int x = 0; x < xField; x++)
		{
			std::cout << Field[y][x] << " ";
		}
		
		std::cout << '\n';
	}
}

void GameField::RotateTetramino(Tetramino& tetramin)
{
	Point TempLocalLocation[4];
	Point TempGlobalLocation[4];
	for (int i = 0; i < 4; i++)
	{
		TempGlobalLocation[i] = tetramin.GetGlobalPoints()[i];
		TempLocalLocation[i] = tetramin.GetLocalPoints()[i];
	}

	tetramin.TempRotatePoints(TempLocalLocation, TempGlobalLocation);

	if (CheckXLeftCollision(TempGlobalLocation))
	{
		if (CheckXRightCollision(TempGlobalLocation))
		{
			if (CheckYDownCollision(TempGlobalLocation))
			{
				tetramin.SetRotateTetramino(TempLocalLocation, TempGlobalLocation);
			}
		}
		else
		{
			TempGlobalLocation[0].SetX(TempGlobalLocation[0].GetX() - 1);
			TempGlobalLocation[1].SetX(TempGlobalLocation[1].GetX() - 1);
			TempGlobalLocation[2].SetX(TempGlobalLocation[2].GetX() - 1);
			TempGlobalLocation[3].SetX(TempGlobalLocation[3].GetX() - 1);

			bool temp;
			for (int i = 0; i < 4; i++)
			{
				if (CollisionField[TempGlobalLocation[i].GetY()][TempGlobalLocation[i].GetX()] == 0) temp = true;
				else
				{
					temp = false;
					break;
				}
			}
			if (temp) tetramin.SetRotateTetramino(TempLocalLocation, TempGlobalLocation);
		}
	}
	else
	{
		TempGlobalLocation[0].SetX(TempGlobalLocation[0].GetX() + 1);
		TempGlobalLocation[1].SetX(TempGlobalLocation[1].GetX() + 1);
		TempGlobalLocation[2].SetX(TempGlobalLocation[2].GetX() + 1);
		TempGlobalLocation[3].SetX(TempGlobalLocation[3].GetX() + 1);

		bool temp;
		for (int i = 0; i < 4; i++)
		{
			if (CollisionField[TempGlobalLocation[i].GetY()][TempGlobalLocation[i].GetX()] == 0) temp = true;
			else
			{
				temp = false;
				break;
			}
		}
		if (temp) tetramin.SetRotateTetramino(TempLocalLocation, TempGlobalLocation);
	}

}

void GameField::FixTetraminoOnField(Tetramino& tetramin)
{
	for (int i = 0; i < 4; i++)
	{
		CollisionField[tetramin.GetGlobalPoints()[i].GetY()][tetramin.GetGlobalPoints()[i].GetX()] = 1;
	}
}

void GameField::AssembleRow(int& Score)
{
	bool FullRow = false;
	for (int y = yField - 2; y > 0; y--)
	{
		for (int x = 1; x < xField - 1 ; x++)
		{
			if (CollisionField[y][x] != 0)
				FullRow = true;
			else
			{
				FullRow = false;
				break;
			}
		}
		
		if (FullRow)
		{
			Score += xField - 2;
			int historyY = y;
			for (int i = y - 1; i > 0; i--)
			{
				for (int j = 1; j < xField - 1; j++)
				{
					CollisionField[historyY][j] = CollisionField[i][j];
				}
				historyY = i;
			}
		}
	}
}

bool GameField::CheckYDownCollision(Point* const PointToCheck)
{
	for (int p = 0; p < 4; p++)
	{
		if (CollisionField[PointToCheck[p].GetY() + 1][PointToCheck[p].GetX()] != 0) return false;
	}
	
	return true;
}

bool GameField::CheckYUpCollision()
{
	
	for (int i = 1; i < xField - 1; i++)
	{
		if (CollisionField[1][i] != 0) return false;
	}
	
	return true;
}

bool GameField::CheckXLeftCollision(Point* const PointToCheck)
{
	int MinXvalue = PointToCheck[0].GetX();
	for (int p = 0; p < 4; p++)
	{
		//Min
		if (PointToCheck[p].GetX() < MinXvalue) MinXvalue = PointToCheck[p].GetX();
	}

	for (int p = 0; p < 4; p++)
	{
		if (PointToCheck[p].GetX() == MinXvalue)
		{
			if (CollisionField[PointToCheck[p].GetY()][PointToCheck[p].GetX() - 1] != 0) return false;
		}
	}

	return true;
}

bool GameField::CheckXRightCollision(Point* const PointToCheck)
{
	int MaxXvalue = PointToCheck[0].GetX();
	for (int p = 0; p < 4; p++)
	{
		//Max
		if (PointToCheck[p].GetX() > MaxXvalue) MaxXvalue = PointToCheck[p].GetX();
	}

	for (int p = 0; p < 4; p++)
	{
		if (PointToCheck[p].GetX() == MaxXvalue)
		{
			if (CollisionField[PointToCheck[p].GetY()][PointToCheck[p].GetX() + 1] != 0) return false;
		}
	}

	return true;
}

