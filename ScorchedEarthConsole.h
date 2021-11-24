// ScorchedEarthConsole.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "LinearAlgebra.h"
#include "HelperLib.h"

#include <iostream>
#include <cstring>
#include <ctype.h>

//structure for a player object
struct Player
{
	int id = -1;				//id of a player
	int teamId;					//id of player's team
	bool human = false;			//bool for determining if player is a human or AI
	char name[50] = {'\n'};		//player's name
	float health = 0;			//player's health
	int diff = 0;				//difficulty of a player (only used for AI players)
	Point pos;
};

//structure for a team object
struct Team
{
	int id = 0;		//id of a particular team
	Player p[100];	//array of all players in a team
};
