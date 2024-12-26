#include "OrderBook.hpp"
#include "CSVReader.hpp"
#include <map>
#include <iostream>

/* construct, reading a csv data file */
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

/* return vector of all know products in the dataset */
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for (const OrderBookEntry &e : orders)
    {
        prodMap[e.product] = true;
    }

    // now flatten the map to a vector of strings
    for (auto const &e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}

/* return vector of Orders according to the sent filters */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (const OrderBookEntry &e : orders)
    {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price > max)
        {
            max = e.price;
        }
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double min = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price < min)
        {
            min = e.price;
        }
    }
    return min;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry &e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "") // if there is no next timestamp ->
    {
        next_timestamp = orders[0].timestamp; //-> then go back to default timestamp
    }
    return next_timestamp;
}

double OrderBook::calculateMovingAverage(std::vector<OrderBookEntry> &orders, int timeWindow)
{
    /**
     * Ensure @param timeWindow doesn't exceed the number of available orders,
     * using @param static_cast<int> to safely compare an @param int timeWindow with
     * the @param std::size_t returned by orders.size().
     * Originally, @param orders was a @std::vector<OrderBookEntry>,
     * but orders.size() returns a value of type @std::size_t.
     */

    timeWindow = std::min(timeWindow, static_cast<int>(orders.size()));

    // Calculate the sum of the last `timeWindow` prices
    double sum = 0.0;
    /**
     * Let's assume ` orders.size() = 10, and timeWindow = 3.
     * So, the first iteration will start a i = 10 - 3 = 7.
     */
    for (int i = orders.size() - timeWindow; i < orders.size(); ++i)
    {
        sum += orders[i].price; // Assuming OrderBookEntry has a member `price`
    }

    // Return the average
    return sum / timeWindow;
}