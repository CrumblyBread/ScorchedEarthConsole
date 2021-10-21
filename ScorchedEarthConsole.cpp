#include "ScorchedEarthConsole.h"

using namespace std;

char gameState = 's';		// 's' = stopped    'p' = playing    'f' = finished
struct Team team;

void main()
{
	//Start of game loop
	InputTeams();
	InputPlayerNames();
	PrepareGame();
	do {

	} while (gameState == 'p');

}

//Function that determines the number of players in each team
// and the amount of human and AI players
void InputTeams() {
	string tempS;
	int size;

	printf("\nInput the number of teams");
	scanf("%d", &size);
	Team* team = (Team*)malloc(size * sizeof(Team));

	printf("\nsize of teams array is %f",sizeof(team));

	for (int i = 0; i < sizeof(team); i++)
	{
		printf("\nInput the size of team %d:   ",i);
		scanf("%d", &size);
		Player* team[i] = (Player*)malloc(size * sizeof(Player));
		printf("\n");
	}

	//Load the team sizes

	printf("\nInput the size of team 2:");
	scanf("%d", &size);
	Player* team2 = (Player*)malloc(size * sizeof(Player));


	//Read the player types
	printf("\nPut in an h character for a human player and a character for an AI player");
	printf("\n(eg: h a h)\n");
	scanf("%s", &tempS);


	//Parse the player input into characters
	char* tempC = (char*)malloc(tempS.length() * sizeof(char));
	strcpy(tempC, tempS.c_str());


	//Loop through characters and establish players
	for (int i = 0,j = 0; i < tempS.length(); i++)
	{
		switch (tempC[i])
		{
		case 'h':
			
			break;
		default:
			j++;
			break;
		}
	}

}

void InputPlayerNames() {

}

void PrepareGame() {

}

struct Player
{
	int id;
	bool human;
	string name;
	float health;

};

struct Team
{
	Player p;
};
