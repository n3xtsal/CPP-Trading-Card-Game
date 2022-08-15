#pragma once

#include"Team.h"
#include "Random.h"

//Static method to generate a random name and return it 
//Format of name is "X. XXX", exactly 6 chars long, where X is a random capital letter 
static string RandomNameGenerator()
{
	string name = "______"; //local variable to use

	for (int i = 0; i < 6; i++) //names are 6 chars long
	{
		if (i == 1) //second char in a name must be a .
		{
			name[i] = '.';
		}
		else if (i == 2) //third char in a name is blank space
		{
			name[i] = ' ';
		}
		else //every other char is a random letter
		{
			name[i] = 'A' + GEP::RandomRange(0, 25); //this line generates a random letter between A and Z.
		}

	}

	return name; //returning name generated to user
}

//Class for generating player pool
class PlayerPoolGenerator
{
private:
	int numPlayers; //number of players
	vector<Player> playerPool; //the pool of players to buy from 

public:
	//Getters
	int getNumPlayers() { return numPlayers; } //getting number of players
	Player getPlayerFromPool(int pos) { return playerPool[pos]; } //getting one player from pool
	vector<Player> getPlayersFromPool() { return playerPool; } //getting the entire pool

	//Setters
	void setNumPlayers(int num) { numPlayers = num; } //setting number of players from 10-20
	void setPlayerInPool(Player player, int pos) { playerPool[pos] = player; } //adding a player to specific place in pool
	void setPlayerPool(vector<Player> players) { playerPool = players; } //setting an entire pool of players 

	//Player generation method
	void genRandomPlayers()
	{
		for (int i = 0; i < getNumPlayers(); i++) //loop for randomly generated size of pool
		{
			//Creating player
			Player tempPlayer; //temporary variable for new player
			tempPlayer.setPlayerName(RandomNameGenerator()); //create name using random name gen function
			tempPlayer.setSkill(GEP::RandomRange(20, 100)); //set skill of player between 20 and 100

			int skill = tempPlayer.getSkill(); //set skill value from above to variable
			int price = (GEP::RandomRange(100, 200) + 500) * skill; //adjust price according to player
			tempPlayer.setPrice(price); //add calculated price of player to the the temp player variable

			//Add temporary player to new slot in playerPool
			playerPool.push_back(tempPlayer);
		}
	}
};

//Actual GameManager class
class GameManager
{
private:
	//Attributes
	bool isGameOver = false; //boolean var to check if game condition to finish has been met
	bool isValid = false; //boolean to check if user input is in valid range

	//Instances of user team and cards available for purchase
	Team myTeam;
	PlayerPoolGenerator cardPool;

public:
	//Getter
	bool getIsValid() { return isValid; }

	//Method for initializing values
	void Start()
	{
		//Asking for user's team name and storing it in variable
		string myName;
		cout << "What is your team's name: ";
		cin >> myName;
		myTeam.setTeamName(myName);

		//Asking for user input and storing it in variable
		cout << "Enter number of players you want available between 10 and 20: ";
		int numIn; //variable for user input for number of cards to initialize in card pool
		cin >> numIn;

		//if input is in the valid range then create cards and exit loop
		if (numIn >= 10 && numIn <= 20)
		{
			cardPool.setNumPlayers(numIn);
			cout << "Generating " << cardPool.getNumPlayers() << " players" << endl << endl;
			cardPool.genRandomPlayers();
			isValid = true;
		}

	}

	//The game looping method to ask whether user wants to buy a unit
	//Leaves game when all units have been bought or user money has gone down to 0
	void GameLoop()
	{
		int numNo = 0; //Variable for how many times user has rejected card
		int numYes = 0; //Variable for how many times user has purchased a card

		while (isGameOver == false) //run loop while isGameOver variable is false
		{
			int randVal = GEP::RandomRange(0, cardPool.getNumPlayers() - 1);

			Player tempPlayer = cardPool.getPlayerFromPool(randVal); //temporary player variable

			//check if player has been purchased
			if (tempPlayer.getIsPurchased() == 0)
			{
				cout << "Card# " << randVal << "/" << cardPool.getNumPlayers() << endl;

				tempPlayer.printPlayer(); //print player values

				cout << "Cash on Hand: $" << myTeam.getCashAvail() << endl;

				cout << "Cash Spent: $" << myTeam.getCashSpent() << endl;
				
				cout << "Players purchased: " << numYes << endl;

				cout << "Purchase this Player Card? Yes(1) or no(0)?" << endl; //prompt user input

				string buyNum = ""; //temporary integer for seeing user input values

				cin >> buyNum; //store input into variable

				cout << endl;

				if (buyNum == "0") //if user chose no then go to next card
				{
					tempPlayer.setIsPurchased(-1); //change player purchased status to denied
					cardPool.setPlayerInPool(tempPlayer, randVal); ////swap local tempPlayer into the cardPool
					numNo++; //add to number of rejections
					cout << "You denied Player Card " << randVal  << endl;
					cout << endl;
				}
				else if (buyNum == "1") //if user chose yes
				{
					if (tempPlayer.getPrice() > myTeam.getCashAvail()) //check if user accidentally buys something too expensive
					{
						numNo++; //increment number of rejections
						tempPlayer.setIsPurchased(-1); //set purchased status such that user cant access unaffordable card
						cardPool.setPlayerInPool(tempPlayer, randVal); //swap changed local tempPlayer into the cardPool
						cout << "You do not have the funds for this Player Card, purchase rejected." << endl;
						cout << endl;
						continue;
					}
					else //if they can afford it then add it properly to their cards team
					{
						myTeam.subCashAvail(tempPlayer.getPrice()); //subtract current player price from total cash
						myTeam.addCashSpent(tempPlayer.getPrice()); //add to total amount of cash spent from player price
						myTeam.addTotalSkill(tempPlayer.getSkill()); //add to total skill from player skill
						tempPlayer.setIsPurchased(1); //change player purchased status to purchased
						cardPool.setPlayerInPool(tempPlayer, randVal); //swap changed local tempPlayer into the cardPool
						numYes++; //increment number of times player has purchased
						myTeam.setMyPlayer(tempPlayer); //add player to my team
						cout << "Player Card " << randVal << " purchased successfully" << endl;
						cout << endl;
					}

				}
				else //if user did neither then we restart 
				{
					cout << "Choose a valid input next time... " << endl;
					cout << endl;
					continue;
				}
			}
			else //if player has been purchased then continue the loop and ignore it
			{
				continue;
			}

			// End the game if the number of rejections and acceptions equal to the total amount of player cards
			// End the game if the amount of cash available to the player is less than 12000
			//Printing team
			//Calculating and then printing avg skill
			if (((numNo + numYes) == cardPool.getNumPlayers()) || myTeam.getCashAvail() < 12000)
			{
				cout << endl;
				myTeam.printTeam();
				int avgSkill = myTeam.getTotalSkill() / numYes;
				cout << "Average Skill Rating: " << avgSkill << endl;
				isGameOver = true;
			}
		}
	}
};