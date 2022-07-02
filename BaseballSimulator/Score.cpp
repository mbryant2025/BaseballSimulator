#include "Score.h"
#include "Roster.h"

Score::Score(Roster* w, Roster* l, int ws, int ls) {
	this->winner = w;
	this->loser = l;
	this->winnerScore = ws;
	this->loserScore = ls;
}