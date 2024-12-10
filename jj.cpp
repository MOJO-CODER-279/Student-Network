#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
void copyString( char source[], char destination[], int& size) {
    int i = 0;
    while (source[i] != '\0') {
        destination[size] = source[i];
        i++;
        size++;
    }
    destination[size] = '\0';
    size++;
}
int student_Index( char data[], int indices[], int size, char name[]) {
    for (int i = 0; i < size; i++) {
        int j = 0;
        while (data[indices[i] + j] == name[j] && name[j] != '\0' && data[indices[i] + j] != '\0') {
            j++;
        }
        if (data[indices[i] + j] == '\0' && name[j] == '\0') {
            return i;
        }
    }
    return -1;
}
bool checkFriendship(int friendship[][2], int count, int a, int b) {
    for (int i = 0; i <count;i++) {
        if (friendship[i][0] == a && friendship[i][1] == b) {
            return true;
        }
    }
    return false;
}
void findNHop(int friendships[][2], int friendshipCount, int count,
                     int studentIndex, int N,char studentData[], int studentIndices[]) {
    const int LINESIZE = 1000;
    int line[LINESIZE][2];  
    int front = 0, end = 0;      
    bool visited[100] = {}; 
    line[end][0] = studentIndex;
    line[end][1] = 0;
    end = (end+ 1) % LINESIZE;
    visited[studentIndex] = true;
    cout << "Students who are " << N << "-hops away from ";
    for (int i = studentIndices[studentIndex]; studentData[i] != '\0'; i++) {
        cout << studentData[i];
    }
    cout << ":"<<endl;
    while (front != end) {
        int student = line[front][0];
        int hop = line[front][1];
        front = (front + 1) % LINESIZE;
        if (hop == N) {
            for (int i = studentIndices[student]; studentData[i] != '\0'; i++) {
                cout << studentData[i];
            }
            cout << endl;
        }
        if (hop < N) {
            for (int i = 0; i < friendshipCount; ++i) {
                int neighbor = -1;
                if (friendships[i][0] == student) {
                    neighbor = friendships[i][1];
                } else if (friendships[i][1] == student) {
                    neighbor = friendships[i][0];
                }
                if (neighbor != -1 && !visited[neighbor]) {
                    visited[neighbor] = true;
                    line[end][0] = neighbor;
                    line[end][1] = hop + 1;
                    end = (end + 1) % LINESIZE;
                }
            }
        }
    }
}
int main() {
    const int NAMESIZE = 10000;  
    const int STUDENTS = 100;       
    const int FRIENDSHIPS = 1000;  
    char studentData[NAMESIZE];  
    int studentIndices[STUDENTS];    
    int friendCounts[STUDENTS];      
    int friendships[FRIENDSHIPS][2]; 
    int counter = 0, dataIndex = 0, friendshipCounter = 0;
    ifstream fin;
    fin.open("StudentData.csv");
    if (!fin.is_open()) {
        cout << "file has not been opened." << endl;
    }
    char line[256];
    fin.getline(line, sizeof(line)); 
    while (fin.getline(line, sizeof(line))) {
        int i = 0, start = 0;
        char studentName[50] = {};
        char currentName[50] = {};
        while (line[i] != ',' && line[i] != '\0') {
            studentName[i] = line[i];
            i++;
        }
        studentName[i] = '\0';
        if (student_Index(studentData, studentIndices, counter, studentName) == -1) {
            studentIndices[counter] = dataIndex;
            copyString(studentName, studentData, dataIndex);
            friendCounts[counter] = 0;
            counter++;
        }
        while (line[i] != '\0') {
            while (line[i] == ',' || line[i] == ' ')i++;
            start = i;
            while (line[i] != ',' && line[i] != '\0')i++;

            int len = i - start;
            for (int j = 0; j < len;j++) {
                currentName[j] = line[start + j];
            }
            currentName[len] = '\0';
            if (currentName[0] != '\0') {
                if (student_Index(studentData, studentIndices,counter, currentName) == -1) {
                    studentIndices[counter] = dataIndex;
                    copyString(currentName, studentData, dataIndex);
                    friendCounts[counter] = 0;
                    counter++;
                }
                int studentIndex = student_Index(studentData, studentIndices,counter, studentName);
                int friendIndex = student_Index(studentData, studentIndices,counter, currentName);
                friendships[friendshipCounter][0] = studentIndex;
                friendships[friendshipCounter][1] = friendIndex;
                friendshipCounter++;
                friendCounts[friendIndex]++;
            }
        }
    }
    fin.close();
    int maxFriends = 0, mostPopularIndex = -1;
    for (int i = 0; i <counter;i++) {
        if (friendCounts[i] > maxFriends) {
            maxFriends = friendCounts[i];
            mostPopularIndex = i;
        }
    }
    if (mostPopularIndex != -1) {
        cout << "The student who is the friend of the most is: ";
        for (int i = studentIndices[mostPopularIndex]; studentData[i] != '\0'; i++) {
            cout << studentData[i];
        }
        cout << " with " << maxFriends << " friends."<<endl;
    } else {
        cout << "No friendships found in the dataset."<<endl;
    }
    cout << "the Asymmetric friendship pairs are:"<<endl;
    for (int i = 0; i < friendshipCounter;i++) {
        int a = friendships[i][0];
        int b = friendships[i][1];
        if (!checkFriendship(friendships, friendshipCounter, b, a)) {
            for (int j = studentIndices[a]; studentData[j] != '\0';j++) {
                cout << studentData[j];
            }
            cout << " -> ";
            for (int j = studentIndices[b]; studentData[j] != '\0';j++) {
                cout << studentData[j];
            }
            cout << endl;
        }
    }
    char checkStudent[50] = "Ruhma Fatima";
    int Index = student_Index(studentData, studentIndices,counter, checkStudent);

    if (Index != -1) {
        for (int hop = 1; hop <= 3;hop++) {
            findNHop(friendships, friendshipCounter,counter,Index, hop, studentData, studentIndices);
        }
    } else {
        cout << "the mentioned student is not in the given dataset."<<endl;
    }

    return 0;
}
