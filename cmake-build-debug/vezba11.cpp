//
// Created by aleks on 3/26/2025.
//

#include<iostream>
#include<cstring>
using namespace std;

class LibraryMember;
class Library;

class Book {
private:
    char name[30];
    char author[30];
    bool availability;
    friend class Library;
    friend void checkOutBook (LibraryMember &member, Library &lib, int indeks);

public:

    Book (char *name = "", char *author = "", bool availability=0) {
        strcpy(this->name, name);
        strcpy(this->author, author);
        this->availability = availability;
    }

    Book (const Book &other) {
        strcpy(this->name, other.name);
        strcpy(this->author, other.author);
        this->availability = other.availability;
    }
};

class Library {
private:
    char name[30];
    Book books[30];
    int num_books;
    friend void checkOutBook (LibraryMember &member, Library &lib, int indeks);

public:
    Library() {
        strcpy(name, "Braka miladinovci");
        num_books = 0;

    }

    void addBook (Book b) {
        if (num_books<30) {
            for (int i = 0; i < num_books; i++) {
                if (strcmp(books[i].author, b.author) == 0) {
                    if (books[i].availability) {
                        return;
                    } else {
                        if (b.availability) {
                            books[i] = b;
                        }
                    }
                    return;
                }
            }
            books[num_books++] = b;
            num_books++;
        } else cout<<"Like, did you get the memo? "<<endl;
    }

    void print () {
        cout<<name<<endl;
        for (int i = 0; i < num_books; i++) {
            cout<<books[i].name<<" "<<books[i].author<<" ";
            if (books[i].availability) {
                cout<<"Available"<<endl;
            } else cout<<"Unavailable"<<endl;
        }
    }
};

class LibraryMember {
private:
    char name[30];
    int id;
public:
    LibraryMember (char *name="", int id = 0) {
        strcpy(this->name,  name);
        this->id = id;
    }

    void print () {
        cout<<"Member: "<<name<<" ID: "<<id<<endl;
    }
};

void checkOutBook (LibraryMember &member, Library &lib, int indeks) {
    if (lib.books[indeks].availability) {
        lib.books[indeks].availability = false;
        cout<<"Knigata ja uspesno iznajmivte"<<endl;
    } cout<<"Knigata ne e dostapna"<<endl;
}



int main () {

    Book kniga ("Parite se otepuvachka", "Risto Krle", 1);
    Library biblioteka;
    biblioteka.print();
    cout<<"---------------"<<endl;
    biblioteka.addBook(kniga);
    biblioteka.print();
    cout<<"----------------"<<endl;
    LibraryMember chlen ("Ime", 123);
    checkOutBook(chlen, biblioteka, 123);
}