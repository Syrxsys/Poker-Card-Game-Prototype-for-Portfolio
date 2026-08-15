#pragma once
#include "Cards.h"
#include "Deck.h"
#include "Board.h"
#include "Player.h"
#include <map>
class HandEvaluator {
public:
	std::map<std::string, int> evaluateHand(const std::vector<Cards>& cards) {
		std::map<std::string, int> handRanks;
		for (Cards card : cards) {
			handRanks[card.rank]++;

		}
		return handRanks;
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
	bool hasFourOfAKind(const std::map<std::string, int>&handRanks) {
			for (const auto& pair : handRanks) {
				if (pair.second == 4) {
					return true;
				}
			}
			return false;
	}
};