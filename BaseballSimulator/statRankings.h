#pragma once
#include <string>
#include "Roster.h"
#include "Player.h"

void initializePlayerRankings(Player** topBA, Player** topHR, Player** topH, Player** top1B, Player** top2B, Player** top3B, Player** topRBI, Player** topR, Player** topPA);

void placePlayerInRankings(Player* p, Player** topBA, Player** topHR, Player** topH, Player** top1B, Player** top2B, Player** top3B, Player** topRBI, Player** topR, Player** topPA);

void initializeRosterRankings(Roster** topRosterW, Roster** topRosterBA, Roster** topRosterHR, Roster** topRosterH, Roster** topRoster1B, Roster** topRoster2B, Roster** topRoster3B, Roster** topRosterR, Roster** topRosterPA);

void placeRosterInRankings(Roster* r, Roster** topRosterW, Roster** topRosterBA, Roster** topRosterHR, Roster** topRosterH, Roster** topRoster1B, Roster** topRoster2B, Roster** topRoster3B, Roster** topRosterR, Roster** topRosterPA);

Roster** createLeagueRankings(Roster**, string l);