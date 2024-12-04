#include "OrderBookEntry.hpp"
// Implementation
OrderBookEntry::OrderBookEntry(double _price,
    double _amount,
    const std::string& _timestamp,
    const std::string& _currencyPair,
    OrderBookType _orderType)
    : price(_price),
    amount(_amount),
    timestamp(_timestamp),
    currencyPair(_currencyPair),
    orderType(_orderType)
{
}