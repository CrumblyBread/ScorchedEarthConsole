#include "ScorchedEarthConsole.h"
using namespace std;

char gameState = 's';		// 's' = stopped    'p' = playing    'f' = finished
struct Team teams[3];		//array of teams (starting to count from 1)	TODO: functionality for more than 2 teams?
int sizes[] = {2,0,0};		//actual player numbers in teams (starting to count from 1)

Lfunc map[8];
int mapSize = 5;

int u = 0;

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
						teams[i].p[j].name[x] = '\0';
					}
				}
			}
		}
	}
}

double GetMapValue(double x) {
	int h = 0;

	do{
		h++;
	} while (h*100 < x);
	
	double n = map[h].getValue(x);
	return n;
}

void ChooseMapSize() {
	char mS;
	Point spawnpoints[100];
	printf("Choose map size (s for small (100m), m for medium (200m), l for large(300m)) :");
	mS = getchar();

	switch (mS)
	{
	case 's':
		mapSize = 1;
		break;
	case 'm':
		mapSize = 2;
		break;
	case 'l':
		mapSize = 3;
		break;
	default:
		printf("Map size not recognised! Try again!");
		ChooseMapSize();
		return;
	}


	//TODO Load Map from file


	//Generate a continuous piecewise function
	for (int i = 1; i <= mapSize; i++)
	{
		map[i].a = (double)rand() / (RAND_MAX / (1));
		if (i % 2 == 0) {
			map[i].a = -map[i].a;
		}


		if (i == 1) {
			map[i].b = (double)rand() / (RAND_MAX / (20));
		}
		else{
			map[i].SetB((i - 1) * 100, map[i - 1].getValue((i - 1) * 100));
		}

		printf("\nx = %lf x + %lf\n", map[i].a, map[i].b);
	}



	for (int i = 1; i <= sizes[0]; i++)
	{
		for (int j = 0; j < sizes[i]; j++)
		{
			if (i == 1) {
				teams[i].p[j].pos.x = ((double)mapSize * 33.33) + (double)rand() / (double)(RAND_MAX / 10);
				teams[i].p[j].pos.y = GetMapValue(teams[i].p[j].pos.x);
				printf("my X and Y is (%lf,%lf)", teams[i].p[j].pos.x, teams[i].p[j].pos.y);
			}
			else
			{
				teams[i].p[j].pos.x = ((double)mapSize * 66.66) + (double)rand() / (double)(RAND_MAX / 10);
				teams[i].p[j].pos.y = GetMapValue(teams[i].p[j].pos.x);
				printf("my X and Y is (%lf,%lf)", teams[i].p[j].pos.x, teams[i].p[j].pos.y);
			}
		}
	}
}

void PrepareGame() {
	gameState = 'p';
}

void Shoot(Player p) {
	if (p.human) {
		double pow, ang;
		printf("\nInput the angle of your shoot :");
		u = scanf("%lf", &ang);
		printf("\nInput the power of your shoot :");
		u = scanf("%lf",&pow);
		ang = p.teamId % 2 == 0 ? -ang : ang;
		ATfunc shot; shot.a = ang / deg2rad; shot.p = pow;
		
		int enemyTeam = p.teamId == 1 ? 2 : 1;
		for (int i = 0; i < sizes[enemyTeam]; i++)
		{
			double offsetX = (teams[enemyTeam].p[i].pos.x - p.pos.x);
			for (double j = -2; j <= 2; j++)
			{
				if (abs(shot.getValue(offsetX) - teams[enemyTeam].p->pos.y) <= 1) {
					//Hit
					printf("\n\n!!!!HIT!!!!\n\n");
					return;
				}
			}
			//Miss
			printf("\n\nMiss\n\n");
		}
		
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
