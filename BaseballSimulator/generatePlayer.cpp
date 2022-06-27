#include "generatePlayer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <random>

using std::string;

std::default_random_engine generator;
std::normal_distribution<double> dist(1, 0.07);

string randomName() {
	string name = "";
	string fname;
	string lname;

	int firstNameId = rand() % 1000;
	int lastNameId = rand() % 30;

	int i = -1;
	
	std::ifstream firstNames("firstNames.txt");
	std::ifstream lastNames("lastNames.txt");

	while (i < firstNameId) {
		firstNames >> fname;
		i++;
	}

	i = -1;
	while (i < lastNameId) {
		lastNames >> lname;
		i++;
	}

	return fname + " " + lname;
}


//Generates random stats for player based on a normal distribution -- center is average 2019 MLB player
int* randomStats() {

	//int h = rand() % 100;

	//Use 2019 MLB stats
	int h = 42039;
	int so = 42823;
	int bb = 15895;
	int _2b = 8521;
	int _3b = 785;
	int hr = 6776;
	int ab = 166651;

	do {
		h *= dist(generator);
		so *= dist(generator);
		bb *= dist(generator);
		_2b *= dist(generator);
		_3b *= dist(generator);
		hr *= dist(generator);
		ab *= dist(generator);
	} while(h < _2b + _3b + hr || ab < h + so || h < 0 || so < 0 || bb < 0 || _2b < 0 || _3b < 0 || hr < 0 || ab < 0);

	return new int[7]{ h, so, bb, _2b, _3b, hr, ab };
	
}