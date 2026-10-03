//
// Created by aleks on 5/20/2025.
//
#include<iostream>
#include <cstring>
using namespace std;

class Car {
    string id;
    double liters;
public:
    Car(string id = "SK-0001-AA", double liters = 0.0) {
        this->id = id;
        this->liters = liters;
    }

    double refuel(double l) {
        liters+=l;
        if (liters > 50)
            liters = 50;
    }

    void print () {
        cout<<id<<" - "<<liters<<" - ";
        if (liters == 0) {
            cout<<"EMPTY"<<endl;
        } else if (liters < 10) {
            cout<<"LOW"<<endl;
        } else cout<<"ENOUGH"<<endl;
    }

};


int main() {
    string command;
    Car s;
    string id;
    double liters;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> id >> liters;
            s = Car(id, liters);
        } else if (command == "constructor2") {
            cin >> id;
            s = Car(id);
        } else if (command == "refuel") {
            cin >> liters;
            s.refuel(liters);
        } else if (command == "print") {
            s.print();
        }
    }


    return 0;
}