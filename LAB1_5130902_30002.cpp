#include <iostream>
#include <string>

class Bank {
private:
    std::string bankName;
    int numberOfDeposits;
    double depositAmount;
    double interestRate;

public:
    // Constructor
    Bank(std::string name, int numDeposits, double amount, double rate)
        : bankName(name), numberOfDeposits(numDeposits), depositAmount(amount), interestRate(rate) {}

    // Method to calculate the total interest payment
    double calculateTotalInterest() const {
        double totalDeposit = numberOfDeposits * depositAmount;
        return totalDeposit * (interestRate / 100);
    }

    // Display bank information and interest
    void displayInfo() const {
        std::cout << "Bank: " << bankName << std::endl;
        std::cout << "Number of Deposits: " << numberOfDeposits << std::endl;
        std::cout << "Amount per Deposit: " << depositAmount << std::endl;
        std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
        std::cout << "Total Interest Payment: " << calculateTotalInterest() << std::endl;
    }
};

int main() {
    // Create an object of Bank class
    std::string bankName;
    int numDeposits;
    double amount, interestRate;

    std::cout << "Enter the bank name: ";
    std::getline(std::cin, bankName);

    std::cout << "Enter the number of deposits: ";
    std::cin >> numDeposits;

    std::cout << "Enter the amount per deposit: ";
    std::cin >> amount;

    std::cout << "Enter the interest rate (in percentage): ";
    std::cin >> interestRate;

    Bank bank(bankName, numDeposits, amount, interestRate);

    // Display bank information and total interest payment
    bank.displayInfo();

    return 0;
}