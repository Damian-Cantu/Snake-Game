#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;

char map[20][40]; //2D array for the map 
void gotoxy(int column, int line) // function that I think gets coordinates of the screen ?
{
	COORD coord;
	coord.Y = column;
	coord.X = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), coord
	);
}
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;   info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void timer(int t)
{
	for (int x = 0; x < t; x++) //some kind of timer I guess? 
	{
		gotoxy(20, 40); //sets the cursor to these coordinates
	}
}

void spawn(char c, int x, int y)
{
	gotoxy(x, y);
	cout << c;
	map[x][y] = c;
}

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //to display color on the screen
	srand(time(0));

	bool game = true;

	char f = 'A';
	int fx = rand() % 18 + 1;
	int fy = rand() % 38 + 1;

	int oldscore = 0;
	int score = 0;

	int tails = 0;
	int tailx[800];
	int taily[800];
	int prevx[800];
	int prevy[800];
	bool tail[800];

	tailx[0] = 10;
	taily[0] = 10;
	
	for (int i = 1; i < 800; i++)
	{
		tailx[i] = 0;
		taily[i] = 40;
		tail[i] = false;
	}
	tail[0] = true;

	bool up = false, down = false, left = false, right = false;
	bool keyup = true, keydown = true, keyleft = true, keyright = true;

	int t = 8000;

	bool pause = false;

	char choice; //variable that holds key input

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ifstream inFile;
	inFile.open("map.txt"); //opens the map file
	for (int x = 0; x < 20; x++) //loop for x coordinates on the map ROW
	{
		for (int y = 0; y < 40; y++) //loop for y coordinates on the map COLUMN
		{
			inFile >> map[x][y]; //grabs every chracter on the map x&y
		}
	}
	inFile.close();

	ifstream inFile2;
	inFile2.open("highscore.txt");
	inFile2 >> oldscore;
	inFile2.close();

	SetConsoleTextAttribute(h, 10);
	spawn('>', tailx[0], taily[0]);

	system("cls"); //cleares the screen from my understanding ?

	SetConsoleTextAttribute(h, 9);
	for (int x = 0; x < 20; x++) //loop for x coordinates on the map ROW
	{
		for (int y = 0; y < 40; y++) //loop for y coordinates on the map COLUMN
		{
			if (map[x][y] == '.') //if the coordinate is a period
				map[x][y] = ' '; //convertst the period into a blank space
			cout << map[x][y]; //displays the map
		}
		cout << endl; //breaks the map rows after the rows characters have printed
	}

	do //infinite while loop for the game
	{
		if (_kbhit()) //checks if the keyboard is pressed
		{
			choice = _getch(); //gets the pressed key and assigns it to variable choice

			if (keyup && choice == 'i' && tail[0] || keyup && choice == 'w' && tail[0] || keyup && GetAsyncKeyState(VK_UP) && tail[0])
			{
				t = 12000;
				up = true;
				down = false; 
				left = false; 
				right = false; 
			}
			if (keydown && choice == 'k' && tail[0] || keydown && choice == 's' && tail[0] || keydown && GetAsyncKeyState(VK_DOWN) && tail[0])
			{
				t = 12000;
				up = false;
				down = true; 
				left = false; 
				right = false;
			}
			if (keyleft && choice == 'j' && tail[0] || keyleft && choice == 'a' && tail[0] || keyleft && GetAsyncKeyState(VK_LEFT) && tail[0])
			{
				t = 8000;
				up = false;
				down = false;
				left = true;
				right = false; 
			}
			if (keyright && choice == 'l' && tail[0] || keyright && choice == 'd' && tail[0] || keyright && GetAsyncKeyState(VK_RIGHT) && tail[0])
			{
				t = 8000;
				up = false;
				down = false;
				left = false; 
				right = true;
			}
			if (pause == false && choice == 'p' && tail[0])
			{
				pause = true;
				gotoxy(9, 16);
				cout << " PAUSED ";
			}
			else if (pause && choice == 'p' && tail[0])
			{
				pause = false;
				gotoxy(9, 16);
				cout << "        ";
			}
			if (choice == 'e')
			{
				game = false;
			}
			if (tail[0] == false && choice == 'r')
			{
				gotoxy(9, 14);
				cout << "           ";
				gotoxy(10, 10);
				cout << "                    ";

				for (int i = 0; i < 800; i++)
				{
					spawn(' ', tailx[i], taily[i]);
				}
				if (tailx[0] == 0 || taily[0] == 39 || taily[0] == 0 || tailx[0] == 19)
				{
					SetConsoleTextAttribute(h, 9);
					spawn('#', tailx[0], taily[0]);
				}
				for (int i = 1; i < 800; i++)
				{
					tailx[i] = 0;
					taily[i] = 40;
					tail[i] = false;
				}
				tail[0] = true;

				gotoxy(10, 45);
				cout << "SCORE: " << "           ";
				score = 0;

				tails = 0;

				tailx[0] = 10;
				taily[0] = 10;
				spawn('>', tailx[0], taily[0]);

				up = false, down = false, left = false, right = false;
				keyup = true, keydown = true, keyleft = true, keyright = true;
			}
		}

		timer(t);
		hidecursor();
		SetConsoleTextAttribute(h, 6);
		gotoxy(9, 45);
		cout << "HIGHSCORE: " << oldscore;
		gotoxy(10, 45);
		cout << "SCORE: " << score;

		SetConsoleTextAttribute(h, 4);
		spawn(f, fx, fy);

		if (pause == false)
		{
			if (up == true)
			{
				SetConsoleTextAttribute(h, 10);
				prevx[0] = tailx[0];
				prevy[0] = taily[0];
				//Sleep(140);
				spawn(' ', tailx[0], taily[0]);
				tailx[0]--;
				spawn('^', tailx[0], taily[0]);
				keyup = true;
				keydown = false;
				keyleft = true;
				keyright = true;
			}
			if (down == true)
			{
				SetConsoleTextAttribute(h, 10);
				prevx[0] = tailx[0];
				prevy[0] = taily[0];
				//Sleep(140);
				spawn(' ', tailx[0], taily[0]);
				tailx[0]++;
				spawn('v', tailx[0], taily[0]);
				keyup = false;
				keydown = true;
				keyleft = true;
				keyright = true;
			}
			if (left == true)
			{
				SetConsoleTextAttribute(h, 10);
				prevx[0] = tailx[0];
				prevy[0] = taily[0];
				//Sleep(90);
				spawn(' ', tailx[0], taily[0]);
				taily[0]--;
				spawn('<', tailx[0], taily[0]);
				keydown = true;
				keyup = true;
				keyleft = true;
				keyright = false;
			}
			if (right == true)
			{
				SetConsoleTextAttribute(h, 10);
				prevx[0] = tailx[0];
				prevy[0] = taily[0];
				//Sleep(90);
				spawn(' ', tailx[0], taily[0]);
				taily[0]++;
				spawn('>', tailx[0], taily[0]);
				keydown = true;
				keyup = true;
				keyleft = false;
				keyright = true;
			}

			for (int i = 1; i < 800; i++)
			{
				if (tail[i] && up)
				{
					spawn(' ', tailx[i], taily[i]);
					prevx[i] = tailx[i];
					prevy[i] = taily[i];
					tailx[i] = prevx[i - 1];
					taily[i] = prevy[i - 1];
					spawn('o', tailx[i], taily[i]);
				}
				if (tail[i] && down)
				{
					spawn(' ', tailx[i], taily[i]);
					prevx[i] = tailx[i];
					prevy[i] = taily[i];
					tailx[i] = prevx[i - 1];
					taily[i] = prevy[i - 1];
					spawn('o', tailx[i], taily[i]);
				}
				if (tail[i] && left)
				{
					spawn(' ', tailx[i], taily[i]);
					prevx[i] = tailx[i];
					prevy[i] = taily[i];
					tailx[i] = prevx[i - 1];
					taily[i] = prevy[i - 1];
					spawn('o', tailx[i], taily[i]);
				}
				if (tail[i] && right)
				{
					spawn(' ', tailx[i], taily[i]);
					prevx[i] = tailx[i];
					prevy[i] = taily[i];
					tailx[i] = prevx[i - 1];
					taily[i] = prevy[i - 1];
					spawn('o', tailx[i], taily[i]);
				}

				if (tailx[0] == tailx[i] && taily[0] == taily[i])
				{
					up = false; down = false; left = false; right = false;
					tail[0] = false;
					gotoxy(9, 14);
					cout << " GAME OVER ";
					gotoxy(10, 10);
					cout << " PRESS R TO RESTART ";
				}

				if (tailx[i] == fx && taily[i] == fy)
				{
					fx = rand() % 18 + 1;
					fy = rand() % 38 + 1;
					spawn(f, fx, fy);
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (tailx[0] == fx && taily[0] == fy)
			{
				fx = rand() % 18 + 1;
				fy = rand() % 38 + 1;
				SetConsoleTextAttribute(h, 4);
				spawn(f, fx, fy);
				tails++;
				//Sleep(200);
				tail[tails] = true;
				score += 10;
			}

			if (tailx[0] == 0 || taily[0] == 39 || taily[0] == 0 || tailx[0] == 19)
			{
				up = false; down = false; left = false; right = false;
				tail[0] = false;
				gotoxy(9, 14);
				cout << " GAME OVER ";
				gotoxy(10, 10);
				cout << " PRESS R TO RESTART ";
			}

			if (score > oldscore)
			{
				ofstream outFile;
				outFile.open("highscore.txt");
				outFile << score;
				outFile.close();
				oldscore = score;
			}
		}
	} while (game == true);
	return 0;
}