#pragma once
#include "Cards.h"
#include "Deck.h"
#include "Board.h"
#include "Player.h"
#include <algorithm>
#include <map>
class HandEvaluator {
public:
	// Evaluates the hand and returns a map of ranks and their counts
	std::map<std::string, int> evaluateHand(const std::vector<Cards>& cards) {
		std::map<std::string, int> handRanks;
		for (Cards card : cards) {
			handRanks[card.rank]++;

		}
		return handRanks;
	}

	// Evaluates the hand and returns a map of suits and their counts
	std::map<std::string, int> countSuits(const std::vector<Cards>& cards) {
		std::map<std::string, int> suits;
		for (const Cards& card : cards) {
			suits[card.suit]++;
		}
		return suits;
	}	

	int getRankValue(const std::string& rank) {
		if (rank == "J") return 11;
		if (rank == "Q") return 12;
		if (rank == "K")return 13;
		if (rank == "A") return 14;

		return std::stoi(rank);

	}

	int countPair(const std::map<std::string, int>& handRanks) {
		int pairCounter = 0;
		for (const auto& pair : handRanks) {
			if (pair.second == 2) {
				pairCounter++;
			}
		}
		if (pairCounter >= 1) {
			return pairCounter;
		}
		return 0;
	}

	int countThreeOfAKind(const std::map<std::string, int>& handRanks) {
		int threeCounter = 0;
		for (const auto& pair : handRanks) {
			if (pair.second == 3) {
				threeCounter++;	

			}
		}
		if (threeCounter >= 1) {
			return threeCounter;
		}
		return 0;
	}

	bool hasFullHouse(const std::map<std::string, int>& handRanks) {
		bool hasThree = false;
		bool hasTwo = false;
		std::string threeRank;

		for (const auto& pair : handRanks) {
			if (pair.second >= 3) {
				 threeRank = pair.first;
				 hasThree = true;
			}
		}

		for (const auto& pair : handRanks) {
			if (hasThree && pair.first != threeRank && pair.second >= 2) {
				hasTwo = true;
			}
		}

		if (hasThree && hasTwo) {
			return true;
		}
		return false;
	}

	bool hasFourOfAKind(const std::map<std::string, int>& handRanks) {
		for (const auto& pair : handRanks) {
			if (pair.second == 4) {
				return true;
			}
		}
		return false;
	}

	bool hasStraight(const std::vector<Cards>& cards) {
		std::vector<int> ranks;
		int succeding = 1;
		for (const auto& card : cards) {
			ranks.push_back(getRankValue(card.rank));
		}
		std::sort(ranks.begin(), ranks.end());

		//Check for straight (10, J, Q, K, A)
		for (int i = 1; i < ranks.size(); i++) {
			if (ranks[i] == ranks[i - 1] + 1) {
				succeding++;
				if (succeding == 5) {
					return true;
				}
			}
			else if (ranks[i] == ranks[i - 1]) {
				//Do nothing, same rank
			}
			else {
				//resets counter if not succeding
				succeding = 1;
			}
		}

		//Check for Ace-low straight (A, 2, 3, 4, 5)

		std::vector<int> aceLowStraight = { 14, 2, 3, 4, 5 };
		bool hasAceLowStraight = true;

		for (const int& rank : aceLowStraight) {
			if (std::find(ranks.begin(), ranks.end(), rank) == ranks.end()) {
				hasAceLowStraight = false;
				break;
			}
		}
		if (hasAceLowStraight) {
			return true;
		}
		return false;
	}

	bool hasFlush(const std::map<std::string, int>& suits) {
		for (const auto& pair : suits) {
			if (pair.second >= 5) {
				return true;
			}
		}
		return false;
	}

	bool hasStraightFlush(const std::vector<Cards>& cards) {
		auto suits = countSuits(cards);

		for (const auto& pair : suits) {
			if (pair.second >= 5) {
				std::vector<Cards> suitedCards;

				for (const auto& card : cards) {
					if (card.suit == pair.first) {
						suitedCards.push_back(card);
					}
				}

				if (hasStraight(suitedCards)) {
					return true;
				}

			}
		}
		return false;
	}

	bool hasRoyalFlush(const std::vector<Cards>& cards) {
		auto suits = countSuits(cards);

		std::vector<std::string> royalSequence = {"10", "J", "Q", "K", "A" };
		

		for (const auto& pair : suits) {
			if (pair.second >= 5) {
				bool isRoyalFlush = true;
				std::vector<Cards> suitedCards;

				for (const auto& card : cards) {
					if (card.suit == pair.first) {
						suitedCards.push_back(card);
					}
				}
				for (const std::string rank : royalSequence) {
					if (std::find_if(suitedCards.begin(), suitedCards.end(), [rank](const Cards& card) {
						return card.rank == rank;
					}) == suitedCards.end()) {
						isRoyalFlush = false;
						break;
					}
				}
				if (isRoyalFlush) {
					return true;
				}
			}
		}
		return false;
	}
};		
