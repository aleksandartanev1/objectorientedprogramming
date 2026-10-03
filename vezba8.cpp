#include<iostream>
#include<cstring>
using namespace std;

class boy {
private:
    char name[100];
    int year;

public:
    boy(char *n = "Stefan", int y = 28) {
    strcpy(name,    n);
        year = y;

    }

    void print () {
        cout<<"Boy: "<<name<<" Age: "<<year<<endl;
    }
    int getAge() const {
        return year;
    }
};

class girl {
private:
    char name[100];
    int year;

public:
    girl(char *n = "Stefanija", int y = 28) {
        strcpy(name,    n);
        year = y;

    }

    void print () {
        cout<<"Girl: "<<name<<" Age: "<<year<<endl;
    }

     int getAge() const {
        return year;
    }
};

class date {
private:
    boy kanye;
    girl bianca;
public:
    date(boy a = boy(), girl b = girl()) {
    kanye = a;
        bianca = b;

    }
    void print() {
        cout<<"Date between:  "<<endl;
        kanye.print();
        cout<<" & ";
        bianca.print();
    }
    bool ismatch(boy a, girl b) {
        int diff = abs(a.getAge() - b.getAge());

        return diff > 5;
    }
};


int main () {

    boy decko;
   // decko.print();

    boy tipce("Petko");
  //  tipce.print();

    boy tipac("Trajko", 19);
  //  tipac.print();

    girl decka;
  //  decka.print();

    girl  tipka("Ana");
 //   tipka.print();

    girl tipaca("Tijana", 20);
   // tipaca.print();

    date date(tipce,tipaca);
    date.print();

    if (date.ismatch(tipce,tipaca)) {
        cout<<"Pedofilija"<<endl;
    } else cout<<"Legalno"<<endl;

    return 0;
}