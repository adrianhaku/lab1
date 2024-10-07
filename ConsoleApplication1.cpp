#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Enumeration for deposit types
enum class DepositType {
    Savings,
    Fixed
};

// Singleton Class for Interest Rates
class InterestRates {
private:
    map<DepositType, double> rates;
    static InterestRates* instance;

    // Private constructor for Singleton
    InterestRates() {
        rates[DepositType::Savings] = 0.03;
        rates[DepositType::Fixed] = 0.05;
    }

public:
    // Get the Singleton instance
    static InterestRates* Instance() {
        if (!instance)
            instance = new InterestRates();
        return instance;
    }

    double getRate(DepositType type) {
        return rates[type];
    }
};

// Initialize the static instance to nullptr
InterestRates* InterestRates::instance = nullptr;

// Deposit class
class Deposit {
private:
    double amount;
    DepositType type;

public:
    Deposit(double amount, DepositType type) : amount(amount), type(type) {}

    double getInterest() {
        InterestRates* rates = InterestRates::Instance();
        return amount * rates->getRate(type);
    }

    void addAmount(double amt) {
        amount += amt;
    }

    double getAmount() {
        return amount;
    }
};

// Client class
class Client {
private:
    int id;
    string name;
    Deposit* deposit;

public:
    Client(int id, string name) : id(id), name(name), deposit(nullptr) {}

    void addDeposit(Deposit* dep) {
        deposit = dep;
    }

    double getInterest() {
        return deposit ? deposit->getInterest() : 0.0;
    }

    void depositAmount(double amt) {
        if (deposit) {
            deposit->addAmount(amt);
        }
    }

    int getId() {
        return id;
    }

    void printClientInfo() {
        cout << "Client ID: " << id << ", Name: " << name << ", Deposit: ";
        if (deposit) {
            cout << deposit->getAmount() << endl;
        }
        else {
            cout << "No deposit" << endl;
        }
    }

    ~Client() {
        delete deposit;
    }
};

// Bank class
class Bank {
private:
    vector<Client*> clients;

public:
    void addClient(Client* client) {
        clients.push_back(client);
    }

    Client* findClientById(int clientId) {
        for (auto& client : clients) {
            if (client->getId() == clientId) {
                return client;
            }
        }
        return nullptr;
    }

    void depositToClient(int clientId, double amt) {
        Client* client = findClientById(clientId);
        if (client && amt > 0) {
            client->depositAmount(amt);
            cout << "Deposit added to client ID " << clientId << endl;
        }
        else {
            cout << "Invalid client ID or amount." << endl;
        }
    }

    double totalInterest() {
        double total = 0;
        for (auto& client : clients) {
            total += client->getInterest();
        }
        return total;
    }

    void listClients() {
        for (auto& client : clients) {
            client->printClientInfo();
        }
    }

    ~Bank() {
        for (auto& client : clients) {
            delete client;
        }
    }
};

// Main Menu and User Interaction
void menu() {
    Bank bank;
    bool running = true;
    while (running) {
        cout << "\nBank Management System\n";
        cout << "1. Add Client" << endl;
        cout << "2. Add Deposit to Client" << endl;
        cout << "3. Replenish Deposit" << endl;
        cout << "4. Calculate Total Interest" << endl;
        cout << "5. List Clients" << endl;
        cout << "6. Exit" << endl;
        cout << "Select an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            string name;
            cout << "Enter Client ID: ";
            cin >> id;
            cout << "Enter Client Name: ";
            cin >> name;
            bank.addClient(new Client(id, name));
            cout << "Client added successfully.\n";
            break;
        }
        case 2: {
            int clientId;
            double amount;
            int type;
            cout << "Enter Client ID: ";
            cin >> clientId;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            cout << "Enter Deposit Type (0 for Savings, 1 for Fixed): ";
            cin >> type;

            DepositType depositType = (type == 0) ? DepositType::Savings : DepositType::Fixed;
            Client* client = bank.findClientById(clientId);
            if (client) {
                client->addDeposit(new Deposit(amount, depositType));
                cout << "Deposit added to client ID " << clientId << endl;
            }
            else {
                cout << "Client not found." << endl;
            }
            break;
        }
        case 3: {
            int clientId;
            double amount;
            cout << "Enter Client ID: ";
            cin >> clientId;
            cout << "Enter Amount to Replenish: ";
            cin >> amount;
            bank.depositToClient(clientId, amount);
            break;
        }
        case 4: {
            cout << "Total Interest for all clients: " << bank.totalInterest() << endl;
            break;
        }
        case 5: {
            cout << "Listing all clients:\n";
            bank.listClients();
            break;
        }
        case 6:
            running = false;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}
