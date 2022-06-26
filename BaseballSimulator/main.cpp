#include <string>
#include "Roster.h"
#include "Player.h"
#include "game.h"
#include <iostream>
#include "statRankings.h"

using std::string;

int main() {
	
	//Array of all rosters
	Roster** league = new Roster* [30];

	//Make chaos roster
	Roster r("Michael's Team");

	//Add custom players to roster
	
	//Player constructor parameters:
	//string givenName, int givenH, int givenSO, int givenBB, int given2B, int given3B, int givenHR, int givenAB

	Player TyCobb("Ty Cobb    ", 4189, 680, 1249, 724, 295, 117, 11440);
	r.addPlayer(&TyCobb);

	Player LouGehrig("Lou Gehrig", 2721, 790, 1508, 534, 163, 493, 8001);
	r.addPlayer(&LouGehrig);
	
	Player BabeRuth("Babe Ruth", 2873, 1330, 2062, 506, 136, 714, 8399);
	r.addPlayer(&BabeRuth);

	Player BarryBonds("Barry Bonds", 2935, 1539, 2558, 601, 77, 762, 9847);
	r.addPlayer(&BarryBonds);

	//A gross overestimate of how I'd do in the MLB
	Player MichaelBryant("Michael Bryant", 5, 100, 5, 0, 0, 0, 500);
	r.addPlayer(&MichaelBryant);
	


	Player g;
	Player h;
	Player j;
	Player m;


	
	
	r.addPlayer(&h);
	r.addPlayer(&j);
	r.addPlayer(&m);
	r.addPlayer(&g);

	//Add custom roster to league
	league[0] = &r;
	
	//Fill out rest of league with rosters composed of random players
	for (int i = 1; i < 30; i++) {
		league[i] = new Roster();
		for (int j = 0; j < 9; j++) {
			league[i]->addPlayer(new Player());
		}
	}

	//Play random matchups until all rosters have played 162 games
	//Plays a game for each team before playing another game for the same team..ensures that all teams play exactly 162 games
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
				playGame(t, s);
			}
			
		}
	}
	
	//Calculate all player and roster stats
	for (int i = 0; i < 30; i++) {
		league[i]->calculateAllStats();
	}

	//Calculate top 10 BA, HR, H, RBI, R, PA
	Player** topBA = new Player* [10];
	Player** topHR = new Player* [10];
	Player** topH = new Player* [10];
	Player** topRBI = new Player* [10];
	Player** topR = new Player* [10];
	Player** topPA = new Player * [10];

	initializePlayerRankings(topBA, topHR, topH, topRBI, topR, topPA);

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 9; j++) {
			Player* p = league[i]->players[j];
			placePlayerInRankings(p, topBA, topHR, topH, topRBI, topR, topPA);
		}
	}

	//Calculate top 10 roster W, BA, HR, H, RBI, R, PA 
	Roster** topRosterW = new Roster * [10];
	Roster** topRosterBA = new Roster* [10];
	Roster** topRosterHR = new Roster* [10];
	Roster** topRosterH = new Roster* [10];
	Roster** topRosterR = new Roster* [10];
	Roster** topRosterPA = new Roster * [10];

	initializeRosterRankings(topRosterW, topRosterBA, topRosterHR, topRosterH, topRosterR, topRosterPA);

	for (int i = 0; i < 30; i++) {
		Roster* t = league[i];
		placeRosterInRankings(t, topRosterW, topRosterBA, topRosterHR, topRosterH, topRosterR, topRosterPA);
	}


	//Display stat leaderboards
	int k = 0;
	std::cout << "League Leaders:\n" << std::endl;
	for (Player** list : { topBA, topHR, topH, topRBI, topR, topPA }) {
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
				std::cout << p->name << "\t" << p->team << "\t" << p->RBI << " RBI" << std::endl;
			}
			else if (k == 4) {
				std::cout << p->name << "\t" << p->team << "\t" << p->R << " R" << std::endl;
			}
			else {
				std::cout << p->name << "\t" << p->team << "\t" << p->PA << " PA" << std::endl;
			}
		}
		std::cout << "======================================" << std::endl;
		k++;
	}
	std::cout << "\n\n" << std::endl;

	k = 0;
	std::cout << "Team Leaders:\n" << std::endl;
	for (Roster** list : { topRosterW, topRosterBA, topRosterHR, topRosterH, topRosterR, topRosterPA }) {
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
	



	//Display custom roster stats
	std::cout << "Final roster statistics:\n" << std::endl;
	std::cout << r.W << " wins out of " << r.gamesPlayed << " games played\n" << std::endl;
	for (int i = 0; i < 9; i++) {
		Player* p = league[0]->players[i];
		std::cout << p->name << "\t\t\t" << p->BA << " BA" << "\t" << p->HR << " HR" << "\t" << p->H << " H" << "\t" << p->RBI << " RBI" << "\t" << p->R << " R" << "\t" << p->PA << " PA" << std::endl;
	}

	std::cout << "========================================================================================" << std::endl;
	
	std::cout << r.name << "\t\t\t" << r.BA << " BA" << "\t" << r.HR << " HR" << "\t" << r.H << " H" << "\t" << r.RBI << " RBI" << "\t" << r.R << " R" <<  "\t" << r.PA << " PA" << std::endl;

	
	
	


	

	//Calculate final standings

	//Playoffs

	

	

	

    return 0;


}