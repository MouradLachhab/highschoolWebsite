#ifndef DEALER_H
#define DEALER_H
#include "player.h"
#include <vector>

class Dealer : public Player {

public:
	Dealer();
	~Dealer();
	int play();
	void addCard(int card);
	int check();
	int showFirst();

protected:
	bool softSeventeen_;
	int cardCount_;
	int firstCard_;
	bool isFirstCard_;
};


#endif 
