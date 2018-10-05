#ifndef PLAYER_H
#define PLAYER_H
#define ACE -1
#define HIT 1
#define PASS 0

class Player {

public:
	Player();
	Player(int type);
	~Player();
	virtual int play(int dealer);
	virtual void addCard(int card);
	virtual bool doubled();
	virtual void check(int dealer);
	virtual int bet();
	bool isDead();
	int getType();
	int getMaximumAmount();
	int getHand();
	int getCurrentAmount();
	bool lost();
protected:
	int lastBet_;
	int type_;
	int numberWinsRow_;
	int bet_;
	int currentAmount_;
	int maximumAmount_;
	int currentHandSum_;
	bool hasAce_;
	bool doubled_;
	bool lost_;
};



#endif 
