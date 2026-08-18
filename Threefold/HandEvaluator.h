#pragma once
#include "Cards.h"
#include "Deck.h"
#include "Board.h"
#include "Player.h"
#include <algorithm>
#include <map>

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

	std::vector<int> getSortedRanks(const std::vector<Cards>& cards) {
		std::vector<int> ranks{};

		for (const auto card : cards) {
			ranks.push_back(getRankValue(card.rank));
		}

		std::sort(ranks.rbegin(), ranks.rend());

		return ranks;

	}

	int getHighCard(const std::vector<Cards>& cards) {
		int highCardValue = 0;
		for (const auto& card : cards) {
			int cardValue = getRankValue(card.rank);
			if (cardValue > highCardValue) {
				highCardValue = cardValue;
			}
		}
		return highCardValue;
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

	HandRank getHandCategory(const std::vector<Cards>& cards) {
		auto cardHand = evaluateHand(cards);
		auto suits = countSuits(cards);

		if (hasRoyalFlush(cards)) {
			return HandRank::RoyalFlush;
		}
		else if (hasStraightFlush(cards)) {
			return HandRank::StraightFlush;
		}
		else if (hasFourOfAKind(cardHand)) {
			return HandRank::FourOfAKind;
		}
		else if (hasFullHouse(cardHand)) {
			return HandRank::FullHouse;
		}
		else if (hasFlush(suits)) {
			return HandRank::Flush;
		}
		else if (hasStraight(cards)) {
			return HandRank::Straight;
		}
		else if (countThreeOfAKind(cardHand) >= 1) {
			return HandRank::ThreeOfAKind;
		}
		else if (countPair(cardHand) >= 2) {
			return HandRank::TwoPair;
		}
		else if (countPair(cardHand) >= 1) {
			return HandRank::Pair;
		}
		return HandRank::HighCard;
	}	

	int compareHands(const std::vector<Cards>& hand1, const std::vector<Cards>& hand2) {
		auto categoryH1 = getHandCategory(hand1);
		auto categoryH2 = getHandCategory(hand2);

		auto ranks1 = getSortedRanks(hand1);
		auto ranks2 = getSortedRanks(hand2);

		auto hand1CardMapping = evaluateHand(hand1);
		auto hand2CardMapping = evaluateHand(hand2);

		if (categoryH1 > categoryH2) {
			return 1;
		}
		else if (categoryH2 > categoryH1) {
			return -1;
		}
		else {
			switch (categoryH1) {
			case HandRank::HighCard:
				for (int i = 0; i < ranks1.size(); i++) {
					if (ranks1[i] > ranks2[i]) {
						return 1;
					}
					else if (ranks2[i] > ranks1[i]) {
						return -1;
					}
				}
				break;

			case HandRank::Pair:
			{
				int PairValue1 = 0;
				int PairValue2 = 0;

				std::vector<int> kickers1{};
				std::vector<int> kickers2{};

				for (auto map : hand1CardMapping) {
					if (map.second == 2) {
						PairValue1 = getRankValue(map.first);
					}
				}

				for (auto map : hand2CardMapping) {
					if (map.second == 2) {
						PairValue2 = getRankValue(map.first);
					}

				}

				for (int rank : ranks1) {
					if (rank != PairValue1) {
						kickers1.push_back(rank);
					}
				}

				for (int rank : ranks2) {
					if (rank != PairValue2) {
						kickers2.push_back(rank);
					}
				}

				if (PairValue1 > PairValue2) {
					return 1;
				}
				else if (PairValue2 > PairValue1) {
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
				}
				break;
			}

			case HandRank::TwoPair:
				std::vector<int> Pairs1{};
				std::vector<int> Pairs2{};
				int kicker1 = 0;
				int kicker2 = 0;
				for (auto map : hand1CardMapping) {
					if (map.second == 2) {
						Pairs1.push_back(getRankValue(map.first));
					}
				}

				for (auto map : hand2CardMapping) {
					if (map.second == 2) {
						Pairs2.push_back(getRankValue(map.first));
					}
				}

				std::sort(Pairs1.rbegin(), Pairs1.rend());
				std::sort(Pairs2.rbegin(), Pairs2.rend());

				for (int rank : ranks1) {
					if (rank != Pairs1[0] && rank != Pairs1[1]) {
						kicker1 = rank;
					}
				}

				for (int rank : ranks2) {
					if (rank != Pairs1[0] && rank != Pairs2[1]) {
						kicker2 = rank;
					}
				}

				if (Pairs1[0] != Pairs2[0]) return (Pairs1[0] > Pairs2[0]) ? 1 : -1;
				if (Pairs1[1] != Pairs2[1]) return (Pairs1[1] > Pairs2[1]) ? 1 : -1;
				return (kicker1 > kicker2) ? 1 : (kicker2 > kicker1) ? -1 : 0;

				break;
			}
			return 0;
		}

	}
};		
