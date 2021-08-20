#include <iostream>
#include <fstream>



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

	// Loop through trades
	// Format:
	// DIRECTION SYMBOL LOTS PRICE
	// Example:
	// BUY AAPL 10 14801
	// (Buy 10 AAPL shares for 14801)

	std::string direction, symbol;
	int lots, price;

	while (inf >> direction >> symbol >> lots >> price) {
		if (direction == "BUY") {
			// check sell part of orderbook for matches.
		}
		else if (direction == "SELL") {
			// check buy part of orderbook for matches.
		}
		else {
			std::cout << "Unrecognised direction: " << direction << std::endl;
		}
	}


	return 0;
} 