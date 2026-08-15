#include "Cards.h"
#include "Deck.h"
#include "Player.h"
#include "Board.h"
#include "HandEvaluator.h"
#include "Game.h"
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Deck deck;
	Board board;
	HandEvaluator evaluator;
    std::cout << "Deck created with " << deck.size() << " cards." << std::endl;
    Player player1(1);
    Player player2(2);

    for (int i = 0; i < 2; i++) {
        player1.drawCard(deck);
        player2.drawCard(deck); 
    }
	for (int i = 0; i < 5; i++) {
		board.addCard(deck);
	}
    player1.showHand();
	std::cout << std::endl;
    player2.showHand();
	std::cout << std::endl;
    board.showBoard();

	std::map<std::string, int> result1 = evaluator.evaluateHand(player1.getCombination(board));
	std::map<std::string, int> result2 = evaluator.evaluateHand(player2.getCombination(board));
	std::map<std::string, int> suits1 = evaluator.countSuits(player1.getCombination(board));
	std::map<std::string, int> suits2 = evaluator.countSuits(player2.getCombination(board));

	if (evaluator.countPair(result1) >= 1) {
        std::cout << "Player 1 has a pair." << std::endl;
    }
    if (evaluator.countPair(result2) >= 1) {
        std::cout << "Player 2 has a pair." << std::endl;
    }
    return 0;
};
