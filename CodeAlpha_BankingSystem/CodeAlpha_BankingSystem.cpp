// CodeAlpha Task 4: Banking System (OOP)
// Classes: Customer, Transaction, Account, Bank
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <limits>
using namespace std;

string currentTime() {
    time_t now = time(nullptr);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buf;
}

class Transaction {
public:
    int id;
    string type;       // Deposit, Withdrawal, Transfer In, Transfer Out
    double amount;
    double balanceAfter;
    string timestamp;
    string note;

    Transaction(int id, string type, double amount, double balanceAfter, string note = "")
        : id(id), type(type), amount(amount), balanceAfter(balanceAfter),
          timestamp(currentTime()), note(note) {}

    void print() const {
        cout << left << "#" << setw(4) << id << setw(14) << type
             << right << setw(10) << fixed << setprecision(2) << amount
             << "  Balance: " << setw(10) << balanceAfter
             << "  " << timestamp;
        if (!note.empty()) cout << "  (" << note << ")";
        cout << "\n";
    }
};

class Customer {
public:
    int id;
    string name;
    string phone;
    Customer() : id(0) {}
    Customer(int id, string name, string phone) : id(id), name(name), phone(phone) {}
};

class Account {
private:
    int accountNumber;
    int customerId;
    double balance;
    vector<Transaction> history;
    int nextTxnId = 1;

public:
    Account() : accountNumber(0), customerId(0), balance(0) {}
    Account(int accNo, int custId, double initial)
        : accountNumber(accNo), customerId(custId), balance(initial) {
        if (initial > 0) history.emplace_back(nextTxnId++, "Deposit", initial, balance, "Opening");
    }

    int getNumber() const { return accountNumber; }
    int getCustomerId() const { return customerId; }
    double getBalance() const { return balance; }

    bool deposit(double amt, const string &type = "Deposit", const string &note = "") {
        if (amt <= 0) return false;
        balance += amt;
        history.emplace_back(nextTxnId++, type, amt, balance, note);
        return true;
    }

    bool withdraw(double amt, const string &type = "Withdrawal", const string &note = "") {
        if (amt <= 0 || amt > balance) return false;
        balance -= amt;
        history.emplace_back(nextTxnId++, type, amt, balance, note);
        return true;
    }

    void showRecent(int count = 5) const {
        if (history.empty()) { cout << "No transactions yet.\n"; return; }
        int start = max(0, (int)history.size() - count);
        for (int i = (int)history.size() - 1; i >= start; i--) history[i].print();
    }
};

class Bank {
private:
    map<int, Customer> customers;
    map<int, Account> accounts;
    int nextCustomerId = 1001;
    int nextAccountNo = 50001;

public:
    int createCustomer(const string &name, const string &phone) {
        int id = nextCustomerId++;
        customers[id] = Customer(id, name, phone);
        return id;
    }

    int createAccount(int customerId, double initialDeposit) {
        if (!customers.count(customerId) || initialDeposit < 0) return -1;
        int no = nextAccountNo++;
        accounts[no] = Account(no, customerId, initialDeposit);
        return no;
    }

    Account *findAccount(int no) {
        auto it = accounts.find(no);
        return it == accounts.end() ? nullptr : &it->second;
    }

    Customer *findCustomer(int id) {
        auto it = customers.find(id);
        return it == customers.end() ? nullptr : &it->second;
    }

    bool transfer(int from, int to, double amt) {
        Account *a = findAccount(from), *b = findAccount(to);
        if (!a || !b || from == to) return false;
        if (!a->withdraw(amt, "Transfer Out", "to " + to_string(to))) return false;
        b->deposit(amt, "Transfer In", "from " + to_string(from));
        return true;
    }

    void showAccountInfo(int no) {
        Account *a = findAccount(no);
        if (!a) { cout << "Account not found.\n"; return; }
        Customer *c = findCustomer(a->getCustomerId());
        cout << "\n----- ACCOUNT INFO -----\n";
        cout << "Account No : " << a->getNumber() << "\n";
        cout << "Holder     : " << c->name << " (ID " << c->id << ", " << c->phone << ")\n";
        cout << "Balance    : " << fixed << setprecision(2) << a->getBalance() << "\n";
        cout << "Recent transactions:\n";
        a->showRecent(5);
    }
};

// ---------- input helpers ----------
int readInt(const string &prompt) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v) return v;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number.\n";
    }
}

double readAmount(const string &prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v) return v;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount.\n";
    }
}

int main() {
    Bank bank;
    int choice;
    do {
        cout << "\n===== BANKING SYSTEM =====\n"
             << "1. Create customer\n"
             << "2. Open account\n"
             << "3. Deposit\n"
             << "4. Withdraw\n"
             << "5. Transfer\n"
             << "6. Account info & recent transactions\n"
             << "0. Exit\n";
        choice = readInt("Choice: ");

        if (choice == 1) {
            string name, phone;
            cout << "Customer name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Phone: ";
            cin >> phone;
            int id = bank.createCustomer(name, phone);
            cout << "Customer created. Customer ID: " << id << "\n";
        } else if (choice == 2) {
            int cid = readInt("Customer ID: ");
            double init = readAmount("Initial deposit: ");
            int no = bank.createAccount(cid, init);
            if (no < 0) cout << "Failed: unknown customer or negative deposit.\n";
            else cout << "Account opened. Account number: " << no << "\n";
        } else if (choice == 3) {
            Account *a = bank.findAccount(readInt("Account number: "));
            if (!a) cout << "Account not found.\n";
            else if (a->deposit(readAmount("Amount: "))) cout << "Deposit successful. Balance: " << a->getBalance() << "\n";
            else cout << "Invalid amount.\n";
        } else if (choice == 4) {
            Account *a = bank.findAccount(readInt("Account number: "));
            if (!a) cout << "Account not found.\n";
            else if (a->withdraw(readAmount("Amount: "))) cout << "Withdrawal successful. Balance: " << a->getBalance() << "\n";
            else cout << "Failed: invalid amount or insufficient funds.\n";
        } else if (choice == 5) {
            int from = readInt("From account: ");
            int to = readInt("To account: ");
            double amt = readAmount("Amount: ");
            if (bank.transfer(from, to, amt)) cout << "Transfer successful.\n";
            else cout << "Transfer failed: check accounts, amount and balance.\n";
        } else if (choice == 6) {
            bank.showAccountInfo(readInt("Account number: "));
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    cout << "Thank you for banking with us!\n";
    return 0;
}