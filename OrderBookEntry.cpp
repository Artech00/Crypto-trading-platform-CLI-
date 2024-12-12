#include "OrderBookEntry.hpp"
// Implementation
OrderBookEntry::OrderBookEntry(double _price,
                               double _amount,
                               const std::string &_timestamp,
                               const std::string &_currencyPair,
                               OrderBookType _orderType)
    : price(_price),
      amount(_amount),
      timestamp(_timestamp),
      currencyPair(_currencyPair),
      orderType(_orderType)
{
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
  if (s == "ask")
  {
    return OrderBookType::ask;
  }
  if (s == "bid")
  {
    return OrderBookType::bid;
  }
  return OrderBookType::unknown;
}