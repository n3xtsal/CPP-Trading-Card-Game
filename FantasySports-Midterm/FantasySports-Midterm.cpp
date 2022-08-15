// FantasySports-Midterm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GameManager.h"

int main()
{
	GameManager gameManage;
	gameManage.Start();
	if (gameManage.getIsValid() == false) //if input is invalid then exit the game
	{
		cout << "You must enter a number between 10 and 20. Exiting the game." << endl;
	}
	else //otherwise, continue with the game
	{
		gameManage.GameLoop();
	}
}