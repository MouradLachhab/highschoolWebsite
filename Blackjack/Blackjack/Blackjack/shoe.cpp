#include "shoe.h"
#define ACE -1

Shoe::Shoe() {

	int card;

	for (unsigned k = 0; k < 8; ++k) {
		for (unsigned i = 2; i <= 14; ++i) {

			if (i == 14)
				card = ACE;
			else if (i > 10)
				card = 10;
			else
				card = i;

			for (unsigned j = 0; j < 4; ++j) {
				cards_.push_back(card);
			}
		}
	}
	cards_.shrink_to_fit();
	for (unsigned i = 0; i < 7; ++i) {
		shuffle();
	}
	cards_[125] = -2;
}

Shoe::~Shoe() {}

int Shoe::hit() {
	if (cards_.empty())
		std::cout << "EmptyShoe";
	int card = cards_.back();
	cards_.pop_back();
	return card;
}

bool Shoe::isLastHand() {
	return (cards_.back() == -2);
}


void Shoe::shuffle() {

	for (unsigned i = cards_.size() - 1; i > 0; --i) {
		int index = rand() % i;
		
		int temp = cards_[index];
		cards_[index] = cards_[i];
		cards_[i] = temp;
	}
}