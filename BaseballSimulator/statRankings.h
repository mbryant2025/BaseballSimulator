#pragma once
#include <string>
#include "Roster.h"
#include "Player.h"

void initializePlayerRankings(Player** topBA, Player** topHR, Player** topH, Player** topRBI, Player** topR, Player** topPA);

void placePlayerInRankings(Player* p, Player** topBA, Player** topHR, Player** topH, Player** topRBI, Player** topR, Player** topPA);

void initializeRosterRankings(Roster** topRosterW, Roster** topRosterBA, Roster** topRosterHR, Roster** topRosterH, Roster** topRosterR, Roster** topRosterPA);

void placeRosterInRankings(Roster* r, Roster** topRosterW, Roster** topRosterBA, Roster** topRosterHR, Roster** topRosterH, Roster** topRosterR, Roster** topRosterPA);