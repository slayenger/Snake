#include <iostream>
#include <conio.h>м
#include <Windows.h>
using namespace std;
bool GameOver;
const int w = 40; //width of map
const int h = 20; //height of map
int x, y, FruitX, FruitY, score; //coordinates
int TailX[100], TailY[100]; //coordinates of tail;
int CTail;
enum eDirection
{
	STOP=0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
eDirection dir;

//start of game
void Setup()
{
	GameOver = false;
	//dir = STOP;
	x = w / 2 - 1 ; //Starting position
	y = h / 2 - 1 ;
	srand(time(NULL));
	FruitX = rand() % w;
	FruitY = rand() % h;
	score = 0;
}
//drawing map, snake etc.
void Draw()
{
	HANDLE wall = GetStdHandle(STD_OUTPUT_HANDLE); //character colors 
	system("cls"); //clear of system
	for (int i=0; i<w+1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (j == 0 || j == w - 1)
			{
				SetConsoleTextAttribute(wall, FOREGROUND_BLUE);
				cout << "#";
			}
				
			if (i == y && j == x)
			{
				SetConsoleTextAttribute(wall, FOREGROUND_GREEN);
				cout << "0"; //drawing snake
			}
			else if (i == FruitY && j == FruitX) 
			{
				SetConsoleTextAttribute(wall, FOREGROUND_RED);
				cout << "$"; //drawing fruit
			}
				
			else 
			{
				bool Print = false;
				for (int k = 0; k < CTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						Print = true;
						SetConsoleTextAttribute(wall, FOREGROUND_GREEN);
						cout << "0";
					}
						
				}
				if (Print == false)
					cout << " " ;
			}

			
		}
		cout << endl;
	}

	for (int i = 0; i < w+1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
	
}
//Click tracking
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (dir != RIGHT)
			dir = LEFT;
			break;
		case 'd':
			if(dir != LEFT)
			dir = RIGHT;
			break;
		case 'w':
			if (dir !=DOWN)
			dir = UP;
			break;
		case 's':
			if (dir != UP)
			dir = DOWN;
			break;
		case 'q': //Quitting the game 
			GameOver = true;
			break;
		}
	}
}
//all logic of game
void Logic()
{
	int PrevX = TailX[0];
	int PrevY = TailY[0];
	int Prev2X, Prev2Y;
	TailX[0] = x;
	TailY[0] = y;
	for (int i = 1; i < CTail; i++)
	{
		Prev2X = TailX[i];
		Prev2Y = TailY[i];
		TailX[i] = PrevX;
		TailY[i] = PrevY;
		PrevX = Prev2X;
		PrevY = Prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x = x - 1;
		break;
	case RIGHT:
		x = x + 1;
		break;
	case UP:
		y = y - 1;
		break;
	case DOWN:
		y = y + 1;
		break;
	}

	if (x >= w - 1) //stepping outside
		x = 0;
	else if (x < 0)
		x = w - 2;
	if (y >= h)
		y = 0;
	else if (y < 0)
		y = h - 2;
	for (int i = 0; i < CTail; i++)
	{
		if (TailX[i] == x && TailY[i] == y)
			GameOver = true;
	}
	if (x == FruitX && y == FruitY)
	{
		score += 1;
		srand(time(NULL));
	FruitX = rand() % w;
	FruitY = rand() % h;
	CTail += 1;

	}
}

int main()
{
	HANDLE wall = GetStdHandle(STD_OUTPUT_HANDLE); //character colors 
	Setup();
	while (GameOver == false)
	{
		Draw();
		Input();
		Logic();
	}

	return 0;

}