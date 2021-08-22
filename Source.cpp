#include <iostream>
#include <fstream>

#include "OrderBook.h"

constexpr auto INPUT_FILE = "input_example.txt"; // const?

int main() {
	std::cout << "Hello world." << std::endl;

	// read file

	std::ifstream inf{ INPUT_FILE };

	if (!inf) {
		std::cout << "Failed to open " << INPUT_FILE << " - exiting." << std::endl;
		return 1;
	}

	std::cout << "Opened " << INPUT_FILE << " successfully." << std::endl;

	OrderBook book;

	// Loop through trade input file
	// Format:
	// DIRECTION SYMBOL LOTS PRICE
	// Example:
	// BUY AAPL 10 14801
	// (Buy 10 AAPL shares for 14801)

	std::string direction;
	Order order;

	while (inf >> direction >> order.symbol >> order.lots >> order.price) {
		std::vector<Trade> matches;
		if (order.lots <= 0) {
			std::cout << "lots <= 0 detected - exiting.";
			return 1;
		}
		if (direction == "BUY") {
			// check sell part of orderbook for matches.
			matches = book.add_buy(order); // returns collection of matches
		}
		else if (direction == "SELL") {
			// check buy part of orderbook for matches.
			matches = book.add_sell(order);
		}
		else {
			std::cout << "Unrecognised direction: " << direction << " - exiting." << std::endl;
			return 1;
		}
		for (auto match : matches) {
			std::cout << "TRADED " << match.lots << " " << match.symbol << " AT " << match.price << std::endl;;
		}
	}


	return 0;
} 