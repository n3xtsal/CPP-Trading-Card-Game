#pragma once

#include<iostream>
#include <string>

using namespace std;

class Player
{
private:
	//Attributes
	string playerName;
	int skill;
	int price;
	int isPurchased = 0; //0 means no decision made, 1 means purchased, -1 means declined

public:
	//Getters
	string getPlayerName() { return playerName; }
	int getSkill() { return skill; }
	int getPrice() { return price; }
	int getIsPurchased() { return isPurchased; }

	//Setters
	void setPlayerName(string name) { playerName = name; }
	void setSkill(int num) { skill = num; }
	void setPrice(int num) { price = num; }
	void setIsPurchased(int tf) { isPurchased = tf; }

	//Printing Player Attributes
	void printPlayer()
	{
		cout
			<< "Name: " << playerName << endl
			<< "SkillRating: " << skill << endl
			<< "Purchase Price: $" << price << endl
			;
	}
};