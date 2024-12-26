#include "MerkelMain.hpp"
#include <iostream>
#include <iomanip> // Required for std::fixed and std::setprecision
#include <vector>
#include "OrderBookEntry.hpp"
#include "CSVReader.hpp"
#include "OrderBook.hpp" // Include for calculateMovingAverage function
#include <optional>      // For std::optional

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    // loadOrderBook();
    int input;
    currentTime = orderBook.getEarliestTime();
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    std::cout << "======================" << std::endl;
    std::cout << "      MerkleRex Menu      " << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << "1. Print help" << std::endl;
    std::cout << "2. Print exchange stats" << std::endl;
    std::cout << "3. Place an ask" << std::endl;
    std::cout << "4. Place a bid" << std::endl;
    std::cout << "5. Print wallet" << std::endl;
    std::cout << "6. Calculate moving average" << std::endl; // New menu option
    std::cout << "7. Continue" << std::endl;
    std::cout << "======================" << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help: Here are the options you can choose from." << std::endl;
}



void MerkelMain::printMarketStats()
{
    for (const std::string &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;

        // Get orders for the current product
        std::vector<OrderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::vector<OrderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid, p, currentTime);

        // Handle asks
        if (!askEntries.empty())
        {
            std::cout << "Asks seen: " << askEntries.size() << std::endl;

            double maxAskPrice = OrderBook::getHighPrice(askEntries);
            double minAskPrice = OrderBook::getLowPrice(askEntries);

            std::cout << std::fixed << std::setprecision(9); // Set fixed-point notation and 9 decimal places
            std::cout << "Max asks: " << maxAskPrice << std::endl;
            std::cout << "Min asks: " << minAskPrice << std::endl;
        }
        else
        {
            std::cout << "No ask prices available." << std::endl;
        }

        // Handle bids
        if (!bidEntries.empty())
        {
            std::cout << "Bids seen: " << bidEntries.size() << std::endl;

            double maxBidPrice = OrderBook::getHighPrice(bidEntries);
            double minBidPrice = OrderBook::getLowPrice(bidEntries);

            std::cout << std::fixed << std::setprecision(9); // Set fixed-point notation and 9 decimal places
            std::cout << "Max bids: " << maxBidPrice << std::endl;
            std::cout << "Min bids: " << minBidPrice << std::endl;
        }
        else
        {
            std::cout << "No bid prices available." << std::endl;
        }
    }
}

void MerkelMain::enterOffer()
{
    std::cout << "Placing an ask: Enter the amount you wish to (sell)." << std::endl;
}

void MerkelMain::enterBid()
{
    std::cout << "Placing a bid: Enter the amount you wish to bid(buy)." << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << "Wallet: Your current wallet is empty." << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame" << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption;

    std::cout << "Please select a choice (1-7): ";
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption <= 0 || userOption > 7)
    {
        std::cout << "Invalid choice. Please select a number between 1 and 7." << std::endl;
        std::cout << "----------------------" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterOffer();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        DisplayMovingAverage(); // Call the new function
    }
    if (userOption == 7)
    {
        gotoNextTimeframe();
    }
}

void MerkelMain::DisplayMovingAverage()
{
    // Read orders from the file (for a given product and timeframe)
    std::vector<OrderBookEntry> orders = CSVReader::readCSV("average.csv");
    // std::vector<OrderBookEntry> orders = orderBook.getOrders(OrderBookType::ask, "BTC-USD", currentTime); // filtered

    // Check if orders are empty right after reading
    if (orders.empty())
    {
        std::cerr << "Error: No orders found." << std::endl;
        return; // Exit the function without calculating the moving average
    }

    // Prompt user for time window
    int timeWindow;
    std::cout << "Enter the time window for moving average: ";
    std::cin >> timeWindow;

    // Validate time window input
    if (timeWindow <= 0 || timeWindow > orders.size())
    {
        std::cerr << "Error: Invalid time window input. Please provide a time window between 1 and "
                  << orders.size() << " (number of orders available)." << std::endl;
        return; // Exit the function without calculating the moving average
    }

    // Calculate the moving average
    std::optional<double> movingAverage = OrderBook::calculateMovingAverage(orders, timeWindow);

    // If the moving average calculation is successful
    if (movingAverage.has_value())
    {
        // Display the result
        std::cout << std::fixed << std::setprecision(9)
                  << "The MA (moving average) for the last " << timeWindow << " orders is: "
                  << movingAverage.value() << std::endl;

        // Print the last N orders based on the valid timeWindow input
        std::cout << "Last " << timeWindow << " orders:" << std::endl;

        // Calculate the starting index for the last 'timeWindow' orders
        int startIndex = orders.size() - timeWindow;

        // Loop through the selected range and print the orders
        for (int i = startIndex; i < orders.size(); ++i)
        {
            const OrderBookEntry &entry = orders[i];
            std::cout << entry.timestamp << ","                                         // Print Timestamp
                      << entry.product << ","                                           // Print Product
                      << (entry.orderType == OrderBookType::ask ? "ask" : "bid") << "," // Print Order Type
                      << entry.price << ","                                             // Print Price
                      << entry.amount << std::endl;                                     // Print Amount
        }
    }
    else
    {
        // If moving average calculation fails, display an error message
        std::cerr << "Error: Unable to calculate moving average." << std::endl;
    }
}
