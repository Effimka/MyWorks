#include "Tetris.h"
#include "windows.h"
#include <conio.h>
#include <thread>

Tetris::Tetris()
{
	NumOfTetramino = 0;
	GameScore = 0;
	SpeedDown = 500;
	bIsPauseGame = false;
}

bool Tetris::SpawnTetramino(Tetramino& tetramin)
{
	if (CanSpawnTetramino())
	{
		if (NumOfTetramino == 7)
			NumOfTetramino = 0;

		if (NumOfTetramino == 0)
			ShuffleBag();

		tetramin.SetTetramino(TetraminoBag[NumOfTetramino]);
		NumOfTetramino++;
		return true;
	}
	return false;	
}

bool Tetris::FallDown(Tetramino& tetramin, GameField& Field)
{
	bool result = false;
	if (Field.CheckYDownCollision(tetramin.GetGlobalPoints()))
	{
		for (int i = 0; i < 4; i++)
		{
			tetramin.GetGlobalPoints()[i].SetY(tetramin.GetGlobalPoints()[i].GetY() + 1);
		}
	}
	else
	{
		Field.FixTetraminoOnField(tetramin);
		result = true;
	}
	return result;
}

void PlayerPressed(int& SpeedDown, Tetramino& figure, GameField& const Field, bool& bIsPauseGame, bool& bIsReturnMenu, bool& bIsLose)
{
	while (!bIsReturnMenu && !bIsLose)
	{
		if (_kbhit())
		{
			char KeyPressed = _getch();

			if (!bIsPauseGame)
			{
				if (KeyPressed == 'w' || KeyPressed == 'W')
				{
					Field.RotateTetramino(figure);
				}
				if (Field.CheckXLeftCollision(figure.GetGlobalPoints()))
				{
					if (KeyPressed == 'a' || KeyPressed == 'A')
					{

						for (int i = 0; i < 4; i++)
						{
							figure.GetGlobalPoints()[i].SetX(figure.GetGlobalPoints()[i].GetX() - 1);
						}

					}
				}
				if (Field.CheckXRightCollision(figure.GetGlobalPoints()))
				{
					if (KeyPressed == 'd' || KeyPressed == 'D')
					{
						for (int i = 0; i < 4; i++)
						{
							figure.GetGlobalPoints()[i].SetX(figure.GetGlobalPoints()[i].GetX() + 1);
						}

					}
				}
				if (KeyPressed == 's' || KeyPressed == 'S')
				{
					if (SpeedDown == 500)
						SpeedDown = 150;
					else
						SpeedDown = 500;
				}
			}

			if (KeyPressed == 'p' || KeyPressed == 'P')
			{
				bIsPauseGame = !bIsPauseGame;
			}

			if (KeyPressed == 27)
			{
				bIsReturnMenu = true;
			}
		}
	}
	return;
}

void Tetris::RunGame()
{
	system("color 04");
	bool bIsReturnMenu = false;
	bool bIsLose = false;
	std::thread KeyboardWork(&PlayerPressed, std::ref(SpeedDown), std::ref(tetramin), std::ref(Field), std::ref(bIsPauseGame),
							std::ref(bIsReturnMenu), std::ref(bIsLose));

	SpawnTetramino(tetramin);

	while (!bIsLose && !bIsReturnMenu)
	{
		if (!bIsPauseGame)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
			Field.UpdateField(tetramin, GameScore);
			std::cout << "\n\n";
			std::cout << " Game Score: " << GameScore << "\t\n";
			std::cout << " Next Tetramin: \n\n";
			ShowNextTetramn();
			if (FallDown(tetramin, Field))
			{
				if (!SpawnTetramino(tetramin))
				{
					bIsLose = true;
				}
			}
			std::cout << "\n\n";
			Sleep(SpeedDown);
		}
	}

	KeyboardWork.join();
	if (bIsLose)
	{
		std::cout << "You are lose!!";
		Sleep(1000);
		system("cls");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
		system("color 02");
		menu.DrawMenu();
	}

	if (bIsReturnMenu)
	{
		system("cls");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
		system("color 02");
		menu.DrawMenu();
	}
}

void Tetris::ShuffleBag()
{
	for (int i = 0; i < 7; i++)
		TetraminoBag[i] = i;
	
	srand(time(0));
	for (int i = 0; i < 7; i++)
		std::swap(TetraminoBag[i], TetraminoBag[std::rand() % 7]);
}

bool Tetris::CanSpawnTetramino()
{
	return 	Field.CheckYUpCollision();
}

void Tetris::StartGame()
{
	menu.InitGameMenu();
	bool bIsCloseGame = false;
	Tetris* game = nullptr;
	while (!bIsCloseGame)
	{
		if (_kbhit())
		{
			char KeyPressed = _getch();

			if (KeyPressed == 'w' || KeyPressed == 'W')
			{
				menu.SwitchOption(-1);
			}

			if (KeyPressed == 's' || KeyPressed == 'S')
			{
				menu.SwitchOption(1);
			}

			if (KeyPressed == 13)
			{
				switch (menu.GetOption())
				{
				case 1:
					delete game;
					game = nullptr;
					game = new Tetris();
					game->RunGame();
					break;
				case 2:
					menu.DrawSettings();
					break;
				case 3:
					system("cls");
					std::cout << "Good bye! \n";
					bIsCloseGame = true;
					break;
				default:
					break;
				}
			}

		}
	}
}

void Tetris::ShowNextTetramn()
{
	Tetramino Tetramin;
	Tetramin.SetTetramino(TetraminoBag[NumOfTetramino]);
	char matrix[4][4];
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			matrix[y][x] = ' ';
		}
	}
	for (int i = 0; i < 4; i++)
	{
		matrix[Tetramin.GetLocalPoints()[i].GetY()][Tetramin.GetLocalPoints()[i].GetX()] = 'X';
	}
	for (int y = 0; y < 4; y++)
	{
		std::cout << " \t";
		for (int x = 0; x < 4; x++)
		{
			std::cout << matrix[y][x] << " ";
		}
		std::cout << "\n";
	}
}
