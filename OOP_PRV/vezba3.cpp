// Да се дефинира класа Subject  за која се чува:
// име (низа од карактери)
// број на кредити (цел број)
// За класата да се дефинира default конструктор, конструктор со аргументи и copy конструктор.
//
// Потоа да се дефинира класа Student за која се чува:
//     име (низа од карактери)
//     презиме (низа од карактери)
//     индекс (низа од карактери)
//     5 предмети што ги слуша (низа од објекти од класата Subject)
//     метод total() што ќе го пресметува вкупниот број на кредити што ќе ги има студентот откако ќе ги положи предметите
//     метод display() кој што ќе испечати информации во формат:
//         Име презиме -> индекс -> кредити
//         За класата да се дефинира  default конструктор и конструктор со аргументи.
//
//         По потреба може да се креираат get и set методи.Ovaa bese ednata drugite dve gi nemam

#include <cstring>
#include <iostream>
using namespace std;

class Subject {
private:
    string name;
    int brojkrediti;

public:
    Subject() {
        name = "";
        brojkrediti = 0;
    }

    Subject(string name, int brojkredti) {
        this->name = name;
        this->brojkrediti = brojkredti;
    }

    Subject(const Subject &o) {
        this->name = o.name;
        this->brojkrediti = o.brojkrediti;
    }

    int getKrediti() {
        return brojkrediti;
    }
};

class Student {
private:
    string name;
    string surname;
    string indeks;
    Subject subjects[5];

public:
    Student () {
        name ="";
        surname ="";
        indeks = "";
    }

    Student(string name, string surname, string indeks, Subject *subjects) {
        this->name = name;
        this->surname = surname;
        this->indeks = indeks;
        for (int i = 0; i < 5; i++) {
            this->subjects[i] = subjects[i];
        }
    }

    int total() {
        int suma = 0;
        for(int i = 0; i < 5; i++) {
            suma+= subjects[i].getKrediti();
        }

        return suma;
    }
    //     метод display() кој што ќе испечати информации во формат:
    //         Име презиме -> индекс -> кредити

    void display() {
        cout<<name<<" "<<surname<<" -> "<<indeks<<" -> "<<total()<<endl;
    }

};
         int main(){
    char stName[100], stSurname[100], stIndex[100];
    cin >> stName;
             cin>> stSurname;
             cin>> stIndex;

    Subject subjects[5];
    for (int i = 0; i < 5; i++)
    {
        char sbName[100];
        int c;
        cin >> sbName >> c;
        subjects[i] = Subject(sbName, c);
    }

    Student student;
    student = Student(stName, stSurname, stIndex, subjects);

    student.display();

    return 0;
}