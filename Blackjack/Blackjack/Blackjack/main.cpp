#include <iostream>
#include "shoe.h"
#include "player.h"
#include "TypeOne.h"
#include "table.h"
#include "Dealer.h"
using namespace std;

int main() {

	char option;
	int nbPlayers;


	for (;;) {
		cout << "(a) Play" << endl << "(b) Test Statistiques" << endl << "(c) Quitter." << endl;
		cin >> option;

		switch (option) {

		case 'a':
			system("CLS");
			cout << "How many players on the table ?";
			cin >> nbPlayers;
			break;

		case 'b': {
			do {
				system("CLS");
				cout << "How many players on the table ? (Maximum 6)" <<  endl;
				cin >> nbPlayers;
			} while (nbPlayers > 6 || nbPlayers < 1);
			int type1 = nbPlayers / 2;
			if (type1 == 0)
				type1 = 1;
			Table table(type1, nbPlayers - type1);
			cout << "How many rounds do you want to simulate ?" << endl;
			int nbRounds;
			cin >> nbRounds;
			table.play(nbRounds);
		}
			break;
		case 'c':
			system("CLS");
			return 0;
			break;
		default:
			cout << "Please select a valid choice." << endl;
			break;

		}

	}
	return 0;
}