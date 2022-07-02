#include <string>
#include "Roster.h"
#include "Player.h"

void initializePlayerRankings(Player** topBA, Player** topHR, Player** topH, Player** top1B, Player** top2B, Player** top3B, Player** topRBI, Player** topR, Player** topPA) {
	for (int i = 0; i < 10; i++) {
		topBA[i] = new Player();
		topHR[i] = new Player();
		top1B[i] = new Player();
		top2B[i] = new Player();
		top3B[i] = new Player();
		topH[i] = new Player();
		topRBI[i] = new Player();
		topR[i] = new Player();
		topPA[i] = new Player();
	}
}

void placePlayerInRankings(Player* p, Player** topBA, Player** topHR, Player** topH, Player** top1B, Player** top2B, Player** top3B, Player** topRBI, Player** topR, Player** topPA) {
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
		if (p->_1B > top1B[i]->_1B)
		{
			for (int j = 9; j > i; j--)
			{
				top1B[j] = top1B[j - 1];
			}
			top1B[i] = p;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (p->_2B > top2B[i]->_2B)
		{
			for (int j = 9; j > i; j--)
			{
				top2B[j] = top2B[j - 1];
			}
			top2B[i] = p;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (p->_3B > top3B[i]->_3B)
		{
			for (int j = 9; j > i; j--)
			{
				top3B[j] = top3B[j - 1];
			}
			top3B[i] = p;
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

void initializeRosterRankings(Roster** topRosterW, Roster** topRosterBA, Roster** topRosterHR, Roster** topRosterH, Roster** topRoster1B, Roster** topRoster2B, Roster** topRoster3B, Roster** topRosterR, Roster** topRosterPA) {
	for (int i = 0; i < 10; i++) {
		topRosterW[i] = new Roster("");
		topRosterBA[i] = new Roster("");
		topRosterHR[i] = new Roster("");
		topRosterH[i] = new Roster("");
		topRoster1B[i] = new Roster("");
		topRoster2B[i] = new Roster("");
		topRoster3B[i] = new Roster("");
		topRosterR[i] = new Roster("");
		topRosterPA[i] = new Roster("");
	}
}

void placeRosterInRankings(Roster* r, Roster** topRosterW, Roster** topRosterBA, Roster** topRosterHR, Roster** topRosterH, Roster** topRoster1B, Roster** topRoster2B, Roster** topRoster3B, Roster** topRosterR, Roster** topRosterPA) {
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
		if (r->_1B > topRoster1B[i]->_1B) {
			for (int j = 9; j > i; j--) {
				topRoster1B[j] = topRoster1B[j - 1];
			}
			topRoster1B[i] = r;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10) {
		if (r->_2B > topRoster2B[i]->_2B) {
			for (int j = 9; j > i; j--) {
				topRoster2B[j] = topRoster2B[j - 1];
			}
			topRoster2B[i] = r;
			break;
		}
		i++;
	}
	i = 0;
	while (i < 10) {
		if (r->_3B > topRoster3B[i]->_3B) {
			for (int j = 9; j > i; j--) {
				topRoster3B[j] = topRoster3B[j - 1];
			}
			topRoster3B[i] = r;
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