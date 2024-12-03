#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void readCSVFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    string line;
    int rowCount = 0;
    int colCount = 0;

    // First, determine the number of rows and columns (for dynamic allocation)
    while (getline(file, line)) {
        rowCount++;
        stringstream lineStream(line);
        string cell;
        int col = 0;
        while (getline(lineStream, cell, ',')) {
            col++;
        }
        colCount = max(colCount, col);
    }

    // Dynamically allocate a 2D array
    string** data = new string*[rowCount];
    for (int i = 0; i < rowCount; i++) {
        data[i] = new string[colCount];
    }

    // Reset the file stream and read the file again to store the data
    file.clear();
    file.seekg(0, ios::beg);
    int row = 0;
    while (getline(file, line) && row < rowCount) {
        stringstream lineStream(line);
        string cell;
        int col = 0;
        while (getline(lineStream, cell, ',') && col < colCount) {
            data[row][col] = cell;
            col++;
        }
        row++;
    }

    // Close the file
    file.close();

    // Output the data
    cout << "Data read from CSV file:" << endl;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (!data[i][j].empty()) {
                cout << data[i][j] << " ";
            }
        }
        cout << endl;
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < rowCount; i++) {
        delete[] data[i];
    }
    delete[] data;
}

int main() {
    string filePath = "StudentData.csv";
    readCSVFile(filePath);
    return 0;
}
