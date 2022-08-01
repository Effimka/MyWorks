#pragma once
#include "Point.h"

class Menu
{
	char StartMenu[4][16]
	{
		{' ',' ','T',' ','E',' ','T',' ','R',' ','I',' ','S',' ',' ',' '},
		{' ',' ',' ','>',' ','S','t','a','r','t',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ','S','e','t','t','i','n','g','s',' ',' ',' '},
		{' ',' ',' ',' ',' ','E','x','i','t',' ',' ',' ',' ',' ',' ',' '},
	};

	Point CursorLocation;
public:
	void InitGameMenu();
	void DrawMenu();
	void SwitchOption(int Dir);
	int GetOption();
	void DrawSettings();
};

