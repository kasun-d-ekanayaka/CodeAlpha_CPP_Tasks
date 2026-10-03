// CodeAlpha Task 1: CGPA Calculator
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Course {
    string name;
    double gradePoint;
    double credits;
};

double readDouble(const string &prompt, double minV, double maxV) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= minV && v <= maxV) return v;
        cout << "  Invalid input. Enter a number between " << minV << " and " << maxV << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int readInt(const string &prompt, int minV, int maxV) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= minV && v <= maxV) return v;
        cout << "  Invalid input. Enter a whole number between " << minV << " and " << maxV << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    cout << "===== CGPA CALCULATOR =====\n";
    cout << "Grade points: A=4.0, A-=3.7, B+=3.3, B=3.0, B-=2.7, C+=2.3, C=2.0, D=1.0, F=0.0\n\n";

    int n = readInt("Number of courses this semester: ", 1, 20);
    vector<Course> courses;
    double totalCredits = 0, totalPoints = 0;

    for (int i = 1; i <= n; i++) {
        Course c;
        cout << "\n--- Course " << i << " ---\n";
        cout << "Course name: ";
        cin >> ws;
        getline(cin, c.name);
        c.gradePoint = readDouble("Grade points (0.0 - 4.0): ", 0.0, 4.0);
        c.credits = readDouble("Credit hours: ", 0.5, 10.0);
        totalCredits += c.credits;
        totalPoints += c.gradePoint * c.credits;
        courses.push_back(c);
    }

    double gpa = totalPoints / totalCredits;

    cout << "\nDo you have previous semesters? (1 = yes, 0 = no): ";
    int hasPrev = readInt("", 0, 1);
    double cgpa = gpa;
    double prevCredits = 0, prevGpa = 0;
    if (hasPrev == 1) {
        prevCredits = readDouble("Total credits earned in previous semesters: ", 0, 1000);
        prevGpa = readDouble("Previous CGPA: ", 0.0, 4.0);
        cgpa = (prevGpa * prevCredits + totalPoints) / (prevCredits + totalCredits);
    }

    cout << "\n===== RESULT =====\n";
    cout << left << setw(25) << "Course" << setw(10) << "Grade"
         << setw(10) << "Credits" << setw(10) << "Points" << "\n";
    cout << string(55, '-') << "\n";
    cout << fixed << setprecision(2);
    for (const auto &c : courses) {
        cout << left << setw(25) << c.name << setw(10) << c.gradePoint
             << setw(10) << c.credits << setw(10) << c.gradePoint * c.credits << "\n";
    }
    cout << string(55, '-') << "\n";
    cout << "Total credits (semester): " << totalCredits << "\n";
    cout << "Total grade points      : " << totalPoints << "\n";
    cout << "Semester GPA            : " << gpa << "\n";
    cout << "Overall CGPA            : " << cgpa << "\n";
    return 0;
}
