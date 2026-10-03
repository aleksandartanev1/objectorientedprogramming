//
// Created by aleks on 3/25/2025.
//
#include <iostream>
using namespace std;

class Number {
private:
    int num;

public:
    Number () {
        num = 0;
    }
    Number (int _num) {
        num = _num;
    }

    void set(int num) {
        this->num = num;
    }

    void decreaseNumber (int o) {
        num -= o;
        if (num < 0) {
            cout<<"Difference is less than 0"<<endl;
            num = 0;
        }
    }

    void print() {
        cout<<num<<endl;
    }

};


int main() {
    Number obj;
    int n;
    cin >> n;
    int cmd;
    int k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                obj.set(k);
                obj.print();
                break;
            }
            case 2: {
                cin >> k;
                obj.decreaseNumber(k);
                obj.print();
                break;
            }
            case 3: {
                Number obj2;
                cin >> k;
                obj2.set(k);
                cin >> k;
                obj2.decreaseNumber(k);
                obj2.print();
                break;
            }
            default: {
                obj.print();
                break;
            }
        }
    }
}