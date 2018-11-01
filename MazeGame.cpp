
#include <iostream>
#include <array>
#include <random>
#include <ctime>
#include <ncurses.h>
#include <stdlib.h>
using namespace std;
const char mapCodeUser = '@';
const char mapCodeExit = 'E';
const char mapCodeWall = 'X';
const char mapCodeField = ' ';
const char mapCodeKey = 'K';
const char mapCodeW = 'W';
const int mapColums = 20;
const int mapRows = 20;
using Map = array<array<char, mapColums>,mapRows >;
array<array<char, mapRows>,mapColums> map;

bool doesUserWantToPlay();
void display();
void field();
void StartUserAndExitAndKeyPos();
void UserMove();
bool ChekMoveAcsses(char MoveWay);

 bool Key = false,Exit=false;
int ExitPosX, ExitPosY, UserPosX, UserPosY, KeyPosX, KeyPosY, UserPosXStart, UserPosYStart;
int main()
{
	Map map;
	
	while (doesUserWantToPlay())
	{
		field();
		StartUserAndExitAndKeyPos();
		display();       
		while ((Exit != true) || (Key != true))
		{
			
			UserMove();
			if ((UserPosX == ExitPosX) && (UserPosY == ExitPosY))
			{
				Exit = true;
			}
			if ((UserPosX == KeyPosX) && (UserPosY == KeyPosY))
			{
				Key = true;
			}
		}
		cout << "U WIN" << endl;                                     
	}
}

bool doesUserWantToPlay()
{
	bool result = false;
	char answer = '\0';
	cout << "==Labirint==" << endl;
	while (true)
	{	
		cout << "Do you want to play game? ((1) - Yes | (0) -NO)" << endl;
		cin >> answer;
		if (answer == '1')
		{
			result = true;
			return result;
		}
		else if (answer == '0')
		{
			cout << "buy buy" << endl;
			break;
		}
		else
		{
			cout << "I don't understand u!" << endl;

		}
	}
	return result;
}
void display()
{
	system("cls");
	for (int column = 0; column < mapColums; ++column)
	{
		for (int row = 0; row < mapRows; ++row)
		{
			cout << map[column][row];
		}
		cout << endl;
	}
}
void field()
{
	for (int column = 0; column < mapColums; ++column)
	{
		for (int row = 0; row < mapRows; ++row)
		{
			map[column][row] = mapCodeField;
		}
	}
	for (int column = 0; column < mapColums; column++)
	{
		map[mapColums-1][column] = mapCodeWall;
		map[0][column] = mapCodeWall;
		map[column][0] = mapCodeWall;
		map[column][mapRows-1] = mapCodeWall;
	}
	
}
void StartUserAndExitAndKeyPos()
{
	time_t Forrandom;
	Forrandom = time(NULL);
	srand(Forrandom);
	ExitPosX = rand() % (mapColums-2)+1;
	ExitPosY = rand() % (mapRows-2)+1;
	KeyPosX = rand() % (mapColums - 2) + 1;
	KeyPosY = rand() % (mapRows - 2) + 1;
	UserPosX = rand() % (mapColums-2)+1;
	UserPosY = rand() % (mapRows-2)+1;
	if ((ExitPosX == UserPosX && ExitPosY == UserPosY) || (KeyPosX==UserPosX && KeyPosY==UserPosY) || (KeyPosX==ExitPosX && KeyPosY==ExitPosY))
	{
		StartUserAndExitAndKeyPos();
	}
	map[ExitPosX][ExitPosY] = mapCodeExit;
	map[UserPosX][UserPosY] = mapCodeUser;
	map[KeyPosX][KeyPosY] = mapCodeKey;
}
void UserMove()
{
	char WayToMove;
	cout << "Please input way to move!((u) - up, (d) - down,(r) - right, (l) -left).(If u can't win or dislike to play please enter e" << endl;
	cin >> WayToMove;
	if (ChekMoveAcsses(WayToMove))
	{
		display();
	}
	else
	{
		cout << "U can't move there" << endl;
	}
	
	
}
bool ChekMoveAcsses(char MoveWay)
{
	int newUserPosX=UserPosX, newUserPosY=UserPosY;
	switch (MoveWay)
	{
	case 'u':
	{
		newUserPosX = UserPosX - 1;
		break;
	}
	case 'd':
	{
		newUserPosX = UserPosX + 1;
		break;
	}
	case 'r':
	{
		newUserPosY = UserPosY + 1;
		break;
	}
	case 'l':
	{
		newUserPosY = UserPosY - 1;
		break;
	}
	case 'e':
	{
		exit(0);
		break;
	}
	default:
		cout << "I don'y understand u!" << endl;
		return false;
	}
	if ((map[newUserPosX][newUserPosY] == mapCodeExit) && (Key != true))
	{
		cout << "U don't have key" << endl;
		return false;
	}
	if (map[newUserPosX][newUserPosY] != mapCodeWall)
	{
	
		map[UserPosX][UserPosY] = mapCodeField;
		UserPosX = newUserPosX;
		UserPosY = newUserPosY;
		map[UserPosX][UserPosY] = mapCodeUser;
		return true;
	}
	return false;
};
