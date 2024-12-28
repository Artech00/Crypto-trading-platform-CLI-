#pragma once
#include <string>
// Specification
enum class OrderBookType
{
    bid,
    ask,
    unknown, // fix later with exception instead of this
    sale     // added for sales
};

class OrderBookEntry
{
public:
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType; // Changed to enum

    OrderBookEntry(double _price,
                   double _amount,
                   const std::string &_timestamp,
                   const std::string &_product,
                   OrderBookType _orderType);

    static OrderBookType stringToOrderBookType(std::string s);

    static bool compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.timestamp < e2.timestamp; // Compare timestamps
    }
    static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.price < e2.price; // Compare prices in ascending order
    }
    static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2)
    {
        return e1.price > e2.price; // Compare prices in descending order
    }
};