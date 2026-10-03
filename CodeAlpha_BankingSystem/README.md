# CodeAlpha_BankingSystem

A console-based Banking System written in C++ using **object-oriented programming**, as part of the **CodeAlpha C++ Programming Internship** (Task 4).

## Features
- Create customers (name, phone, auto-generated customer ID)
- Open accounts for customers with an initial deposit
- **Deposit** and **withdraw** money (insufficient funds are rejected)
- **Transfer** funds between two accounts
- Transaction history with type, amount, balance after, and timestamp
- View account information and the **5 most recent transactions**

## Class Design
| Class | Responsibility |
|-------|----------------|
| `Customer` | Stores customer ID, name and phone number |
| `Account` | Holds balance, performs deposits/withdrawals, keeps transaction history |
| `Transaction` | Records one transaction (id, type, amount, balance after, time, note) |
| `Bank` | Manages all customers and accounts, handles transfers |

## How to Compile and Run
```bash
g++ -std=c++11 main.cpp -o app
./app          # Windows: .\app.exe
```

## Menu
```
1. Create customer
2. Open account
3. Deposit
4. Withdraw
5. Transfer
6. Account info & recent transactions
0. Exit
```

## Example Flow
1. Create a customer, which gives you a Customer ID (e.g. 1001).
2. Open an account with that ID, which gives you an Account Number (e.g. 50001).
3. Deposit, withdraw or transfer using the account number.
4. View the account info to see the balance and recent transactions.

## Note
Data is stored in memory only, so it resets when the program closes. Saving to a file is a possible future improvement.

## Concepts Used
Classes and objects, encapsulation, `vector`, `map`, input validation, date/time formatting.

## Author
Your Name — CodeAlpha C++ Programming Intern
