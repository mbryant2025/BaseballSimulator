#include "generatePlayer.h"
#include <string>
#include <iostream>
#include <fstream>

using std::string;

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
