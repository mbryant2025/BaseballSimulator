#include "game.h"
#include "Roster.h"
#include "Player.h"
#include "Score.h"
#include <iostream>
#include <string>

//Simulates a game by updating rosters and all involved players
void playGame(Roster* home, Roster* away, Score** scores, int* scorePos) {

	if (home->numPlayers != 9 || away->numPlayers != 9) {
		std::cout << "Error: Rosters must have 9 players" << std::endl;
		exit(1);
	}

	//Inning tracker -- only incremented after home team has batted
	double inning = 1;

	//Outs for inning
	int outs = 0;

	//What current player is up [1-9]
	int homePlayer = 1;
	int awayPlayer = 1;

	//Scores
	int homeScore = 0;
	int awayScore = 0;

	//Keeps track of top/bottom of inning
	bool homeAtBat = false;

	//Current batting team
	Roster* batting = away;

	//Baserunners
	Player* first = NULL;
	Player* second = NULL;
	Player* third = NULL;

	//Player at bat
	Player* atBat = NULL;
	int atBatIndexHome = 1;
	int atBatIndexAway = 1;

	//Pointers that change depending on the team at bat
	int* battingIndex = NULL;
	int* score = NULL;


	//Loop until game is over
	//Does not yet account for walk-offs...it finishes simulating the inning
	while ((inning <= 9 || homeScore == awayScore) || batting == home) {

		//Clear runners
		Player* first = NULL;
		Player* second = NULL;
		Player* third = NULL;

		//Reset outs
		outs = 0;

		//What scores and atBatIndex will be incremented this half inning
		if (batting == home) {
			score = &homeScore;
			battingIndex = &atBatIndexHome;
		}
		else {
			score = &awayScore;
			battingIndex = &atBatIndexAway;
		}

		while (outs < 3) {

			atBat = batting->players[*battingIndex - 1];

			string battingResult = atBat->plateAppearance();
			
			//Update outs based on batting result
			if (battingResult == "SO" || battingResult == "out") {
				outs++;
			}

			//Simulate the game depending on batting results
			if (battingResult == "HR") {

				//Update score
				(*score)++;
				atBat->RBI++;
				atBat->R++;
				if (first != NULL) {
					(*score)++;
					first->R++;
					atBat->RBI++;
				}
				if (second != NULL) {
					(*score)++;
					second->R++;
					atBat->RBI++;
				}
				if (third != NULL) {
					(*score)++;
					third->R++;
					atBat->RBI++;
				}

				//Clear the bases
				Player* first = NULL;
				Player* second = NULL;
				Player* third = NULL;
			}

			else if (battingResult == "1B" || battingResult == "BB") {
				
				//Update score
				if (third != NULL) {
					(*score)++;
					third->R++;
					atBat->RBI++;
				}

				//Update bases
				third = second;
				second = first;
				first = atBat;

			}

			else if (battingResult == "2B") {
				
				//Update score
				if (second != NULL) {
					(*score)++;
					second->R++;
					atBat->RBI++;
				}
				if (third != NULL) {
					(*score)++;
					third->R++;
					atBat->RBI++;
				}

				//Update bases
				third = first;
				second = atBat;
				first = NULL;
			}

			else if (battingResult == "3B") {
				
				//Update score
				if (first != NULL) {
					(*score)++;
					first->R++;
					atBat->RBI++;
				}
				if (second != NULL) {
					(*score)++;
					second->R++;
					atBat->RBI++;
				}
				if (third != NULL) {
					(*score)++;
					third->R++;
					atBat->RBI++;
				}

				//Update bases
				third = atBat;
				second = NULL;
				first = NULL;
			}

			//Increment player at bat
			(*battingIndex)++;

			if (*battingIndex == 10) {
				*battingIndex = 1;
			}

		}
		
		if (homeAtBat) {
			inning++;
			batting = away;
		}
		else {
			batting = home;
		}
		
		homeAtBat = !homeAtBat;
		
	}

	//Game is over, assign win and gamePlayed
	home->gamesPlayed++;
	away->gamesPlayed++;

	Score* s;

	if (homeScore > awayScore) {
		home->W++;
		s = new Score(home, away, homeScore, awayScore);
	}
	else {
		away->W++;
		s = new Score(away, home, awayScore, homeScore);
	}

	scores[(*scorePos)++] = s;

}
