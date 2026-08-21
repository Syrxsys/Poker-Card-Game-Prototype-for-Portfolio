#include "HandComparator.h"
#include "HandEvaluator.h"

int HandComparator::compareHighCard(const HandData& d1, const HandData& d2) const {
	for (int i = 0; i < d1.ranks.size(); i++) {
		if (d1.ranks[i] > d2.ranks[i]) {
			return 1;
		}
		else if (d2.ranks[i] > d1.ranks[i]) {
			return -1;
		}
	}
	return 0;
}

int HandComparator::comparePair(const HandData& d1, const HandData& d2) const {
	int pairValue1 = 0;
	int pairValue2 = 0;

	std::vector<int> kickers1{};
	std::vector<int> kickers2{};

	for (auto map : d1.cardMapping) {
		if (map.second == 2) {
			pairValue1 = evaluator.getRankValue(map.first);
		}
	}

	for (auto map : d2.cardMapping) {
		if (map.second == 2) {
			pairValue2 = evaluator.getRankValue(map.first);
		}
	}

	for (int rank : d1.ranks) {
		if (rank != pairValue1) {
			kickers1.push_back(rank);
		}
	}

	for (int rank : d2.ranks) {
		if (rank != pairValue2) {
			kickers2.push_back(rank);
		}
	}

	if (pairValue1 > pairValue2) {
		return 1;
	}
	else if (pairValue2 > pairValue1) {
		return -1;
	}
	else {
		for (int i = 0; i < kickers1.size(); i++) {
			if (kickers1[i] > kickers2[i]) {
				return 1;
			}
			else if (kickers2[i] > kickers1[i]) {
				return -1;
			}
		}
		return 0;
	}
}

int HandComparator::compareTwoPair(const HandData& d1, const HandData& d2) const {
	std::vector<int> pairs1{};
	std::vector<int> pairs2{};

	int kicker1 = 0;
	int kicker2 = 0;

	for (auto map : d1.cardMapping) {
		if (map.second == 2) {
			pairs1.push_back(evaluator.getRankValue(map.first));
		}
	}

	for (auto map : d2.cardMapping) {
		if (map.second == 2) {
			pairs2.push_back(evaluator.getRankValue(map.first));
		}
	}

	std::sort(pairs1.rbegin(), pairs1.rend());
	std::sort(pairs2.rbegin(), pairs2.rend());

	for (int rank : d1.ranks) {
		if (rank != pairs1[0] && rank != pairs1[1]) {
			kicker1 = rank;
		}
	}

	for (int rank : d2.ranks) {
		if (rank != pairs2[0] && rank != pairs2[1]) {
			kicker2 = rank;
		}
	}

	if (pairs1[0] != pairs2[0])
		return (pairs1[0] > pairs2[0]) ? 1 : -1;

	if (pairs1[1] != pairs2[1])
		return (pairs1[1] > pairs2[1]) ? 1 : -1;

	return (kicker1 > kicker2) ? 1 :
		(kicker2 > kicker1) ? -1 : 0;
}

int HandComparator::compareThreeOfAKind(const HandData& d1, const HandData& d2) const {
	int threeValue1{};
	int threeValue2{};

	std::vector<int> kickers1{};
	std::vector<int> kickers2{};

	for (auto map : d1.cardMapping) {
		if (map.second == 3) {
			threeValue1 = evaluator.getRankValue(map.first);
		}
	}

	for (auto map : d2.cardMapping) {
		if (map.second == 3) {
			threeValue2 = evaluator.getRankValue(map.first);
		}
	}

	for (int rank : d1.ranks) {
		if (rank != threeValue1) {
			kickers1.push_back(rank);
		}
	}

	for (int rank : d2.ranks) {
		if (rank != threeValue2) {
			kickers2.push_back(rank);
		}
	}

	std::sort(kickers1.rbegin(), kickers1.rend());
	std::sort(kickers2.rbegin(), kickers2.rend());

	if (threeValue1 > threeValue2) {
		return 1;
	}
	else if (threeValue2 > threeValue1) {
		return -1;
	}
	else {
		for (int i = 0; i < kickers1.size(); i++) {
			if (kickers1[i] > kickers2[i]) {
				return 1;
			}
			else if (kickers2[i] > kickers1[i]) {
				return -1;
			}
		}
		return 0;
	}
}

