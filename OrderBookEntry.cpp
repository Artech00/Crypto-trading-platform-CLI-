#include "OrderBookEntry.hpp"
// Implementation
OrderBookEntry::OrderBookEntry(const std::string &_timestamp,
                               const std::string &_currencyPair,
                               OrderBookType _orderType,
                               double _price,
                               double _quantity)
    : timestamp(_timestamp),
      currencyPair(_currencyPair),
      orderType(_orderType),
      price(_price),
      quantity(_quantity)
{
}