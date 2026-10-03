# 🧩 CodeAlpha_SudokuSolver

A **Sudoku Solver** written in C++ 💻 using the **backtracking algorithm**, as part of the **CodeAlpha C++ Programming Internship** (Task 3). 🚀

## ✨ Features
- 🔢 Sudoku grid stored as a 9×9 2D array
- 🔁 Solves the puzzle using recursion and backtracking
- ✅ Checks all three Sudoku rules before placing a number:
  - ↔️ No repeated number in a **row**
  - ↕️ No repeated number in a **column**
  - ⬜ No repeated number in a **3×3 box**
- 🚫 Validates the starting puzzle and reports invalid puzzles or puzzles with no solution
- 🖨️ Prints the puzzle and the solution in a clear grid format

## 🧠 How It Works
1. 🔍 Find an empty cell (`0`).
2. 🎲 Try numbers 1 to 9 in that cell.
3. ✅ If a number is safe, place it and recursively solve the rest.
4. ↩️ If the rest cannot be solved, remove the number (**backtrack**) and try the next one.
5. 🎉 When no empty cells remain, the puzzle is solved.

## ⚙️ How to Compile and Run
```bash
g++ -std=c++11 CodeAlpha_SudokuSolver.cpp -o app
./app          # Windows: .\app.exe
```

## ⌨️ Input Format
Enter 9 rows of 9 characters. Use digits `1-9` for given numbers and `0` or `.` for empty cells.

```
530070000
600195000
098000060
800060003
400803001
700020006
060000280
000419005
000080079
```

## 🖥️ Sample Output
```
5 3 4 | 6 7 8 | 9 1 2
6 7 2 | 1 9 5 | 3 4 8
1 9 8 | 3 4 2 | 5 6 7
------+-------+------
8 5 9 | 7 6 1 | 4 2 3
4 2 6 | 8 5 3 | 7 9 1
7 1 3 | 9 2 4 | 8 5 6
------+-------+------
9 6 1 | 5 3 7 | 2 8 4
2 8 7 | 4 1 9 | 6 3 5
3 4 5 | 2 8 6 | 1 7 9
```

## 📚 Concepts Used
2D arrays, recursion, backtracking, input validation.

## 👨‍💻 Author
**M.Kasun Dilruksha Ekanayaka** — CodeAlpha C++ Programming Intern 🌟
