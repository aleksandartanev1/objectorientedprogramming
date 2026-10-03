//
// Created by aleks on 3/26/2025.
//
#include<iostream>
#include<cstring>

using namespace std;

class Student {
private:
    char name[30];
    int index;
    float prosek;
    static int br_studenti;
    static float vkupno_prosek;

public:
    Student (char *name = "", int index = br_studenti, float prosek = 0) {
        strcpy(this->name, name);
        this->index  = index;
        this->prosek = prosek;
        br_studenti++;
        vkupno_prosek+=prosek;
    }

    void print() {
        cout<<name<<" "<<index<<" "<<prosek<<endl;

    }

    float prosecen_prosek () {
        return vkupno_prosek /  br_studenti;
    }
    static float zemi_vkprosek () {
        return vkupno_prosek;
    }
};

int Student::br_studenti = 2300000;
float Student::vkupno_prosek =  0;

int main () {
    Student s ("Ime", 8.5);
    s.print();
    Student k ("Ime2", 8);
    k.print();
    cout<<s.prosecen_prosek()<<endl;
    cout<<k.prosecen_prosek()<<endl;
}