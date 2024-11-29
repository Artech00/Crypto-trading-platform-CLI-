#include <iostream>

int main()
{
    int choice;

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
            std::cout << "Exchange Stats: Current exchange rates and statistics." << std::endl;
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
    } while (choice != 6); // Repeat untill the user chooses to continue

    return 0;
}
