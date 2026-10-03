# CodeAlpha_LoginSystem

A console-based Login and Registration System written in C++ as part of the **CodeAlpha C++ Programming Internship** (Task 2).

## Features
- **Register** with a username and password
- Username validation (3-20 characters, letters, digits and underscore only)
- Password validation (at least 6 characters, must contain letters and digits)
- Password confirmation during registration
- **Duplicate username check**
- **Login** by verifying the entered credentials against the stored data
- Clear success and error messages for every case

## Secure Storage
Each user is saved in their own file: `user_<username>.txt`

The file stores only:
1. A random **salt**
2. A **hash** of (salt + password)

The plain-text password is **never** saved. Login works by hashing the entered password with the stored salt and comparing it to the stored hash.

> Note: This project uses a simple FNV-1a based hash to stay dependency-free. Production systems should use a proven algorithm such as bcrypt or Argon2.

## How to Compile and Run
```bash
g++ -std=c++11 main.cpp -o app
./app          # Windows: .\app.exe
```

## Menu
```
1. Register
2. Login
3. Exit
```

## Concepts Used
File handling (`ifstream` / `ofstream`), hashing, salting, string validation, random number generation, functions.

## Author
Your Name — CodeAlpha C++ Programming Intern
