//
// Created by aleks on 3/24/2025.
//
#include<iostream>
#include<cstring>
using namespace std;

class boy {
private:
    char name[20];
    int age;

public:
    boy (char *_name = "alex", int _age = 18) {
        strcpy(name,_name);
        age = _age;
    }

    int getAge() {
        return age;
    }

    void print() {
        cout<<"Boy: "<<name<<" Age:"<<age<<endl;
    }

};

class girl {
private:
    char name[20];
    int age;

public:
    girl (char *_name = "dar", int _age = 18) {
        strcpy(name, _name);
        age = _age;
    }
    int getAge() {
        return age;
    }
    void print() {
        cout<<"Girl: "<<name<<" Age:"<<age<<endl;
    }
};

int diff (boy a, girl b) {
    int agedif;
    if (a.getAge() > b.getAge()) {
        agedif = a.getAge() - b.getAge();
} else if (a.getAge() < b.getAge()) {
    agedif = b.getAge() - a.getAge();
} else agedif = 0;

    return agedif > 5;
}

int main () {
    boy Kanye("kanye", 18);
    girl Kim("kim", 18);
    Kanye.print();
    Kim.print();

    if (diff(Kanye,Kim)) {
        cout<<"Pedofilija"<<endl;
    } else cout<<"Legal"<<endl;



}