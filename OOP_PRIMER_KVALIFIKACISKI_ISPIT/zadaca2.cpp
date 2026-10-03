//
// Created by aleks on 5/20/2025.
//
#include<iostream>
#include <cstring>
using namespace std;

class Book {
    string name;
    int pagesRead;
public:
    Book(string name = "TEST_BOOK", int pagesRead = 0) {
        this->name = name;
        this->pagesRead = pagesRead;
    }

    int readPages (int pages) {
        pagesRead +=pages;
        if (pagesRead > 200) {
            pagesRead = 200;
        }
    }

    void print() {
        cout<<name<<" - "<<pagesRead<<"/200"<<" - ";
        if (pagesRead < 100) {
            cout<<"IN PROGRESS"<<endl;
        } else if (pagesRead >= 100 && pagesRead < 200) {
            cout<<"ALMOST DONE"<<endl;
        } else cout<<"FINISHED"<<endl;
    }



};

int main() {
    string command;
    Book s;
    string name;
    int pagesRead;

    while (cin >> command) {
        if (command == "constructor1") {
            cin >> name >> pagesRead;
            s = Book(name, pagesRead);
        } else if (command == "constructor2") {
            cin >> name;
            s = Book(name);
        } else if (command == "readPages") {
            cin >> pagesRead;
            s.readPages(pagesRead);
        } else if (command == "print") {
            s.print();
        }
    }


    return 0;
}