#include "CSVReader.hpp"
#include <iostream>
#include <fstream>
CSVReader::CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception &e)
            {
                std::cout << "CSVReader::readCSV bad data" << std::endl;
            }

        } // end of while
    }

    // Log the result for debugging
    if (entries.empty())
    {
        std::cout << "Warning: No orders found in the CSV file." << std::endl;
    }
    else
    {
        // std::cout << "Successfully read " << entries.size() << " orders from the CSV file." << std::endl;
    }
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::size_t start, end;
    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
        {
            break;
        }
        if (end == std::string::npos)
        {
            tokens.push_back(csvLine.substr(start));
        }
        else
        {
            tokens.push_back(csvLine.substr(start, end - start));
        }
        start = end + 1;
    } while (end != std::string::npos);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{

    double price, amount;
    if (tokens.size() != 5)
    {
        std::cout << "Bad line, skipping..." << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error processing line: " << tokens[3] << std::endl;
        std::cout << "Error processing line: " << tokens[4] << std::endl;
        throw;
    }
    OrderBookEntry obe{price,
                       amount,
                       tokens[0],
                       tokens[1],
                       OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType)
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error processing line(Bad float)!: " << priceString << std::endl;
        std::cout << "Error processing line(Bad float)!: " << amountString << std::endl;
        throw;
    }
    OrderBookEntry obe{price,
                       amount,
                       timestamp,
                       product,
                       orderType};
    return obe;
}