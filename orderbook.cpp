//
#include "OrderBook.h"

std::vector<Trade> OrderBook::add_buy(Order order) {
	return add_order(Direction::buy, order);
}
std::vector<Trade> OrderBook::add_sell(Order order) {
	return add_order(Direction::sell, order);
}
std::vector<Trade> OrderBook::add_order(Direction direction, Order order) {
	std::vector<Trade> matches{};
	if (order.lots == 0) {
		return matches;
	}

	int multiplier = direction == Direction::buy ? 1 : -1;
	auto& counter_orders = direction == Direction::buy ? sell_half[order.symbol] : buy_half[order.symbol];
	auto& existing_orders = direction == Direction::buy ? buy_half[order.symbol] : sell_half[order.symbol];


	// fill as many orders as possible, if there are still lots left, add order to other_half.
	for (auto& counter_order : counter_orders) { // TODO: figure out how you want to iterate / better data structure
		if (multiplier * (order.price - counter_order.price) >= 0) { // match! trade!!
			// if counter order lots < order lots, fill the counter order, subtract from order lots
			// if counter order lots == order lots, fill the counter order, 0 order lots
			// if counter order lots > order lots, partially fill the counter order, 0 order lots
			// TODO: if order lots becomes 0, break as no more can be fulfilled.
			// TODO: can this be simplified?
			// TODO: this is super inefficient.
			// using erase-remove paradigm kind of.
			// price traded at is counter order's

			auto lots_filled = std::min(counter_order.lots, order.lots);
			order.lots -= lots_filled;
			counter_order.lots -= lots_filled;
			Trade match{ order.symbol, lots_filled, counter_order.price };
			matches.push_back(match);
		}
	}
	// clean up counter_orders with 0 lots.
	//counter_orders.erase(std::remove_if(counter_orders.begin(), counter_orders.end(), [](const Order& co) {return co.lots == 0; }));
	if (order.lots > 0) {
		existing_orders.push_back(order);
	}
	return matches;
}