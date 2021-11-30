#pragma once

#include <iostream>

void Spacer();
void ReadString(char* text);
void TitleScreen();
void WinScreen();
void WinScreen2();
FILE* open_file(char* filepath, char* mode);
void close_file(FILE* fp);
void BattleLog(char* s);

//Colors
void Black();
void BlackBold();
void Red();
void RedBold();
void Green();
void GreenBold();
void Yellow();
void YellowBold();
void Blue();
void BleuBold();
void Purple();
void PurpleBold();
void Cyan();
void CyanBold();
void White();
void WhiteBold();