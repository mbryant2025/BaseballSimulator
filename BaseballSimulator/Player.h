#pragma once

#include <string>

using std::string;

class Player {

	private:
		double probSO;
		double probOut; //Out that isn't SO
		double probBB;
		double prob1B;
		double prob2B;
		double prob3B;
		double probHR;
	
	public:
		string name;
		string team;
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
		int HR;
		int _1B;
		int _2B;
		int _3B;

		void init(string givenName, int givenH, int givenSO, int givenBB, int given2B, int given3B, int givenHR, int givenAB);

		Player(string givenName, int givenH, int givenSO, int givenBB, int given2B, int given3B, int givenHR, int givenAB);
		Player();

		//Returns string representing outcome... includes SO, out, BB, 1B, 2B, 3B, HR
		// Updates player stats accordingly
		string plateAppearance();

		void calculateStats();

};

