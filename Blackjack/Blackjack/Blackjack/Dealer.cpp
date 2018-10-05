#include "Dealer.h"

Dealer::Dealer() {
	softSeventeen_ = false;
}


Dealer::~Dealer() {}

void Dealer::addCard(int card) {

	if (isFirstCard_) {
		firstCard_ = card;
		isFirstCard_ = false;
	}
	if (hasAce_ && currentHandSum_ == 11 && card == 6)
		softSeventeen_ == true;
	else if (currentHandSum_ == 6 && card == ACE && cardCount_ == 1)
		softSeventeen_ == true;

	if (card == ACE && (hasAce_ || (currentHandSum_ + 11 > 21))) {
		card = 1;
	}
	else if (card == ACE) {
		card = 11;
		hasAce_ = true;
	}

	if (hasAce_ && (currentHandSum_ + card > 21))
		currentHandSum_ -= 10;

	currentHandSum_ += card;
	if (currentHandSum_ > 21)
		lost_ = true;

	cardCount_++;
}


int Dealer::check() {
	isFirstCard_ = true;
	int sum = currentHandSum_;
	currentHandSum_ = 0;
	hasAce_ = false;
	cardCount_ = 0;
	softSeventeen_ = false;
	lost_ = false;
	return sum;
}

int Dealer::play() {

	if (lost_)
		return PASS;
	else if (currentHandSum_ == 17 && softSeventeen_)
		return HIT;
	else if (currentHandSum_  < 17)
		return HIT;
	else if (currentHandSum_ >= 17)
		return PASS;
	else
		return PASS;

}

int Dealer::showFirst() {
	return firstCard_;
}