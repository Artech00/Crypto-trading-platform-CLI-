#include <string>
// Specification
enum class OrderBookType
{
    bid,
    ask
};

class OrderBookEntry
{
public:
    std::string timestamp;
    std::string currencyPair;
    OrderBookType orderType; // Changed to enum
    double price;
    double quantity;

    OrderBookEntry(const std::string &_timestamp,
                   const std::string &_currencyPair,
                   OrderBookType _orderType,
                   double _price,
                   double _quantity);
};