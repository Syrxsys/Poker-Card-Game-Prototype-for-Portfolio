#pragma once
#include "HandEvaluator.h"
#include "Player.h"
#include <algorithm>
#include "Cards.h"
#include "Board.h"

class HandComparator {
private:
	// helpers operate on evaluated HandData; functions that need original
	// card vectors receive them as parameters when necessary
	HandEvaluator evaluator;

	int compareHighCard(const HandData& d1, const HandData& d2) const;
	int comparePair(const HandData& d1, const HandData& d2) const;
	int compareTwoPair(const HandData& d1, const HandData& d2) const;
	int compareThreeOfAKind(const HandData& d1, const HandData& d2) const;
	int compareStraight(const HandData& d1, const HandData& d2) const;
	int compareFlush(const HandData& d1, const HandData& d2) const;
	int compareStraightFlush(const HandData& d1, const HandData& d2) const;
	int compareFullHouse(const HandData& d1, const HandData& d2) const;
	int compareFourOfAKind(const HandData& d1, const HandData& d2) const;
	int compareRoyalFlush(const HandData& d1, const HandData& d2) const;

public:
	int compareHands(const std::vector<Cards>& hand1, const std::vector<Cards>& hand2) const;
};