int HandComparator::compareStraight(const HandData& d1, const HandData& d2) const {
	int straightValue1 = evaluator.getHighestStraightCard(d1.cards);
	int straightValue2 = evaluator.getHighestStraightCard(d2.cards);

	if (straightValue1 > straightValue2)
		return 1;

	if (straightValue2 > straightValue1)
		return -1;

	return 0;
}

int HandComparator::compareFlush(const HandData& d1, const HandData& d2) const {
	auto suits1 = evaluator.countSuits(d1.cards);
	auto suits2 = evaluator.countSuits(d2.cards);

	std::string flushSuit1;
	std::string flushSuit2;

	for (auto map : suits1) {
		if (map.second == 5) {
			flushSuit1 = map.first;
		}
	}

	for (auto map : suits2) {
		if (map.second == 5) {
			flushSuit2 = map.first;
		}
	}

	std::vector<int> flushRanks1;
	std::vector<int> flushRanks2;

	for (const auto& card : d1.cards) {
		if (card.suit == flushSuit1) {
			flushRanks1.push_back(evaluator.getRankValue(card.rank));
		}
	}

	for (const auto& card : d2.cards) {
		if (card.suit == flushSuit2) {
			flushRanks2.push_back(evaluator.getRankValue(card.rank));
		}
	}

	std::sort(flushRanks1.rbegin(), flushRanks1.rend());
	std::sort(flushRanks2.rbegin(), flushRanks2.rend());

	for (int i = 0; i < flushRanks1.size(); i++) {
		if (flushRanks1[i] > flushRanks2[i]) {
			return 1;
		}
		else if (flushRanks2[i] > flushRanks1[i]) {
			return -1;
		}
	}

	return 0;
}		

int HandComparator::compareStraightFlush(const HandData& d1, const HandData& d2) const {
	auto suits1 = evaluator.countSuits(d1.cards);
	auto suits2 = evaluator.countSuits(d2.cards);

	std::string sfSuit1;
	std::string sfSuit2;

	std::vector<Cards> suitedCards1;
	std::vector<Cards> suitedCards2;

	for (auto map : suits1) {
		if (map.second >= 5) {
			std::vector<Cards> tempCards;

			for (auto card : d1.cards) {
				if (card.suit == map.first) {
					tempCards.push_back(card);
				}
			}

			if (evaluator.hasStraight(tempCards)) {
				sfSuit1 = map.first;
				suitedCards1 = tempCards;
			}
		}
	}

	for (auto map : suits2) {
		if (map.second >= 5) {
			std::vector<Cards> tempCards;

			for (auto card : d2.cards) {
				if (card.suit == map.first) {
					tempCards.push_back(card);
				}
			}

			if (evaluator.hasStraight(tempCards)) {
				sfSuit2 = map.first;
				suitedCards2 = tempCards;
			}
		}
	}

	int sfValue1 = evaluator.getHighestStraightCard(suitedCards1);
	int sfValue2 = evaluator.getHighestStraightCard(suitedCards2);

	if (sfValue1 > sfValue2)
		return 1;

	if (sfValue2 > sfValue1)
		return -1;

	return 0;
}

