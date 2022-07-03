#include "Roster.h"
#include "Player.h"
#include <string>
#include <iostream>

int rosterNum = 1;

void Roster::init(string league, string givenName) {
	
	this->name = givenName;
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
	this->G = 0;
	this->HR = 0;
	this->_1B = 0;
	this->_2B = 0;
	this->_3B = 0;

	this->numPlayers = 0;
	this->players = new Player*[9];

	this->gamesPlayed = 0;
	this->W = 0;

	this->league = league;

	this->playoffSeed = -1;
}

Roster::Roster(string league, string givenName) {

	Roster::init(league, givenName);
}

Roster::Roster(string league) {
	Roster::init(league, "CPU Team " + std::to_string(rosterNum++));
}

void Roster::addPlayer(Player* p) {
	if (numPlayers == 9) {
		std::cout << "Error: Roster overload" << std::endl;
		exit(1);
	}
	else {
		this->players[numPlayers] = p;
		p->team = this->name;
		numPlayers++;
	}

}

void Roster::calculateAllStats() {
	for (int i = 0; i < numPlayers; i++) {
		players[i]->calculateStats();

		this->R += players[i]->R;
		this->RBI += players[i]->RBI;
		this->BB += players[i]->BB;
		this->H += players[i]->H;
		this->PA += players[i]->PA;
		this->HR += players[i]->HR;
		this->_1B += players[i]->_1B;
		this->_2B += players[i]->_2B;
		this->_3B += players[i]->_3B;
	}

	this->BA = (double)this->H / (this->PA - this->BB);
}

