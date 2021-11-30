#include "HelperLib.h"



void Spacer() {
	printf("\n"); printf("\n"); printf("\n");
}

void ReadString(char* text) {
	for (size_t i = 0; i < 50; i++)
	{
		if (text[i] != '\0') {
			if (text[i] != '\n') {
				printf("%c", text[i]);
			}
		}
	}
}

void TitleScreen() {
	Green();
	printf("\n---------------------------------------------------------------------------");
	Spacer();
	printf("\n   _____                    _              _   _____           _   _     ");
	printf("\n  /  ___|                  | |            | | |  ___|         | | | |    ");
	printf("\n  \\ `--.  ___ ___  _ __ ___| |__   ___  __| | | |__  __ _ _ __| |_| |__  ");
	printf("\n   `--. \\/ __/ _ \\| '__/ __| '_ \\ / _ \\/ _` | |  __|/ _` | '__| __| '_ \\ ");
	printf("\n  /\\__/ / (_| (_) | | | (__| | | |  __/ (_| | | |__| (_| | |  | |_| | | |");
	printf("\n  \\____/ \\___\\___/|_|  \\___|_| |_|\\___|\\__,_| \\____/\\__,_|_|   \\__|_| |_|");
	printf("\n				Cosnole Version	made by Branislav Kadlec						 ");
	Spacer();
	printf("\n---------------------------------------------------------------------------");
	White();
}

void WinScreen() {
	Green();
	printf("\n---------------------------------------------------------------------------");
	Spacer();
	printf("\n  __   __            _    _             _ ");
	printf("\n  \\ \\ / /           | |  | |           | |");
	printf("\n   \\ V /___  _   _  | |  | | ___  _ __ | |");
	printf("\n    \\ // _ \\| | | | | |/\\| |/ _ \\| '_ \\| |");
	printf("\n    | | (_) | |_| | \\  /\\  / (_) | | | |_|");
	printf("\n    \\_/\\___/ \\__,_|  \\/  \\/ \\___/|_| |_(_)");
	printf("\n");
}

void WinScreen2() {
	printf("\n");
	printf("\n	   [ O ]						");
	printf("\n	     \\ \\      p					");
	printf("\n	      \\ \\  \\o/					");
	printf("\n	       \\ \\--'---_				");
	printf("\n	       /\\ \\   / ~~\\_			");
	printf("\n	 ./---/__|=/_/------//~~~\\		");
	printf("\n	/___________________/O   O \\	");
	printf("\n	(===(\\_________(===(Oo o o O)   ");
	printf("\n	 \\~~~\\____/     \\---\\Oo__o--	");
	printf("\n	   ~~~~~~~       ~~~~~~~~~~		");

	Spacer();
	printf("\n---------------------------------------------------------------------------");
}

FILE* open_file(char* filepath, char* mode)
{
	FILE* fptr;
	errno_t err;

	err = fopen_s(&fptr, filepath, mode);

	if (fptr == NULL)
	{
		printf("Error opening the file!");
		exit(1);
	}
	return fptr;
}

void close_file(FILE* fp)
{
	fclose(fp);
}

void BattleLog(char* s) {
	FILE* log;
	log = open_file("battleLog.txt", "w");

	fprintf(log, s);

	close_file(log);
}

void Black() {
	printf("\033[0;30m");
}
void BlackBold() {
	printf("\033[1;30m");
}

void Red() {
	printf("\033[0;31m");
}
void RedBold() {
	printf("\033[1;31m");
}

void Green() {
	printf("\033[0;32m");
}
void GreenBold() {
	printf("\033[1;32m");
}

void Yellow() {
	printf("\033[0;33m");
}
void YellowBold() {
	printf("\033[1;33m");
}

void Blue() {
	printf("\033[0;34m");
}
void BleuBold() {
	printf("\033[1;34m");
}

void Purple() {
	printf("\033[0;35m");
}
void PurpleBold() {
	printf("\033[1;35m");
}

void Cyan() {
	printf("\033[0;36m");
}

void CyanBold() {
	printf("\033[1;36m");
}

void White() {
	printf("\033[0;37m");
}

void WhiteBold() {
	printf("\033[1;37m");
}

/*
Black \033[0;30m
Red   \033[0;31m
Green \033[0;32m
Yellow\033[0;33m
Blue  \033[0;34m
Purple\033[0;35m
Cyan  \033[0;36m
White \033[0;37m
*/