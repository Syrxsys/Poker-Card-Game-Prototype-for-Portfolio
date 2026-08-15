#pragma once
#include "Cards.h"
#include "Deck.h"
#include "Board.h"
#include <vector>
#include <iostream>

class Player {
public:
    // Constructor for the Player class that takes an integer id as a parameter and initializes the id member variable
    Player(int id) {
        this->id = id;
    };
    std::vector<Cards> cards;
    int id;

    void drawCard(Deck& deck) {
        cards.push_back(deck.drawCard());
    }

    std::size_t handSize() const {
        return cards.size();
    }

    void showHand() const {
        std::cout << "Player " << id << " has " << cards.size() << " cards." << std::endl;
        for (Cards card : cards) {
            card.show();
        }
    }
    std::vector<Cards> getCombination(const Board& board) {
		std::vector<Cards> combination;
		combination.insert(combination.end(), cards.begin(), cards.end());
		combination.insert(combination.end(), board.boardCards.begin(), board.boardCards.end());
		return combination;
    }
};