#pragma once

#include <memory>
#include "Player.h"
#include <vector>

using namespace std;

class Team
{
private:
	string teamName;
	int cashAvailable = 100000;
	int cashSpent;
	vector<Player> teamPlayers;
	int cumulativeSkillRating;

public:
	//Getters
	int getCashAvail() { return cashAvailable; }
	int getCashSpent() { return cashSpent; }
	int getTotalSkill() { return cumulativeSkillRating; }

	//Setters
	void setTeamName(string name) { teamName = name; }
	void subCashAvail(int num) { cashAvailable -= num; }
	void addCashSpent(int num) { cashSpent += num; }
	void setMyPlayer(Player player) { teamPlayers.push_back(player); }
	void addTotalSkill(int num) { cumulativeSkillRating += num; }

	//Print Team Properties
	void printTeam()
	{
		cout << "TEAM " << teamName << endl;
		for (int i = 0; i < teamPlayers.size(); i++)
		{
			cout
				<< i + 1 << ". " << teamPlayers[i].getPlayerName()
				<< " " << teamPlayers[i].getSkill()
				<< " $" << teamPlayers[i].getPrice()
				<< endl;
		}
		cout << "Cash Spent: $" << cashSpent << endl;
		cout << "Cash Available: $" << cashAvailable << endl;
	}
};