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
		league[i] = new Roster(i % 2 == 0 ? "AL" : "NL");
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
	Score** scores = new Score* [2430];
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
	std::cout << "Regular Season Roster Statistics:\n" << std::endl;
	std::cout << r.W << " wins out of " << r.gamesPlayed << " games played\n" << std::endl;
	for (int i = 0; i < 9; i++) {
		Player* p = league[0]->players[i];
		std::cout << p->name << "\t\t" << p->BA << " BA" << "\t" << p->HR << " HR" << "\t" << p->H << " H" << "\t" << p->_1B << " 1B" << "\t" << p->_2B << " 2B" << "\t" << p->_3B << " 3B" << "\t" << p->BB << " BB" << "\t" << p->R << " R" << "\t" << p->PA << " PA" << "\t" << p->RBI << " RBI" << std::endl;
	}

	std::cout << "======================================================================================================================" << std::endl;
	
	std::cout << r.name << "\t\t" << r.BA << " BA" << "\t" << r.HR << " HR" << "\t" << r.H << " H" << "\t" << r._1B << " 1B" << "\t" << r._2B << " 2B" << "\t" << r._3B << " 3B" << "\t" << r.BB << " BB" << "\t" << r.R << " R" << "\t" << r.PA << " PA" << "\t" << r.RBI << " RBI" << std::endl;
	
	

	//Playoffs

	std::cout << "\n\nPlayoffs:\n\n" << std::endl;

	//Get top 5 teams from each league for playoffs
	Roster** ALRankings = createLeagueRankings(league, "AL");
	Roster** NLRankings = createLeagueRankings(league, "NL");

	for (int i = 0; i < 5; i++) {
		ALRankings[i]->playoffSeed = i + 1;
		NLRankings[i]->playoffSeed = i + 1;
	}

	int zero = 0;
	Roster* winner;
	Roster* loser;

	//Wild Card

	Score** ALWC = new Score* [1];
	Score** NLWC = new Score* [1];
	
	playGame(ALRankings[3], ALRankings[4], ALWC, &zero); zero--; //Undo auto-increment of position variable
	playGame(NLRankings[3], NLRankings[4], NLWC, &zero); zero--;

	std::cout << "ALWC\n==========" << std::endl;

	winner = ALWC[0]->winner;
	loser = ALWC[0]->loser;

	std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << ALWC[0]->winnerScore << "-" << ALWC[0]->loserScore << std::endl;
	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the ALWC against " << loser->name << " (" << loser->playoffSeed << ") 1-0" << std::endl;

	std::cout << "\n\nNLWC\n==========" << std::endl;

	winner = NLWC[0]->winner;
	loser = NLWC[0]->loser;

	std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << NLWC[0]->winnerScore << "-" << NLWC[0]->loserScore << std::endl;
	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the NLWC against " << loser->name << " (" << loser->playoffSeed << ") 1-0" << std::endl;

	//Divisional

	Score** ALDSa = new Score* [5];
	Score** ALDSb = new Score* [5];
	Score** NLDSa = new Score* [5];
	Score** NLDSb = new Score* [5];

	Roster** ALDSWinners = new Roster* [2];
	Roster** NLDSWinners = new Roster* [2];

	std::cout << "\n\nALDS (1/2)\n==========" << std::endl;

	int homeTeamWins = 0;
	int awayTeamWins = 0;

	int g_ALDSa = 0; //Keeps track of current game in the series -- winner of the final game wins the series
	while (homeTeamWins < 3 && awayTeamWins < 3) {
		playGame(ALRankings[0], ALWC[0]->winner, ALDSa, &g_ALDSa);

		if (ALDSa[g_ALDSa - 1]->winner == ALRankings[0]) {
			winner = ALDSa[g_ALDSa - 1]->winner;
			loser = ALDSa[g_ALDSa - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << ALDSa[g_ALDSa - 1]->winnerScore << "-" << ALDSa[g_ALDSa - 1]->loserScore << std::endl;
			homeTeamWins++;
		}

		if (ALDSa[g_ALDSa - 1]->winner == ALWC[0]->winner) {
			winner = ALDSa[g_ALDSa - 1]->winner;
			loser = ALDSa[g_ALDSa - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << ALDSa[g_ALDSa - 1]->winnerScore << "-" << ALDSa[g_ALDSa - 1]->loserScore << std::endl;
			awayTeamWins++;
		}
	}

	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the ALDS against " << loser->name << " (" << loser->playoffSeed << ") ";

	if (homeTeamWins > awayTeamWins) {
		std::cout << homeTeamWins << "-" << awayTeamWins << std::endl;
		ALDSWinners[0] = ALRankings[0];
	}
	else {
		std::cout << awayTeamWins << "-" << homeTeamWins << std::endl;
		ALDSWinners[0] = ALWC[0]->winner;
	}


	std::cout << "\n\nALDS (2/2)\n==========" << std::endl;

	homeTeamWins = 0;
	awayTeamWins = 0;

	int g_ALDSb = 0;
	while (homeTeamWins < 3 && awayTeamWins < 3) {
		playGame(ALRankings[1], ALRankings[2], ALDSb, &g_ALDSb);

		if (ALDSb[g_ALDSb - 1]->winner == ALRankings[1]) {
			winner = ALDSb[g_ALDSb - 1]->winner;
			loser = ALDSb[g_ALDSb - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << ALDSb[g_ALDSb - 1]->winnerScore << "-" << ALDSb[g_ALDSb - 1]->loserScore << std::endl;
			homeTeamWins++;
		}

		if (ALDSb[g_ALDSb - 1]->winner == ALRankings[2]) {
			winner = ALDSb[g_ALDSb - 1]->winner;
			loser = ALDSb[g_ALDSb - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << ALDSb[g_ALDSb - 1]->winnerScore << "-" << ALDSb[g_ALDSb - 1]->loserScore << std::endl;
			awayTeamWins++;
		}
	}

	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the ALDS against " << loser->name << " (" << loser->playoffSeed << ") ";

	if (homeTeamWins > awayTeamWins) {
		std::cout << homeTeamWins << "-" << awayTeamWins << std::endl;
		ALDSWinners[1] = ALRankings[1];
	}
	else {
		std::cout << awayTeamWins << "-" << homeTeamWins << std::endl;
		ALDSWinners[1] = ALRankings[2];
	}
	
	std::cout << "\n\nNLDS (1/2)\n==========" << std::endl;

	homeTeamWins = 0;
	awayTeamWins = 0;

	int g_NLDSa = 0; //Keeps track of current game in the series -- winner of the finNL game wins the series
	while (homeTeamWins < 3 && awayTeamWins < 3) {
		playGame(NLRankings[0], NLWC[0]->winner, NLDSa, &g_NLDSa);

		if (NLDSa[g_NLDSa - 1]->winner == NLRankings[0]) {
			winner = NLDSa[g_NLDSa - 1]->winner;
			loser = NLDSa[g_NLDSa - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << NLDSa[g_NLDSa - 1]->winnerScore << "-" << NLDSa[g_NLDSa - 1]->loserScore << std::endl;
			homeTeamWins++;
		}

		if (NLDSa[g_NLDSa - 1]->winner == NLWC[0]->winner) {
			winner = NLDSa[g_NLDSa - 1]->winner;
			loser = NLDSa[g_NLDSa - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << NLDSa[g_NLDSa - 1]->winnerScore << "-" << NLDSa[g_NLDSa - 1]->loserScore << std::endl;
			awayTeamWins++;
		}
	}

	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the NLDS against " << loser->name << " (" << loser->playoffSeed << ") ";

	if (homeTeamWins > awayTeamWins) {
		std::cout << homeTeamWins << "-" << awayTeamWins << std::endl;
		NLDSWinners[0] = NLRankings[0];
	}
	else {
		std::cout << awayTeamWins << "-" << homeTeamWins << std::endl;
		NLDSWinners[0] = NLWC[0]->winner;
	}


	std::cout << "\n\nNLDS (2/2)\n==========" << std::endl;

	homeTeamWins = 0;
	awayTeamWins = 0;

	int g_NLDSb = 0;
	while (homeTeamWins < 3 && awayTeamWins < 3) {
		playGame(NLRankings[1], NLRankings[2], NLDSb, &g_NLDSb);

		if (NLDSb[g_NLDSb - 1]->winner == NLRankings[1]) {
			winner = NLDSb[g_NLDSb - 1]->winner;
			loser = NLDSb[g_NLDSb - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << NLDSb[g_NLDSb - 1]->winnerScore << "-" << NLDSb[g_NLDSb - 1]->loserScore << std::endl;
			homeTeamWins++;
		}

		if (NLDSb[g_NLDSb - 1]->winner == NLRankings[2]) {
			winner = NLDSb[g_NLDSb - 1]->winner;
			loser = NLDSb[g_NLDSb - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << NLDSb[g_NLDSb - 1]->winnerScore << "-" << NLDSb[g_NLDSb - 1]->loserScore << std::endl;
			awayTeamWins++;
		}
	}

	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the NLDS against " << loser->name << " (" << loser->playoffSeed << ") ";

	if (homeTeamWins > awayTeamWins) {
		std::cout << homeTeamWins << "-" << awayTeamWins << std::endl;
		NLDSWinners[1] = NLRankings[1];
	}
	else {
		std::cout << awayTeamWins << "-" << homeTeamWins << std::endl;
		NLDSWinners[1] = NLRankings[2];
	}

	//League Championship

	Score** ALCS = new Score* [7];
	Score** NLCS = new Score* [7];

	Roster** CSWinners = new Roster * [2];

	std::cout << "\n\nALCS\n==========" << std::endl;

	homeTeamWins = 0;
	awayTeamWins = 0;

	int g_ALCS = 0;
	while (homeTeamWins < 4 && awayTeamWins < 4) {
		playGame(ALDSWinners[0], ALDSWinners[1], ALCS, &g_ALCS);

		if (ALCS[g_ALCS - 1]->winner == ALDSWinners[0]) {
			winner = ALCS[g_ALCS - 1]->winner;
			loser = ALCS[g_ALCS - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << ALCS[g_ALCS - 1]->winnerScore << "-" << ALCS[g_ALCS - 1]->loserScore << std::endl;
			homeTeamWins++;
		}

		if (ALCS[g_ALCS - 1]->winner == ALDSWinners[1]) {
			winner = ALCS[g_ALCS - 1]->winner;
			loser = ALCS[g_ALCS - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << ALCS[g_ALCS - 1]->winnerScore << "-" << ALCS[g_ALCS - 1]->loserScore << std::endl;
			awayTeamWins++;
		}
	}

	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the ALCS against " << loser->name << " (" << loser->playoffSeed << ") ";

	if (homeTeamWins > awayTeamWins) {
		std::cout << homeTeamWins << "-" << awayTeamWins << std::endl;
		CSWinners[0] = ALDSWinners[0];
	}
	else {
		std::cout << awayTeamWins << "-" << homeTeamWins << std::endl;
		CSWinners[0] = ALDSWinners[1];
	}

	std::cout << "\n\nNLCS\n==========" << std::endl;

	homeTeamWins = 0;
	awayTeamWins = 0;

	int g_NLCS = 0;
	while (homeTeamWins < 4 && awayTeamWins < 4) {
		playGame(NLDSWinners[0], NLDSWinners[1], NLCS, &g_NLCS);

		if (NLCS[g_NLCS - 1]->winner == NLDSWinners[0]) {
			winner = NLCS[g_NLCS - 1]->winner;
			loser = NLCS[g_NLCS - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << NLCS[g_NLCS - 1]->winnerScore << "-" << NLCS[g_NLCS - 1]->loserScore << std::endl;
			homeTeamWins++;
		}

		if (NLCS[g_NLCS - 1]->winner == NLDSWinners[1]) {
			winner = NLCS[g_NLCS - 1]->winner;
			loser = NLCS[g_NLCS - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << NLCS[g_NLCS - 1]->winnerScore << "-" << NLCS[g_NLCS - 1]->loserScore << std::endl;
			awayTeamWins++;
		}
	}

	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the NLCS against " << loser->name << " (" << loser->playoffSeed << ") ";

	if (homeTeamWins > awayTeamWins) {
		std::cout << homeTeamWins << "-" << awayTeamWins << std::endl;
		CSWinners[1] = NLDSWinners[0];
	}
	else {
		std::cout << awayTeamWins << "-" << homeTeamWins << std::endl;
		CSWinners[1] = NLDSWinners[1];
	}

	//World Series

	Score** WS = new Score * [7];

	std::cout << "\n\WS\n==========" << std::endl;

	homeTeamWins = 0;
	awayTeamWins = 0;

	int g_WS = 0;
	while (homeTeamWins < 4 && awayTeamWins < 4) {
		playGame(CSWinners[0], CSWinners[1], WS, &g_WS);

		if (WS[g_WS - 1]->winner == CSWinners[0]) {
			winner = WS[g_WS - 1]->winner;
			loser = WS[g_WS - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << WS[g_WS - 1]->winnerScore << "-" << WS[g_WS - 1]->loserScore << std::endl;
			homeTeamWins++;
		}

		if (WS[g_WS - 1]->winner == CSWinners[1]) {
			winner = WS[g_WS - 1]->winner;
			loser = WS[g_WS - 1]->loser;
			std::cout << winner->name << " (" << winner->playoffSeed << ") defeated " << loser->name << " (" << loser->playoffSeed << ") " << WS[g_WS - 1]->winnerScore << "-" << WS[g_WS - 1]->loserScore << std::endl;
			awayTeamWins++;
		}
	}

	std::cout << "\n" << winner->name << " (" << winner->playoffSeed << ") has won the World Series against " << loser->name << " (" << loser->playoffSeed << ") ";

	if (homeTeamWins > awayTeamWins) {
		std::cout << homeTeamWins << "-" << awayTeamWins << std::endl;
	}
	else {
		std::cout << awayTeamWins << "-" << homeTeamWins << std::endl;
	}

    return 0;
}