#pragma once
#include "OrderBookEntry.hpp"
#include "CSVReader.hpp"
#include <string>
#include <vector>

class OrderBook
{
public:
    /* construct, reading a csv data file */
    OrderBook(std::string filename);
    /* return vector of all know products in the dataset */
    std::vector<std::string> getKnownProducts();
    /* return vector of Orders according to the sent filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);
    /* returns the earliest time in the orderbook */
    std::string getEarliestTime();
    /* returns the next time after the sent time in the orderbook */
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry &order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    static double getHighPrice(std::vector<OrderBookEntry> &orders);
    static double getLowPrice(std::vector<OrderBookEntry> &orders);

    /**
     * Calculate the moving average of prices over the last `timeWindow` orders.
     * @param orders A vector of OrderBookEntry objects representing the dataset.
     * @param timeWindow The number of most recent entries to consider for the average.
     * @return The moving average of prices.
     */
    static double calculateMovingAverage(std::vector<OrderBookEntry> &orders, int timeWindow);

private:
    std::vector<OrderBookEntry> orders;
};