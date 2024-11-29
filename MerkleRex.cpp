#include <iostream>
#include <vector>
#include <string>

// Define the OrderBookEntry class
class OrderBookEntry
{
public:
    std::string timestamp;
    std::string currencyPair;
    std::string orderType;
    double price;
    double quantity;

    // Constructor
    OrderBookEntry(std::string _timestamp, std::string _currencyPair,
                   std::string _orderType, double _price, double _quantity)
        : timestamp(_timestamp), currencyPair(_currencyPair),
          orderType(_orderType), price(_price), quantity(_quantity) {}
};

// Function to calculate the average price
double computeAveragePrice(const std::vector<OrderBookEntry> &entries)
{
    double total = 0.0;

    for (const auto &entry : entries)
    {
        total += entry.price;
    }

    return total / entries.size();
}

// Function to calculate the lowest price
double computeLowPrice(const std::vector<OrderBookEntry> &entries)
{
    double lowPrice = entries[0].price;

    for (const auto &entry : entries)
    {
        if (entry.price < lowPrice)
        {
            lowPrice = entry.price;
        }
    }

    return lowPrice;
}

// Function to calculate the highest price
double computeHighPrice(const std::vector<OrderBookEntry> &entries)
{
    double highPrice = entries[0].price;

    for (const auto &entry : entries)
    {
        if (entry.price > highPrice)
        {
            highPrice = entry.price;
        }
    }

    return highPrice;
}

// Function to calculate the price spread (high - low)
double computePriceSpread(const std::vector<OrderBookEntry> &entries)
{
    return computeHighPrice(entries) - computeLowPrice(entries);
}

int main()
{
    int choice;

    std::vector<OrderBookEntry> entries = {
        {"2020/03/17 17:01:24.884492", "ETH/BTC", "bid", 0.02186299, 0.1},
        {"2020/03/17 17:02:24.884492", "ETH/BTC", "ask", 0.02200000, 0.2},
        {"2020/03/17 17:03:24.884492", "ETH/BTC", "bid", 0.02180000, 0.15},
        {"2020/03/17 17:04:24.884492", "ETH/BTC", "ask", 0.02210000, 0.25}};

    do
    {
        // Display the menu
        std::cout << "======================" << std::endl;
        std::cout << "      MerkleRex Menu      " << std::endl;
        std::cout << "======================" << std::endl;
        std::cout << "1. Print help" << std::endl;
        std::cout << "2. Print exchange stats" << std::endl;
        std::cout << "3. Place an ask" << std::endl;
        std::cout << "4. Place a bid" << std::endl;
        std::cout << "5. Print wallet" << std::endl;
        std::cout << "6. Continue" << std::endl;
        std::cout << "======================" << std::endl;
        std::cout << "Please select a choice (1-6): ";

        // Get user input
        std::cin >> choice;

        // Respond to user
        std::cout << "----------------------" << std::endl;
        switch (choice)
        {
        case 1:
            std::cout << "Help: Here are the options you can choose from." << std::endl;
            break;
        case 2:
            if (!entries.empty())
            {
                std::cout << "Average Price: " << computeAveragePrice(entries) << std::endl;
                std::cout << "Lowest Price: " << computeLowPrice(entries) << std::endl;
                std::cout << "Highest Price: " << computeHighPrice(entries) << std::endl;
                std::cout << "Price Spread: " << computePriceSpread(entries) << std::endl;
            }
            else
            {
                std::cout << "No data available to compute statistics." << std::endl;
            }
            break;
        case 3:
            std::cout << "Placing an ask: Enter the amount you wish to ask." << std::endl;
            break;
        case 4:
            std::cout << "Placing a bid: Enter the amount you wish to bid." << std::endl;
            break;
        case 5:
            std::cout << "Wallet: Your current wallet balance is X." << std::endl;
            break;
        case 6:
            std::cout << "Continuing with the application..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please select a number between 1 and 6." << std::endl;
        }
        std::cout << "----------------------" << std::endl;
    } while (choice != 6); // Repeat until the user chooses to continue

    return 0;
}
