#ifndef TABLE_H
#define TABLE_H
#include "player.h"
#include "Dealer.h"
#include "shoe.h"
#include <windows.h>
#include <iostream>
#include <vector>

class Table {

public:
	Table(int nbType1, int nbType0);
	~Table();
	void play(int nbRounds);
	void check();
	void bet();
	void playing();
	void replacePlayers();
	void getStats();
	void debugWinners();
	int getCard();

protected:
	int maximumPayoutType1;
	int maximumPayoutType0;
	int totalPayoutType1;
	int totalPayoutType0;
	int totalPlayersType1;
	int totalPlayersType0;
	int dealersHand_;
	int winners0_ = 0;
	int winners1_ = 0;
	bool done_ = false;
	bool isLastHand_;
	std::vector<Player> players_;
	Shoe shoe_;
	Dealer dealer_;
};



#endif 
