#include <iostream>
#include <cstring>


using namespace std;

enum tip {
    pop, rap, rok
};

class Pesna {
private:
    char name[50];
    int minuti;
    tip _type;

public:
    Pesna() {
        strcpy(name, "");
        minuti = 0;
        _type = pop;
    }
    Pesna(char *name, int minuti, tip _type) {
        strcpy(this->name, name);
        this->minuti = minuti;
        this->_type = _type;
    }

    void pecati() {
        cout<<'\"'<<name<<"\""<<"-"<<minuti<<"min"<<endl;
    }

    int getMin() {return minuti;};
    tip getTip() {return _type;};
};

class CD {
private:
    Pesna pesni[10];
    int brojpesni;
    int maxpesni;

public:
    CD(){};

    CD(int maxpesni) {
        brojpesni = 0;
        this->maxpesni = maxpesni;
    }

    int getminut() {
        int suma = 0;
        for(int i = 0; i < brojpesni; i++) {
            suma+=pesni[i].getMin();
        }

        return suma;
    }

    void dodadiPesna(Pesna p) {
        if(p.getMin() + getminut() > maxpesni) return;
        if (brojpesni >= 10) return;

        pesni[brojpesni] = p;
        brojpesni++;
    }

    void pecatiPesniPoTip(tip t) {
        for(int i = 0; i < brojpesni; i++) {
            if(pesni[i].getTip() == t) {
                pesni[i].pecati();
            }
        }
    }

    int getBroj() {
        return brojpesni;
    }

    Pesna getPesna(int i) {
        return pesni[i];
    }

};

int main() {
   // se testira zadacata modularno
   int testCase;
   cin >> testCase;


   int n, minuti, kojtip;
   char ime[50];


   if (testCase == 1) {
       cout << "===== Testiranje na klasata Pesna ======" << endl;
       cin >> ime;
       cin >> minuti;
       cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
       Pesna p(ime, minuti, (tip) kojtip);
       p.pecati();
   } else if (testCase == 2) {
       cout << "===== Testiranje na klasata CD ======" << endl;
       CD omileno(20);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> ime;
           cin >> minuti;
           cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
           Pesna p(ime, minuti, (tip) kojtip);
           omileno.dodadiPesna(p);
       }
       for (int i = 0; i < n; i++)
           (omileno.getPesna(i)).pecati();
   } else if (testCase == 3) {
       cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
       CD omileno(20);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> ime;
           cin >> minuti;
           cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
           Pesna p(ime, minuti, (tip) kojtip);
           omileno.dodadiPesna(p);
       }
       for (int i = 0; i < omileno.getBroj(); i++)
           (omileno.getPesna(i)).pecati();
   } else if (testCase == 4) {
       cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
       CD omileno(20);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> ime;
           cin >> minuti;
           cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
           Pesna p(ime, minuti, (tip) kojtip);
           omileno.dodadiPesna(p);
       }
       cin >> kojtip;
       omileno.pecatiPesniPoTip((tip) kojtip);


   } else if (testCase == 5) {
       cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
       CD omileno(20);
       cin >> n;
       for (int i = 0; i < n; i++) {
           cin >> ime;
           cin >> minuti;
           cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
           Pesna p(ime, minuti, (tip) kojtip);
           omileno.dodadiPesna(p);
       }
       cin >> kojtip;
       omileno.pecatiPesniPoTip((tip) kojtip);


   }


   return 0;
}
