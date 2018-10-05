#include "table.h"

Table::Table(int type1, int type0) {

	dealer_ = Dealer();
	maximumPayoutType1 = 0;
	maximumPayoutType0 = 0;
	totalPayoutType1 = 0;
	totalPayoutType0 = 0;
	totalPlayersType1 = 0;
	totalPlayersType0 = 0;
	isLastHand_ = false;

	for (int i = 0; i < type1; ++i) {
		players_.push_back(Player(1));
	}
	for (int i = 0; i < type0; ++i) {
		players_.push_back(Player(0));
	}
}

Table::~Table() {

}

void Table::play(int nbRounds) {
	for (int i = 0; i < nbRounds; ++i) {

		// Refill Shoe
		if (isLastHand_) {
			shoe_ = Shoe();
			isLastHand_ = false;
		}
		// Play 1 turn
		playing();

		replacePlayers();
	}

	getStats();
}

void Table::check() {

}
void Table::bet() {

}

void Table::playing() {

	for (unsigned i = 0; i < players_.size(); ++i) {
		players_[i].bet();
		
	}
	for (unsigned i = 0; i < players_.size(); ++i) {
		players_[i].addCard(getCard());
		players_[i].addCard(getCard());
	}

	dealer_.addCard(getCard());
	dealer_.addCard(getCard());

	for (unsigned i = 0; i < players_.size(); ++i) {
		done_ = false;
		do {
			switch (players_[i].play(dealer_.showFirst())) {
			case HIT:
				players_[i].addCard(getCard());
				break;
			case PASS:
				done_ = true;
				break;
			}
		} while (!done_);
	}
	done_ = false;
	do {
		switch (dealer_.play()) {
		case HIT:
			dealer_.addCard(getCard());
			break;
		case PASS:
			done_ = true;
			break;
		}
	} while (!done_);
	dealersHand_ = dealer_.check();
	//debugWinners();
	for (unsigned i = 0; i < players_.size(); ++i) {
		players_[i].check(dealersHand_);
	}
}

void Table::replacePlayers() {
	for (unsigned i = 0; i < players_.size(); ++i) {
		Player player = players_[i];
		if (player.isDead()) {
			int payout = player.getMaximumAmount();
			if (player.getType() == 1) {
				if (payout > maximumPayoutType1)
					maximumPayoutType1 = payout;
				totalPayoutType1 += payout;
				totalPlayersType1++;
				players_[i] = Player(1);
				if (payout > 200)
					winners1_++;
			}
			else {
				if (payout > maximumPayoutType0)
					maximumPayoutType0 = payout;
				totalPayoutType0 += payout;
				totalPlayersType0++;
				players_[i] = Player(0);
				if (payout > 200)
					winners0_++;
			}
			
		}
	}
}

void Table::getStats() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	float moyenneType1 = 0;
	float moyenneType0 = 0;
	if (totalPlayersType0 != 0 && totalPlayersType1 != 0) {
		moyenneType1 = (float)totalPayoutType1 / (float)totalPlayersType1;
		moyenneType0 = (float)totalPayoutType0 / (float)totalPlayersType0;
	}

	std::cout << std::endl << "Nombre de Joueur de ";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "Type 0: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << totalPlayersType0 << std::endl;

	std::cout << "Payout Moyen pour ";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "Type 0: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << moyenneType0 << std::endl;

	std::cout << "Payout Maximum pour ";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "Type 0: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << maximumPayoutType0 << std::endl;

	std::cout << "Gain au dessus de 200 pour le type ";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "Type 0: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << winners0_ << std::endl << std::endl << std::endl;


	std::cout << "Nombre de Joueur de ";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "Type 1: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << totalPlayersType1 << std::endl;

	std::cout << "Payout Moyen pour ";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "Type 1: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << moyenneType1 << std::endl;

	std::cout << "Payout Maximum pour ";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "Type 1: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << maximumPayoutType1 << std::endl;

	std::cout << "Gain au dessus de 200 pour le type ";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "Type 1: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << winners1_ << std::endl << std::endl << std::endl;
}

int Table::getCard() {
	int card = shoe_.hit();
	if (card == -2) {
		card = shoe_.hit();
		isLastHand_ = true;
	}
	return card;
}

void Table::debugWinners() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	std::cout << std::endl << "Dealer: " << dealersHand_ << std::endl;
	for (unsigned i = 0; i < players_.size(); ++i) {
		std::cout << "Type " << players_[i].getType() << ": " << players_[i].getHand();
		std::cout << "   Current Amount: " << players_[i].getCurrentAmount();
		if (players_[i].getHand() > dealersHand_ && !players_[i].lost() || dealersHand_ > 21) {
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << " WON" << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		else if ((players_[i].getHand() < dealersHand_ && !players_[i].lost())) {
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << " LOST" << std::endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		else 
			std::cout << " TIE" << std::endl;
	}
}