#include <string>
#include "Roster.h"
#include "Player.h"

void initializePlayerRankings(Player** topBA, Player** topHR, Player** topH, Player** topRBI, Player** topR, Player** topPA) {
	for (int i = 0; i < 10; i++) {
		topBA[i] = new Player();
		topHR[i] = new Player();
		topH[i] = new Player();
		topRBI[i] = new Player();
		topR[i] = new Player();
		topPA[i] = new Player();
	}
}

void placePlayerInRankings(Player* p, Player** topBA, Player** topHR, Player** topH, Player** topRBI, Player** topR, Player** topPA)
{
	int i = 0;
	while (i < 10)
	{
		if (p->BA > topBA[i]->BA)
		{
			for (int j = 9; j > i; j--)
			{
				topBA[j] = topBA[j - 1];
			}
			topBA[i] = p;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (p->HR > topHR[i]->HR)
		{
			for (int j = 9; j > i; j--)
			{
				topHR[j] = topHR[j - 1];
			}
			topHR[i] = p;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (p->H > topH[i]->H)
		{
			for (int j = 9; j > i; j--)
			{
				topH[j] = topH[j - 1];
			}
			topH[i] = p;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (p->RBI > topRBI[i]->RBI)
		{
			for (int j = 9; j > i; j--)
			{
				topRBI[j] = topRBI[j - 1];
			}
			topRBI[i] = p;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (p->R > topR[i]->R)
		{
			for (int j = 9; j > i; j--)
			{
				topR[j] = topR[j - 1];
			}
			topR[i] = p;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (p->PA > topPA[i]->PA)
		{
			for (int j = 9; j > i; j--)
			{
				topPA[j] = topPA[j - 1];
			}
			topPA[i] = p;
			break;
		}
		i++;
	}
}

void initializeRosterRankings(Roster** topRosterW, Roster** topRosterBA, Roster** topRosterHR, Roster** topRosterH, Roster** topRosterR, Roster** topRosterPA) {
	for (int i = 0; i < 10; i++) {
		topRosterW[i] = new Roster("");
		topRosterBA[i] = new Roster("");
		topRosterHR[i] = new Roster("");
		topRosterH[i] = new Roster("");
		topRosterR[i] = new Roster("");
		topRosterPA[i] = new Roster("");
	}
}

void placeRosterInRankings(Roster* r, Roster** topRosterW, Roster** topRosterBA, Roster** topRosterHR, Roster** topRosterH, Roster** topRosterR, Roster** topRosterPA) {
	int i = 0;
	while (i < 30) {
		if (r->W > topRosterW[i]->W) {
			for (int j = 29; j > i; j--) {
				topRosterW[j] = topRosterW[j - 1];
			}
			topRosterW[i] = r;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10) {
		if (r->BA > topRosterBA[i]->BA) {
			for (int j = 9; j > i; j--) {
				topRosterBA[j] = topRosterBA[j - 1];
			}
			topRosterBA[i] = r;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10) {
		if (r->HR > topRosterHR[i]->HR) {
			for (int j = 9; j > i; j--) {
				topRosterHR[j] = topRosterHR[j - 1];
			}
			topRosterHR[i] = r;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10) {
		if (r->H > topRosterH[i]->H) {
			for (int j = 9; j > i; j--) {
				topRosterH[j] = topRosterH[j - 1];
			}
			topRosterH[i] = r;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10) {
		if (r->R > topRosterR[i]->R) {
			for (int j = 9; j > i; j--) {
				topRosterR[j] = topRosterR[j - 1];
			}
			topRosterR[i] = r;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10) {
		if (r->PA > topRosterPA[i]->PA) {
			for (int j = 9; j > i; j--) {
				topRosterPA[j] = topRosterPA[j - 1];
			}
			topRosterPA[i] = r;
			break;
		}
		i++;
	}
}