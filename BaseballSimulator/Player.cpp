#include "Player.h"
#include "Roster.h"
#include "generatePlayer.h"
#include <string>
#include <stdlib.h>
#include <iostream>

using std::string;

void Player::init(string givenName, int givenH, int givenSO, int givenBB, int given2B, int given3B, int givenHR, int givenAB) {
	
	this->name = givenName;
	this->team = "";
	this->BA = 0;
	this->SLG = 0;
	this->RBI = 0;
	this->R = 0;
	this->SB = 0;
	this->CS = 0;
	this->BB = 0;
	this->H = 0;
	this->PA = 0;
	this->SO = 0;
	this->HR = 0;
	this->_1B = 0;
	this->_2B = 0;
	this->_3B = 0;

	//This simulation does not account for HBP or sac flies -- only hits, outs, and walks
	int givenPA = givenAB + givenBB;
	
	int given1B = givenH - given2B - given3B - givenHR;
	
	//All other outs that are not SO
	int givenOut = givenAB - givenSO - givenH;

	this->probSO = (double) givenSO /givenPA;
	this->probOut = (double) givenOut /givenPA;
	this->probBB = (double) givenBB / givenPA;
	this->prob1B = (double) given1B / givenPA;
	this->prob2B = (double) given2B / givenPA;
	this->prob3B = (double) given3B / givenPA;
	this->probHR = (double) givenHR / givenPA;

	//Check for probabilities >1 or < 0
	for (double x : {probSO, probOut, probBB, prob1B, prob2B, prob3B, probHR}) {
		if(x > 1 || x < 0) {
			std::cout << "Error: Invalid player input statistics" << std::endl;
			exit(1);
		}
	}
}

Player::Player(string givenName, int givenH, int givenSO, int givenBB, int given2B, int given3B, int givenHR, int givenAB) {
	init(givenName, givenH, givenSO, givenBB, given2B, given3B, givenHR, givenAB);
}

Player::Player() {
	//Will be random values in the future
	//Using Brett Gardner's stats for now

	string n = randomName();

	int* stats = randomStats();
	
	init(n, stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6]);
}

//Returns string representing outcome and updates player stats
string Player::plateAppearance() {
		
	this->PA++;

	string result = "";

	double random = (double)rand() / (double)RAND_MAX;

	if (random < probSO) { //doesn't include other forms of outs
		this->SO++;
		result = "SO";
	}
	else if (random < probSO + probOut) {
		result = "out";
	}
	else if (random < probSO + probOut + probBB) {
		this->BB++;
		result = "BB";
	}
	else if (random < probSO + probOut + probBB + prob1B) {
		this->_1B++;
		this->H++;
		result = "1B";
	}
	else if (random < probSO + probOut + probBB + prob1B + prob2B) {
		this->_2B++;
		this->H++;
		result = "2B";
	}
	else if (random < probSO + probOut + probBB + prob1B + prob2B + prob3B) {
		this->_3B++;
		this->H++;
		result = "3B";
	}
	else {
		this->HR++;
		this->H++;
		result = "HR";
	}

	return result;
}

void Player::calculateStats() {
	this->BA = (double) this->H / (this->PA - this->BB);
}

