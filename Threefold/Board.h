#pragma once
#include "Cards.h"
#include "Deck.h"
#include <vector>
class Board {
public:
	std::vector<Cards> boardCards;
	void addCard(Deck& deck) {
		boardCards.push_back(deck.drawCard());
	}
	void showBoard() const {
		std::cout << "Board has " << boardCards.size() << " cards." << std::endl;
		for (Cards card : boardCards) {
			card.show();
		}
	}
};