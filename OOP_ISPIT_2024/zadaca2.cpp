//
// Created by aleks on 6/15/2025.
//

#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

class InvalidCodeFormatException : public exception {
    string code;
public:
    InvalidCodeFormatException(const string& code = "") {
        this->code = code;
    }
        void print() {
            cout << "The code " << code
                 << " is invalid doctor code format. THE CODE MUST BE 8 CHARACTERS LONG AND CANNOT CONTAIN COMMA."
                 << endl;
        }

};

class Doctor {
protected:
    string name;
    string surname;
    float pay;
    string code;
public:
    virtual float calculateSalary() = 0;
    virtual void print() = 0;
    ~Doctor(){};
};

class GeneralDoctor : public Doctor {
    int patientnumber;
public:
    GeneralDoctor(string name = " ", string surname = " ", string code = " ", int patientnumber = 0) {
        this->name = name;
        this->surname = surname;
        this->patientnumber = patientnumber;
        if (code.length() != 8) {
            throw InvalidCodeFormatException(code);
        }
        for(int i = 0; i < 8; i++) {
            if (code[i] == ',') {
                throw InvalidCodeFormatException(code);
            }
        }
        this->code = code;
        this->pay = 45000;
    }
    float calculateSalary() override {
        float newpay = 45000;
        newpay += (patientnumber / 10) * 3000;
        return newpay *= 0.93;
    }

    void print() override {
        //General Doctor: John Smith CODE:236XY@2B Salary: 75330↩
        cout<<"General Doctor: "<<name<<" "<<surname<<" CODE:"<<code<<" Salary: "<<calculateSalary()<<endl;
    }
};

class Specialist : public Doctor {
    string specialty;
    int numberofinterventions;
    int yearsofexperience;
public:
    Specialist(string name = " ", string surname = " ", string code = " ",string specialty = " ", int numberofinterventions = 0, int yearsofexperience = 0) {
        if (code.length() != 8) {
            throw InvalidCodeFormatException(code);
        }
        for(int i = 0; i < 8; i++) {
            if (code[i] == ',') {
                throw InvalidCodeFormatException(code);
            }
        }
        this->code = code;
        this->name = name;
        this->surname = surname;
        this->numberofinterventions = numberofinterventions;
        this->yearsofexperience = yearsofexperience;
        this->specialty = specialty;
        this->pay = 55000;
    }

    float calculateSalary() override {
       float newpay = 55000;
        newpay += numberofinterventions * 85;
        newpay += yearsofexperience * (0.05 * 55000);
        return newpay *= 0.93;
    }

    void print() override {
        //Specialist: Beth Davis CODE:96Tr$$33 Cardiologist Salary: 67494.8↩
        cout<<"Specialist: "<<name<<" "<<surname<<" CODE:"<<code<<" "<<specialty<<" Salary: "<<calculateSalary()<<endl;
    }
};

void findDoctorsPercentage(Doctor **doctors, int n) {
    float percentgen = 0;
    float percentspec = 0;
    for(int i = 0; i < n; i++) {
        if(dynamic_cast<GeneralDoctor*>(doctors[i])) {
            percentgen++;
        }
        if(dynamic_cast<Specialist*>(doctors[i])) {
            percentspec++;
        }
    }
    percentgen/=n;
    percentgen*=100;
    percentspec/=n;
    percentspec*=100;

    cout<<percentspec<<"% of the doctors are specialists and "<<percentgen<<"% are general doctors."<<endl;
}

int main() {
    int testCase, n;
    string name, surname, specialty, code;
    int numberOfPatients, yearsOfExperience, numberOfInterventions;
    cin >> testCase;

    if (testCase == 1) {
        cout << "TESTING GENERAL DOCTOR CLASS" << endl;
        Doctor *d = new GeneralDoctor("John", "Smith", "236XY@2B", 120);
        Doctor *d1 = new GeneralDoctor("Marco", "Brown", "345X!Y2B", 120);
        Doctor *d2 = new GeneralDoctor("Emily", "Johnson", "ABCD123@", 230);
        d->print();
        d1->print();
        d2->print();

        cout << "GENERAL DOCTOR CLASS OK!" << endl;
    } else if (testCase == 2) {
        cout << "TESTING SPECIALIST DOCTOR CLASS" << endl;
        Doctor *d = new Specialist("Beth", "Davis", "96Tr$$33", "Cardiologist", 45, 5);
        Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
        Doctor *d2 = new Specialist("Micheal", "Rosen", "7896YZ$s", "Radiologist", 41, 10);
        d->print();
        d1->print();
        d2->print();
        cout << "SPECIALIST DOCTOR CLASS OK!" << endl;
    } else if (testCase == 3) {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new GeneralDoctor("John", "Smith", "23Y@2B", 120);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    } else if (testCase == 4) {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    } else if (testCase == 5) {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        try {
            Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
            d1->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        try {
            Doctor *d2 = new Specialist("Beth", "Davis", "96Tr,", "Cardiologist", 45, 5);
            d2->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }

        cout << "EXCEPTION HANDLING OK!" << endl;
    } else {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION!" << endl;
        cin >> n;
        Doctor **doctors = new Doctor *[n];
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            cin >> name >> surname;
            cin >> code;
            if (t == 1) // General doctor
            {
                cin >> numberOfPatients;
                try {
                    doctors[i] = new GeneralDoctor(name, surname, code, numberOfPatients);
                } catch (InvalidCodeFormatException &e) {
                    e.print();
                    i--;
                    n--;
                }
            } else // Specialist
            {
                cin >> specialty;
                cin >> numberOfInterventions >> yearsOfExperience;
                try {
                    doctors[i] = new Specialist(name, surname, code, specialty, numberOfInterventions,
                                                yearsOfExperience);
                } catch (InvalidCodeFormatException &e) {
                    e.print();
                    i--;
                    n--;
                }
            }
        }
        cout << "LIST OF ALL DOCTORS: " << endl;
        for (int i = 0; i < n; i++) {
                doctors[i]->print();
        }
        findDoctorsPercentage(doctors, n);
        for (int i = 0; i < n; i++) {
            delete doctors[i];
        }
        delete[] doctors;
    }
    return 0;
}