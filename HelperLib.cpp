#include "HelperLib.h"



void Spacer() {
	printf("\n"); printf("\n"); printf("\n");
}

void ReadString(char* text) {
	for (size_t i = 0; i < 50; i++)
	{
		if (text[i] != '\0') {
			printf("%c", text[i]);
		}
	}
}