#include<iostream>
using namespace std;

struct car {
    string name;
    string model;
    int year;
    int price;

};

void print (car &d) {
    cout<<d.name<<endl;
    cout<<d.model<<endl;
    cout<<d.year<<endl;
    cout<<d.price<<"$"<<endl;
    cout<<endl;
}
int main () {
    car Toyota {
    "Toyota", "Corolla", 2005, 1300
    };
    car Kia {
    "Kia", "Rio", 2004, 1700
    };

    car Renault {
    "Renault", "Clio", 1997, 700
    };


    print(Toyota);
    print (Kia);
    print(Renault);

}