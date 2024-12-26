#pragma once
#include <vector>
#include "OrderBookEntry.hpp"
#include "OrderBook.hpp"

class MerkelMain
{
public:
    MerkelMain();
    void init();

private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);
    void DisplayMovingAverage(); 

    std::string currentTime;
    OrderBook orderBook{"average.csv"}; // info and logic now is used from OrderBook class(.hpp)
};
