#include "player.h"

Player::Player() : Player::Player(1) {

}

Player::Player(int type) {
	

	numberWinsRow_ = 0;
	bet_ = 10;
	currentAmount_ = 20;
	maximumAmount_ = 20;
	currentHandSum_ = 0;
	hasAce_ = false;
	doubled_ = false;
	lost_ = false;
	type_ = type;
}

Player::~Player() {}

void Player::addCard(int card) {

	if (card == ACE && ( hasAce_ || (currentHandSum_ + 11 > 21))) {
		card = 1;
	}
	else if (card == ACE) {
		card = 11;
		hasAce_ = true;
	}

	if (hasAce_ &&  (currentHandSum_ + card > 21))
		currentHandSum_ -= 10;

	currentHandSum_ += card;
	if (currentHandSum_ > 21)
		lost_ = true;
}

bool Player::doubled() {
	return doubled_;
}

void Player::check(int dealer) {

	if ((currentHandSum_ > dealer || dealer > 21) && !lost_ ) {
		currentAmount_ += bet_;
		numberWinsRow_++;
	}
	else if (currentHandSum_ < dealer || lost_) {
		currentAmount_ -= bet_;
		numberWinsRow_ = 0;
	}

	if (currentAmount_ > maximumAmount_)
		maximumAmount_ = currentAmount_;

	currentHandSum_ = 0;
	hasAce_ = false;
	doubled_ = false;
	lost_ = false;
}

int Player::play(int dealer) {
	if (doubled_ || lost_)
		return PASS;
	else if (currentHandSum_ >= 15 && hasAce_)
		return PASS;
	else if (hasAce_)
		return HIT;
	else if (currentHandSum_ >= 17)
		return PASS;
	else if ((currentHandSum_ == 10 || currentHandSum_ == 11) && dealer < 7 && dealer > 1 && (currentAmount_ >= 2*bet_)) {
		doubled_ = true;
		bet_ *= 2;
		return HIT;
	}
	else if (currentHandSum_ <= 11)
		return HIT;
	else if (currentHandSum_ <= 13 && dealer >= 7)
		return HIT;
	else 
		return PASS;

}
int Player::bet() {
	if (currentAmount_ == 0)
		return 0;
	if (type_ == 1) {		// Adds on streaks, reset on loss
		if (numberWinsRow_ > 1)
			return bet_ = lastBet_ += 10;
		else {
			bet_ = 10;
			lastBet_ = 10;
		}
		}
	else if (type_ == 0) {} // Always bets the same
	return bet_ = 10;;
}

bool Player::isDead() {
	return (currentAmount_ <= 0);
}

int Player::getType() {
	return type_;
}
int Player::getMaximumAmount() {
	return maximumAmount_;
}

int Player::getHand() {
	return currentHandSum_;
}

int Player::getCurrentAmount() {
	return currentAmount_;
}

bool Player::lost() {
	return lost_;
}