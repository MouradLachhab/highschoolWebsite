#ifndef SHOE_H
#define SHOE_H

#include <vector>
#include <time.h>  
#include <iostream>

class Shoe {

public:
	Shoe();
	~Shoe();
	int hit();
	bool isLastHand();
	void shuffle();

private:
	std::vector<int> cards_;
};



#endif 

