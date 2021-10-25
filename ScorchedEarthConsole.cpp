#include "ScorchedEarthConsole.h"

using namespace std;

//structure for a player object
struct Player
{
	int id = -1;				//id of a player
	bool human = false;			//bool for determining if player is a human or AI
	string name = "newbie";		//player's name
	float health = 0;			//player's health
	int diff = 0;				//difficulty of a player (only used for AI players)
};

//structure for a team object
struct Team
{
	int id = 0;		//id of a particular team
	Player p[100];	//array of all players in a team
};

char gameState = 's';		// 's' = stopped    'p' = playing    'f' = finished
struct Team teams[3];		//array of teams (starting to count from 1)	TODO: functionality for more than 2 teams?
int sizes[] = {0,0,0};		//actual player numbers in teams (starting to count from 1)


//Function that establishes player ids and human status from a string
// and returns ture if user passed the exact number of parameters
bool EstablishTeams(Player *t, char *S, int id) {

	int h = 0;		//int h for keeping count of established players

	//for loop that goes through every character of a srting provided by user
	for (int i = 1; i < strlen(S); i++)
	{
		//switch for distinguishing different characters
		switch (S[i])
		{
		//human player
		case 'h':
			t[h].human = true;
			t[h].health = 100;
			h++;
			break;
		//easy AI
		case 'e':
			t[h].id = h;
			t[h].human = false;
			t[h].health = 100;
			t[h].diff = 1;
			h++;
			break;
		//medium AI
		case 'm':
			t[h].id = h;
			t[h].human = false;
			t[h].health = 100;
			t[h].diff = 2;
			h++;
			break;
		//difficult AI
		case 'd':
			t[h].id = h;
			t[h].human = false;
			t[h].health = 100;
			t[h].diff = 3;
			h++;
			break;
		}
	}

	//statement that determines if all players have been correctly established and returns a value
	if (h == sizes[id]) {
		return true;
	}
	else {
		if (h > sizes[id]) {
			printf("\nToo many parameters, try again!\n");
			return false;
		}
		else{
			printf("\nNot enough parameters, try again!\n");
			return false;
		}
	}

	printf("\n");
}

//Function that determines the number of players in each team
// and the amount of human and AI players
void InputTeams() {

	//Load the team sizes
	for (int i = 1; i <= 2; i++)
	{
		char tempC[100];
		teams[i].id = i;
		do {

			printf("\nInput the size of team %d:   ", i);
			scanf_s("%d", &sizes[i]);

			printf("\n");

			//Read the player types
			printf("\nPut in an h character for a human player and e,m,d character for an AI player");
			printf("\n(Easy, Medium, Difficult) and end with a ; (eg: h e h d ;)\n");
			int x = -1;
			do {
				x++;
				scanf("%c", &tempC[x]);
			} while (tempC[x] != ';');

			//Loop through characters and establish players
		} while (!EstablishTeams(teams[i].p, tempC, i));
	}

	Spacer();
}

void InputPlayerNames() {

}

void PrepareGame() {

}

void main()
{
	//Start of game loop
	InputTeams();
	InputPlayerNames();
	PrepareGame();
	do {

	} while (gameState == 'p');

}
