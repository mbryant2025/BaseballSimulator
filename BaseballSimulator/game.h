#pragma once
#include "Roster.h"
#include "Player.h"
#include "Score.h"

//Simulates a game by updating rosters and all involved players
//For this method, there is no statistical difference between home and away
void playGame(Roster* home, Roster* away, Score**, int* scorePos);

