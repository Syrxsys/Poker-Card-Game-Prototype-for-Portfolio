#pragma once
#include "HandData.h"
#include "Cards.h"
#include "Deck.h"
#include "Board.h"
#include "Player.h"
#include <algorithm>
#include <map>

/* Hand evaluator class for evaluating and comparing poker hands
 
Provides functionality to:
- Identify hand categories (high card, pair, flush, straight, etc.)
- Compare two hands and determine the winner
- Extract card information (ranks, suits, sorted values)

Usage:
HandEvaluator evaluator;
HandRank category = evaluator.getHandCategory(cards);   Get hand ranking
int result = evaluator.compareHands(hand1, hand2);      Compare hands (1/-1/0) */
class HandEvaluator {
public:
	/* Extracts all information needed to evaluate and compare a poker hand, including rank counts, suit counts, sorted ranks, and straight information.
Centralizes hand analysis so comparison functions do not need to recalculate it. */
	HandData getHandData(const std::vector<Cards>& cards) const;

	/* Returns a map of card ranks and their occurrence count.
Number of times that rank appears in the hand.
Example: {"A":2, "K": 1, "7": 2} */
	std::map<std::string, int> evaluateHand(const std::vector<Cards>& cards) const;

	/* Returns a map of card suits and their occurrence count
Number of times that a suit appears in the hand
Example: {"Hearts": 2, "Spades": 3} */
	std::map<std::string, int> countSuits(const std::vector<Cards>& cards) const;

	/* Converts a card rank string to its numeric value for comparison */
	int getRankValue(const std::string& rank) const;

	/* Returns 5 for the ace in an ace - low straight(A, 2, 3, 4, 5), since the ace acts as the lowest card in this case. */
	int getHighestStraightCard(const std::vector<Cards>& cards)const;

	// Extract every card rank in hand as numbers and sort them in descending order
	std::vector<int> getSortedRanks(const std::vector<Cards>& cards) const;

	int getHighCard(const std::vector<Cards>& cards) const;

	// Counts how many pairs exists
	int countPair(const std::map<std::string, int>& handRanks) const;

	/*Count how many distincts three-of-a-kind combinations exists
Four-of-a-kind is not counted as a three-of-a-kind */
	int countThreeOfAKind(const std::map<std::string, int>& handRanks) const;

	// Returns true if the hand contains at least one three-of-a-kind and a separate pair)
	bool hasFullHouse(const std::map<std::string, int>& handRanks) const;

	/* Returns true if the hand contains four cards of the same rank.
Cards don't need to be of the same suit.*/
	bool hasFourOfAKind(const std::map<std::string, int>& handRanks) const;

	/* Determines if the hand contains five consecutive ranked cards, including ace - low straights
Handles duplicates by ignoring matching consecutive values
Checks both regular straights and the special ace-low case (A,2,3,4,5) */
	bool hasStraight(const std::vector<Cards>& cards) const;

	/* Returns true if at least five cards belongs to the same suit.
The actual cards don't need to be consecutives to return true. */
	bool hasFlush(const std::map<std::string, int>& suits) const;

	// Determines if the hand contains five consecutive cards of the same suit
	bool hasStraightFlush(const std::vector<Cards>& cards) const;

	/* Returns true if the hand contains cards 10, J, Q, K, A. 
The five cards must belong of the same suit.
	*/
	bool hasRoyalFlush(const std::vector<Cards>& cards) const;

	/* Determines the highest ranking poker hand category present.
Checks all possible categories and returns the strongest one. 
he returned HandRank is later used by HandComparator to determine winner.*/
	HandRank getHandCategory(const std::vector<Cards>& cards) const;
};	