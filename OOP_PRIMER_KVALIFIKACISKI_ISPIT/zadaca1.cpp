//
// Created by aleks on 5/20/2025.
//
#include<iostream>
#include <cstring>
using namespace std;

class Student {
    string id;
    int points;
public:
    Student(string id = "NO_ID", int points = 0) {
        this->id = id;
        this->points = points;
    }

    int addPoints (int p) {
        if ((points + p) <= 100) {
            points+=p;
        } else if ((points + p) > 100) {
            points = 100;
        }
    }

    void print() {
        cout<<id<<" - "<<points<<" ";
        if (points > 90) {
            cout<<"BEST"<<endl;
        } else if (points >= 50) {
            cout<<"PASSED"<<endl;
        } else if (points < 50) {
            cout<<"FAILED"<<endl;
        }
    }
};


int main() {
    string command;
    Student s;
    string id;
    int points;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> id >> points;
            s = Student(id, points);
        } else if (command == "constructor2") {
            cin >> id;
            s = Student(id);
        } else if (command == "addPoints") {
            cin >> points;
            s.addPoints(points);
        } else if (command == "print") {
            s.print();
        }
    }


    return 0;
}