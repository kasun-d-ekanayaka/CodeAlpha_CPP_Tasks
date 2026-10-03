# 🎓 CodeAlpha_CGPACalculator

A console-based **CGPA Calculator** written in C++ 💻 as part of the **CodeAlpha C++ Programming Internship** (Task 1). 🚀

## ✨ Features
- 📚 Enter the number of courses for the semester
- 📝 For each course, enter the course name, grade points and credit hours
- ➕ Calculates total credits and total grade points (grade × credit hours)
- 📊 Computes the **semester GPA**
- 🏆 Computes the **overall CGPA** using your previous credits and previous CGPA
- 📋 Displays a neat table of all courses with the final results
- ✅ Input validation for grades, credits and course count

## 🧮 How It Works
```
GPA  = total grade points / total credits
CGPA = (previous CGPA × previous credits + semester points) / (previous credits + semester credits)
```

## 🎯 Grade Scale Used
| Grade | Points | Grade | Points |
|-------|--------|-------|--------|
| A     | 4.0    | C+    | 2.3    |
| A-    | 3.7    | C     | 2.0    |
| B+    | 3.3    | D     | 1.0    |
| B     | 3.0    | F     | 0.0    |
| B-    | 2.7    |       |        |

## ⚙️ How to Compile and Run
```bash
g++ -std=c++11 CodeAlpha_CGPACalculator.cpp -o app
./app          # Windows: .\app.exe
```

## 🖥️ Sample Run
```
Number of courses this semester: 2
Course name: Math        Grade points: 4.0   Credit hours: 3
Course name: Physics     Grade points: 3.3   Credit hours: 4

Semester GPA : 3.60
Overall CGPA : 3.60
```

## 🧠 Concepts Used
Structs, vectors, loops, functions, input validation, formatted output (`iomanip`).

## 👨‍💻 Author
**Your Name** — CodeAlpha C++ Programming Intern 🌟
## Concepts Used
Structs, vectors, loops, functions, input validation, formatted output (`iomanip`).

## Author
Your Name — CodeAlpha C++ Programming Intern
