#pragma once

#include "Cards.h"
#include "HandEvaluator.h"
#include <map>
#include <string>
#include <vector>


enum class HandRank {
	HighCard = 1,
	Pair,
	TwoPair,
	ThreeOfAKind,
	Straight,
	Flush,
	FullHouse,
	FourOfAKind,
	StraightFlush,
	RoyalFlush
};

struct HandData {
	HandRank category;
	std::vector<int> ranks;
	std::map<std::string, int> cardMapping;
	const std::vector<Cards>& cards;
};
