//
// Created by aleks on 4/9/2025.
//

// #include<iostream>
// using namespace std;
//
// int main () {
//
//     int array[10] = {10, 5, 7, 32, 25, 16, 13, 12, 1, 66};
//
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9 - i; j++) {
//             if (array[j] > array[j + 1]) {
//                 swap(array[j], array[j+1]);
//             }
//         }
//     }
//     for (int i = 0; i < 10; i++) {
//         cout<<array[i]<<" ";
//     }
// }

#include <iostream>
#include <cstring>
using namespace std;

class Book {
private:
    string name;
    int pagesRead;
public:
    Book(string name = "TEST_BOOK", int pages_read = 0)
        : name(name), pagesRead(pages_read) {
    }

    int readPages(int pages) {
        if (pagesRead + pages > 200) {
            pagesRead = 200;
        } else {
            pagesRead += pages;
        }
    }

    void print() {
        string status;
        if (pagesRead < 100) {
            status = "IN PROGRESS";
        } else if (pagesRead >= 100 && pagesRead < 200) {
            status = "ALMOST DONE";
        } else if (pagesRead == 200) {
            status = "FINISHED";
        }

        // Fix the formatting issue here
        cout<<name<<" "<<"-"<<" "<<pagesRead<<"/200"<<" "<<"-"<<" "<<status<<endl;
        //   cout<<id<<" "<<"-"<<" "<<points<<" "<<""<<status<<endl;
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