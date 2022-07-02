#pragma once
#include "Roster.h"

class Score {

	public:
		Roster* winner;
		Roster* loser;
		int winnerScore;
		int loserScore;

		Score(Roster* w, Roster* l, int ws, int ls);

};

