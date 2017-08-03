// Win32Project1.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Windows.h"
#include "iostream"
#include "conio2.h"
#include <stdlib.h>
#include <ctype.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class ConsoleUtil
{
private:
	int posY, color;
	const int posX = 4;
public:
	static void changepos(int posX, int posY)
	{
		COORD p = { posX, posY };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}

	static void clrscr()
	{
		system("cls");
	}

	static void setColor(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}


};

class Helloworld 
{
private:
	int colorcode;
	bool rainbow;
public:
	void generate()
	{
		ConsoleUtil::changepos(1, 21);
		ConsoleUtil::setColor(colorcode);
		std::cout << "Hello world" << std::endl;
		ConsoleUtil::setColor(15);
	}

	void setColor(int color)
	{
		this->colorcode = color;
	}
};


class Interface
{
public:
	static void drawMenu(bool init) {
		if (init)
		{
			ConsoleUtil::clrscr();
		}
		std::cout << "|-----------------------------------|" << std::endl;
		std::cout << "|       Hello world Generator C++   |" << std::endl;
		std::cout << "|-----------------------------------|" << std::endl;
		std::cout << "\n                                   " << std::endl;
		std::cout << "     1. Select your color            " << std::endl;
		std::cout << "     2. Select effect                " << std::endl;
		std::cout << "     3. Generate!                    " << std::endl;
		std::cout << "\n                                   " << std::endl;
		std::cout << "Created by getfreecancer©            " << std::endl;
		
	}
	static void drawColorChoice(Helloworld hw)
	{
		int code;
		ConsoleUtil::clrscr();
		std::cout << "|-----------------------------------|" << std::endl;
		std::cout << "|       Hello world Generator C++   |" << std::endl;
		std::cout << "|-----------------------------------|" << std::endl;
		std::cout << "| Enter color code:                 |" << std::endl;
		std::cout << "|-----------------------------------|" << std::endl;
		ConsoleUtil::changepos(21, 3);
		std::cin >> code;
		hw.setColor(code);
	}

};

class Cursor
{
public:
	char s = '>';
	int cursorPos = 5;
	int currentChoice;
	void drawCursor(int key)
	{
		ConsoleUtil::changepos(3, 5);
		ConsoleUtil::changepos(3, 6);
		ConsoleUtil::changepos(3, 7);
		std::cout << "  " << std::endl;

		if (key == 72 /*&& currentChoice != 3*/)
		{
			currentChoice = 1;
			ConsoleUtil::changepos(3, 5);
			std::cout << s;
		}
		if (key == 80 /*&& currentChoice != 1*/)
		{
			currentChoice = 3;
			ConsoleUtil::changepos(3, 7);
			std::cout << s;
		}
	}
};

int main()
{
	bool init = false;
	Helloworld hw;
	Cursor cursor;
	cursor.currentChoice = 1;
	ConsoleUtil o1;
	bool handle = false;
	bool running = true;
	Interface::drawMenu(init);
	init = true;

	while(running)  
	{
		int c = getch();
		switch (c)
		{
		case 72 :
		case 80 :
			cursor.drawCursor(c);

			break;
		case 75 :
			std::cout << "VK_LEFT detected" << std::endl;
			break;
		case 77 :
			std::cout << "VK_RIGHT detected" << std::endl;
			break;
		case 13 :
			if (cursor.currentChoice == 1) 
			{
				Interface::drawColorChoice(hw);
				Interface::drawMenu(init);
			}
			if (cursor.currentChoice == 3) 
			{
				hw.generate();
			}

			break;
		case 27 :
			std::cout << "ESCAPE detected" << std::endl;
			running = false;
			break;
		}
		
		
	}
    return 0;
}


