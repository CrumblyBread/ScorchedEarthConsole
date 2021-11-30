#include "ScorchedEarthConsole.h"
using namespace std;

struct Team teams[3];		//array of teams (starting to count from 1)	TODO: functionality for more than 2 teams?
int sizes[] = {2,0,0};		//actual player numbers in teams (starting to count from 1)
int victoryTeam;

Lfunc map[8];
int mapSize = 5;

int u = 0;

//Establish player data
//returns ture if user passed the exact number of parameters
bool EstablishTeams(Player *t, char *S, int id) {

	int h = 0;		//number of established players

	//loop through every character of a srting provided by user
	for (int i = 1; i < strlen(S); i++)
	{
		t[h].id = h;
		t[h].teamId = id;
		t[h].health = 100;

		char ch = S[i];
		//switch for distinguishing different characters
		switch (ch)
		{
		//human player
		case 'h':
			t[h].human = true;
			h++;
			break;
		//easy AI
		case 'e':
			t[h].human = false;
			t[h].diff = 1;
			h++;
			break;
		//medium AI
		case 'm':
			t[h].human = false;
			t[h].diff = 2;
			h++;
			break;
		//difficult AI
		case 'd':
			t[h].human = false;
			t[h].diff = 3;
			h++;
			break;
		default:
			t[h].id = 0;
			t[h].teamId = 0;
			t[h].health = 0;
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
		bool est = false;
		teams[i].id = i;
		do {
			sizes[i] = 0;
			char tempC[100];
			do {
				while ((getchar()) != '\n');
				printf("\nInput the size of team %d:   ", i);
				u = scanf_s("%d", &sizes[i]);
			} while (sizes[i] == 0 || isdigit(sizes[i]));
			
			int set = 0;
			do {
				fill(tempC, tempC + 100, '\0');
				//Read the player types
				printf("\nPut in an h character for a human player and e,m,d character for an AI player");
				printf("\n(Easy, Medium, Difficult) and end with a ; (eg: h e h d ;)\n");
				int x = -1;
				do {
					x++;
					u = scanf("%c", &tempC[x]);
				} while (tempC[x] != ';');

				set = 0;
				for(int i = 0; i < 100; i++)
				{
					if (tempC[i] == 'h' || tempC[i] == 'e' || tempC[i] == 'm' || tempC[i] == 'd') {
						set++;
					}
				}
			} while (set != sizes[i]);

			//Loop through characters and establish players
			est = EstablishTeams(teams[i].p, tempC, i);
		} while (!est);
	}

	Spacer();
}

void InputPlayerNames() {
	BattleLog("\nPlayers were:");
	for (int i = 1; i <= sizes[0]; i++)
	{
		for (int j = 0; j < sizes[i]; j++)
		{
			if (teams[i].p[j].human) {
				printf("\nChoose a name for player %d from team %d (Letters and Numbers Only):    ",j+1,i);
				u = scanf("%s", teams[i].p[j].name);
				for (int x = 0; x < strlen(teams[i].p[j].name); x++)
				{
					if (!isalnum(teams[i].p[j].name[x])) {
						teams[i].p[j].name[x] = '\0';
						break;
					}
				}
			}
			else
			{
				FILE* bots;
				bots = open_file("botNames.txt", "r");
				int count;
				u = fscanf(bots,"%d",&count);
				int random = (rand() % count) + 2;
				count = 0;
				char line[250];
				while (fgets(line,sizeof(line),bots)){
					count++;
					if (count == random) {
						int x = -1; bool test = true;
						do
						{
							x++;
							teams[i].p[j].name[x] = line[x];
							if (x == 45 || teams[i].p[j].name[x] == '\n') {
								test = false;
							}
						} while (test);
					}
				}
				printf("\nBot number %d from team %d is named ",j+1,i); ReadString(teams[i].p[j].name);
				close_file(bots);
			}
			BattleLog("\n");
			BattleLog(teams[i].p[j].name);
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

void GeneratePlayerPositions() {

	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	timer = time(NULL);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	printf("\n---------------------------------------------------------------------------");
	BattleLog("Game has started at: ");
	BattleLog(buffer);

	Cyan();
	printf("\nVisualizer Data:");
	BattleLog("\nVisualizer Data:");

	for (int i = 1; i <= mapSize; i++)
	{
		printf("\ny = %lf x + %lf", map[i].a, map[i].b);
		char str2[255];
		sprintf(str2, "\ny = %lf x + %lf", map[i].a, map[i].b);
		BattleLog("\ny = ");
		memcpy(str2, &map[i].a, sizeof(&map[i].a));
		BattleLog(str2);
		BattleLog(" x + ");
		memcpy(str2, &map[i].a, sizeof(&map[i].a));
		BattleLog(str2);
	}

	for (int i = 1; i <= sizes[0]; i++)
	{
		for (int j = 0; j < sizes[i]; j++)
		{
			int h = 10 * (j + 1);
			if (i == 1) {
				teams[i].p[j].pos.x = ((double)mapSize * 33.33) + (double)rand() / (double)(RAND_MAX / h);
				teams[i].p[j].pos.y = GetMapValue(teams[i].p[j].pos.x);
				printf("\n(%lf,%lf)", teams[i].p[j].pos.x, teams[i].p[j].pos.y);
				char str2[255];
				sprintf(str2, "\n(%lf,%lf)", teams[i].p[j].pos.x, teams[i].p[j].pos.y);
				BattleLog(str2);
			}
			else
			{
				teams[i].p[j].pos.x = ((double)mapSize * 66.66) + (double)rand() / (double)(RAND_MAX / h);
				teams[i].p[j].pos.y = GetMapValue(teams[i].p[j].pos.x);
				printf("\n(%lf,%lf)", teams[i].p[j].pos.x, teams[i].p[j].pos.y);
				char str2[255];
				sprintf(str2, "\n(%lf,%lf)", teams[i].p[j].pos.x, teams[i].p[j].pos.y);
				BattleLog(str2);
			}
		}
	}
	printf("\ny\\ -j=\\ \\left(x-i\\right)\\tan\\left(a\\right)-\\frac{9.81\\left(x-i\\right)^{2}}{2p^{2}\\cdot\\cos^{2}a}");
	printf("\na\\ =\\ \\frac{o}{57.2957795}");
	printf("\n");
	BattleLog("\n");
	White();
}

void ChooseMapSize(bool read, char mS) {
	Point spawnpoints[100];
	if (!read) {
		while ((getchar()) != '\n');
		printf("\nChoose map size (s for small (100m), m for medium (200m), l for large(300m)) :  ");
		mS = getchar();
	}

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
		ChooseMapSize(false, 'l');
		return;
	}

	if (!read) {

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
			else {
				map[i].SetB((i - 1) * 100, map[i - 1].getValue((i - 1) * 100));
			}
		}

		GeneratePlayerPositions();
	}
}

bool LoadFromFile() {

	printf("\nShould game setup be read from setup.txt file? \n (0 for no, 1 for yes):   ");
	int x = 0;
	u = scanf("%d", &x);
	if (x == 1) {
		FILE* setup;
		setup = fopen("setup.txt", "r");

		char line[50];
		int i = 0;
		while (fscanf(setup, "%[^\n] ", line) != EOF) {

			//Nested if statement, please forgive me for the sin I'm about to commit
			if (i <= 1) {
				u = sscanf(line, "%d", &sizes[i + 1]);
			}
			else
			{
				if (i <= 3) {
					EstablishTeams(teams[i - 1].p, line, i - 1);
				}
				else
				{
					if (i == 4) {
						char c;
						u = sscanf(line, "%c", &c);
						ChooseMapSize(true, c);
					}
					else
					{
						if (i <= 4 + mapSize) {
							u = sscanf(line, ";%lf %lf", &map[i - 4].a, &map[i - 4].b);
						}
					}
				}
			}
			i++;
			//Why didn't I just make it a switch? What is wrong with me?
		}
		GeneratePlayerPositions();

		fclose(setup);
		return true;
	}
	else
	{
		return false;
	}
}

void Shoot(Player p) {
	int enemyTeam = p.teamId % 2 == 1 ? 2 : 1;

	if (p.human) {
		double pow, ang;
		printf("\nInput the angle of your shoot :");
		u = scanf("%lf", &ang);
		printf("\nInput the power of your shoot :");
		u = scanf("%lf",&pow);

		ang = ang > 89 ? 89 : ang; ang = ang < 1 ? 1 : ang;
		pow = pow > 100 ? 100 : pow; pow = pow < 0 ? 0 : pow;

		ang = p.teamId % 2 == 0 ? -ang : ang;
		ATfunc shot; shot.a = ang / deg2rad; shot.p = pow;
		
		double d = 9999;
		for (int i = 0; i < sizes[enemyTeam]; i++){
			for (double j = -2, h; j <= 2; j++){
				d = 9999;
				h = abs(shot.getValueOffset(teams[enemyTeam].p[i].pos.x + j,p.pos) - teams[enemyTeam].p[i].pos.y);
				if (h < d) { d = h;}
				if (h <= 1) {
					//Hit
					double damage = 10 < ((10 * h) + 10) ? 10 : ((10 * h) + 10);
					char str2[255];
					teams[enemyTeam].p[i].health -= damage;
					if (10 < damage) {
						printf("\n\n!	Critical HIT	!");
						printf("\nYou hit player %s for 10 damage!", teams[enemyTeam].p[i].name);
						printf("\nThey have %.1f hp left\n\n", teams[enemyTeam].p[i].health);
					}else{
						printf("\n\n!	HIT		!");
						printf("\nYou hit player %s for %lf damage!\n\n", teams[enemyTeam].p[i].name, damage);
						printf("\nThey have %.1f hp left\n\n", teams[enemyTeam].p[i].health);
					}
					BattleLog("\nPlayer ");
					BattleLog(p.name);
					BattleLog(" hit player ");
					BattleLog(teams[enemyTeam].p[i].name);
					BattleLog(" for ");
					memcpy(str2, &damage, sizeof(damage));
					BattleLog("damage");
					BattleLog(str2);
					return;
				}
			}
			//Miss
			if (i = sizes[enemyTeam]-1) {
				printf("\n\n	Miss	");
				printf("\nYou Shot %.2f meters too high\n\n", d);

				BattleLog("\nPlayer");
				BattleLog(p.name);
				BattleLog(" has missed his shot!");
			}
		}
		
	}
	else{
		int random = rand() % 100;

		int max = 20;
		switch (p.diff)
		{
		case 1:
			max = 20;
			break;
		case 2:
			max = 50;
			break;
		case 3:
			max = 75;
			break;
		}

		double damage = (double)rand() / (RAND_MAX / 10);
		if (random > 1 && random < max) {
			if (sizes[enemyTeam] - 1 == 0) {
				random = 0;
			}
			else
			{
				random = rand() % (sizes[enemyTeam] - 1);
			}
			teams[enemyTeam].p[random].health -= damage;


			if (damage >= 10) {
				printf("\n\n!	Critical HIT	!");
				printf("\nYou hit player %s for 10 damage!", teams[enemyTeam].p[random].name);
				printf("\nThey have %.1f hp left\n\n", teams[enemyTeam].p[random].health);
			}
			else {
				printf("\n\n!	HIT		!");
				printf("\nYou hit player %s for %lf damage!\n\n", teams[enemyTeam].p[random].name, damage);
				printf("\nThey have %.1f hp left\n\n", teams[enemyTeam].p[random].health);
			}
			char str2[255];
			BattleLog("\nPlayer ");
			BattleLog(p.name);
			BattleLog(" hit player ");
			BattleLog(teams[enemyTeam].p[random].name);
			BattleLog(" for ");
			memcpy(str2, &damage, sizeof(damage));
			BattleLog("damage");
			BattleLog(str2);
		}
		else
		{
			printf("\n\n	Miss	");
			printf("\nYou Shot %.2f meters too high\n\n", damage);
			BattleLog("\nPlayer");
			BattleLog(p.name);
			BattleLog(" has missed his shot!");
		}
	}
}

void Move(Player p) {
	while ((getchar()) != '\n');
	printf("How far to move? (-5 to 5): ");
	double dis = 0;
	u = scanf("%lf",&dis);
	dis = dis > 5 ? 5 : dis; dis = dis < -5 ? -5 : dis;
	p.pos.x += dis;
	p.pos.y = GetMapValue(p.pos.x);
	printf("Your new position is ");
	Cyan();
	printf("(%lf,%lf)", p.pos.x, p.pos.y);

	char s[25];
	BattleLog("\nPlayer");
	BattleLog(p.name);
	BattleLog(" has moved to position (");
	memcpy(s, &p.pos.x, sizeof(p.pos.x));
	BattleLog(s);
	BattleLog(",");
	memcpy(s, &p.pos.y, sizeof(p.pos.x));
	BattleLog(s);
	BattleLog(")");
}

void PlayerTurn(Player p) {
	if (p.human) {
		printf("\n Move or Shoot? (m or s): ");
		while ((getchar()) != '\n');
		char c = getchar();
		switch (c)
		{
		case 'm':
			Move(p);
			if (p.teamId % 2 == 0) {
				RedBold();
			}
			else {
				BleuBold;
			}
			break;
		case 's':
			Shoot(p);
			break;
		}
	}
	else
	{
		Shoot(p);
	}
}

bool CheckForWin() {
	for (int i = 1; i <= sizes[0]; i++) {
		int k = 0;
		for (int j = 0; j < sizes[i]; j++) {
			if (teams[i].p[j].health < 0) {
				k++;
			}
		}
		if (k == sizes[i]) {
			victoryTeam = i == 1 ? 2 : 1;
			return true;
		}
	}
	return false;
}

void Win() {

	WinScreen();
	BattleLog("\nThe game was won by");
	printf("\nTeam number %d is Victorious!", victoryTeam);
	printf("\nPlayers ");
	int h = 0;
	for (int i = 1; i <= sizes[0]; i++) {
		for (int j = 0; j < sizes[i]; j++) {
			if (teams[i].p[j].health > 0) {
				if (h != 0) {
					printf(" and ");
					BattleLog(" and ");
				}
				if (teams[i].p[j].teamId % 2 == 0) {
					Red();
				}
				else {
					Blue();
				}
				ReadString(teams[i].p[j].name);
				BattleLog(teams[i].p[j].name);
				Green();
				h++;
			}
		}
	}
	printf(" are left to controll the battlefield!");
	BattleLog("\n---------------------------------------------------------------------------");
	WinScreen2();
	White();
}

void main() {
	srand(time(NULL));
	TitleScreen();
	char ch;
	u = scanf("%c", &ch);

	//Start of game loop
	bool loadedFile = LoadFromFile();
	if (!loadedFile) {
		InputTeams();
	}

	InputPlayerNames();

	if (!loadedFile) {
		ChooseMapSize(false, 'l');
	}

	do {
		for (int i = 1; i <= sizes[0]; i++){
			for (int j = 0; j < sizes[i]; j++){
				if (teams[i].p[j].health > 0) {
					if (i % 2 == 0) {
						Red();
					}else{
						Blue();
					}
					printf("\n\nTurn of player "); ReadString(teams[i].p[j].name); printf(" :");
					PlayerTurn(teams[i].p[j]);
				}
			}
		}
	} while (!CheckForWin());

	Win();
}
