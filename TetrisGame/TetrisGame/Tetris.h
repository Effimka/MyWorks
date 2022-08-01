#pragma once
#include <iostream>
#include "Point.h"
#include "GameField.h"
#include "Tetramino.h"
#include "Menu.h"

class Tetris
{
	GameField Field;
	Tetramino tetramin;
	Menu menu;
	int GameScore;
	bool bIsPauseGame;
	int SpeedDown;
	int NumOfTetramino;
	int TetraminoBag[7];
public:

	Tetris();

	bool SpawnTetramino(Tetramino& tetramin);
	bool FallDown(Tetramino& tetramin, GameField& Field);
	void RunGame();
	void ShuffleBag();
	bool CanSpawnTetramino();
	void ShowNextTetramn();
	void StartGame();

};

