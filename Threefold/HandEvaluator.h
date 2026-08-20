#pragma once
#include "HandData.h"
#include "Cards.h"
#include "Deck.h"
#include "Board.h"
#include "Player.h"
#include <algorithm>
#include <map>

// Hand evaluator class for evaluating and comparing poker hands
// 
// Provides functionality to:
// - Identify hand categories (high card, pair, flush, straight, etc.)
// - Compare two hands and determine the winner
// - Extract card information (ranks, suits, sorted values)
//
// Usage:
//   HandEvaluator evaluator;
//   HandRank category = evaluator.getHandCategory(cards);  // Get hand ranking
//   int result = evaluator.compareHands(hand1, hand2);     // Compare hands (1/-1/0)
class HandEvaluator {
public:

	HandData getHandData(const std::vector<Cards>& cards) const;

	// Returns a map of card ranks and their occurrence count
	std::map<std::string, int> evaluateHand(const std::vector<Cards>& cards) const;

	// Returns a map of card suits and their occurrence count
	std::map<std::string, int> countSuits(const std::vector<Cards>& cards) const;

	// Converts a card rank string to its numeric value for comparison
	int getRankValue(const std::string& rank) const;

	// Returns the highest card value of a straight, considering ace-low straights (A,2,3,4,5 = value 5)
	// Returns 0 if no straight exists
	int getHighestStraightCard(const std::vector<Cards>& cards)const;

	// Extracts rank values from cards and returns them sorted in descending order
	std::vector<int> getSortedRanks(const std::vector<Cards>& cards) const;

	// Returns the highest ranked card value in the hand
	int getHighCard(const std::vector<Cards>& cards) const;

	// Counts the number of pairs in the hand
	int countPair(const std::map<std::string, int>& handRanks) const;

	// Counts the number of three-of-a-kind combinations in the hand
	int countThreeOfAKind(const std::map<std::string, int>& handRanks) const;

	// Determines if the hand contains a full house (three-of-a-kind plus a pair)
	bool hasFullHouse(const std::map<std::string, int>& handRanks) const;

	// Determines if the hand contains four cards of the same rank
	bool hasFourOfAKind(const std::map<std::string, int>& handRanks) const;

	// Determines if the hand contains five consecutive ranked cards, including ace-low straights
	// Handles duplicates by ignoring matching consecutive values
	// Checks both regular straights and the special ace-low case (A,2,3,4,5)
	bool hasStraight(const std::vector<Cards>& cards) const;

	// Determines if the hand contains five or more cards of the same suit
	bool hasFlush(const std::map<std::string, int>& suits) const;

	// Determines if the hand contains five consecutive cards of the same suit
	// Filters cards by suit first, then checks if the filtered cards form a straight
	bool hasStraightFlush(const std::vector<Cards>& cards) const;

	// Determines if the hand contains cards 10, J, Q, K, A all of the same suit
	bool hasRoyalFlush(const std::vector<Cards>& cards) const;

	// Evaluates the hand and returns the highest ranking category
	HandRank getHandCategory(const std::vector<Cards>& cards) const;
};	