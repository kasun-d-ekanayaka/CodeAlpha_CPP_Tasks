// CodeAlpha Task 2: Login and Registration System
// Build: g++ -std=c++11 main.cpp -o login
// Each user is stored in its own file: user_<username>.txt (same folder as the program)
// The file contains a random salt and a hash of (salt + password), never the plain password.
// NOTE: FNV-1a is used to keep this project dependency-free. Real systems should
// use bcrypt/argon2.
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <ctime>
using namespace std;

bool fileExists(const string &path) {
    ifstream f(path.c_str());
    return f.good();
}

string hashPassword(const string &salt, const string &password) {
    unsigned long long h = 14695981039346656037ULL;
    string data = salt + password;
    for (unsigned char c : data) {
        h ^= c;
        h *= 1099511628211ULL;
    }
    // Extra rounds to slow down brute force slightly
    for (int i = 0; i < 10000; i++) {
        h ^= (h >> 13);
        h *= 1099511628211ULL;
    }
    stringstream ss;
    ss << hex << setw(16) << setfill('0') << h;
    return ss.str();
}

string generateSalt() {
    random_device rd;
    mt19937_64 gen(static_cast<unsigned long long>(rd()) ^ static_cast<unsigned long long>(time(nullptr)));
    stringstream ss;
    ss << hex << setw(16) << setfill('0') << gen();
    return ss.str();
}

bool validUsername(const string &u) {
    if (u.size() < 3 || u.size() > 20) return false;
    for (char c : u)
        if (!isalnum(static_cast<unsigned char>(c)) && c != '_') return false;
    return true;
}

bool validPassword(const string &p, string &reason) {
    if (p.size() < 6) { reason = "Password must be at least 6 characters."; return false; }
    bool digit = false, alpha = false;
    for (char c : p) {
        if (isdigit(static_cast<unsigned char>(c))) digit = true;
        if (isalpha(static_cast<unsigned char>(c))) alpha = true;
    }
    if (!digit || !alpha) { reason = "Password must contain letters and digits."; return false; }
    return true;
}

string userFile(const string &username) {
    return "user_" + username + ".txt";
}

void registerUser() {
    string username, password, confirm, reason;
    cout << "\n--- REGISTER ---\n";
    cout << "Username (3-20 chars, letters/digits/_): ";
    cin >> username;
    if (!validUsername(username)) {
        cout << "Error: invalid username format.\n";
        return;
    }
    if (fileExists(userFile(username))) {
        cout << "Error: username already exists. Choose another.\n";
        return;
    }
    cout << "Password: ";
    cin >> password;
    if (!validPassword(password, reason)) {
        cout << "Error: " << reason << "\n";
        return;
    }
    cout << "Confirm password: ";
    cin >> confirm;
    if (password != confirm) {
        cout << "Error: passwords do not match.\n";
        return;
    }
    string salt = generateSalt();
    ofstream out(userFile(username).c_str());
    if (!out) {
        cout << "Error: could not save user data.\n";
        return;
    }
    out << salt << "\n" << hashPassword(salt, password) << "\n";
    out.close();
    cout << "Success: account created for '" << username << "'.\n";
}

void loginUser() {
    string username, password;
    cout << "\n--- LOGIN ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Reject odd usernames so nobody can read arbitrary file paths
    if (!validUsername(username) || !fileExists(userFile(username))) {
        cout << "Error: invalid username or password.\n";
        return;
    }
    ifstream in(userFile(username).c_str());
    string salt, storedHash;
    getline(in, salt);
    getline(in, storedHash);
    if (hashPassword(salt, password) == storedHash)
        cout << "Success: welcome back, " << username << "!\n";
    else
        cout << "Error: invalid username or password.\n";
}

int main() {
    int choice;
    do {
        cout << "\n===== LOGIN SYSTEM =====\n";
        cout << "1. Register\n2. Login\n3. Exit\nChoice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }
        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);
    return 0;
}
