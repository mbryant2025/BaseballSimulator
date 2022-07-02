#include <string>
#include "Roster.h"
#include "Player.h"
#include "game.h"
#include "Score.h"
#include <iostream>
#include "statRankings.h"

using std::string;

int main() {
	
	//Array of all rosters
	Roster** league = new Roster* [30];

	//Make chaos roster
	Roster r("AL", "Michael's Team");

	//Add custom players to roster
	
	//Player constructor parameters:
	//string givenName, int givenH, int givenSO, int givenBB, int given2B, int given3B, int givenHR, int givenAB

	Player TyCobb("Ty Cobb    ", 4189, 680, 1249, 724, 295, 117, 11440);
	r.addPlayer(&TyCobb);

	Player LouGehrig("Lou Gehrig", 2721, 790, 1508, 534, 163, 493, 8001);
	r.addPlayer(&LouGehrig);
	
	Player HankAaron("Hank Aaron", 3771, 1383, 1402, 624, 98, 755, 12364);
	r.addPlayer(&HankAaron);

	Player BabeRuth("Babe Ruth", 2873, 1330, 2062, 506, 136, 714, 8399);
	r.addPlayer(&BabeRuth);

	Player BarryBonds("Barry Bonds", 2935, 1539, 2558, 601, 77, 762, 9847);
	r.addPlayer(&BarryBonds);

	Player WillieMays("Willie Mays", 3293, 1526, 1468, 525, 141, 660, 10924);
	r.addPlayer(&WillieMays);

	Player MickeyMantle("Mickey Mantle", 2415, 1710, 1733, 344, 72, 536, 8102);
	r.addPlayer(&MickeyMantle);

	Player MarkMcGwire("Mark McGwire", 1626, 1596, 1317, 252, 6, 583, 6187);
	r.addPlayer(&MarkMcGwire);

	//A gross overestimate of how I'd do in the MLB
	Player MichaelBryant("Michael Bryant", 5, 100, 5, 0, 0, 0, 500);
	r.addPlayer(&MichaelBryant);

	//Add custom roster to league
	league[0] = &r;
	
	//Fill out rest of league with rosters composed of random players
	for (int i = 1; i < 29; i++) {
		league[i] = new Roster(i % 2 ? "Al" : "NL");
		for (int j = 0; j < 9; j++) {
			league[i]->addPlayer(new Player());
		}
	}
	//...Except for team 30 which has super slugger because why not
	league[29] = new Roster("NL");
	Player Slugger("Slug McSlugger", 100, 10, 10, 1, 1, 97, 550);
	league[29]->addPlayer(&Slugger);
	for (int j = 0; j < 8; j++) {
		league[29]->addPlayer(new Player());
	}

	//Record of all regular season game scores for stats
	Score** scores = new Score* [4860];
	int scorePos = 0;

	//Play random matchups until all rosters have played 162 games
	//Plays a game for each team before playing another game for the same team...ensures that all teams play exactly 162 games
	//There is no statistical advantage to having games played at home or away
	for (int i = 0; i < 162; i++) {
		for (int j = 0; j < 30; j++) {
			Roster* t = league[j];
			if (t->gamesPlayed < i + 1) {
				int r = rand() % 30;
				while (r == j || league[r]->gamesPlayed == i + 1) {
					r = rand() % 30;
				}
				Roster* s = league[r];
				playGame(t, s, scores, &scorePos);
			}
		}
	}
	
	//Calculate all player and roster stats
	for (int i = 0; i < 30; i++) {
		league[i]->calculateAllStats();
	}

	//Calculate top 10 BA, HR, H, 1B, 2b, 3B, RBI, R, PA
	Player** topBA = new Player* [10];
	Player** topHR = new Player* [10];
	Player** topH = new Player* [10];
	Player** top1B = new Player * [10];
	Player** top2B = new Player * [10];
	Player** top3B = new Player * [10];
	Player** topRBI = new Player* [10];
	Player** topR = new Player* [10];
	Player** topPA = new Player * [10];

	initializePlayerRankings(topBA, topHR, topH, top1B, top2B, top3B, topRBI, topR, topPA);

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 9; j++) {
			Player* p = league[i]->players[j];
			placePlayerInRankings(p, topBA, topHR, topH, top1B, top2B, top3B, topRBI, topR, topPA);
		}
	}

	//Calculate top 10 roster W, BA, HR, H, RBI, R, PA 
	Roster** topRosterW = new Roster * [30];
	Roster** topRosterBA = new Roster* [10];
	Roster** topRosterHR = new Roster* [10];
	Roster** topRosterH = new Roster* [10];
	Roster** topRoster1B = new Roster* [10];
	Roster** topRoster2B = new Roster* [10];
	Roster** topRoster3B = new Roster* [10];
	Roster** topRosterR = new Roster* [10];
	Roster** topRosterPA = new Roster * [10];

	initializeRosterRankings(topRosterW, topRosterBA, topRosterHR, topRosterH, topRoster1B, topRoster2B, topRoster3B, topRosterR, topRosterPA);

	for (int i = 0; i < 30; i++) {
		Roster* t = league[i];
		placeRosterInRankings(t, topRosterW, topRosterBA, topRosterHR, topRosterH, topRoster1B, topRoster2B, topRoster3B, topRosterR, topRosterPA);
	}

	//Display stat leaderboards
	int k = 0;
	std::cout << "League Leaders:\n" << std::endl;
	for (Player** list : { topBA, topHR, topH, top1B, top2B, top3B, topRBI, topR, topPA }) {
		for (int i = 0; i < 10; i++) {
			Player* p = list[i];
			if (k == 0) {
				std::cout << p->name << "\t" << p->team << "\t" << p->BA << " BA" << std::endl;
			}
			else if (k == 1) {
				std::cout << p->name << "\t" << p->team << "\t" << p->HR << " HR" << std::endl;
			}
			else if (k == 2) {
				std::cout << p->name << "\t" << p->team << "\t" << p->H << " H" << std::endl;
			}
			else if (k == 3) {
				std::cout << p->name << "\t" << p->team << "\t" << p->_1B << " 1B" << std::endl;
			}
			else if (k == 4) {
				std::cout << p->name << "\t" << p->team << "\t" << p->_2B << " 2B" << std::endl;
			}
			else if (k == 5) {
				std::cout << p->name << "\t" << p->team << "\t" << p->_3B << " 3B" << std::endl;
			}
			else if (k == 6) {
				std::cout << p->name << "\t" << p->team << "\t" << p->RBI << " RBI" << std::endl;
			}
			else if (k == 7) {
				std::cout << p->name << "\t" << p->team << "\t" << p->R << " R" << std::endl;
			}
			else {
				std::cout << p->name << "\t" << p->team << "\t" << p->PA << " PA" << std::endl;
			}
		}
		std::cout << "======================================" << std::endl;
		k++;
	}
	std::cout << "\n" << std::endl;

	k = 0;
	std::cout << "Team Leaders:\n" << std::endl;
	for (Roster** list : { topRosterW, topRosterBA, topRosterHR, topRosterH, topRoster1B, topRoster2B, topRoster3B, topRosterR, topRosterPA }) {
		for (int i = 0; i < 10; i++) {
			Roster* t = list[i];
			if (k == 0) {
				std::cout << t->name << "\t" << t->W << " W" << std::endl;
			}
			else if (k == 1) {
				std::cout << t->name << "\t" << t->BA << " BA" << std::endl;
			}
			else if (k == 2) {
				std::cout << t->name << "\t" << t->HR << " HR" << std::endl;
			}
			else if (k == 3) {
				std::cout << t->name << "\t" << t->H << " H" << std::endl;
			}
			else if (k == 4) {
				std::cout << t->name << "\t" << t->_1B << " 1B" << std::endl;
			}
			else if (k == 5) {
				std::cout << t->name << "\t" << t->_2B << " 2B" << std::endl;
			}
			else if (k == 6) {
				std::cout << t->name << "\t" << t->_3B << " 3B" << std::endl;
			}
			else if (k == 7) {
				std::cout << t->name << "\t" << t->R << " R" << std::endl;
			}
			else {
				std::cout << t->name << "\t" << t->PA << " PA" << std::endl;
			}
		}
		std::cout << "======================================" << std::endl;
		k++;
	}
	std::cout << "\n" << std::endl;

	//Record scores
	std::cout << "Record Scores:\n" << std::endl;

	//Find highest score in a game
	Score* highScore = scores[0];
	for (int i = 0; i < scorePos; i++) {
		if (scores[i]->winnerScore > highScore->winnerScore) {
			highScore = scores[i];
		}
	}
	std::cout << "Highest Score:" << std::endl;
	std::cout << highScore->winner->name << " vs. " << highScore->loser->name << ": " << highScore->winnerScore << " - " << highScore->loserScore << "\n\n" << std::endl;

	//Find highest combined score
	Score* highCombinedScore = scores[0];
	int combinedScore = highCombinedScore->winnerScore + highCombinedScore->loserScore;
	for (int i = 0; i < scorePos; i++) {
		if (scores[i]->winnerScore + scores[i]->loserScore > combinedScore) {
			highScore = scores[i];
			combinedScore = scores[i]->winnerScore + scores[i]->loserScore;
		}
	}
	std::cout << "Highest Combined Score:" << std::endl;
	std::cout << highScore->winner->name << " vs. " << highScore->loser->name << ": " << highScore->winnerScore << " - " << highScore->loserScore << "\n\n" << std::endl;

	//Find lowest combined score
	Score* lowCombinedScore = scores[0];
	int combinedScoreLow = highCombinedScore->winnerScore + highCombinedScore->loserScore;
	for (int i = 0; i < scorePos; i++) {
		if (scores[i]->winnerScore + scores[i]->loserScore < combinedScoreLow) {
			highScore = scores[i];
			combinedScoreLow = scores[i]->winnerScore + scores[i]->loserScore;
		}
	}
	std::cout << "Lowest Combined Score:" << std::endl;
	std::cout << highScore->winner->name << " vs. " << highScore->loser->name << ": " << highScore->winnerScore << " - " << highScore->loserScore << "\n\n" << std::endl;



	
	std::cout << "======================================================================================================================" << std::endl;

	//Display custom roster stats
	std::cout << "Final roster statistics:\n" << std::endl;
	std::cout << r.W << " wins out of " << r.gamesPlayed << " games played\n" << std::endl;
	for (int i = 0; i < 9; i++) {
		Player* p = league[0]->players[i];
		std::cout << p->name << "\t\t" << p->BA << " BA" << "\t" << p->HR << " HR" << "\t" << p->H << " H" << "\t" << p->_1B << " 1B" << "\t" << p->_2B << " 2B" << "\t" << p->_3B << " 3B" << "\t" << p->BB << " BB" << "\t" << p->R << " R" << "\t" << p->PA << " PA" << "\t" << p->RBI << " RBI" << std::endl;
	}

	std::cout << "======================================================================================================================" << std::endl;
	
	std::cout << r.name << "\t\t" << r.BA << " BA" << "\t" << r.HR << " HR" << "\t" << r.H << " H" << "\t" << r._1B << " 1B" << "\t" << r._2B << " 2B" << "\t" << r._3B << " 3B" << "\t" << r.BB << " BB" << "\t" << r.R << " R" << "\t" << r.PA << " PA" << "\t" << r.RBI << " RBI" << std::endl;
	
	

	//Playoffs

	

	

	

    return 0;


}