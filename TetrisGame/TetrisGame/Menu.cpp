#include "Menu.h"
#include <iostream>
#include "windows.h"
#include <conio.h>



void Menu::InitGameMenu()
{
	system("mode con cols=50 lines=35");
	CursorLocation.SetPoint(3, 1);
	system("color 02");
	DrawMenu();
}



void Menu::DrawMenu()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			std::cout << StartMenu[i][j];
		}
		std::cout << "\n\n";
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
}

void Menu::SwitchOption(int Dir)
{
	if (CursorLocation.GetY() + Dir != 0)
	{
		if (CursorLocation.GetY() + Dir != 4)
		{
			StartMenu[CursorLocation.GetY()][CursorLocation.GetX()] = ' ';
			CursorLocation.SetY(CursorLocation.GetY() + Dir);
			StartMenu[CursorLocation.GetY()][CursorLocation.GetX()] = '>';
			DrawMenu();
		}
	}
}

int Menu::GetOption()
{
	return CursorLocation.GetY();
}

void Menu::DrawSettings()
{
	system("cls");
	std::cout << "W - Rotate figure.\nA - Move left.\nD - Move right.\nS - Fast down.\nP - Pause.\nEsc - Return to menu.\n\nPress Esc - go to menu.";
	while (true)
	{
		if (_kbhit())
		{
			char KeyPressed = _getch(); 
			if (KeyPressed == 27)
			{
				break;
			}
		}
	}
	system("cls");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
	DrawMenu();
}
