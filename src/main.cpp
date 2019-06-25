#include <stdio.h>
#ifdef _WIN32
    #include <Windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <ctype.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51

#ifndef _WIN32
char getch(){
    // from: https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n", buf); // not needed
    return buf;
 }
#endif

class ConsoleUtil
{
private:
	int posY, color;
	const int posX = 4;
public:
	static void changepos(int posX, int posY)
	{
		#ifdef _WIN32
			COORD p = { posX, posY };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
		#else
			std::cout << "\033[<" << posY << ">;<" << posX << ">H";
		#endif
	}

	static void clrscr()
	{
		#ifdef _WIN32
			system("cls");
		#else
			std::cout << "\033[2J";
		#endif
	}

	static void setColor(int color)
	{
		#ifdef _WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		#else
			std::cout << "\033[" << color << "m";
		#endif
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
		std::cout << "|---------------------------------------|" << std::endl;
		std::cout << "|       Hello world Generator C++       |" << std::endl;
		std::cout << "|---------------------------------------|" << std::endl;
		std::cout << "\n                                       " << std::endl;
		std::cout << "     1. Select your color                " << std::endl;
		std::cout << "     2. Select effect                    " << std::endl;
		std::cout << "     3. Generate!                        " << std::endl;
		std::cout << "\n                                       " << std::endl;
		std::cout << "Created by DradonHunter11                " << std::endl;
		std::cout << "Made work better yes please by HumanGamer" << std::endl;
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

		if (key == KEY_UP /*&& currentChoice != 3*/)
		{
			currentChoice = 1;
			ConsoleUtil::changepos(3, 5);
			std::cout << s;
		}
		if (key == KEY_DOWN /*&& currentChoice != 1*/)
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
		case KEY_UP :
		case KEY_DOWN :
			cursor.drawCursor(c);

			break;
		case KEY_LEFT :
			std::cout << "VK_LEFT detected" << std::endl;
			break;
		case KEY_RIGHT :
			std::cout << "VK_RIGHT detected" << std::endl;
			break;
		case KEY_ESCAPE :
			std::cout << "ESCAPE detected" << std::endl;
			running = false;
			break;
		case KEY_1 :
			Interface::drawColorChoice(hw);
			Interface::drawMenu(init);
			break;
		case KEY_2 :
			// TBD: Effects
			break;
		case KEY_3 :
			hw.generate();
			break;
		//default:
		//	std::cout << c << std::endl;
		//break;
		}
		
	}

    return 0;
}


