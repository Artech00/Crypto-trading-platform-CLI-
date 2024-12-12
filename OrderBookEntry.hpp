#pragma once
#include <string>
// Specification
enum class OrderBookType
{
    bid,
    ask,
    unknown // fix later with exception instead of this
};

class OrderBookEntry
{
public:
    double price;
    double amount;
    std::string timestamp;
    std::string currencyPair;
    OrderBookType orderType; // Changed to enum

    OrderBookEntry(double _price,
                   double _amount,
                   const std::string &_timestamp,
                   const std::string &_currencyPair,
                   OrderBookType _orderType);
    static OrderBookType stringToOrderBookType(std::string s);
};