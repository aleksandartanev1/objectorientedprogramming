#include <iostream>
#include<cstring>
using namespace std;

class Employee {
    string name;
    int id;
    float pay;
    static int vkupnoVraboteni;
    static int vkupnaPlata;
public:
    Employee (string name = "", int id = 0, float pay = 0) {
        this->name = name;
        this->id = id;
        this->pay = pay;
        vkupnoVraboteni++;
        vkupnaPlata+=pay;
    }

    Employee (const Employee &other) {
        this->name = other.name;
        this->id = other.id;
        this->pay = other.pay;
    }

    ~Employee() {};

    void print () {
        cout<<"Ime: "<<name<<endl;
        cout<<"ID: "<<id<<endl;
        cout<<"Pay: "<<pay<<endl;
    }

  static  int getTotalEmployees () {
        return vkupnoVraboteni;
    }

  static  int getAverageSalary () {
        return vkupnaPlata;
    }
};

int Employee::vkupnaPlata = 0;
int Employee::vkupnoVraboteni = 0;




int main() {
    int n;
    cout << "Vnesi broj na vraboteni: ";
    cin >> n;

    Employee* employees = new Employee[n];

    for (int i = 0; i < n; i++) {
        string ime;
        int id;
        float plata;

        cout << "\nVnesi podatoci za vraboten " << i + 1 << endl;
        cout << "Ime: ";
        cin >> ime;
        cout << "ID: ";
        cin >> id;
        cout << "Plata: ";
        cin >> plata;

        employees[i] = Employee(ime, id, plata);
    }

    cout << "\n--- Lista na vraboteni ---\n";
    for (int i = 0; i < n; i++) {
        employees[i].print();
    }

    cout << "\nVkupno vraboteni: " << Employee::getTotalEmployees() << endl;
    cout << "Prosecna plata: " << Employee::getAverageSalary() << endl;

    delete[] employees;
    return 0;
}