int HandComparator::compareFullHouse(const HandData& d1, const HandData& d2) const {
	int ToaK1 = 0;
	int ToaK2 = 0;
	int Pair1 = 0;
	int Pair2 = 0;
	int ThreeCount1 = evaluator.countThreeOfAKind(d1.cardMapping);
	int ThreeCount2 = evaluator.countThreeOfAKind(d2.cardMapping);
	int PairCount1 = evaluator.countPair(d1.cardMapping);
	int PairCount2 = evaluator.countPair(d2.cardMapping);
	
	//Hand 1 Tree Of A Kind
	if (ThreeCount1 == 2) {
		int highest1 = 0;
		int secHighest1 = 0;

		for (const auto& map : d1.cardMapping) {
			if (map.second >= 3) {
				int rank = evaluator.getRankValue(map.first);
				if (rank > highest1) {
					secHighest1 = highest1;
					highest1 = rank;
				}
				else if (rank > secHighest1) {
					secHighest1 = rank;
				}
			}
			
		}

		ToaK1 = highest1;
		Pair1 = secHighest1;
	}
	else if (ThreeCount1 == 1) {
		for (const auto& map : d1.cardMapping) {
			if (map.second >= 3) {
				ToaK1 = evaluator.getRankValue(map.first);
			}
			else if (map.second == 2 && PairCount1 == 1) {
				Pair1 = evaluator.getRankValue(map.first);
			}
			else if (map.second == 2 && PairCount1 == 2) {
				int actual = evaluator.getRankValue(map.first);
				if (actual > Pair1) {
					Pair1 = actual;
				}
				
			}
		} 
	}

	// Hand 2 ThreeOfAKind
	if (ThreeCount2 == 2) {
		int highest2 = 0;
		int secHighest2 = 0;

		for (const auto& map : d2.cardMapping) {
			if (map.second >= 3) {
				int rank = evaluator.getRankValue(map.first);
				if (rank > highest2) {
					secHighest2 = highest2;
					highest2 = rank;
				}
				else if (rank > secHighest2) {
					secHighest2 = rank;
				}
			}
		}

		ToaK2 = highest2;
		Pair2 = secHighest2;
	}
	else if (ThreeCount2 == 1) {
		for (const auto& map : d2.cardMapping) {
			if (map.second >= 3) {
				ToaK2 = evaluator.getRankValue(map.first);
			}
			else if (map.second == 2 && PairCount2 == 1) {
				Pair2 = evaluator.getRankValue(map.first);
			}
			else if (map.second == 2 && PairCount2 == 2) {
				int actual = evaluator.getRankValue(map.first);
				if (actual > Pair2) {Pair2 = actual;}
			}	
		}
	}

	if (ToaK1 > ToaK2) return 1;
	if (ToaK2 > ToaK1) return -1;
	if (Pair1 > Pair2) return 1;
	if (Pair2 > Pair1) return -1;
	return 0;
}

int HandComparator::compareFourOfAKind(const HandData& d1, const HandData& d2) const {
	int rank1 = 0;
	int kicker1 = 0;
	int rank2 = 0;
	int kicker2 = 0;

	for (const auto& map : d1.cardMapping) {
		if (map.second == 4) {
			rank1 = evaluator.getRankValue(map.first);
		}
	}

	for (const int& actual : d1.ranks) {
		if (actual != rank1 && actual > kicker1) {
			kicker1 = actual;
		}
	}

	for (const auto& map : d2.cardMapping) {
		if (map.second == 4) {
			rank2 = evaluator.getRankValue(map.first);
		}
	}

	for (const int& actual : d2.ranks) {
		if (actual != rank2 && actual > kicker2) {
			kicker2 = actual;
		}
	}
	
	if (rank1 > rank2) return 1;
	if (rank2 > rank1) return -1;
	if (kicker1 > kicker2) return 1;
	if (kicker2 > kicker1) return -1;
	return 0;
}

int HandComparator::compareRoyalFlush(const HandData& d1, const HandData& d2) const {
	return 0;
}

int HandComparator::compareHands(const std::vector<Cards>& hand1, const std::vector<Cards>& hand2) const {
	HandData d1 = evaluator.getHandData(hand1);
	HandData d2 = evaluator.getHandData(hand2);

	if (d1.category > d2.category) {
		return 1;
	}
	else if (d2.category > d1.category) {
		return -1;
	}

	switch (d1.category) {

	case HandRank::HighCard:
		return compareHighCard(d1, d2);

	case HandRank::Pair:
		return comparePair(d1, d2);

	case HandRank::TwoPair:
		return compareTwoPair(d1, d2);

	case HandRank::ThreeOfAKind:
		return compareThreeOfAKind(d1, d2);

	case HandRank::Straight:
		return compareStraight(d1, d2);

	case HandRank::Flush:
		return compareFlush(d1, d2);

	case HandRank::FullHouse:
		return compareFullHouse(d1, d2);

	case HandRank::FourOfAKind:
		return compareFourOfAKind(d1, d2);

	case HandRank::StraightFlush:
		return compareStraightFlush(d1, d2);

	case HandRank::RoyalFlush:
		return compareRoyalFlush(d1, d2);
	}

	return 0;
}