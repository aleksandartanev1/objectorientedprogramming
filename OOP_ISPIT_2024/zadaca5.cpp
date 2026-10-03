//
// Created by aleks on 6/17/2025.
//
#include <iostream>

using namespace std;

//Your code here

class Library {
protected:
    string name;
    string city;
    double rate;
    bool weekend;
public:
    Library(string name = " ", string city = " ", double rate = 0, bool weekend = false) {
        this->name = name;
        this->city = city;
        this-> rate = rate;
        this->weekend = weekend;
    }

    virtual void printDetail() = 0;
    virtual double calculateMembershipCardCost() = 0;

    bool getWeekend() {
        return weekend;
    }
};

class AcademicLibrary : public Library {
    bool research;
    int journals;
public:
    AcademicLibrary(string name = " ", string city = " ", double rate = 0, bool weekend = false, bool research = false, int journals = 0) : Library(name, city, rate, weekend) {
        this->research = research;
        this->journals = journals;
    }

    double calculateMembershipCardCost() override {
        double membershipcard = rate;
        if(research) {
            membershipcard += rate * 0.24;
        }
        membershipcard += journals * 6;

        return membershipcard;
    }

    void printDetail() override {
        cout<<name<<" - (Academic) "<<city<<" "<<journals<<" "<<calculateMembershipCardCost()<<endl;
    }
};

class NationalLibrary : public Library {
    bool culture;
    int manuscripts;
public:
    NationalLibrary(string name = " ", string city = " ", double rate = 0, bool weekend = false, bool culture = false, int manuscripts = 0) : Library(name, city, rate, weekend) {
        this->culture = culture;
        this->manuscripts = manuscripts;
    }

    double calculateMembershipCardCost() override {
        double membershipcard = rate;
        if(culture) {
            membershipcard -= rate * 0.07;
        }

        membershipcard += manuscripts * 15;

        return membershipcard;
    }

    void printDetail() override {
        cout<<name<<" - (National) "<<city<<" "<<manuscripts<<" "<<calculateMembershipCardCost()<<endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int index = -1;
    int max = 0;
    for(int i = 0; i < n; i++) {
        if(dynamic_cast<NationalLibrary*>(l[i]) && l[i]->calculateMembershipCardCost() > max) {
            if(l[i]->calculateMembershipCardCost() == max) {
                if(l[i]->getWeekend() >= l[index]->getWeekend()) {
                    index = i;
                    max = l[i]->calculateMembershipCardCost();
                }
            }
            else {
                index = i;
                max = l[i]->calculateMembershipCardCost();
            }
        }
    }

    return index;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
