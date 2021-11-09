#include "ScorchedEarthConsole.h"
using namespace std;

char gameState = 's';		// 's' = stopped    'p' = playing    'f' = finished
struct Team teams[3];		//array of teams (starting to count from 1)	TODO: functionality for more than 2 teams?
int sizes[] = {2,0,0};		//actual player numbers in teams (starting to count from 1)

//Establish player ids and human status
//returns ture if user passed the exact number of parameters
bool EstablishTeams(Player *t, char *S, int id) {

	int h = 0;		//number of established players

	//loop through every character of a srting provided by user
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

bool LoadFromFile() {

	printf("\nShould game setup be read from setup.txt file? \n (0 for no, 1 for yes):   ");
	int x = 0;
	u = scanf("%d", &x);
	if (x == 1) {
		return true;
	}
	else
	{
		return false;
	}
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
				u = scanf("%c", &tempC[x]);
			} while (tempC[x] != ';');

			//Loop through characters and establish players
		} while (!EstablishTeams(teams[i].p, tempC, i));
	}

	Spacer();
}

void InputPlayerNames() {
	for (int i = 1; i <= sizes[0]; i++)
	{
		for (int j = 0; j < sizes[i]; j++)
		{
			if (teams[i].p[j].human) {
				printf("\nChoose a name for player %d from team %d (LettersOnly):    ",j+1,i);
				u = scanf("%s", teams[i].p[j].name);
				for (int x = 0; x < strlen(teams[i].p[j].name); x++)
				{
					if (!isalpha(teams[i].p[j].name[x])) {
						teams[i].p[j].name[x] == '\0';
					}
				}
			}
		}
	}
}

void ChooseMapSize() {
	char mS;
	int mapSize = 0;
	Point spawnpoints[100];
	printf("Choose map size (s for small (200m), m for medium (500m), l for large(800m)) :");
	u = scanf("%c", &mS);

	switch (mS)
	{
	case 's':
		mapSize = 200;
		break;
	case 'm':
		mapSize = 500;
		break;
	case 'l':
		mapSize = 800;
		break;
	default:
		printf("Map size not recognised! Try again!");
		ChooseMapSize();
	}


	//TODO Load Map



	for (int i = 1; i <= sizes[0]; i++)
	{
		for (int j = 0; j < sizes[i]; j++)
		{
			if (i == 1) {
				teams[i].p[j].pos.x = ((float)mapSize * 0.3333) + (float)rand() / (float)(RAND_MAX / 10);
				teams[i].p[j].pos.y = 3;
			}
			else
			{
				teams[i].p[j].pos.x = ((float)mapSize * 0.6666) + (float)rand() / (float)(RAND_MAX / 10);
				teams[i].p[j].pos.y = 3;
			}
		}
	}
}

void PrepareGame() {

}

void Shoot(Player p) {
	if (p.human) {
		double p, a;
		printf("\nInput the angle of your shoot :");
		u = scanf("%lf", &a);
		printf("\nInput the power of your shoot :");
		u = scanf("%lf",&p);


	}
	else
	{

	}
}

void CheckForWin() {
	//TODO check for a player winning!
}

void main() {
	//Start of game loop
	if (LoadFromFile()) {
		//TODO: Load settings from file;
	}
	else{
		InputTeams();
		InputPlayerNames();
	}

	ChooseMapSize();
	PrepareGame();

	do {
		for (int i = 1; i <= sizes[0]; i++){
			for (int j = 0; j < sizes[i]; j++){
				if (teams[i].p[j].health > 0) {
					printf("\nTurn of player "); ReadString(teams[i].p[j].name);
					Shoot(teams[i].p[j]);
				}
			}
		}
		CheckForWin();
	} while (gameState == 'p');

}
