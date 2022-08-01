#include "Tetramino.h"


Tetramino::Tetramino(int LocationX, int LocationY): SpawnLocationX(LocationX), SpawnLocationY(LocationY)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			matrix[y][x] = '.';
		}
	}
}

void Tetramino::SetTetramino(int tetramin)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			matrix[y][x] = '.';
		}
	}
	Color = tetramin;

	switch (tetramin)
	{
	case 0: // T
		LocalPoints[0].SetPoint(1, 0);
		LocalPoints[1].SetPoint(0, 1);
		LocalPoints[2].SetPoint(1, 1);
		LocalPoints[3].SetPoint(2, 1);
		break;
	case 1:// I
		LocalPoints[0].SetPoint(0, 0);
		LocalPoints[1].SetPoint(1, 0);
		LocalPoints[2].SetPoint(2, 0);
		LocalPoints[3].SetPoint(3, 0);
		break;
	case 2:// J
		LocalPoints[0].SetPoint(2, 0);
		LocalPoints[1].SetPoint(2, 1);
		LocalPoints[2].SetPoint(2, 2);
		LocalPoints[3].SetPoint(1, 2);
		break;
	case 3:// L
		LocalPoints[0].SetPoint(2, 0);
		LocalPoints[1].SetPoint(2, 1);
		LocalPoints[2].SetPoint(2, 2);
		LocalPoints[3].SetPoint(3, 2);
		break;
	case 4:// O
		LocalPoints[0].SetPoint(1, 0);
		LocalPoints[1].SetPoint(2, 0);
		LocalPoints[2].SetPoint(1, 1);
		LocalPoints[3].SetPoint(2, 1);
		break;
	case 5:// Z
		LocalPoints[0].SetPoint(1, 0);
		LocalPoints[1].SetPoint(1, 1);
		LocalPoints[2].SetPoint(0, 1);
		LocalPoints[3].SetPoint(0, 2);
		break;
	case 6:// S
		LocalPoints[0].SetPoint(0, 0);
		LocalPoints[1].SetPoint(0, 1);
		LocalPoints[2].SetPoint(1, 1);
		LocalPoints[3].SetPoint(1, 2);
		break;
	default:
		break;
	}

	
	for (int i = 0; i < 4; i++)
	{
		matrix[LocalPoints[i].GetY()][LocalPoints[i].GetX()] = 'X';

		GlobalPoints[i].SetPoint(LocalPoints[i].GetX() + SpawnLocationX, LocalPoints[i].GetY() + SpawnLocationY);
	}

}

void Tetramino::TempRotatePoints(Point* LocaclLocation, Point* GlobalLocation)
{
	char TempMatrix[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			TempMatrix[i][j] = matrix[3 - j][i];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		GlobalLocation[i].SetPoint(GlobalPoints[i].GetX() - LocalPoints[i].GetX(), GlobalPoints[i].GetY() - LocalPoints[i].GetY());
	}

	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (TempMatrix[i][j] == 'X' && count < 4)
			{
				LocaclLocation[count].SetPoint(j, i);
				count++;
			}
		}
	}

	while (true)
	{
		if (LocaclLocation[0].GetX() == 0 || LocaclLocation[1].GetX() == 0 || LocaclLocation[2].GetX() == 0 || LocaclLocation[4].GetX() == 0)
			break;
		LocaclLocation[0].SetX(LocaclLocation[0].GetX() - 1);
		LocaclLocation[1].SetX(LocaclLocation[1].GetX() - 1);
		LocaclLocation[2].SetX(LocaclLocation[2].GetX() - 1);
		LocaclLocation[3].SetX(LocaclLocation[3].GetX() - 1);
	}

	while (true)
	{
		if (LocaclLocation[0].GetY() == 0 || LocaclLocation[1].GetY() == 0 || LocaclLocation[2].GetY() == 0 || LocaclLocation[4].GetY() == 0)
			break;
		LocaclLocation[0].SetY(LocaclLocation[0].GetY() - 1);
		LocaclLocation[1].SetY(LocaclLocation[1].GetY() - 1);
		LocaclLocation[2].SetY(LocaclLocation[2].GetY() - 1);
		LocaclLocation[3].SetY(LocaclLocation[3].GetY() - 1);
	}	

	for (int i = 0; i < 4; i++)
	{
		GlobalLocation[i].SetPoint(GlobalLocation[i].GetX() + LocaclLocation[i].GetX(), GlobalLocation[i].GetY() + LocaclLocation[i].GetY());
	}

}
void Tetramino::SetRotateTetramino(Point* LocaclLocation, Point* GlobalLocation)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = '.';
		}
	}

	for (int i = 0; i < 4; i++)
	{
		LocalPoints[i].SetPoint(LocaclLocation[i].GetX(), LocaclLocation[i].GetY());
		GlobalPoints[i].SetPoint(GlobalLocation[i].GetX(), GlobalLocation[i].GetY());
		matrix[LocaclLocation[i].GetY()][LocaclLocation[i].GetX()] = 'X';
	}
}


Point* Tetramino::GetLocalPoints()
{
	return LocalPoints;
}

Point* Tetramino::GetGlobalPoints()
{
	return GlobalPoints;
}

unsigned Tetramino::GetColor()
{
	return Color;
}


