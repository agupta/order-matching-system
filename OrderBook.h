#pragma once
#include <vector>
#include <string>
#include <unordered_map>

enum class Direction {
	buy,
	sell
};
// TODO: Order and Trade are somewhat similar at least as of now, could we redesign this so there is less redundancy?
struct Order {
	std::string symbol;
	unsigned lots;
	int price;
};

struct Trade {
	std::string symbol;
	unsigned lots;
	int price;
};


// The order book consists of two halves: the buy orders and the sell orders.
// Each half is an unordered map std::string symbol -> std::vector<Order> orders.

using OrderBookHalf = std::unordered_map<std::string, std::vector<Order>>; 


class OrderBook {
public:
	std::vector<Trade> add_buy(Order order);
	std::vector<Trade> add_sell(Order order);
private:
	std::vector<Trade> add_order(Direction direction, Order order);
	OrderBookHalf buy_half, sell_half;
};