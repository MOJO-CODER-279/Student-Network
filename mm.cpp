#include <iostream>
#include <windows.h> // Include Windows API
using namespace std;

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void clearConsole() {
    system("cls");
}

void setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, pos);
}

void drawBorder(int width, int height) {
    setConsoleColor(11); // Light cyan
    for (int i = 0; i <= height; ++i) {
        for (int j = 0; j <= width; ++j) {
            if (i == 0 || i == height) {
                cout << "="; // Top and bottom border
            } else if (j == 0 || j == width) {
                cout << "|"; // Left and right border
            } else {
                cout << " "; // Empty space inside the border
            }
        }
        cout << endl;
    }
    setConsoleColor(7); // Reset to default color
}

int main() {
    // Dummy data for demonstration
    char studentData[] = "Ali Raza\0Fatima Noor\0Ruhma Fatima\0";
    int studentIndices[] = { 0, 9, 21 };
    int counter = 3;
    int friendships[][2] = { {0, 1}, {1, 2} };
    int friendshipCounter = 2;

    char checkStudent[50] = "Ruhma Fatima";
    int Index = student_Index(studentData, studentIndices, counter, checkStudent);

    clearConsole();
    drawBorder(50, 15);
    setCursorPosition(2, 2);
    setConsoleColor(14); // Yellow
    cout << "Student Friendship Explorer";

    if (Index != -1) {
        setCursorPosition(2, 4);
        setConsoleColor(10); // Green
        cout << "Student found: " << checkStudent;

        for (int hop = 1; hop <= 3; hop++) {
            setCursorPosition(2, 6 + hop);
            setConsoleColor(9); // Light blue
            findNHop(friendships, friendshipCounter, counter, Index, hop, studentData, studentIndices);
        }
    } else {
        setCursorPosition(2, 4);
        setConsoleColor(12); // Red
        cout << "The mentioned student is not in the dataset.";
    }

    setConsoleColor(7); // Reset to default color
    return 0;
}