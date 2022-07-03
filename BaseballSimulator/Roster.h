#pragma once


#include "Player.h"
#include <string>

using std::string;

class Roster {
	
	public:

		Player** players;
		int numPlayers;
		string name;
		double BA;
		double SLG;
		int RBI;
		int R;
		int SB;
		int CS;
		int BB;
		int H;
		int PA;
		int SO;
		int G;
		int HR;
		int _1B;
		int _2B;
		int _3B;
		int gamesPlayed;
		int W;
		string league;
		int playoffSeed;
		
		void init(string league, string givenName);
		
		Roster(string league, string givenName);
		Roster(string league);
		
		void addPlayer(Player* p);

		//Calls calculateStats method on each player in the roster
		void calculateAllStats();
		
		
};
