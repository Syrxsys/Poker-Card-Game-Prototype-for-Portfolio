#pragma once
#include "Cards.h"
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

class Deck {
public:
    struct DeckData {
        std::vector<std::string> suits{ "♥", "♦", "♣", "♠" };
        std::vector<std::string> ranks{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    };
    std::vector<Cards> deckCards{};

    // Contructor to create a deck of cards by iterating through the suits and ranks vectors and creating a Cards object for each combination and then shuffle it.
    Deck() {
        DeckData data;
        for (std::string suit : data.suits) {
            for (std::string rank : data.ranks) {
                Cards card;
                card.suit = suit;
                card.rank = rank;

                deckCards.push_back(card);
            }

        }
        shuffle();


    }

    std::size_t size() const {
        return deckCards.size();

    }
    // Shuffle the deck of cards using the random_device and mt19937 classes from the <random> header
    void shuffle() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(deckCards.begin(), deckCards.end(), gen);
    }
    Cards drawCard() {
        if (deckCards.empty()) { throw std::runtime_error("Cannot draw card from an empty deck"); }
        Cards card = deckCards.back();
        deckCards.pop_back();
        return card;
    }
};
